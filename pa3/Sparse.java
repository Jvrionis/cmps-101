//---------------------------------------------------------
// James Michael Vrionis
// JVrionis
// 2-15-17
// Programming Assignment 3
//
// Sparse.java: The top level client module for this project. 
// It takes two command line arguments: input file and output
// file, respectively. Input file must begin with a blank 
// single line containing 3 integers n, a, and b (separated 
// by spaces). The Second line will be blank, and the 
// following a lines will specify non-zero entries of a 
// nxn matrix A, of the form (int, int, double) which is 
// row, column, value. After another blank line, there will 
// be b non-zero entries. All of thise will be written to 
// an output file. 
//
// 
//---------------------------------------------------------

//--------------------------------------------------------------------------------------------------------        

import java.io.*;
import java.util.Scanner;

//--------------------------------------------------------------------------------------------------------        

//--------------------------------------------------------------------------------------------------------        
public class Sparse {
    public static void main(String[] args) throws IOException {
      
        Scanner in = null;
        PrintWriter out = null;
        String line = null;
        String[] token = null;
        int i, n, lineNumber = 0;

        // Check that there are two command line arguments. 
        // Quit with a usage message to stderr if more than or less 
        // than two strings are given on the command line.
        if(args.length < 2){
            System.err.println("Sparse Error: Sparse <in_file> <out_file>");
            System.exit(1);
        }
        // filename/path given from command line 
        in = new Scanner(new File(args[0]));
        int lineA, lineB;

        // Add extra space 
        // Split line around that extra space
        line = in.nextLine()+" ";    
        token = line.split("\\s+");  
        
        // Initialize Matrix A and B and convert into ints
        Matrix A = new Matrix(Integer.parseInt(token[0]));
        Matrix B = new Matrix(Integer.parseInt(token[0]));
        
        lineA = Integer.parseInt(token[1]) + 2;
        lineB = Integer.parseInt(token[2]) + lineA + 1;
        
        // Read in file and out file 
        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));
        
        // keep reading in 
        // Add extra space so split works right
        // Split line around the white space       
        while( in.hasNextLine() ){
            lineNumber++;
            line = in.nextLine()+" ";    
            token = line.split("\\s+");  
            // Populate A and B with int, int, double 
            if(lineNumber > 2 && lineNumber <= lineA) {
                A.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            }
            if(lineNumber > (lineA + 1) && lineNumber <= lineB) {
                B.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            } 
            // used while i was testing for errors
            // can't use because of this condition if(!found && x != 0.0) {
            // and this condition if(row[i].index() == -1) within Matrix.java
            // else{
            //     B.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            // }
         }
//--------------------------------------------------------------------------------------------------------        


//--------------------------------------------------------------------------------------------------------        
      // Print Operations to file:
      out.println();
      out.println("--- Non-zeroz entries for A ----------------"); 
      out.println("A has " + A.getNNZ() + " non-zero entries:"); 
      out.println(A);                                            
                                                                   
      out.println("--- Non-zeroz entries for B ----------------"); 
      out.println("B has " + B.getNNZ() + " non-zero entries:");
      out.println(B);
      out.println("--------------------------------------------");
      out.println("--------------------------------------------");

      out.println();
      out.println();
      out.println("--- (1.5)*A --------------------------------");
      out.println(A.scalarMult(1.5));
      out.println("--------------------------------------------");

      out.println("--- A+B ------------------------------------");
      out.println(A.add(B));
      out.println("--------------------------------------------");

      out.println("--- A+A ------------------------------------");
      out.println(A.add(A));
      out.println("--------------------------------------------");

      out.println("--- B-A ------------------------------------");
      out.println(B.sub(A));
      out.println("--------------------------------------------");

      out.println("--- A-A ------------------------------------");
      out.println(A.sub(A));
      out.println("--------------------------------------------");

      out.println("--- Transpose(A) ---------------------------");
      out.println(A.transpose());
      out.println("--------------------------------------------");

      out.println("--- A*B ------------------------------------");
      out.println(A.mult(B));
      out.println("--------------------------------------------");
      
      out.println("--- B*B ------------------------------------");
      out.println(B.mult(B));
      out.println("--------------------------------------------");

//--------------------------------------------------------------------------------------------------------        

//--------------------------------------------------------------------------------------------------------              
      // close(): File read and write
      in.close();
      out.close();

//--------------------------------------------------------------------------------------------------------           

   }
}
