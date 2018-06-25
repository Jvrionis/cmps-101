/**********************************************************************
* James Michael Vrionis
* JVrionis
* 1-24-17
* Programming Assingment 2
* Lex.c : A client program that takes an input file and 
* indirectly organizes it in lexicographic order into an 
* ouput file.  
**********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LENGTH 256

int main(int argc, char* argv[]) {

	/* vars */
    int count = 0;
    FILE *in, *out;
    char line[MAX_LENGTH];
	List list = NULL;

    /* Open files: Read and Write */
    in = fopen(argv[1],"r");
    out = fopen(argv[2],"w");
    
    if(in == NULL) {
        printf(
            "Lex Error (1): unable to read file %s\n",argv[1]);
        exit(1);
    }

    if(out == NULL) {
        printf(
            "Lex Error (2): unable to write file %s\n",argv[2]);
        exit(1);
    }

    /* check to see if command line arguments are of the correct form */
    if(argc != 3) {
        // printf( "Lex Error (3): %s <input_file> <output_file> expected as command line agruments\n", argv[0]);
    	printf(
            "Lex Error (3): %s <input_file> <output_file> \
                expected as command line agruments\n", argv[0]);
    	exit(1);
    }
	
	/* Check that there are two command line arguments. 
	 * Quit with a usage message to stderr if more than or less 
	 * than two strings are given on the command line.
	 
	if(args.length != 2 ) {
		System.err.println(
        "Lex Error: Two strings must be given as command line agruments");
		System.exit(1);
	}
	*/

	/* Read, count and then print lines */
    while(fgets(line,MAX_LENGTH,in) != NULL){
        count++;
	}		

	/* File pointer set to begining of file */
	rewind(in);

	char lines[count-1][MAX_LENGTH];
	int inner = -1;

	/* Traverse through while copying file lines into string array */
	while( fgets(line,MAX_LENGTH,in) != NULL){
		strcpy(lines[++inner],line);
	}

	/* New List ADT */
	//List list = newList();
    list = newList();

	/* First line of input file into the already sorted list */
	append(list,0);


	/* InsertionSort(): 
	 * InsertionSort on List of with length-1 elements 
	 * list.index() >= 0 insertAfter otherwise put the 
	 * element in the front of the list
	 */
	for(int j = 1; j< count; ++j) {
		char* temp = lines[j];
		int i = j-1;
		moveBack(list); /* set list to back to the back */

		/* Compare current line with each line in the list */
		while( i>=0 && strcmp(temp,lines[get(list)]) <= 0) {
		    --i;
			movePrev(list); /* traverse list from right to left */
		}
		if(index(list) >= 0) {
            insertAfter(list,j);
        }	
		else {
            prepend(list,j);
        }
    }
    
	/* Reset list index to the front of the list */
    moveFront(list);

	/* Print to file the list in correct order */
	while(index(list) >= 0) {
		fprintf(out, "%s", lines[get(list)]);
		moveNext(list);
	}

	/* close(): File read and write */
	fclose(in);
	fclose(out);

	/* free list ADT and set to NULL*/
	freeList(&list);
	list = NULL;


	return(EXIT_SUCCESS);
}
