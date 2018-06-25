//---------------------------------------------------------
// List.java
// James Michael Vrionis
// JVrionis
// 1-20-17
// Programming Assingment 1
// 
// My List ADT module contained below with required 
// operations. All services exported to the 
// client module.
// 
//---------------------------------------------------------

public class List {
   private class Node {
      // Fields for inner class Node
      int item;
      Node prev;
      Node next;
      
      // Constructor 
      Node(int item) {
         this.item = item;
         prev = null;
         next = null;
      }
      
      // Creates a Node with int item, Node prev, and Node next
      Node (int item, Node prev, Node next) {
         this.item = item;
         this.prev = prev;
         this.next = next;
      }

      // toString(): overrides Object's toString() method
      // Returns String representation of the item property
      public String toString() {
         return String.valueOf(item);
      }
      
      // equals():
      // Returns true if two Nodes item properties are equal
      public boolean equals(Object x) {
         boolean eq = false;
         Node that;
         if(x instanceof Node) {
            that = (Node) x;
            eq = (this.item == that.item);
         }
         return eq;
      }
   }

   // Fields
   private Node front; // Front of List
   private Node back;  // Back of List
   private Node cursor; // Used for bi-directional traversal
   private int length; // # of elements in List
   private int index; // index of List

   // List():
   // Creates a new Empty List
   List() {
      front = null;
      back = null;
      cursor = null;
      length = 0;
      index = -1;
   }
   
   // length():
   // Returns the number of elements in this List
   int length() {
      return length;
   }

   // index()
   // If cursor is defined, returns the index of the cursor
   // element, otherwise returns -1
   int index() {
      return index;
   }

   // front():
   // Returns front element
   // Pre: length() > 0
   int front() {
      if(length < 1)
         throw new RuntimeException(
            "List Error: front() called on empty List");
      return front.item;
   }

   // back():
   // Returns back element
   // Pre: length() > 0
   int back() {
      if(length < 1)
         throw new RuntimeException(
            "List Error: back() called on empty List");
      return back.item;
   }

   // get():
   // Returns cursor element
   // Pre: length() > 0
   int get() {
      if(index < 0)
         throw new RuntimeException(
            "List Error: get() called with undefined index on List");
      if(length < 1)
         throw new RuntimeException(
            "List Error: get() called on an empty List");
      return cursor.item;
   }

   // equals():
   // Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists
   boolean equals(List L) {
      if(L.length() != length) {
         return false;
      }
      Node frontc = L.front;
      Node temp = front;
      while(frontc.next != null && temp.next != null) {
         if(!frontc.equals(temp))
            return false;
         frontc = frontc.next;
         temp = temp.next;
      }
      return true;
   }

   // clear():
   // Resets this List to its original empty state
   void clear() {
      front = null;
      back = null;
      cursor = null;
      length = 0;
      index = -1;
   }
   
   // moveFront():
   // If List is non-empty, places the cursor under the front
   // element, otherwise does nothing
   void moveFront() {
      if(length > 0) {
         cursor = front;
         index = 0;
      } 
   }

   // moveBack():
   // If List is non-empty, places the cursor under the back
   // element, otherwise does nothing
   void moveBack() {
      if(length > 0) {
         cursor = back;
         index = length - 1;
      }
   }

   // movePrev():
   // If cursor is defined and not at front, moves cursor one step
   // toward front of this List, if cursor is defined and at front,
   // cursor becomes undefined, if cursor is undefined does nothing
   void movePrev() {
      if(cursor != null && index != 0) {
         cursor = cursor.prev;
         index--;
      }
      else if(cursor != null && index == 0) {
         cursor = null;
         index = -1;
      }
   }
   
   // moveNext():
   // If cursor is defined and not at back, moves cursor one step
   // toward back of this List, if cursor is defined and at back,
   // cursor becomes undefined, if cursor is undefined does nothing
   void moveNext() {
      if(cursor != null && index != length - 1) {
         cursor = cursor.next;
         index++;
      }
      else if(cursor != null && index == length - 1) {
         cursor = null;
         index = -1;
      }
   }

