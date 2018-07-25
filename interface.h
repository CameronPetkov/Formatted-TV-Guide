/* FILE: interface.h
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: General header includes, definitions, and forward-declarations.
 * REFERENCE: N/A
 * LAST MOD: 24/05/2018
 * COMMENTS: None
 */


#ifndef INTERFACE_H
#define INTERFACE_H



#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "data.h"
#include "boolean.h"


/* +1 extra size for differentiating between "wednesday" and "wednesdayX" */
#define DAY_SIZE 11
#define SORT_SIZE 6


int inputStrings( char day[], char sortType[] );
int outputArray( TVEntry *array, int arraySize );
int decideFlush( char inputString[] );
int flushInput( void );
int makeLower( char str[] );



#endif
