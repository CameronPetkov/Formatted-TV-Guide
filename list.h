/* FILE: list.h
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: General header includes, typedefs, definitions, 
 *          and forward-declarations.
 * REFERENCE:
 * LAST MOD: 24/05/2018
 * COMMENTS: 
 */


#ifndef LIST_H
#define LIST_H



#include <stdlib.h>
#include <stdio.h>

#include "boolean.h"


/* NAME: LLNode
 * PURPOSE: Act as a node that holds the data desired, and two pointers to
 *          traverse to a previous or the next item. Essentially acts as half
 *          a linked list, which can be implemented with the LinkedList
 *          structure, and appropriate methods found in linkedList.c
 * FIELDS:  [ void* ] data: holds a pointer to a void type, allowing the data
 *          to be anything i.e. generic.
 *          [ LLNode* ] next: holds a pointer to another node (like itself)
 *          which is designated as being the next node.
 *          [ LLNode* ] prev: holds a pointer to another node (like itself)
 *          which is designated as being the previous node. This field allows
 *          reverse traversal and makes the LL "doubly linked".
 * REMARKS: LLNode requires the LinkedList structure and methods to manipulate
 *          the structure as required. */

typedef struct LLNode
{

    void *data;
    struct LLNode *next;
    struct LLNode *prev;
} LLNode;


/* NAME: LinkedList
 * PURPOSE: Acts as the other half of the linked list. This structure holds
 *          the address of the first and last nodes, as well as the length
 *          of the amount of nodes stored.
 * FIELDS:  [ LLNode* ] head: holds a pointer to the first node, allowing the
 *          list to be traversed just by having the LinkedList's head.
 *          [ LLNode* ] tail: holds a pointer to the last node. In addition
 *          to letting a user get the last node, combined with a doubly LL,
 *          traversal can occur from the back. Having a tail means the LL
 *          is a double ended LL.
 *          [ int ] length: An optional field that allows updating of the
 *          amount of nodes in the LL, useful for checking if the list is
 *          empty.
 * REMARKS: LinkedList requires the LLNode structure and methods to manipulate
 *          the structure as required. */

typedef struct
{
    LLNode *head;
    LLNode *tail;
    int length;
} LinkedList;


LinkedList* createLinkedList( void );
int isEmpty( LinkedList *list );
int insertFirst( LinkedList *list, void *value );
int insertLast( LinkedList *list, void *value );
int insertBefore( LinkedList *list, void *valueToFind, void *value );
int insertAfter( LinkedList *list, void *valueToFind, void *value );
void* removeFirst( LinkedList *list );
void* removeLast( LinkedList *list );
int removeValue( LinkedList *list, void *value );
void* peekFirst( LinkedList *list );
void* peekLast( LinkedList *list );
int find( LinkedList *list, void *value );
int getLength( LinkedList *list );
int outputList( LinkedList *list );
int clear( LinkedList *list );



#endif
