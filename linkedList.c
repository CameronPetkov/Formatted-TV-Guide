/* FILE: linkedList.c
 * AUTHOR: Cameron Petkov
 * UNIT: Unix and C Programming
 * PURPOSE: Contains all functions that get implement the LL and LLNode
 *          structures.
 * REFERENCE: None
 * LAST MOD: 27/05/2018
 * COMMENTS: None
 */


#include "list.h"




/* NAME: createLinkedList
 * PURPOSE: Assign memory to a LinkedList structure and assign values to it.
 * IMPORTS: void
 * EXPORTS: [ LinkedList* ] list: the linked list structure created and
 *          allocated in this function.
 * ASSERTIONS
 *  PRE: N/A
 *  POST: A LL structure will be allocated and assigned default state.
 * REMARKS: None */

LinkedList* createLinkedList( void )
{
    /* if malloc fails, list will be NULL and is checked */
    LinkedList *list = ( LinkedList* ) malloc ( sizeof ( LinkedList ) );
    if ( list == NULL )
    {
        fprintf( stderr, "Error: Memory not assigned!\n" );
    }

    /* starting state of an empty LL is a NULL head, tail, and 0 length */
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}




/* NAME: isEmpty
 * PURPOSE: Check if the given list is empty or not.
 * IMPORTS: [ LinkedList* ] list: the list to check empty status
 * EXPORTS: [ int ] empty: the status of whether the list is empty or not
 *          FALSE is used for not empty, TRUE for empty
 * ASSERTIONS
 *  PRE: list is an allocated list
 *  POST: list is empty
 * REMARKS: If the error ever prints, any functions that use (or should use)
 *          the length should be analysed for mistakes, as this error
 *          indicates length has been miscalculated somewhere. */

int isEmpty( LinkedList *list )
{
    int empty;

    /* if the length is 0, the list is empty */
    if ( list->length == 0 )
    {
        empty = TRUE;
    }
    /* this is a back-up/failsafe to the length check, HOWEVER if this occurs
     * it indicates length has been incorrectly set/modified, and there is an
     * issue inside this code. This does not occur in testing, but future
     * modification/maintenance to this code may make this check relevant */
    else if ( list->head == NULL )
    {
        empty = TRUE;
        fprintf( stderr, "Length is incorrect. \n" );
    }
    /* otherwise the list is not empty */
    else
    {
        empty = FALSE;
    }
    return empty;
}




/* NAME: insertFirst
 * PURPOSE: Allow insertion at the front of the list.
 * IMPORTS: [ LinkedList* ] list: the list to add to
 *          [ void* ] value: the value to add to the list
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The value will be stored or an appropriate error will be displayed
 *        and returned to the caller function.
 * REMARKS: Duplicate values are NOT allowed in this list. If a duplicate item
 *          is to be inserted into the list, a copy of the original item
 *          should be made and passed to the list. Referring to the same
 *          pointer will result in an error. */

int insertFirst( LinkedList *list, void *value )
{
    int success = TRUE;

    /* if the list is empty, treat insertion like inserting before
     * any value (or no value, NULL) */
    if ( isEmpty( list ) )
    {
        /* if the called function throws an error, set the success 
         * of this function to FALSE, and print the error */
        if ( !insertBefore( list, NULL, value ) )
        {
            fprintf( stderr, "Error: Value not stored! \n" );
            success = FALSE;
        }
    }
    /* if the value to be inserted into the list is already found
     * in the list, set the success of this function to FALSE, and print
     * the error. This is to prohibit inserting duplicate pointers into the
     * list, requiring each pointer to uniquely identify itself in the list */
    else if ( find( list, value ) )
    {
        fprintf( stderr, "Error: Value already exists in list! \n " );
        success = FALSE;
    }
    /* otherwise treat this as if inserting before the list's 
     * first node's (head's) value */
    else
    {
        /* if this is not successful, print an error and set success = FALSE*/
        if ( !insertBefore( list, list->head->data, value ) )
        {
            fprintf( stderr, "Error: Value not stored! \n" );
            success = FALSE;
        }
    }
    return success;
}




/* NAME: insertLast
 * PURPOSE: Allow insertion at the back of the list.
 * IMPORTS: [ LinkedList* ] list: the list to add to
 *          [ void* ] value: the value to add to the list
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The value will be stored or an appropriate error will be displayed
 *        and returned to the caller function.
 * REMARKS: Duplicate values are NOT allowed in this list. If a duplicate item
 *          is to be inserted into the list, a copy of the original item
 *          should be made and passed to the list. Referring to the same
 *          pointer will result in an error. */

