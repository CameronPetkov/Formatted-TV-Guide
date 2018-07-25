/* FILE: comparison.c
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: Provide qsort() methods for comparing by time or by name.
            Acts as the logic that decides what is bigger/smaller.
 * REFERENCE: N/A
 * LAST MOD: 24/05/2018
 * COMMENTS: None
 */


#include "comparison.h"




/* NAME: compareByTime
 * PURPOSE: Provide comparison by time of TVEntry structure.
 * IMPORTS: [ const void* ] obj1: item1 to compare
 *          [ const void* ] obj2: item2 to compare
 * EXPORTS: [ int ] sortVal: The value of the comparison;
 *          -1 for i1 < i2, 1 for i1 > i2, and 0 for i1 == i2
 * ASSERTIONS
 *  PRE: obj1 and obj2 contain pointers to valid TVEntry structures.
 *  POST: sortVal will give the correct comparison value to qsort().
 * REMARKS: None */

int compareByTime( const void *obj1, const void *obj2 )
{
    int sortVal;
    /* typecast objects to TVEntry pointers */
    TVEntry *item1 = ( TVEntry* )obj1;
    TVEntry *item2 = ( TVEntry* )obj2;

    /* compare by day code by using getDay() on TVEntry's day field */
    int day1 = getDay( item1->day );
    int day2 = getDay( item2->day );

    if ( day1 < day2 ) /* e.g. day1 = Monday, day2 = Friday */
    {
        sortVal = -1;
    }
    else if ( day1 > day2 ) /* e.g. day1 = Tuesday, day2 = Monday */
    {
        sortVal = 1;
    }
    else if ( day1 == day2 ) /* compare by hour next */
    {
        if ( item1->time.hour < item2->time.hour )
        {
            sortVal = -1;
        }
        else if ( item1->time.hour > item2->time.hour )
        {
            sortVal = 1;
        }
        else /* finally compare by minute */
        {
            if ( item1->time.minute < item2->time.minute )
            {
                sortVal = -1;
            }
            else if ( item1->time.minute > item2->time.minute )
            {
                sortVal = 1;
            }
            else /* and if everything is equal, sortVal = 0 */
            {
                sortVal = 0;
            }
        }
    }

    return sortVal;
}




/* NAME: getDay
 * PURPOSE: Gives each day an "ID" to allow easy comparison between days.
 * IMPORTS: [ char* ] day: lowercase string from TVEntry's day field
 * EXPORTS: [ int ] dayCode: the ID for each day
 * ASSERTIONS
 *  PRE: N/A
 *  POST: dayCode will be between 1-7 inclusive, depending on the day in the
 *        string, or 0 if the day is invalid.
 * REMARKS: This is a general function that can be reused elsewhere to provide
 *          easy comparison of strings holding days. */

int getDay( char *day )
{
    /* Assigns each day an "ID", 0 being considered invalid */
    int dayCode = 0;

    /* strncmp each day, with max comparison size of DAY_SIZE */
    if ( strncmp( day, "monday", DAY_SIZE ) == 0 )
    {
        dayCode = 1;
    }
    else if ( strncmp( day, "tuesday", DAY_SIZE ) == 0 )
    {
        dayCode = 2;
    }
    else if ( strncmp( day, "wednesday", DAY_SIZE ) == 0 )
    {
        dayCode = 3;
    }
    else if ( strncmp( day, "thursday", DAY_SIZE ) == 0 )
    {
        dayCode = 4;
    }
    else if ( strncmp( day, "friday", DAY_SIZE ) == 0 )
    {
        dayCode = 5;
    }
    else if ( strncmp( day, "saturday", DAY_SIZE ) == 0 )
    {
        dayCode = 6;
    }
    else if ( strncmp( day, "sunday", DAY_SIZE ) == 0 )
    {
        dayCode = 7;
    }
    return dayCode;
}




/* NAME: compareByName
 * PURPOSE: Provide comparison by title of TVEntry structure.
 * IMPORTS: [ const void* ] obj1: item1 to compare
 *          [ const void* ] obj2: item2 to compare
 * EXPORTS: [ int ] sortVal: The value of the comparison;
 *          -1 for i1 < i2, 1 for i1 > i2, and 0 for i1 == i2
 * ASSERTIONS
 *  PRE: obj1 and obj2 contain pointers to valid TVEntry structures.
 *  POST: sortVal will give the correct comparison value to qsort().
 * REMARKS: If <strings.h> library is allowed to be used, this function can be
 *          reduced to dereferencing to str1 and str2, and then passing both 
 *          to strcasecmp( str1, str2 ), which will compare both strings,
 *          converting uppercase to lowercase for easy comparison. */

int compareByName( const void *obj1, const void *obj2 )
{
    int sortVal;
    /* typecast objects to TVEntry pointers */
    TVEntry *item1 = ( TVEntry* )obj1;
    TVEntry *item2 = ( TVEntry* )obj2;

    /* strings are found in the structure's title field */
    char *str1 = ( char* )( item1->title );
    char *str2 = ( char* )( item2->title );

    /* below function is the alternative way of comparing strings
     * irrespective of case. Uses non-standard <strings.h> library
     * so not included just in case its not allowed */
    /*  sortVal = strcasecmp( str1, str2 ); */


    char ch1, ch2;
    /* read each string character by character, and while the characters
     * are not NULL-terminators, AND the characters are equal,
     * keep looping through to new characters */
    while( ( *str1 != '\0' ) && ( *str2 != '\0' ) && 
         ( tolower( *str1 ) == tolower( *str2 ) ) ) 
    {
        /* increment pointer for both strings, so that it points
         * to the next character in the string */
        str1 += 1;
        str2 += 1;
    }

    /* Once the characters are no longer equal, convert to lowercase and then
     * compare these characters to work out sort values */
    ch1 = tolower( *str1 );
    ch2 = tolower( *str2 );

    if ( ch1 < ch2 )
    {
        sortVal = -1;
    }
    else if ( ch1 > ch2 )
    {
        sortVal = 1;
    }
    else
    {
        sortVal = 0;
    }

    return sortVal;
}
