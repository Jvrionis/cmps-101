//---------------------------------------------------------
// James Michael Vrionis
// JVrionis
// 2-15-17
// Programming Assignment 3
//
// Matrix.java: This Matrix ADT (Array of List Objects) 
// defines the Objects referred to by the List ADT. It 
// contains an The equals() operation altered to override, 
// as a pose to overload Object's built in method. Helper 
// functions used: addSub(), and dot(). addSub(): will add 
// if true, otherwise it will take the difference; 
// dot(): takes the dot product of two lists.
// 
//---------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
public class Matrix {
    // private inner class Entry pairwise values
    private class Entry {
        int column;
        double value;
           
        // Column Value Entry
        Entry(int column, double value) {
            this.column = column;
            this.value = value;
        }
        

        // returns (column,value)
        // converts Entry to a string
        public String toString() {
            return "(" + column + ", " + value + ")";
        }
      
        // equals():
        // Overrides Object's equals() method 
        // eqif = equal if.
        public boolean equals(Object x) {
            boolean eqif = false;
            Entry that;
            if(x instanceof Entry) {
                that = (Entry) x;
                eqif = (this.column == that.column && this.value == that.value);
            }
            return eqif;
        }
    }//end of private class Entry
//--------------------------------------------------------------------------------------------------------
   
