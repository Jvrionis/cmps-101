/**************************************************************
 * James Michael Vrionis
 * JVrionis
 * 3-2-17
 * Programming Assingment 4
 * 
 * List.c: List ADT used to implement both the FIFO queue and
 * the adjacency lists representing the graph itself.
 *  
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/* NodeObj */
typedef struct NodeObj {
    int item;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

/* Node  */
typedef NodeObj* Node;

/* private ListObj type */
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int index;
   //int length;
} ListObj;

/* newNode():
 * Returns reference to new Node object. Initializes prev, next, and item 
 * fields. Private.
 */
Node newNode(int item) {
    Node N = malloc(sizeof(NodeObj));
    N->item = item;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

/* freeNode():
 * List Type Destructor
 */
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
       free(*pN);
       *pN = NULL;
    }
}

/* newList(): 
 * List Type Constructor
 */
List newList() {
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->index = -1;
    return(L);
}

/* freeList():
 * List Type Destructor
 * Frees all heap memory associated with List *pL, and sets *pL to NULL.
 */
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while( length(*pL) > 0 ) {
            deleteBack(*pL);   
        }
        free(*pL);
        *pL = NULL;
    }
}

/* length():
 * Returns number of elements in this list.
 */
int length(List L) {
    int result = 0;
    for (Node curr = L->front; curr != NULL; curr = curr->next) {
        result++;
    }
    return result;
}

/* getIndex()
 * Returns the index of the cursor element in this list, or
 * returns -1 if the cursor element is undefined.
 */
int getIndex(List L) {
    return L->index;
}

/* front()
 * Returns front element in this list. Pre: length()>0
 */
int front(List L) {
    if ( L == NULL ) {
        printf("List Error(1): calling front() on NULL List reference\n");
        exit(1);
    }
    if ( length(L) <= 0 ) {
        printf("List Error(2): calling front() on empty List\n");
        exit(1);
   }
   return (L->front->item);
}

/* back()
 * Returns back element in this List. Pre: length()>0
 */
int back(List L) {
    if ( L == NULL ) {
        printf("List Error(3): calling back() on NULL List reference\n");
        exit(1);
    }
    if ( length(L) <= 0 ) {
        printf("List Error(4): calling back() on empty List\n");
        exit(1);
    }
    return (L->back->item);
}

/* getElement()
 * Returns cursor element in this list. Pre: length()>0, getIndex()>=0
 */ 
int getElement(List L) {
    if ( L == NULL ) {
        printf("List Error(5): calling getElement() on NULL List reference\n");
        exit(1);
    }
    if ( length(L) <= 0 ) {
        printf("List Error(6): calling getElement() on empty List\n");
        exit(1);
    } 
    if ( getIndex(L) < 0 ) {
        printf("List Error(7): calling getElement() on undefined cursor\n");
    }
    return (L->cursor->item);
}

/* equals():
 * Returns true if this List and L are the same integer
 * sequence. The cursor is ignored in both lists.
 */
int equals(List A, List B) {
    int flag = 1;
    Node N = NULL;
    Node M = NULL;
    if ( A==NULL || B==NULL ) {
        printf("List Error(8): calling equals() on NULL List reference\n");
        exit(1);
    }
    N = A->front;
    M = B->front;
    if ( length(A) != length(B) ) {
        return 0;
    }
    while ( flag && N!=NULL ) {
        flag = (N->item==M->item);
        N = N->next;
        M = M->next;
    }
    return flag;
}

/* clear():
 * Re-sets this List to the empty state.
 */
void clear(List L) {
   if (L != NULL) {
      while( length(L) > 0 ) {
         deleteBack(L);   
      }
   }
   L->front = L->back = L->cursor = NULL;
   L->index = -1;
}

/* moveTo():
 * If 0<=i<=length()-1, moves the cursor to the element
 * at index i, otherwise the cursor becomes undefined.
 */
void moveTo(List L, int i) {
    if ( L == NULL ) {
        printf("List Error(9): moveTo() called on NULL List reference\n");
        exit(1);
    }
    if ( (0 <= i) && (i <= (length(L)-1)) ) {
        Node curr = L->front;
        for(int j = 0; j < i; j++) {
            curr = curr->next;
        }
        L->cursor = curr;
        L->index = i;
    } else {
        L->cursor = NULL;
        L->index = -1;
    }
}

/* movePrev():
 * If 0<getIndex()<=length()-1, move cursor one step toward the
 * front of the list. If getIndex()==0, cursor = undefined.
 * If getIndex()== -1, cursor == undefined. This operation is
 * equivalent to moveTo(getIndex()-1).
 */
