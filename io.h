/* FILE: io.h
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: General header includes, definitions, and forward-declarations.
 * REFERENCE: N/A
 * LAST MOD: 24/05/2018
 * COMMENTS: None
 */


#ifndef IO_H
#define IO_H



#include <string.h>
#include <stdio.h>

#include "data.h"
#include "list.h"
#include "interface.h"
#include "comparison.h"


#define LINE_SIZE 255
#define NAME_SIZE 100
#define DAY_SIZE 11


int readFile( char filename[], LinkedList *list );
int writeFile( char filename[], TVEntry *array, int arraySize );



#endif
