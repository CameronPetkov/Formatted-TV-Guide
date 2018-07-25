/* FILE: tvguide.c
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming 
 * PURPOSE: Accept command line arguments and output a sorted, filtered array
 *          to screen and file as requested from the user.
 * REFERENCE: https://stackoverflow.com/a/26226613; M.M's answer
 * LAST MOD: 27/05/2018
 * COMMENTS: None
 */


#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "io.h"
#include "list.h"
#include "comparison.h"
/*#include "unittest.h"*/


static int processArgs( char *argv[] );
static int copyToArray( LinkedList *list, TVEntry *array );
static int filter( TVEntry *array, char *day, int arraySize );




/* NAME: main
 * PURPOSE: Take two command line (CL) arguments from the user and call a
 *          helper function to: read user input, read from file into a LL,
 *          copy to a dynamically allocated array, sort, filter, and output
 *          a filtered, sorted TV guide to screen and into a specified output
 *          file.
 * IMPORTS: [ int ] argc: amount of input CL arguments
 *          [ char* [] ] argv: CL arguments
 * EXPORTS: [ int ] status: success or failure of program
 *          0 is used for success, 1 is used for all errors.
 * ASSERTIONS
 *  PRE: N/A
 *  POST: A sorted, filtered TV guide will be output to screen and into the
 *        user specified file OR a relevant error message will be output.
 * REMARKS: Uses helper function processArgs() to ease readibility. */

int main( int argc, char *argv[] )
{
    /* status is the variable returned to the shell, the exit status
     * of the program. I set it to 0 for success, and 1 for error. */
    int status = 0;

    /* Require 3 arguments: the executable, input file, and output file */
    if ( argc != 3 )
    {
        fprintf( stderr, "Error: Enter 2 arguments, the name of input and "
    "output files.  \nExample: ./ProductionBuild input.txt output.txt \n" );
        status = 1;
    }
    else
    {
        /* status is equal to the negation of what processArgs() returns.
         * this is because processArgs returns 0 on failure, and 1 on success
         * and returning to the shell uses the reverse convention. */
        status = !processArgs( argv );
    }
    return status; /* returns to shell: 1 on error, 0 on success */
}




/* NAME: processArgs
 * PURPOSE: Helper function to main() to ease readability. 
 * IMPORTS: [ char* [] ] argv: CL arguments
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE:  N/A
 *  POST: A sorted, filtered TV guide will be output to screen and into the
 *        user specified file OR a relevant error message will be output.
 * REMARKS: Helper function. This function is quite long (going against
 *          normal C standards, because error checking and commenting is 
 *          quite exhaustive. Perhaps this could be reduced further than me
 *          just removing it from main(), but I am not sure how feasible
 *          this would be. */

int processArgs( char *argv[] )
{
    int success = TRUE;

    /* function to pass to qsort() */
    int ( *compare )( const void*, const void* );
    int arraySize;
    char day[DAY_SIZE], sortType[SORT_SIZE];
    TVEntry *array;

    /* list stores the linked list, and will be equal to NULL
     * if the function failed */
    LinkedList *list = createLinkedList( );

    /* test if the function failed */
    if ( list == NULL )
    {
        success = FALSE; /* fail status */
    }
    else
    {
        /* passes 2 precreated arrays to input user response into */
        inputStrings( day, sortType );

        /* readFile() returns a success code that is tested,
         * a value of 0 means failure, and 1 is success.
         * It is given argv[1] (input file) and the list to store into */
        if ( readFile( argv[1], list ) )
        {
            /* malloc() the amount of LL entries */
            arraySize = getLength( list );
            array = ( TVEntry* )malloc( arraySize * sizeof ( TVEntry ) );

            /* if the malloc failed, the array is NULL */
            if ( array == NULL )
            {
                fprintf( stderr, "Error: Memory not assigned!\n" );
                success = FALSE;
            }
            else
            {
                /* copy LL to a dynamically allocated array, as required*/
                copyToArray( list, array );

                /* the comparison function is dependent on what sortType
                 * was selected */
                if ( strncmp( sortType, "name", SORT_SIZE ) == 0 )
                {
                    compare = &compareByName;
                }
                else
                {
                    compare = &compareByTime;
                }

                qsort( ( void* )array, arraySize, 
                            sizeof ( TVEntry ), compare );

                /* arraySize is updated by filter(), as it shuffles
                 * elements forwards. This is done in place of
                 * reallocation (mentioned later in documentation) */
                arraySize = filter( array, day, arraySize );

                outputArray( array, arraySize );

                /* if writing returns an error (0), set approp. status */
                if ( !writeFile( argv[2], array, arraySize ) )
                {
                    success = FALSE;
                }

                free( array ); /* IO done, so array can be free'd */
            }
        }
        else /* i.e. file read was unsuccessful */
        {
            /* removes and frees list elements, then frees the list */
            clear( list );
            free( list );
            list = NULL;
            success = FALSE;
        }
        array = NULL; /* set the array to NULL after its unallocated */
    }

    return success;
}




