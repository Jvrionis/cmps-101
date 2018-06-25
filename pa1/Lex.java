//--------------------------------------------------------------------
// Lex.java
// James Michael Vrionis
// JVrionis
// 1-20-17
// Programming Assignment 1
// Takes an input file and indirectly organizes it
// in lexicographic order into an ouput file.
// 
//--------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Lex {
	public static void main(String [] args) throws IOException {
		// variables 
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] token = null;
		int lineNumber = -1;

		// Check that there are two command line arguments. 
		// Quit with a usage message to stderr if more than or less 
		// than two strings are given on the command line.
		if(args.length != 2 ) {
			System.err.println(
				"Lex Error: Two strings must be given as command line agruments");
			System.exit(1);
		}
		
		// runs if command line arguments = 2.
		in = new Scanner(new File(args[0]));

		// Count the lines of the file
		int lines = 0;
		while(in.hasNextLine()) {
			++lines;
			in.nextLine();
		}

		in.close();
		in = null;

		List list = new List();
		token = new String[lines];
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		while(in.hasNextLine()) {
			token[++lineNumber] = in.nextLine();
		}

		// first line of input file into the already sorted list
		list.append(0);

		// InsertionSort on List of with length-1 elements
		for(int j = 1; j< token.length; ++j) {
			String temp = token[j];
			int i = j-1;
			list.moveBack();

			// Compare current line with each line in the list
			while( i>=0 && temp.compareTo(token[list.get()]) <= 0) {
			    --i;
				list.movePrev();
			}
			if(list.index() >= 0) {
				list.insertAfter(j);
			}	
			else {
				list.prepend(j);
			}
		}
		list.moveFront();

		while(list.index() >= 0) {
			out.println(token[list.get()]);
			list.moveNext();
		}

		// close(): File read and write
		in.close();
		out.close();
	}
}
