/**********************************************************************
* James Michael Vrionis
* JVrionis
* 1-24-17
* Programming Assingment 2
* List.c : A List ADT module contained below with 
* required operations. All services exported to the 
* client module.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "List.h" 

/* NodeObj */
typedef struct NodeObj {
    int item;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

/* NODE */
typedef NodeObj* Node;

typedef struct ListObj {
    Node front; /* Front of List */
    Node back;  /* Back of List */
    Node cursor; /* Used for bi-directional traversal */
    int length; /* # of elements in List */
    int index; 	
} ListObj;

/* Node newNode(): 
 * Creates a 'new'Node with int item, Node prev, and Node next 
 */
Node newNode(int item, Node prev, Node next) {
    Node N = malloc(sizeof(NodeObj));
    N->item = item;
    N->prev = prev;
    N->next = next;
    return N;
}

/* freeNode(): 
 * Destructor for Node type 
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
List newList(void) {
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front= L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);	
}

/* freeList()
 * List Type Destructor
 */
void freeList(List* pL) {
    if(pL != NULL && *pL != NULL) {
        Node temp = (*pL)->front;
        while(temp != NULL){
            Node K = temp;
            temp = temp->next;
            free(K);
            K = NULL;  
        }
        free(*pL);
        *pL = NULL;	
    } 		
}

/* length():
 * Returns the number of elements in this List
 */
int length(List L) {
    if(L == NULL) {
        printf("List Error (1): calling length() on NULL list reference.\n");
        exit(1);
    }		
    return L->length;
}

/*
 * index():
 * If cursor is defined, returns the index of the cursor
 * element, otherwise returns -1   
 */
int index(List L) {
    if(L == NULL) {
        printf("List Error (2): calling index() on NULL list reference.\n");
        exit(1);
    }		
    return L->index;
}
   
/* front():
 * Returns front element
 * Pre: length() > 0
 */
int front(List L) {
    if(L == NULL){
        printf("List Error (3a): front() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 1) {
        printf("List Error (3b): front() called on empty List.\n");
        exit(1);
    }
    return L->front->item;
}

/* back():
 * Returns back element
 * Pre: length() > 0
 */
int back(List L) {
    if(L == NULL) {
        printf("List Error (4a): back() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 1) {
        printf("List Error (4b): back() called on empty List.\n");
        exit(1);
    }
    return L->back->item;
}

/* get():
 * Returns cursor element
 * Pre: length() > 0
 */
int get(List L) {
    if(L == NULL){
        printf("List Error (5a): get() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 0) {
        printf("List Error (5b): get() called with undef index on List.\n");
        exit(1);
    }
    if(L->length < 1) {
  	    printf("List Error (5c): get() called on an empty List.\n");
	    exit(1);
    }
    return L->cursor->item;
}

/* equals():
 * Returns true if this List and L are the same integer
 * sequence. The cursor is ignored in both lists
 */
int equals(List T, List F) {
    if(T == NULL || F == NULL) {
        printf("List Error (6): equals() called on NULL List reference.\n");
        exit(1);
    }
    if(T->length != F->length) {
        return 0;
    }
    Node frontc = F->front;
    Node temp = T->front;
    while(frontc->next != NULL && temp->next != NULL) {
        if(frontc->item != temp->item)
            return 0;
        frontc = frontc->next;
        temp = temp->next;
    }
    return 1;
}

/* clear():
 * Resets this List to its original empty state
 */
void clear(List L) {
    if(L == NULL){
        printf("List Error (7): Clear() called on NULL list reference.\n");
        exit(1);
    }
  	Node temp = L->front;
    while(temp != NULL) {
  	    Node K = temp;
  	    temp = temp->next;
        free(K);
        K=NULL; 
  	}	
    L->front=L->back=L->cursor=NULL;
    L->length = 0;
    L->index = -1;
}
      
/* moveFront():
 * If List is non-empty, places the cursor under the front
 * element, otherwise does nothing
 */
void moveFront(List L) {
    if(L == NULL) {
        printf("List Error (8): moveFront() called on NULL list reference.\n");
   	    exit(1);
    }
    if(L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    } 
}

/* moveBack():
 * If List is non-empty, places the cursor under the back
 * element, otherwise does nothing
 */
void moveBack(List L) {
    if(L == NULL) {
        printf("List Error (9): moveBack() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

/* movePrev():
 * If cursor is defined and not at front, moves cursor one step
 * toward front of this List, if cursor is defined and at front,
 * cursor becomes undefined, if cursor is undefined does nothing
 */
void movePrev(List L) {
    if(L == NULL) {
        printf("List Error (10): movePrev() called on NULL list reference.\n");
        exit(1);
    }
    if(L->cursor != NULL && L->index != 0) {
        L->cursor = L-> cursor->prev;
        --L->index; 
    }
    else if(L->cursor != NULL && L-> index == 0) {
        L->cursor = NULL;
        L->index = -1;
    }
}

/* moveNext():
 * If cursor is defined and not at back, moves cursor one step
 * toward back of this List, if cursor is defined and at back,
 * cursor becomes undefined, if cursor is undefined does nothing
 */
void moveNext(List L) {
    if(L == NULL) {
        printf("List Error (11): moveNext() called on NULL list reference.\n");
        exit(1);
    }
    if(L->cursor != NULL && L->index != L->length - 1) {
        L->cursor = L->cursor->next;
        ++L->index; 
    }
    else if(L->cursor != NULL && L->index == L->length - 1) {
        L->cursor = NULL;
        L->index = -1;
    }
}

/* prepend():
 * Insert new element into this List. If List is non-empty,
 * insertion takes place before the front element
 */
void prepend(List L, int item) {
    if(L == NULL) {
        printf("List Error (12): prepend() called on NULL list reference.\n");
        exit(1);
    }
    Node temp = newNode(item, NULL, L->front);
    if(L->front == NULL)
        L->back = temp;
    else
        L->front->prev = temp;
    L->front = temp;
    ++L->length;
}

/* append():
 * Insert new element into this List. If List is non-empty,
 * insertion takes place after back element
 */
void append(List L, int item) {
	if(L == NULL) {
        printf("List Error (13): append() called on NULL list reference.\n");
        exit(1);
    }
    Node temp = newNode(item, L->back, NULL);
    if(L->front == NULL)
        L->front = temp;
    else
        L->back->next = temp;
    L->back = temp;
    ++L->length; 
}

/* insertBefore():
 * Insert new element before cursor
 * Pre: length() > 0, index() >= 0
 */
void insertBefore(List L, int item) {
    if(L == NULL) {
   	    printf("List Error (14a): insertBefore() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 0){
        printf("List Error (14b): insertBefore() called with undefined index on List.\n");
        exit(1);
    }
    if(L->length < 1) {
        printf("List Error (14c): insertBefore() called on an empty List.\n");
        exit(1);
    }
    Node temp = newNode(item, L->cursor->prev, L->cursor); 
    if(L->cursor->prev != NULL)
        L->cursor->prev->next = temp;
	else
		L->front = temp;
    L->cursor->prev = temp;
    ++L->length;
}

/* insertAfter():
 * Inserts new element after cursor
 * Pre: length() > 0, index() >= 0
 */
void insertAfter(List L,int item) {
    if(L == NULL){
        printf("List Error (15a): insertAfter() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 0) {
        printf("List Error (15b): InsertAfter() called with undefined index on List.\n");
        exit(1);
    }
  	if(L->length < 1) {
  	    printf("List Error (15c): InsertAfter() called on an empty List.\n");
        exit(1);
  	}    	
    Node temp = newNode(item, L->cursor, L->cursor->next);
    if(L->cursor->next != NULL)
        L->cursor->next->prev = temp;
    else
        L->back = temp;
    L->cursor->next = temp;
    ++L->length; 
}

/* deleteFront():
 * Deletes the front element
 * Pre: length() > 0
 */
void deleteFront(List L) {
    if(L == NULL) {
        printf("List Error (16a): deleteFront() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 1) {
  	    printf("List Error (16b): deleteFront() called on an empty List.\n");
        exit(1);
  	}
    if(L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    }
    Node temp = L->front;
    L->front = L->front->next;
    L->front->prev = NULL;
    --L->length;
    freeNode(&temp);
    temp = NULL; 
}

/* deleteBack():
 * Deletes the back element
 * Pre: length() > 0
 */
void deleteBack(List L) {
    if(L == NULL){
        printf("List Error (17a): deleteBack() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 1) {
  	    printf("List Error (17b): deleteBack() called on an empty List.\n");
        exit(1);
    }
    if(L->cursor == L->back) {
        L->cursor = NULL;
        --L->index;
    }
    Node temp = L->back;
    L->back = L->back->prev;
    L->back->next = NULL;
    --L->length;
    freeNode(&temp);
    temp = NULL; 
}

/* delete():
 * Deletes cursor element, making cursor undefined
 * Pre: length() > 0, index() >= 0
 */
void delete(List L) {
    if(L == NULL){
        printf("List Error (18a): delete() called on NULL list reference.\n");
        exit(1);
    }
    if(L->length < 0){
        printf("List Error (18b): delete() called with undef index on List.\n");
        exit(1);
    }
    if(L->length < 1) {
      	printf("List Error (18c): delete() called on an empty List.\n");
        exit(1);
    }
    if(L->cursor == L->back)
        deleteBack(L);
    else if(L->cursor == L->front)
        deleteFront(L);
    else {
        Node temp = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&temp);
        L->cursor = NULL;
        L->index = -1;
        --L->length;
    }
}

/* printList():
 * separated sequence of integers, with front on left
 * pL: print list
 */
void printList(FILE* out, List L) {
    Node temp = L->front;
    while(temp != NULL) {
        printf("%d ",temp->item); 
        temp = temp->next;
    }
}

/* copyList()
 * Returns a new List representing the same integer sequence as this
 * List. The cursor in the new list is undefined, regardless of the
 * state of the cursor in this List. This List is unchanged
 * cope is new List representing int sequence
 * make a tempory Node that points to the front of the list
 * put the list items onto cope until temp falls off list.
 * return "copy" (cope) of the list.
 */
List copyList(List L) {
    List cope = newList();
    Node temp = L->front;
    while(temp != NULL) {
        append(cope,temp->item);
        temp = temp->next;
    }
    return cope;
}

/* concat():
 * Returns a new List which is the concatenation of
 * this list followed by L. The cursor in the new List
 * is undefined, regardless of the states of the cursors
 * in this List and L. The states of this List and L are
 * unchanged
 */
List concat(List L) {
    List catcon = newList();
    Node temp = L->front;
    while(temp != NULL) {
	    append(catcon,temp->item);
	    temp = temp->next;
    }
    return catcon;
}