void movePrev(List L) {
    if ( L == NULL ) {
        printf("List Error(10): calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if( (0 < getIndex(L)) && (getIndex(L) <= (length(L)-1)) ) {
        L->cursor = L->cursor->prev;
        L->index = L->index - 1;
    }else if (getIndex(L) == 0) {
        L->cursor = NULL;
        L->index = -1;
    }else if (getIndex(L) == -1) {
        L->cursor = NULL;
        L->index = -1;
    }
}

/* moveNext():
 * If 0<=getIndex()<length()-1, move cursor one step toward
 * back of the list. If getIndex()==length()-1, cursor = UNDF 
 * .If index==-1, cursor remains undefined. This  operation 
 * is equivalent to moveTo(getIndex()+1).
 */
void moveNext(List L) {
    if ( L == NULL ) {
        printf("List Error(11): calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if( (0 <= getIndex(L)) && (getIndex(L) < (length(L)-1)) ) {
        L->cursor = L->cursor->next;
        L->index = L->index + 1;
    }else if (getIndex(L) == (length(L)-1)) {
        L->cursor = NULL;
        L->index = -1;
    }else if (getIndex(L) == -1) {
        L->cursor = NULL;
        L->index = -1;
    }
}

/* prepend()
 * Inserts a new element before front element in this List
 */
void prepend(List L, int item) {
    if ( L == NULL ) {
        printf("List Error(12): calling prepend() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(item);
    if( length(L) == 0 ) {
        L->front = L->back = N;
    }else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
    }
    if(getIndex(L) != -1) {
        L->index = L->index+1;
    }
}

/* append()
 * Inserts new element after back element in this List.
 */
void append(List L, int item) {
    if ( L == NULL ) {
        printf("List Error(13): calling append() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(item);
    if (length(L) == 0) {
        L->front = L->back = N;
    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
}

/* insertBefore()
 * Pre: length()>0, getIndex()>=0
 * Inserts new element before cursor element in this List.
 */
void insertBefore(List L, int item) {
    if ( L == NULL ) {
        printf("List Error(14): calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0) {
        printf("List Error(15): insertBefore() called on empty list.\n");
        exit(1);
    }
    if(getIndex(L) < 0) {
        printf("List Error(16): insertBefore() called on undefined cursor.\n");
        exit(1);
    }
    Node node = newNode(item);
    if(L->cursor == L->front) {
        L->front->prev = node;
        node->next = L->front;
        L->front = node;
        L->index++;
    }else {
        L->cursor->prev->next = node;
        node->prev = L->cursor->prev;
        L->cursor->prev = node;
        node->next = L->cursor;
        L->index++;
    }
}

/* insertAfter()
 * Pre: length()>0, getIndex()>=0 
 * Inserts new element after cursor element in this List.
 */
void insertAfter(List L, int item) {
    if ( L == NULL ) {
        printf("List Error(17): calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0) {
        printf("List Error(18): insertAfter() called on empty list.\n");
        exit(1);
    }
    if(getIndex(L) < 0) {
        printf("List Error(19): insertAfter() called on undefined cursor.\n");
        exit(1);
    }
    Node node = newNode(item);
    if(L->cursor == L->back) {
        L->back->next = node;
        node->prev = L->back;
        L->back = node;
    } else {
        L->cursor->next->prev = node;
        node->next = L->cursor->next;
        L->cursor->next = node;
        node->prev = L->cursor;
    }
}

/* deleteFront()
 * Deletes the front element in this List. Pre: length()>0
 */
void deleteFront(List L) {
    if( L == NULL ) {
        printf("List Error(20): calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0) {
        printf("List Error(21): deleteFront() called on empty list.\n");
        exit(1);
    }
    Node temp = L->front;
    if(length(L) > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
        if(L->index != -1)
            L->index--;
   }else {
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
   }
   freeNode(&temp);
}

/* deleteBack()
 * Deletes the back element in this List. Pre: length()>0
 */
void deleteBack(List L) {
    if( L == NULL ) {
        printf("List Error(22): calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0) {
        printf("List Error(23): deleteBack() called on empty list.\n");
        exit(1);
    }
    if(L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
    Node temp = L->back;
    if(length(L) > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    }else {
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
    }
    freeNode(&temp);
}

/* delete()
 * Deletes cursor element in this List. Cursor is undefined after this
 * operation. Pre: length()>0, getIndex()>=0
 */
void delete(List L) {
    if( L == NULL ) {
        printf("List Error(24): calling delete() on NULL List reference\n");
        exit(1);
    }
    if(length(L) <= 0) {
        printf("List Error(25): delete() called on empty list.\n");
        exit(1);
    }
    if(getIndex(L) < 0) {
        printf("List Error(26): delete() called on undefined cursor.\n");
        exit(1);
    }
    Node temp = L->cursor;
    if(L->cursor == L->front) {
        L->front = L->front->next;
        L->front->prev = NULL;
    }else if(L->cursor == L->back) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
    }
    L->cursor = NULL;
    L->index = -1;
    freeNode(&temp);
}


/* printList()
 * Prints item elements in L on a single line to file out.
 */
void printList(FILE* out, List L) {
    if ( L == NULL ) {
        printf("List Error(27): printList() called on NULL List reference\n");
        exit(1);
    }
   
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d", N->item);
        if(N->next != NULL) 
            fprintf(out, " ");
    }
    fprintf(out, "\n");
}

/* copyList()
 * Returns a new list representing the same integer sequence as this
 * list. The cursor in the new list is undefined.
 */
List copyList(List L) {
    if ( L == NULL ) {
        printf("List Error (28): calling copyList() on NULL List reference\n");
        exit(1);
    }
    List list = newList();
    Node N = L->front;
    
    while( N != NULL ) {
        append(list, N->item);
        N = N->next;
    }
    return list;
}

/* concatList()
 * Returns a new List which is the concatenation of
 * this list followed by L. The cursor in the new list
 * is undefined, regardless of the states of the cursors
 * in this list and L. The states of both remain unchanged
 */
List concatList(List A, List B) {
    if ( A == NULL  || B == NULL ) {
        printf("List Error (29): calling concatList() on NULL List reference\n");
        exit(1);
    }

    List list = newList();
    Node N = A->front;
    Node M = B->front;

    while( N != NULL ) {
        append(list, N->item);
        N = N->next;
    }
    while( M != NULL ) {
        append(list, M->item);
        M = M->next;
    }
    return list;
}