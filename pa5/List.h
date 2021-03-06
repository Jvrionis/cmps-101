/************************************************************** 
 * Programming Assingment 5
 *
 * List.h: Header file for List ADT.
 *
 *************************************************************/

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

/* private ListObj type */
typedef struct ListObj* List;

/* newList():
 * List Type Constructor
 */
List newList(void);

/* freeList():
 * List Type Destructor
 * Frees all heap memory associated with List *pL, and sets *pL to NULL.
 */
void freeList(List* pL);

/* length():
 * Returns number of elements in this list.
 */
int length(List L);

/* index()
 * Returns the index of the cursor element in this list, or
 * returns -1 if the cursor element is undefined.
 */
int index(List L);

/* front()
 * Returns front element in this list. Pre: length()>0
 */
int front(List L);

/* back()
 * Returns back element in this List. Pre: length()>0
 */
int back(List L);

/* get()
 * Returns cursor element in this list. Pre: length()>0, getIndex()>=0
 */
int get(List L);

/* equals():
 * Returns true if this List and L are the same integer
 * sequence. The cursor is ignored in both lists.
 */
int equals(List A, List B);

/* clear():
 * Re-sets this List to the empty state.
 */
void clear(List L);

/* movefront():
 * If List is non-empty, places the cursor under the front
 * element, otherwise does nothing.
 */
void moveFront(List L);
 
 /* moveBack():
  * If List is non-empty, places the cursor under the back
  * element, otherwise does nothing.
  */
void moveBack(List L);

/* movePrev():
 * If 0<getIndex()<=length()-1, move cursor one step toward the
 * front of the list. If getIndex()==0, cursor = undefined.
 * If getIndex()== -1, cursor == undefined. This operation is
 * equivalent to moveTo(getIndex()-1).
 */
void movePrev(List L);

/* moveNext():
 * If 0<=getIndex()<length()-1, move cursor one step toward
 * back of the list. If getIndex()==length()-1, cursor = UNDF
 * .If index==-1, cursor remains undefined. This  operation
 * is equivalent to moveTo(getIndex()+1).
 */
void moveNext(List L);

/* prepend():
 * Inserts a new element before front element in this List
 */
void prepend(List L, int data);

/* append():
 * Inserts new element after back element in this List.
 */
void append(List L, int data);

/* insertBefore():
 * Pre: length()>0, getIndex()>=0
 * Inserts new element before cursor element in this List.
 */
void insertBefore(List L, int data);

/* insertAfter():
 * Pre: length()>0, getIndex()>=0
 * Inserts new element after cursor element in this List.
 */
void insertAfter(List L, int data);

/* deleteFront():
 * Deletes the front element in this List. Pre: length()>0
 */
void deleteFront(List L);

/* deleteBack():
 * Deletes the back element in this List. Pre: length()>0
 */
void deleteBack(List L);

/* delete():
 * Deletes cursor element in this List. Cursor is undefined after this
 * operation. Pre: length()>0, getIndex()>=0
 */
void delete(List L);

/* printList():
 * Prints item elements in L on a single line to file out.
 */
void printList(FILE* out, List L);

/* copyList()
 * Returns a new list representing the same integer sequence as this
 * list. The cursor in the new list is undefined.
 */
List copyList(List L);

/* concatList()
 * Returns a new List which is the concatenation of
 * this list followed by L. The cursor in the new list
 * is undefined, regardless of the states of the cursors
 * in this list and L. The states of both remain unchanged
 */
List concatList(List A, List B);


#endif