int insertLast( LinkedList *list, void *value )
{
    int success = TRUE;

    /* if the list is empty, treat insertion like inserting before
     * any value (or no value, NULL) */
    if ( isEmpty( list ) )
    {
        /* if the called function throws an error, set the success
         * of this function to FALSE, and print the error */
        if ( !insertBefore( list, NULL, value ) )
        {
            fprintf( stderr, "Error: Value not stored! \n" );
            success = FALSE;
        }
    }
    /* if the value to be inserted into the list is already found
     * in the list, set the success of this function to FALSE, and print
     * the error. This is to prohibit inserting duplicate pointers into the
     * list, requiring each pointer to uniquely identify itself in the list */
    else if ( find( list, value ) )
    {
        fprintf( stderr, "Error: Value already exists in list! \n " );
        success = FALSE;
    }
    /* otherwise treat this as if inserting after the list's
     * last node's (tail's) value */
    else
    {
        /* if this is not successful, print an error and set success = FALSE*/
        if ( !insertAfter( list, list->tail->data, value ) )
        {
            fprintf( stderr, "Error: Value not stored! \n" );
            success = FALSE;
        }
    }
    return success;
}




/* NAME: insertBefore
 * PURPOSE: Allow insertion before some value in the list.
 * IMPORTS: [ LinkedList* ] list: the list to add to
 *          [ void* ] valueToFind: the value to find in list
 *          [ void* ] value: the value to add to the list
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The value will be stored or an appropriate error will be displayed
 *        and returned to the caller function.
 * REMARKS: Duplicate values are NOT allowed in this list. If a duplicate item
 *          is to be inserted into the list, a copy of the original item
 *          should be made and passed to the list. Referring to the same
 *          pointer will result in an error. */

int insertBefore( LinkedList *list, void *valueToFind, void *value )
{
    int success = TRUE;
    LLNode *newNode;

    /* if the list is empty, the list needs to be setup specifically like so*/
    if ( isEmpty( list ) )
    {
        /* malloc the new node, and if it is NULL, malloc has failed */
        newNode = ( LLNode* ) malloc ( sizeof ( LLNode ) );
        if ( newNode == NULL )
        {
            fprintf( stderr, "Error: Memory not assigned!\n" );
            success = FALSE;
        }
        else
        {
            /* otherwise, set the new node to have the passed value, and no
             * next or previous nodes to link to yet */
            newNode->data = value;
            newNode->next = NULL;
            newNode->prev = NULL;

            /* set the list's head and tail to the only node,
             * and the length has to be 1 at this point */
            list->head = newNode;
            list->tail = newNode;
            list->length = 1;
        }
    }
    /* check for duplicate entry */
    else if ( find( list, value ) )
    {
        fprintf( stderr, "Error: Value already exists in list! \n " );
        success = FALSE;
    }
    else /* list is NOT empty */
    {
        /* make a current node to traverse forward through the list */
        LLNode *currNode = list->head;

        /* while there is another node after the current node,
         * AND the current node's value is not the value to find, keep
         * traversing forward through the list */
        while ( ( currNode->data != valueToFind ) &&
                    ( currNode->next != NULL ) )
        {
            currNode = currNode->next; /* set current node to the next node */
        }

        /* if the while loop finished without finding the value, print error*/
        if ( currNode->data != valueToFind )
        {
            fprintf( stderr, "Error: Element not found! \n" );
            success = FALSE;
        }
        else
        {
            /* malloc the new node, and if it is NULL, malloc has failed */
            newNode = ( LLNode* ) malloc ( sizeof ( LLNode ) );
            if ( newNode == NULL )
            {
                fprintf( stderr, "Error: Memory not assigned!\n" );
                success = FALSE;
            }
            else
            {
                newNode->data = value; /* node's data is the value desired */

                /* Essentially, the 2 below operations slot newnode between
                 * the matching node, and the previous node to that */

                /* because it is insertBefore(), the new node's next node is
                 * the current node that matched the value to find */
                newNode->next = currNode;

                /* new node's prev node is the current node's prev value*/
                newNode->prev = currNode->prev;

                /* the current "found" node has a new previous node, which is
                 * the new node that is inserted */
                currNode->prev = newNode;

                /* if the new node's previous (the current node's previous)
                 * exists, then the previous node's next field is the inserted
                 * newNode */
                if ( newNode->prev != NULL )
                {
                    currNode->prev->next = newNode;
                }
                else /* the "found" node is the first node */
                {
                    /* the new node becomes the first node (head) */
                    list->head = newNode;
                }
                list->length += 1; /* add 1 to the list length */
            }
        }
    }
    return success;
}