/* NAME: copyToArray
 * PURPOSE: Take a list and copy it to a given array of type TVEntry*,
 *          removing and freeing the list as it does so.
 * IMPORTS: [ LinkedList* ] list: the linked list created in main()
 *          [ TVEntry* ] array: the array dynamically created in main()
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: List contains a valid linked list
 *  POST: Array contains all linked list values, and List is empty and freed
 * REMARKS: clear( list ) is redundant, but is acts as a backup if the length
 * count is ever off or something could not be removed. */

int copyToArray( LinkedList *list, TVEntry *array )
{
    int success = TRUE, ii = 0;

    /* loops through all list elements, unless failure occurs */
    while ( ( !isEmpty( list ) ) && ( success ) )
    {
        /* entry is the element at the top of the stack
         * which is copied to the array
         * and then freed (as it was not freed in removeFirst()) */
        TVEntry *entry = ( TVEntry* )removeFirst( list );
        if ( entry == NULL )
        {
            fprintf( stderr, "Error: Value could not be removed!\n" );
            success = FALSE;
        }
        else
        {
            array[ii] = *entry;
            free( entry );
            ii++;
        }
    }

    clear( list ); /* redundant, but helps if length count is ever off */
    free ( list ); /* free the list structure itself */
    list = NULL; /* and set the variable to NULL as is good practice */

    return success;
}




/* NAME: filter
 * PURPOSE: Take an array and filter the array so that only the day the user
 *          selected is present in the array.
 * IMPORTS: [ TVEntry* ] array: the array dynamically created in main()
 *          [ char* ] day: string with the user's choice of day for filtering
 *          [ int ] arraySize: the size of the array passed
 * EXPORTS: [ int ] jj: a counter for the amount of array indexes that match
 *                      the desired filter; effectively becomes the new array
 *                      size in main()
 * ASSERTIONS
 *  PRE: arraySize is the size of the array
 *       day contains a valid day of the week
 *       array is not empty 
 *  POST: jj will represent the new arraySize
 *        array will contain the filtered selection
 * REMARKS: I could have used realloc() instead, but there is no certainty 
 * that the function would free() the memory to the OS (but rather for future
 * malloc uses (which are not present in this program), and thus the realloc 
 * has no real benefit as the array is free'd shortly after this function.
 * See: https://stackoverflow.com/a/26226613, 2014; M.M's answer */

int filter( TVEntry *array, char *day, int arraySize )
{
    int jj = 0;
    int ii;

    /* go through the entire array */
    for( ii = 0; ii < arraySize; ii++ )
    {
        /* and if the array's day field is the same as the day option
         * selected by the user previously, save it to the array */
        if ( strncmp( array[ii].day, day, DAY_SIZE ) == 0 )
        {
            /* array[jj] will overwrite existing previous values
             * by effectively copying the matching day's structure
             * to the start of the array */
            array[jj] = array[ii];
            jj++; /* increment for following matches to be stored sequential*/
        }
    }

    

    return jj;
}
