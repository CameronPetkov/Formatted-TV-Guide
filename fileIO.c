/* FILE: fileIO.c
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: Handle any reading or writing of files.
 * REFERENCE: N/A
 * LAST MOD: 24/05/2018
 * COMMENTS: None
 */


#include "io.h"


/* private to other files as its specific to this file's methods */
static int processFile( FILE *f, LinkedList *list );




/* NAME: readFile
 * PURPOSE: Open a file for reading, and call a helper function to parse
 *          the contents into a data structure.
 * IMPORTS: [ char [] ] filename: file to read from
 *          [ LinkedList* ] list: a LL data structure to store into
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: filename is to be read from, and has appropriate structure.
 *  POST: The file will be read completely OR an appropriate error is output.
 * REMARKS: Function is very specific to this task and is likely unsuitable
 *          for major reuse outside of this program. */

int readFile( char filename[], LinkedList* list )
{
    int success = TRUE;
    FILE *f = fopen( filename, "r" );
    /* file is NULL when it errors out */
    if ( f == NULL )
    {
        perror( "Error reading file" );
        success = FALSE; /* set status to fail (success=false) */
    }
    else
    {
        /* process the file, passing it the file* and list*/
        success = processFile( f, list );

        /* if there is an error, print and flag failure */
        if ( ferror( f ) )
        {
            perror( "Error while reading from file" );
            success = FALSE;
        }

        fclose( f );
    }
    
    return success;
}




/* NAME: writeFile
 * PURPOSE: Go through an array, writing in a specific format to a designed
 *          file.
 * IMPORTS: [ char [] ] filename: file to read to
 *          [ TVEntry* ] array: array of TVEntry structure to output
 *          [ int ] arraySize : the size of array
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: filename is to be written to. arraySize is the size of the array.
 *  POST: The array will be fully written to file in set format, or an error
 *        will be output to indicate failure.
 * REMARKS: Function is very specific to this task and is likely unsuitable
 *          for major reuse outside of this program. */

int writeFile( char filename[], TVEntry *array, int arraySize )
{
    int success = TRUE;
    FILE *f = fopen( filename, "w" );
    /* file is NULL when it errors out */
    if ( f == NULL )
    {
        perror( "Error writing file" );
        success = FALSE;
    }
    else
    {
        int ii;

        /*fprintf( f, "**************************************\n" );
        fprintf( f, "* %19s                *\n", array->day );
        fprintf( f, "**************************************\n" );*/

        /* print out array in specified format */
        for (ii = 0; ii < arraySize; ii++ )
        {
            fprintf( f, "%2d:%02d - %s", array[ii].time.hour,
            array[ii].time.minute, array[ii].title );
        }

        /* if there is an error, print and flag failure */
        if ( ferror( f ) )
        {
            perror( "Error while writing from file" );
            success = FALSE;
        }

        fclose( f );
    }
    return success;
}




/* NAME: processFile
 * PURPOSE: Parse the file's contents into a linked list, ensuring that all
 *          data makes logical sense (such as hour being between 0-23).
 * IMPORTS: [ FILE* ] f: Pointer to FILE from caller function
 *          [ LinkedList* ] list: a LL data structure to store into
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: N/A
 *  POST: File contents have been parsed into LL or an appropriate error has
 *  been output.
 * REMARKS: Helper function to readFile(). */

int processFile( FILE *f, LinkedList *list )
{
    int success = TRUE;
    char name[NAME_SIZE];
    char line[NAME_SIZE];
    char day[DAY_SIZE];
    int hour, minute;

    /* while not EOF (fgets would be NULL on EOF)
     * AND while there is no error ( success == TRUE ) */
    while ( ( fgets( name, LINE_SIZE, f ) != NULL ) && ( success ) )
    {
        /* if the 1st character was a newline, the line is empty,
         * so therefore output error and set success flag to FALSE */
        if ( name[0] == '\n' )
        {
            fprintf( stderr, "Error: File has empty title field!\n");
            success = FALSE;
        }
        else
        {
            /* if the following line is not EOF */
            if ( fgets( line, LINE_SIZE, f ) == NULL )
            {
                perror( "Error while reading from file" );
                success = FALSE;
            }
            else
            {
                int scans = 0;
                /* malloc the data to put in the LL, so it exists outside
                 * of this method */
                TVEntry *entry = (TVEntry*) malloc( sizeof ( TVEntry ) );
                /* if the malloc fails, entry will be NULL */
                if ( entry == NULL )
                {
                    fprintf( stderr, "Error: Memory not assigned!\n" );
                    success = FALSE;
                }
                else
                {
                    hour = 0;
                    minute = 0;
                    /* process the fgets line for specific format */
                    scans = sscanf( line, "%s %d:%d", day, &hour, &minute );
                    /* convert day to lowercase for later comparison */
                    makeLower( day );

                    /* Require scans for day, hour, and minute */
                    if ( scans != 3 )
                    {
                        fprintf( stderr, "Error: Could not scan in "
                                     "file parameters!\n" );
                        free( entry );
                        success = FALSE;
                    }
                    /* getDay() will get a number representing the day of the
                     * week, 1-7 or 0 if unsuccessful. Check if unsuccessful*/
                    else if ( getDay( day ) == 0 )
                    {
                        fprintf( stderr, "Error: Incorrect day "
                            "in file!\n" );
                        free( entry );
                        success = FALSE;
                    }
                    /* otherwise check hour and minute being correct values */
                    else if ( ( hour < 0 ) || ( hour > 23 ) ||
                                ( minute < 0 ) || ( minute > 59 ) )
                    {
                        fprintf( stderr, "Error: Incorrect time "
                                "in file!\n" );
                        free( entry );
                        success = FALSE;
                    }
                    /* Only now can further processing be done */
                    else
                    {
                        /* strncpy as string can't be defined after
                         * being initialised in main() */ 
                        strncpy( entry->title, name, NAME_SIZE );
                        strncpy( entry->day, day, DAY_SIZE );
                        /* set entry's other structure fields */
                        entry->time.hour = hour;
                        entry->time.minute = minute;

                        /* and insert this finished entry at the end of LL */
                        insertLast( list, entry );
                    }
                }
            }
        }
    }
    return success;
}