/* NAME: insertAfter
 * PURPOSE: Allow insertion after some value in the list.
 * IMPORTS: [ LinkedList* ] list: the list to add to
 *          [ void* ] valueToFind: the value to find in list
 *          [ void* ] value: the value to add to the list
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The value will be stored or an appropriate error will be displayed 
 *        and returned to the caller function.
 * REMARKS: Duplicate values are NOT allowed in this list. If a duplicate item
 *          is to be inserted into the list, a copy of the original item 
 *          should be made and passed to the list. Referring to the same
 *          pointer will result in an error. */

int insertAfter( LinkedList *list, void *valueToFind, void *value )
{
    int success = TRUE;

    /* if the list is empty, inserting after or before nothing is equivalent,
     * so insertBefore() can be called to increase code reuse */
    if ( isEmpty( list ) )
    {
        insertBefore( list, NULL, value ); /* treat same as insertBefore */
    }
    /* check for duplicate entry */
    else if ( find( list, value ) )
    {
        fprintf( stderr, "Error: Value already exists in list! \n " );
        success = FALSE;
    }
    else
    {
        LLNode *newNode;

        /* make a current node to traverse backwards through the list */
        LLNode *currNode = list->tail;

        /* while there is another node before the current node,
         * AND the current node's value is not the value to find, keep
         * traversing backwards through the list */
        while ( ( currNode->data != valueToFind ) && 
                    ( currNode->prev != NULL ) )
        {
            currNode = currNode->prev; /* set current node to the next node */
        }

        /* if the while loop finished without finding the value, print error*/
        if ( currNode->data != valueToFind )
        {
            fprintf( stderr, "Error: Could not insert, "
                       "element was not found! \n" );
            success = FALSE;
        }
        else
        {
            /* malloc the new node, and if it is NULL, malloc has failed */
            newNode = ( LLNode* ) malloc ( sizeof ( LLNode ) );
            if ( newNode == NULL )
            {
                fprintf( stderr, "Error: Memory not assigned!\n" );
                success = FALSE;
            }
            else
            {
                newNode->data = value;  /* node's data is the value desired */

                /* Essentially, the 2 below operations slot newnode between
                 * the matching node, and the next node to that */

                /* because it is insertAfter(), the new node's next node is
                 * the current "found" node's next */
                newNode->next = currNode->next;

                /* new node's previous node is the "found" node */
                newNode->prev = currNode;

                /* the node following the found node is the new node */
                currNode->next = newNode;

                /* if the new node's next (the current node's next)
                 * exists, then the next node's prev field is the inserted
                 * newNode */
                if ( newNode->next != NULL )
                {
                    newNode->next->prev = newNode;
                }
                else /* the "found" node is the last node */
                {
                    /* the new node becomes the last node (tail) */
                    list->tail = newNode;
                }
                list->length += 1; /* add 1 to the list length */
            }
        }
    }
    return success;
}




/* NAME: removeFirst
 * PURPOSE: Remove the first node in the list.
 * IMPORTS: [ LinkedList* ] list: the list to remove the first value of
 * EXPORTS: [ void* ] value: the value of the first node
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The first node will be removed and value returned; OR an error will
 *        be output, and the node will be NULL.
 * REMARKS: Uses removeValue function to search forward for value to delete.*/

void* removeFirst( LinkedList *list )
{
    void *value = NULL;

    if  ( isEmpty( list ) )
    {
        fprintf( stderr, "Error: Could not delete, list is empty! \n" );
        value = NULL;
    }
    else /* list not empty */
    {
        /* the value is the first node's value */
        value = list->head->data;

        /* removeValue will remove the specified value, from above.
           if the removeValue function is unsuccessful, print error */
        if ( !removeValue( list, value ) )
        {
            fprintf( stderr, "Error: Value not deleted! \n" );
            value = NULL;
        }
    }
    return value;
}




