/* FILE: comparison.h
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: General header includes and forward-declarations.
 * REFERENCE: N/A
 * LAST MOD: 24/05/2018
 * COMMENTS: <strings.h> commented out, but could be uncommented if allowed
 *           to use that library for its strcasecmp() function.
 */


#ifndef COMPARISON_H
#define COMPARISON_H



#include <string.h>
#include <stdio.h>
#include <ctype.h>
/*#include <strings.h>*/

#include "data.h"


int compareByTime( const void *obj1, const void *obj2 );
int getDay( char *day );
int compareByName( const void *obj1, const void *obj2 );



#endif