   // prepend():
   // Insert new element into this List. If List is non-empty,
   // insertion takes place before the front element
   void prepend(int item) {
      Node temp = new Node(item, null, front);
      if(front == null)
         back = temp;
      else
         front.prev = temp;
      front = temp;
      length++;
   }
   // append():
   // Insert new element into this List. If List is non-empty,
   // insertion takes place after back element
   void append(int item) {
      Node temp = new Node(item, back, null);
      if(front == null)
         front = temp;
      else
         back.next = temp;
      back = temp;
      length++;
   }

   // insertBefore():
   // Insert new element before cursor
   // Pre: length() > 0, index() >= 0
   void insertBefore(int item) {
      if(index < 0)
         throw new RuntimeException(
            "List Error: insertBefore() called with an undefined index on List");
      if(length < 1)
         throw new RuntimeException(
            "List Error: insertBefore() called on an empty List");
      Node temp = new Node(item, cursor.prev, cursor);
      if(cursor.prev != null)
         cursor.prev.next = temp;
      else
         front = temp;
      cursor.prev = temp;
      length++;
   }
   
   // insertAfter():
   // Inserts new element after cursor
   // Pre: length() > 0, index() >= 0
   void insertAfter(int item) {
      if(index < 0)
         throw new RuntimeException(
            "List Error: insertAfter() called with an undefined index on List");
      if(length < 1)
         throw new RuntimeException(
            "List Error: insertAfter() called on an empty List");
      Node temp = new Node(item, cursor, cursor.next);
      if(cursor.next != null)
         cursor.next.prev = temp;
      else
         back = temp;
      cursor.next = temp;
      length++; 
   }
   
   // deleteFront():
   // Deletes the front element
   // Pre: length() > 0
   void deleteFront() {
      if(length < 1)
         throw new RuntimeException(
            "List Error: deleteFront() called on an empty List");
      if(cursor == front) {
         cursor = null;
         index = -1;
      }
      front = front.next;
      front.prev = null;
      length--;
   }
   
   // deleteBack():
   // Deletes the back element
   // Pre: length() > 0
   void deleteBack() {
      if(length < 1)
         throw new RuntimeException(
            "List Error: deleteBack() called on an empty List");
      if(cursor == back) {
         cursor = null;
         index = -1;
      }
      back = back.prev;
      back.next = null;
      length--;
   }
   
   // delete():
   // Deletes cursor element, making cursor undefined
   // Pre: length() > 0, index() >= 0
   void delete() {
      if(index < 0)
         throw new RuntimeException(
         "List Error: delete() called with an undefined List index");
      if(length < 1)
         throw new RuntimeException(
            "List Error: delete() called on an empty List");
      if(cursor == back)
         deleteBack();
      else if(cursor == front)
         deleteFront();
      else {
         cursor.prev.next = cursor.next;
         cursor.next.prev = cursor.prev;
         cursor = null;
         index = -1;
         length--;
      }
   }
   
   // toString():
   // Overrides Object's toString method. Returns a String
   // representation of this List consisting of a space
   // separated sequence of integers, with front on left
   // pL: print list
   public String toString() {
      Node temp = front;
      String pL = new String();
      while(temp != null) {
         pL = pL + String.valueOf(temp.item) + " ";
         temp = temp.next;
      }
      return pL;
   }

   // copy()
   // Returns a new List representing the same integer sequence as this
   // List. The cursor in the new list is undefined, regardless of the
   // state of the cursor in this List. This List is unchanged
   List copy() {
      // cope is new List representing int sequence
      // make a tempory Node that points to the front of the list
      // put the list items onto cope until temp falls off list.
      // return "copy" (cope) of the list.
      List cope = new List();
      Node temp = front;
      while(temp != null) {
         cope.append(temp.item);
         temp = temp.next;
      }
      return cope;
   }

   // concat():
   // Returns a new List which is the concatenation of
   // this list followed by L. The cursor in the new List
   // is undefined, regardless of the states of the cursors
   // in this List and L. The states of this List and L are
   // unchanged
   List concat(List L) {
      List catcon = copy();
      Node temp = L.front;
      while(temp != null) {
         catcon.append(temp.item);
         temp = temp.next;
      }
      return catcon;
   }
}
