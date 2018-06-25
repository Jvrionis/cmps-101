/**********************************************************************
* James Michael Vrionis
* JVrionis
* 1-24-17
* Programming Assingment 2
* List.h : A List header file that contains prototypes for 
* List.c.  
**********************************************************************/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

/* List
 * Exported reference type
 */
typedef struct ListObj* List;


/* newList()
 * constructor for the List type
 */
List newList(void);

/* freeList()
 * Destructor for the List type
 */
void freeList(List* pL);

/* length():
 * Returns the number of elements in this List
 */
int length(List L);

/* index():
 * If cursor is defined, returns the index of the cursor
 * element, otherwise returns -1   
 */
int index(List L);

/* front():
 * Returns front element
 * Pre: length() > 0
 */
int front(List L);


/* back():
 * Returns back element
 * Pre: length() > 0
 */
int back(List L);

/* get():
 * Returns cursor element
 * Pre: length() > 0
 */
int get(List L);

/* equals():
 * Returns true if this List and L are the same integer
 * sequence. The cursor is ignored in both lists
 */
int equals(List A, List B);

/* clear():
 * Resets this List to its original empty state
 */
void clear(List L);


/* moveFront():
 * If List is non-empty, places the cursor under the front
 * element, otherwise does nothing
 */ 
void moveFront(List L);

/* moveBack():
 * If List is non-empty, places the cursor under the back
 * element, otherwise does nothing
 */ 
void moveBack(List L);

/* movePrev():
 * If cursor is defined and not at front, moves cursor one step
 * toward front of this List, if cursor is defined and at front,
 * cursor becomes undefined, if cursor is undefined does nothing
 */
void movePrev(List L);

/* moveNext():
 * If cursor is defined and not at back, moves cursor one step
 * toward back of this List, if cursor is defined and at back,
 * cursor becomes undefined, if cursor is undefined does nothing
 */
void moveNext(List L);

/* prepend():
 * Insert new element into this List. If List is non-empty,
 * insertion takes place before the front element
 */
void prepend(List L, int data);

/* append():
 * Insert new element into this List. If List is non-empty,
 * insertion takes place after back element
 */
void append(List L, int data);

/* insertBefore():
 * Insert new element before cursor
 * Pre: length() > 0, index() >= 0
 */
void insertBefore(List L, int data);

/* insertAfter():
 * Inserts new element after cursor
 * Pre: length() > 0, index() >= 0
 */
void insertAfter(List L, int data);

/* deleteFront():
 * Deletes the front element
 * Pre: length() > 0
 */
void deleteFront(List L);

/* deleteBack():
 * Deletes the back element
 * Pre: length() > 0
 */
void deleteBack(List L);

/* delete():
 * Deletes cursor element, making cursor undefined
 * Pre: length() > 0, index() >= 0
 */
void delete(List L);

/* printList():
 * separated sequence of integers, with front on left
 */
void printList(FILE* out, List L);

/* copyList()
 * Returns a new List representing the same integer sequence as this
 * List. The cursor in the new list is undefined, regardless of the
 * state of the cursor in this List. This List is unchanged
 */
List copyList(List L);


#endif