    private List[] row;

//--------------------------------------------------------------------------------------------------------
	// Constructor
	// Makes a new n x n zero Matrix
	// pre: n>=1
    Matrix(int n) {
        if(n < 1) {
            throw new RuntimeException("Matrix Error: Matrix() called on invalid amount of column entries");
        }
        row = new List[n + 1];        
        for(int i = 1; i < (n + 1); i++) {
            row[i] = new List();
        }
    }
//--------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
// --------------------- Access functions ------------------------
	// getSize()
	// Returns n, the number of rows and columns of this Matrix
    int getSize() {
        return row.length - 1;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // Returns the number of non-zero entries in this Matrix.
    int getNNZ() {
        // nnz = # of entries.
        int nnz = 0;
        for(int i = 1; i <= getSize(); i++) {
            nnz += row[i].length();
        }
        return nnz;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // boolean equals(Object): 
    // Overrides Object's equals() method.
    public boolean equals(Object x) {
        Matrix that;
        if(x instanceof Matrix) {
            that = (Matrix) x;
            if(getSize() != that.getSize()) {
                 return false;
            }   
            for(int i = 1; i <= getSize(); i++) {   
                if(!(row[i].equals(that.row[i])))
                return false;
            }
        }
        return true;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // makeZero():
    // Manipulation procedures
    // Sets this Matrix to the zero state
    void makeZero() {
        for(int i = 1; i <= getSize(); i++) {
            row[i] = new List();
        }
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // copy():
    // Returns a new Matrix having the same entries as this Matrix.
    Matrix copy() {
        Matrix M = new Matrix(getSize());
        for(int i = 1; i <= getSize(); i++) {
            row[i].moveFront();
            while(row[i].index() >= 0) {
                Entry temp = (Entry) row[i].get();
                M.changeEntry(i, temp.column, temp.value);
                row[i].moveNext();
            }
        }
        return M;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // changeEntry(int i, int j, double x):
    // Changes the ith row, jth columnumn of this Matrix to x.
    // Pre: 1 <= i <= getSize(), 1 <= j <= getSize()
    void changeEntry(int i, int j, double x) {
        if(i < 1 || i > getSize()) {
            throw new RuntimeException("Matrix Error: changeEntry() called with invalid ith position");
        }
        if(j < 1 || j > getSize()) {
      	    throw new RuntimeException("Matrix Error: changeEntry() called with invalid jth position");
        }
        boolean found = false;
        row[i].moveFront();
        while(row[i].index() >= 0) {
            Entry entry = (Entry) row[i].get();
            found = (entry.column == j ? true : false);
            if(found) {
                if(x == 0.0) {
                    row[i].delete(); 
                    return;
                }else { 
                    entry.value = x; 
                    return;
                }
            }
            row[i].moveNext();
        }
        if(!found && x != 0.0) {
            row[i].moveFront();
            if(row[i].index() == -1) {
                row[i].append(new Entry(j, x)); 
                return;
            }else {
                while(row[i].index() > -1 && ((Entry)row[i].get()).column < j) {
                    row[i].moveNext();
                }
                if(row[i].index() > -1) {
                    row[i].insertBefore(new Entry(j, x)); 
                    return;
                }else {
                    row[i].append(new Entry(j, x)); 
                    return;
                }
            }
        }
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // scalarMult(double):
    // Returns a new Matrix that is the scalar product of this Matrix with x.
    Matrix scalarMult(double x) {
        Matrix M = this.copy();
        for(int i = 1; i <= M.getSize(); i++) {
            M.row[i].moveFront();
            while(M.row[i].index() >= 0) {
                Entry temp = (Entry) M.row[i].get();
                M.changeEntry(i, temp.column, (x * temp.value));
                M.row[i].moveNext();
            }
        }
        return M;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // add(Matrix ):
    // Returns a new Matrix that is the sum of this Matrix with M.
    // Pre: getSize() == M.getSize()
    Matrix add(Matrix M) {
        if(getSize() != M.getSize()) {
            throw new RuntimeException("Matrix Error: add() called on Matrices of different sizes!");
        }
        if(M == this) {
            return this.copy().scalarMult(2);
        }
        Matrix A = new Matrix(getSize());
        // Step through Matrix and call helper function addSub
        // when True it will take the sum
        for(int i = 1; i <= getSize(); i++) {
            A.row[i] = addSub(row[i], M.row[i], true);
        }
        return A;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
   // sub(Matrix):
   // Returns a new Matrix that is the difference of this Matrix with M.
   // Pre: getSize() == M.getSize()
    Matrix sub(Matrix M) {
        if(getSize() != M.getSize()) {
            throw new RuntimeException("Matrix Error: add() called on Matrices of different sizes!");
        }
        if(M == this) {
            return new Matrix(getSize());
        }
        Matrix A = new Matrix(getSize());
        // Step through Matrix and call helper function addSub
        // when false it takes the difference.
        for(int i = 1; i <= getSize(); i++) {
            A.row[i] = addSub(row[i], M.row[i], false);
        }
        return A;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // transpose():
    // Returns a new Matrix that is the transpose of this Matrix.
    // used in mult(Matrix) to mult row * row.
    Matrix transpose() {
        Matrix M = new Matrix(getSize());
        for(int i = 1; i <= getSize(); i++) {
            row[i].moveFront();
            // Swap the entries so rows are in place of columns and columns are in place
            // of rows.
            while(row[i].index() >= 0) {
                M.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).value);
                row[i].moveNext();
            }
        }
        return M;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
   // mult(Matrix):
   // Returns a new Matrix that is the product of this Matrix with M.
   // Pre: getSize() == M.getSize()
    Matrix mult(Matrix M) {
        if(getSize() != M.getSize()) {
            throw new RuntimeException("Matrix Error: mult() called on Matrices of different sizes!");
        }
        Matrix A = new Matrix(getSize());
        // Use transpose to make mult. simpler
        Matrix Mtr = M.transpose();
        for(int i = 1; i <= getSize(); ++i) {
            if(row[i].length() == 0) continue;
            for(int j = 1; j <= getSize(); ++j) {
                if(Mtr.row[j].length() == 0) continue;
                A.changeEntry(i, j, dot(row[i], Mtr.row[j]));
            }
        }
        return A;   
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // toString():
    // Overrides Object's toString() method.
    public String toString() {
        String out = "";
        // Step through the Matrix rows
        for(int i = 1; i <= getSize(); i++) {
            // If a non-empty row is found -> print the row
            if(row[i].length() > 0) {
                out += (i + ": " + row[i] + "\n"); 
            }
        }
        return out;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // dot(List, list):
    // Helper for dot product of two Lists
    private static double dot(List P, List Q) {
        double dotProd = 0.0;
        P.moveFront();
        Q.moveFront();
        // Loop to step through both List
        while(P.index() >= 0 && Q.index() >= 0) {
            Entry a = (Entry) P.get();
            Entry b = (Entry) Q.get();
            if(a.column > b.column) {
                Q.moveNext();
            }else if(a.column < b.column) {
                P.moveNext();
            } else {
                // A*B = a1*b1 + a2*b2 +....     
                dotProd += (a.value * b.value);
                P.moveNext();
                Q.moveNext();
            }
        }
        return dotProd;
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    // addSub(List, List, boolean):
    // adding/subtracting of two Lists
    // if adder is true then addition of two list is possible
    // if adder is false then subtraction is possible
    // When either Adding or Subtracting, keep moving the curser
    // until you run out of rows or colums, then return result.
    private List addSub(List P, List Q, boolean adder) {
        List L = new List();
        P.moveFront();
        Q.moveFront();
        while(P.index() >= 0 || Q.index() >= 0) {
            if(P.index() >= 0 && Q.index() >= 0) {
                Entry a = (Entry) P.get();
                Entry b = (Entry) Q.get();
                
                if(a.column > b.column) {
                    L.append(new Entry(b.column, (adder ? 1.0 : -1.0) * b.value));
                    Q.moveNext();
                }else if(a.column < b.column) {
                    L.append(new Entry(a.column, a.value));
                    P.moveNext();
                }else if(a.column == b.column) {
                    if((adder && a.value + b.value != 0) || (!adder && a.value - b.value != 0)) {
                        L.append(new Entry(a.column, (adder ? a.value + b.value : a.value - b.value)));
                    }
                    P.moveNext();
                    Q.moveNext();
                }
            }else if(P.index() >= 0) {
                Entry a = (Entry) P.get();
                L.append(new Entry(a.column, a.value));
                P.moveNext();
            }else{
                Entry b = (Entry) Q.get();
                L.append(new Entry(b.column, (adder ? 1.0 : -1.0) * b.value));
                Q.moveNext();
            }
        }
        return L;
    }
}
//--------------------------------------------------------------------------------------------------------