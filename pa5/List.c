/**************************************************************
 * Programming Assingment 5
 *
 * List.c: Doubly linked list data structure used to store an
 * integer data capable of traversing the list via index, that
 * is, index of cursor.
 *
 *************************************************************/

#include<stdio.h>
#include<stdlib.h>

#include "List.h"

/* NodeObj */
typedef struct NodeObj {
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

/* Node  */
typedef NodeObj* Node;

/* private ListObj type
 * index of curser
 */
typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

/* newNode():
 * Returns reference to new Node object. Initializes prev, next, and item
 * fields. Private.
 */
Node newNode(int data, Node prev, Node next) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = prev;
   N->next = next;
   return(N);
}

/* freeNode():
 * List Type Destructor
 */
void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

/* newList():
 * List Type Constructor
 */
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

/* freeList():
 * List Type Destructor
 * Frees all heap memory associated with List *pL, and sets *pL to NULL.
 */
void freeList(List* pL) {
   if(pL != NULL && *pL != NULL) { 
      Node tmp = (*pL)->front; 
      while(tmp != NULL) {
         Node cur = tmp;
         tmp = tmp->next;
         free(cur);
      }
      free(*pL);
      *pL = NULL;
   }
}

/* length():
 * Returns number of elements in this list.
 */
int length(List L) {
   if(L == NULL) {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return L->length;
}

/* index():
 * Returns idnex element
 */
int index(List L) {
   if(L == NULL) {
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return L->index;
}

/* front():
 * Returns front element.
 * Pre: length() > 0
 */
int front(List L) {
   if(L == NULL) {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: calling front() on empty List reference\n");
      exit(1);
   }
   return L->front->data;
}

/* back():
 * Returns back element in this List. Pre: length()>0
 */
int back(List L) {
   if(L == NULL) {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: calling back() on empty List reference\n");
      exit(1);
   }
   return L->back->data;
}

/* get():
 * Returns cursor element in this list. Pre: length()>0, getIndex()>=0
 */
int get(List L) {
   if(L == NULL) {
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0) {
      printf("List Error: calling get() with an undefined index on List\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: calling get() on empty List reference\n");
      exit(1);
   }
   return L->cursor->data;
}

/* equals():
 * Returns true if this List and L are the same integer
 * sequence. The cursor is ignored in both lists.
 */
int equals(List A, List B) {
   if(A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   if(A->length != B->length) {
      return 0;
   }
   Node cfront = B->front;
   Node tmp = A->front;
   while(cfront->next != NULL && tmp->next != NULL) {
      if(cfront->data != tmp->data)
         return 0;
      cfront = cfront->next;
      tmp = tmp->next;
   }
   return 1;
}

/* clear():
 * Re-sets this List to the empty state.
 */
void clear(List L) {
   if(L == NULL) {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node tmp = L->front; 
   while(tmp != NULL) {
      Node cur = tmp;
      tmp = tmp->next;
      free(cur);
   }
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}

/* movefront():
 * If List is non-empty, places the cursor under the front
 * element, otherwise does nothing.
 */
void moveFront(List L) {
   if(L == NULL) {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0) {
      L->cursor = L->front;
      L->index = 0;
   }
}

 /* moveBack():
  * If List is non-empty, places the cursor under the back
  * element, otherwise does nothing.
  */
void moveBack(List L) {
   if(L == NULL) {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0) {
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}

/* movePrev():
 * If 0<getIndex()<=length()-1, move cursor one step toward the
 * front of the list. If getIndex()==0, cursor = undefined.
 * If getIndex()== -1, cursor == undefined. This operation is
 * equivalent to moveTo(getIndex()-1).
 */
void movePrev(List L) {
   if(L == NULL) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->index != 0) {
      L->cursor = L->cursor->prev;
      --L->index;
   }
   else if(L->cursor != NULL && L->index == 0) {
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
   if(L == NULL) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->cursor != L->back) {
      L->cursor = L->cursor->next;
      ++L->index;
   }
   else if(L->cursor != NULL && L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
   }
}

/* prepend():
 * Inserts a new element before front element in this List
 */
void prepend(List L, int data) {
   if(L == NULL) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   Node tmp = newNode(data, NULL, L->front);
   if(L->front == NULL)
      L->back = tmp;
   else
      L->front->prev = tmp;
   L->front = tmp;
   ++L->length;
}

/* append():
 * Inserts new element after back element in this List.
 */
void append(List L, int data) {
   if(L == NULL) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node tmp = newNode(data, L->back, NULL);
   if(L->front == NULL)
      L->front = tmp;
   else
      L->back->next = tmp;
   L->back = tmp;
   ++L->length;
}

/* 
 * insertBefore():
 * Pre: length()>0, getIndex()>=0
 * Inserts new element before cursor element in this List.
 */
void insertBefore(List L, int data) {
   if(L == NULL) {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0) {
      printf("List Error: insertBefore() called with an undefined index on List");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: insertBefore() called on an empty List");
      exit(1);
   }
   Node tmp = newNode(data, L->cursor->prev, L->cursor);
   if(L->cursor->prev != NULL)
      L->cursor->prev->next = tmp;
   else
      L->front = tmp;
   L->cursor->prev = tmp;
   ++L->length;
}

/* 
 * insertAfter():
 * Pre: length()>0, getIndex()>=0
 * Inserts new element after cursor element in this List.
 */
void insertAfter(List L, int data) {
   if(L == NULL) {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0) {
      printf("List Error: insertAfter() called with an undefined index on List");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: insertAfter() called on an empty List");
      exit(1);
   }
   Node tmp = newNode(data, L->cursor, L->cursor->next);
   if(L->cursor->next != NULL)
      L->cursor->next->prev = tmp;
   else
      L->back = tmp;
   L->cursor->next = tmp;
   ++L->length;
}

/* 
 * deleteFront():
 * Deletes the front element in this List. Pre: length()>0
 */
void deleteFront(List L) {
   if(L == NULL) {
      printf("List Error: deleteFront() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: deleteFront() called on an empty List\n"); 
      exit(1);
   }
   if(L->cursor == L->front) {
      L->cursor = NULL;
      L->index = -1;
   }
   Node tmp = L->front;
   L->front = L->front->next;
   L->front->prev = NULL;
   --L->length;
   freeNode(&tmp);
}

/* deleteBack():
 * Deletes the back element in this List. Pre: length()>0
 */
void deleteBack(List L) {
   if(L == NULL) {
      printf("List Error: deleteBack() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: deleteBack() called on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
   }
   if(L->back == L->front)
      L->front = NULL;

   Node tmp = L->back;
   if(L->back->prev != NULL)
      L->back = L->back->prev;
   L->back->next = NULL;
   --L->length;
   freeNode(&tmp);
}

/*
 * delete():
 * Deletes cursor element in this List. Cursor is undefined after this
 * operation. Pre: length()>0, getIndex()>=0
 */
void delete(List L) {
   if(L == NULL) {
      printf("List Error: delete() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: delete() called with an undefined index on List\n");
      exit(1);
   }
   if(L->index < 0) {
      printf("List Error: delete() called on empty List");
      exit(1);
   }
   if(L->cursor == L->back) {
      deleteBack(L);
   } else if(L->cursor == L->front) {
      deleteFront(L);
   } else {
      Node tmp = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&tmp);
      L->cursor = NULL;
      L->index = -1;
      --L->length;
   }
}

/* printList():
 * Prints item elements in L on a single line to file out.
 */
void printList(FILE* out, List L) {
   Node tmp = L->front;
   int i = 0;
   while(tmp != NULL) {
      if(i != 0)
         fprintf(out, " %d", tmp->data);
      else 
         fprintf(out, "%d", tmp->data);
      tmp = tmp->next;
      ++i;
   }
   
}

/* copyList():
 * Returns a new list representing the same integer sequence as this
 * list. The cursor in the new list is undefined.
 */
List copyList(List L) {
   List c = newList();
   Node tmp = L->front;
   while(tmp != NULL) {
      append(c, tmp->data);
      tmp = tmp->next;
   }
   return c;
}

/* concatList():
 * Returns a new List which is the concatenation of
 * this list followed by L. The cursor in the new list
 * is undefined, regardless of the states of the cursors
 * in this list and L. The states of both remain unchanged
 */
List concat(List L) {
   List cc = newList();
   Node tmp = L->front;
   while(tmp != NULL) {
      append(cc, tmp->data);
      tmp = tmp->next;
   }
   return cc;
}