/* NAME: removeLast
 * PURPOSE: Remove the last node in the list.
 * IMPORTS: [ LinkedList* ] list: the list to remove the first value of
 * EXPORTS: [ void* ] value: the value of the first node
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The last node will be removed and value returned; OR an error will
 *        be output, and the node will be NULL.
 * REMARKS: Does not use removeValue() function like removeFirst() does, this
 *          is explained in the function commenting. */

void* removeLast( LinkedList *list )
{
    void *value = NULL;
    if ( isEmpty( list ) )
    {
        fprintf( stderr, "Error: Could not delete, list is empty! \n" );
        value = NULL;
    }
    else
    {
        /* the reason this function does not call removeValue() while
         * removeFirst() does, is because removeValue() traverses from the
         * front to the end, which is very efficient for removing the first
         * value, but VERY inefficient for removing the last value
         * O(1) vs O(n), so this function is done with reverse searching */

        /* make a temp node containg the last node */
        LLNode *temp = list->tail;
        /* and the value to return is given the tail's value */
        value = list->tail->data;

        /* the list's tail is now the previous node */
        list->tail = list->tail->prev;
        list->length -= 1; /* length decremented as a node is "deleted" */
        free( temp ); /* the node structure can be free'd */
        temp = NULL; /* and variable set to NULL as is good practice */
    }
    return value;
}




/* NAME: removeValue
 * PURPOSE: Remove a node with a specific value from the list.
 * IMPORTS: [ LinkedList* ] list: the list to remove the first value of
 *          [ void* ] value: the value to search for and then delete
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The list will have found the value in the list and delete the node,
 *        OR an error will be output and success code will be FALSE.
 * REMARKS: Helper function to removeFirst(), as well as being able to be used
 *          as a standalone function. */

int removeValue( LinkedList *list, void *value )
{
    int success = TRUE;
    if ( isEmpty( list ) )
    {
        fprintf( stderr, "Error: Could not delete, list is empty! \n" );
        success = FALSE;
    }
    else
    {
        /* make a current node to traverse forwards through the list */
        LLNode *currNode = list->head;
 
        /* while there is another node after the current node,
         * AND the current node's value is not the value to find, keep
         * traversing forward through the list */       
        while ( ( currNode->next != NULL ) && ( currNode->data != value ) )
        {
            currNode = currNode->next; /* node's data is the value desired */
        }

        /* if the while loop finished without finding the value, print error*/
        if ( currNode->data != value )
        {
            fprintf( stderr, "Error: Could not delete, "
                            "element was not found!\n " );
            success = FALSE;
        }
        else
        {
            /* make a temp node containg the "found" node */
            LLNode *temp = currNode;
            /* the value is the current node's value */
            value = currNode->data; 

            /* if the current node has a previous node, set that node's next
             * to be the current node's next (skipping current node) */
            if ( currNode-> prev != NULL )
            {
                currNode->prev->next = currNode->next;
            }
            else /* current node is first node */
            {
                /* set the head to the following node */
                list->head = currNode->next;
            }
            /* if the current node has a next node, set that node's previous
             * to be the current node's previous (skipping current node) */
            if ( currNode->next != NULL )
            {
                currNode->next->prev = currNode->prev;
            }
            else /* current node is last node */
            {
                /* set the tail to the preceding node */
                list->tail = currNode->prev;
            }

            list->length -= 1; /* decrement list length on node "delete" */
            free( temp ); /* the node structure can be free'd */
            temp = NULL; /* and variable set to NULL as is good practice */
        }
    }
    return success;
}




/* NAME: peekFirst
 * PURPOSE: Return the first node's value without removing the node itself.
 * IMPORTS: [ LinkedList* ] list: the list to peek from
 * EXPORTS: [ void* ] value: the first node's value
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: value will be the first node's value OR the value will be NULL and
 *        an error message will be output.
 * REMARKS: None */

void* peekFirst( LinkedList *list )
{
    void *value;
    if ( isEmpty( list ) )
    {
        fprintf( stderr, "Error: Could not return value, list is empty! \n" );
        value = NULL;
    }
    else
    {
        value = list->head->data; /* value is simply the head's data */
    }
    return value;
}




/* NAME: peekLast
 * PURPOSE: Return the last node's value without removing the node itself.
 * IMPORTS: [ LinkedList* ] list: the list to peek from
 * EXPORTS: [ void* ] value: the last node's value
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: value will be the last node's value OR the value will be NULL and
 *        an error message will be output.
 * REMARKS: None */

