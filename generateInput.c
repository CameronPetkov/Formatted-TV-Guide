/* FILE: generateInput.c
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: Generate test input for the TV guide formatting program.
 * REFERENCE: N/A
 * LAST MOD: 26/05/2018
 * COMMENTS: Data pool from randomlists.com's TV and movie show generator.
 */


#include "generateInput.h"




/* NAME: main
 * PURPOSE: Accept command line arguments and write a file of TV show entries.
 * IMPORTS: [ int ] argc: number of input CL arguments
 *          [ char* [] ] argv: CL argument strings
 * EXPORTS: [ int ] status: success or failure of program
 *          0 is used for success, 1 is used for all errors.
 * ASSERTIONS
 *  PRE: argv[1] should be a valid number (for number of entries).
 *  POST: A file with correctly formatted TV guide entries should been output
 *        to the file specified in argv[2].
 * REMARKS: None */

int main( int argc, char *argv[] )
{
    int status = 0;
    if ( argc != 3 )
    {
        fprintf( stderr, "Error: Enter how many TV shows should be generated,"
                            " and a filename where to store it\n" );
        status = 1;
    }
    else
    {
        FILE *f;
        extern char *entryPool[ARRAY_LENGTH]; /* array hardcoded in header */

        srand( ( unsigned )time( NULL ) ); /* seed for rand function */

        f = fopen( argv[2], "w" );
        if ( f == NULL )
        {
            perror( "Error writing file" );
            status = 1;
        }
        else
        {
            writeInputFile( entryPool, f, argv[1] );
        }
    }

    return status;
}




/* NAME: dayFind
 * PURPOSE: Give an integer a corresponding day and return that day.
 * IMPORTS: [ int ] dayID: the ID to convert into a day
 * EXPORTS: [ char* ] day: a day of the week corresponding to that ID
 * ASSERTIONS
 *  PRE: dayID is between 0 and 6 inclusively.
 *  POST: day is correctly assigned the corresponding value.
 * REMARKS: None */

char* dayFind( int dayID )
{
    char *day;
    if ( dayID == 0 )
    {
        day = "Monday";
    }
    else if ( dayID == 1 )
    {
        day = "Tuesday";
    }
    else if ( dayID == 2 )
    {
        day = "Wednesday";
    }
    else if ( dayID == 3 )
    {
        day = "Thursday";
    }
    else if ( dayID == 4 )
    {
        day = "Friday";
    }
    else if ( dayID == 5 )
    {
        day = "Saturday";
    }
    else
    {
        day = "Sunday";
    }

    return day;
}




/* NAME: writeInputFile
 * PURPOSE: Generate random input that is written to the user specified file.
 * IMPORTS: [ char* [] ] entryPool: the array of entry titles used for entry
 *          [ FILE* ] f: the file created in main()
 *          [ char* ] argv: the required amount of entries to generate
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: argv is an integer with the amount of entries to generate. 
 *  POST: A file will be generated with random input data in correct format.
 * REMARKS: None */

int writeInputFile( char *entryPool[], FILE *f, char *argv )
{
    int ii, success = TRUE;
    int inputEntries = atoi( argv ); /* convert string to num */
    /* loop for the amount of entries the user entered */
    for ( ii = 0; ii < inputEntries; ii++ )
    {
        int dayID, hour, minute, index;
        char *day;
        dayID = rand( ) % 7; /* random a number between 0-6 */
        day = dayFind( dayID ); /* allocate prev number to a day of week */

        hour = rand( ) % 24; /* random hour between 0-23 */
        minute = rand( ) % 60; /* random minue between 0-59 */

        index = rand( ) % ARRAY_LENGTH; /* get index of array at random */
        fprintf( f, "%s\n", entryPool[index] ); /*title is this random index*/
        fprintf( f, "%s %d:%02d\n", day, hour, minute); /*in format required*/
    }
    return success;
}
