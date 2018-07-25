/* FILE: interface.c
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: Contains all functions that get input from the user 
 *          (inputStrings), give output to user (outputArray), and any helper
 *          functions (isValidDay, isValidSort).
 * REFERENCE: https://stackoverflow.com/a/39421460, 2016, SO user "Kaz"
 * LAST MOD: 24/05/2018
 * COMMENTS: isValidDay/isValidSort functions are static because they are
 *           specific to the output from fgets() which attaches a '\n' char.
 */


#include "interface.h"


/* static as these functions only check valid day/sort from fget lines
 * because they have the newline attached */
static int isValidDay( char day[DAY_SIZE] );
static int isValidSort( char sortType[SORT_SIZE] );




/* NAME: inputStrings
 * PURPOSE: Reads in a valid day of the week and valid sort type, reprompting 
 *          the user if the input is invalid.
 * IMPORTS: [ char [] ] day: string to store a valid day into
 *          [ char [] ] sortType: string to store a valid sort type into
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: day and sortType are of correct size and are empty
 *  POST: day and sortType contain valid options
 * REMARKS: decideFlush() is called, which checks if there is any buffer in
 *          stdin or not and deals with it accordingly. */

int inputStrings( char day[DAY_SIZE], char sortType[SORT_SIZE] )
{
    int success = TRUE;
    char *scanSuc = NULL;

    printf( "Enter a day of the week: \n" );
    scanSuc = fgets( day, DAY_SIZE, stdin ); /* equals NULL when it fails */
    makeLower( day ); /* call user-defined function that makes str lowercase*/

    /* while the user's input doesn't match a day of the week or the scan
     * fails, reprompt for user input */
    while ( ( isValidDay( day ) == FALSE ) || ( scanSuc == NULL ) )
    {
        /* if the previous input was long, it will be buffered in stdin
         * so it must be cleared/flushed. This is decided by decideFlush() */
        decideFlush( day );
        fprintf( stderr, "Error: Enter a valid day of the week. \n" );
        scanSuc = fgets( day, DAY_SIZE, stdin );
        makeLower( day );
    }

    decideFlush( day ); /* decide if stdin needs to be flushed */
    scanSuc = NULL;

    printf( "Sort by \"time\" or \"name\"? \n" );
    scanSuc = fgets( sortType, SORT_SIZE, stdin );
    makeLower( sortType );

    /* while the user's input does not match a sort type or the scan fails,
     * reprompt for user input */
    while ( ( isValidSort( sortType ) == FALSE ) || (scanSuc == NULL ) )
    {
        decideFlush( sortType );
        fprintf( stderr, "Error: Enter either time or name for sort type."
            "\n" );
        scanSuc = fgets( sortType, SORT_SIZE, stdin );
        makeLower( sortType );
    }

    decideFlush( sortType ); /* conditionally flush anything in stdin again */
    scanSuc = NULL;

    return success;
}




/* NAME: outputArray
 * PURPOSE: Go through an array and print it to the screen, OR if the array is
 *          empty, print that fact to screen.
 * IMPORTS: [ TVEntry* ] array: a usually sorted/filtered array containing
 *                              a pointer to a TVEntry structure
 *          [ int ] arraySize: the array size of array
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: arraySize is equal to the amount of filtered entries.
 *  POST: The array has been printed to screen OR an error is output alerting
 *        of the empty array.
 * REMARKS: A header/title for the day can be enabled by uncommenting the
 *          relevant section. */

int outputArray( TVEntry *array, int arraySize )
{
    int success = TRUE, ii;

    printf("\n\n");

    /* Uncomment to print out a day header to the screen */
    /*printf( "**************************************\n" );
    printf( "* %19s                *\n", array->day );
    printf( "**************************************\n" );*/

    /* if the given (filtered) array is empty, output this fact */
    if ( arraySize == 0 )
    {
        fprintf( stderr, "No TV shows found on selected day.\n");
        success = FALSE;
    }
    else
    {
        /* otherwise loop through array and print in the specified format */
        for (ii = 0; ii < arraySize; ii++ )
        {
            printf("%2d:%02d - %s",array[ii].time.hour, 
                        array[ii].time.minute, array[ii].title );
        }
    }
    
    return success;
}