void* peekLast( LinkedList *list )
{
    void *value = NULL;
    if ( isEmpty( list ) )
    {
        fprintf( stderr, "Error: Could not return value, list is empty! \n" );
        value = NULL;
    }
    else
    {
        value = list->tail->data; /* value is simply the tail's data */
    }
    return value;
}




/* NAME: find
 * PURPOSE: Find if a value is found in any node (in the entire list).
 * IMPORTS: [ LinkedList* ] list: the list to search from
 *          [ void* ] value: the value to search for
 * EXPORTS: [ int ] found: if any node is found to contain the value
 *          FALSE is used for not found, TRUE for found
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: The appropriate node will be either found (TRUE) or not (FALSE).
 * REMARKS: None */

int find( LinkedList *list, void *value )
{
    int found = FALSE;
    if ( isEmpty( list ) ) /* if empty, nothing will be found */
    {
        found = FALSE;
    }
    else
    {
        /* make a current node to traverse forwards through the list */
        LLNode *currNode = list->head;

        /* while there is another node after the current node,
         * AND the current node's value is not the value to find, keep
         * traversing forward through the list */
        while ( ( currNode->next != NULL ) && ( currNode->data != value ) )
        {
            currNode = currNode->next; /* node's data is the value desired */
        }
        /* if the value was not found after the loop finishes, found = FALSE*/
        if ( currNode->data != value )
        {
            found = FALSE;
        }
        else
        {
            found = TRUE;
        }
    }
    return found;
}




/* NAME: getLength
 * PURPOSE: Get the length of the list.
 * IMPORTS: [ LinkedList* ] list: the list to get length of
 * EXPORTS: [ int ] list->length: the length of the list
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: length will be greater than or equal to 0.
 * REMARKS: This function is sort of redundant, and list-length could be done 
 *          directly in place of calling this function. However this function 
 *          could be extended in the future to give warnings for negative \
 *          length or some other feature. */

int getLength( LinkedList *list )
{
    /* this could be done directly anywhere, acts as an accessor */
    return list->length;
}




/* NAME: outputList
 * PURPOSE: Debugging function used in testing for integer list input.
 * IMPORTS: [ LinkedList* ] list: the list to output to screen
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list's data field holds a pointer to an integer.
 *  POST: list's data will be output from head to tail, in integer form.
 * REMARKS: Will only work for lists that have used insert functions to input
 *          ONLY int* data. Was used in unit testing. To output a list, a user
 *          should write their own output function, given they know what data
 *          is in the list, and what it should be typecasted to. */

int outputList( LinkedList *list )
{
    int success = TRUE;
    if ( isEmpty( list ) ) /* warn user that the list is empty */
    {
        fprintf( stderr, "Error: Cannot output list as it is empty!\n" );
        success = FALSE;
    }
    else
    {
        /* make a current node to traverse forwards through the list */
        LLNode *currNode = list->head;

        /* loop through until end of list is reached */
        while ( currNode->next != NULL )
        {
            /* this is assuming the data is a pointer to an int */
            printf( "%d\n", *(int*)currNode->data );
            currNode = currNode->next; /* get the next node */
        }

        /* while loop terminates on the last node as it's next field is NULL
         * so the last element must be printed here*/
        printf( "%d\n", *(int*)currNode->data );
    }
    return success;
}




/* NAME: clear
 * PURPOSE: To completely clear a list of all nodes and nodes' contents.
 * IMPORTS: [ LinkedList* ] list: list to clear
 * EXPORTS: [ int ] success: success or failure of the function
 *          FALSE (0) is used for failure, TRUE (!0) is used for success
 * ASSERTIONS
 *  PRE: list is valid (has valid structure, length, etc).
 *  POST: list is empty and appropriate free's have occured.
 * REMARKS: The calling function should free the list as well, if it finished
 *          with the list completely. */

int clear( LinkedList *list )
{
    int success = TRUE;

    /* while the list is not empty, keep looping */
    while ( !isEmpty( list ) )
    {
        /* remove the first node, and free it */
        void *item = removeFirst( list );
        free( item );
    }

    /* if the length is 0 (it should be), this will be false
     * if the length is anything but 0, something has not been free'd
     * correctly, or the list length has incorrectly been calculated */
    if ( getLength( list ) )
    {
        fprintf( stderr, "Error: Cannot empty out the list!\n" );
        success = FALSE;
    }
    return success;
}
