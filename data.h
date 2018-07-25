/* FILE: data.h
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: Define a structure appropriate for storing TV guide entries.
 * REFERENCE: N/A
 * LAST MOD: 24/05/2018
 * COMMENTS: None
 */


#ifndef DATA_H
#define DATA_H



#define NAME_SIZE 100
#define DAY_SIZE 11 


/* NAME: TVEntry
 * PURPOSE: Allow a TV guide entry of a certain format to be parsed from a
 *          file into a suitable structure.
 * FIELDS:  [ char [] ] title: represents the name of the TV show
 *          [ char [] ] day: represents the day of the TV show
 *          [ time ] : a structure in itself containing hour and minute
 *          [ int ] hour : represents the hour of the TV show
 *          [ int ] minute : represents the minute of the TV show
 * REMARKS: Validation should occur external to the structure. It is the
 *          responsibility of the implementer to handle validity.
 *          The only validation the structure has is that title and day
 *          should be of max size, seen defined above. */

typedef struct {
    char title[NAME_SIZE];
    char day[DAY_SIZE];
    struct {
        int hour;
        int minute;
    } time;    
} TVEntry;



#endif