/* NAME: isValidDay
 * PURPOSE: Check if the string input into day is correct.
 * IMPORTS: [ char [] ] day: the day input by the user
 * EXPORTS: [ int ] valid: validity of the user's input
 *          FALSE is used for invalid, TRUE for valid
 * ASSERTIONS
 *  PRE: day holds a string retrieved from fgets() on stdin.
 *  POST: validity is either TRUE or FALSE depending on day.
 * REMARKS: Will not work on general string input, because of the newline
 *          character being part of the comparison. */

int isValidDay( char day[DAY_SIZE] )
{
    int valid = FALSE;

    /* compare user input with the days of the week and set validity as below
     * the \n is because fgets() also retrives the newline character */
    if ( strncmp( day, "monday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( day, "tuesday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( day, "wednesday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( day, "thursday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( day, "friday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( day, "saturday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( day, "sunday\n", DAY_SIZE ) == 0 )
    {
        valid = TRUE;
    }

    return valid;
}




/* NAME: isValidSort
 * PURPOSE: Check if the string input into sortType is correct.
 * IMPORTS: [ char [] ] sortType: the type of sort input by the user
 * EXPORTS: [ int ] valid: validity of the user's input
 *          FALSE is used for invalid, TRUE for valid
 * ASSERTIONS
 *  PRE: sortType holds a string retrieved from fgets() on stdin.
 *  POST: validity is either TRUE or FALSE depending on sortType.
 * REMARKS: Will not work on general string input, because of the newline
 *          character being part of the comparison. */

int isValidSort( char sortType[SORT_SIZE] )
{
    int valid = FALSE;

    /* compare user input with the sort types offered, set validity as below
     * the \n is because fgets() also retrives the newline character */
    if ( strncmp( sortType, "time\n", SORT_SIZE ) == 0 )
    {
        valid = TRUE;
    }
    else if ( strncmp( sortType, "name\n", SORT_SIZE ) == 0 )
    {
        valid = TRUE;
    }

    return valid;
}




/* NAME: decideFlush
 * PURPOSE: Decide if stdin needs to be flushed or not.
 * IMPORTS: [ char [] ] inputString: any string read in from stdin by fgets
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: inputString is a string retrieved from fget() on stdin.
 *  POST: stdin will be flushed if there was extra characters left in the
 *        buffer, or the newline is replaced by a null-terminator to stop
 *        skipping a line of stdin.
 * REMARKS: Works on any fgets() input needing to be flushed on large input.*/

int decideFlush( char inputString[] )
{
    int success = TRUE;

    /* Below algorithm loosely based on Stack Overflow user Kaz:
     * See: https://stackoverflow.com/a/39421460 (2016) */

    int len = strlen( inputString ); /* length of stdin */
    /* if the last character is a newline, make it a NULL terminator instead
     * this means stdin had equal or less characters, and there is no need
     * to flush the input */
    if ( inputString[len - 1] == '\n' )
    {
        inputString[len - 1] = '\0';
    }
    else
    {
        /* otherwise flush stdin, disregarding all characters */
        flushInput();
    }
    return success;
}




/* NAME: flushInput
 * PURPOSE: Flush any character is the stdin buffer.
 * IMPORTS: void
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: There is something in stdin buffer to remove.
 *  POST: There is nothing in the stdin buffer.
 * REMARKS: This is a general function that can be used to flush stdin
 *          regardless of implementation details.
 *          Used as helper function to decideFlush(). */

int flushInput( void )
{
    int success = TRUE;

    /* Below algorithm part of the algorithm included in decideFlush()
     * Adapted to use fgetc() instead of getchar()
     * Loosely based on Stack Overflow user Kaz
     * See: https://stackoverflow.com/a/39421460 (2016) */

    int ch = 0;
    do
    {
        ch = fgetc( stdin );
        /* do nothing and go to next char (i.e. discard each char) */
    }
    while ( ( ch != '\n' ) && ( ch != EOF ) ); /* stop on newline or EOF */
    return success;
}




/* NAME: makeLower
 * PURPOSE: Make any uppercase chars in str be their lowercase equivalent.
 * IMPORTS: [ char [] ] str: a string to make lowercase
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: str is a null-terminated string.
 *  POST: str will not contain any uppercase characters.
 * REMARKS: This is a general function that can be used to make any string
 *          lowercase, regardless of implementation details. The string
 *          should be null-terminated, however. */

int makeLower( char str[] )
{
    int success = TRUE, ii = 0;
    /* while the string has not ended */
    while ( str[ii] != '\0' )
    {
        /* make the char at ii be lowercase */
        str[ii] = tolower( str[ii] );
        ii++;
    }
    return success;
}
