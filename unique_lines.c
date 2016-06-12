/* unique_lines.c
  
   SENG 265 - Summer 2016
   Assignment 2
   
   A program which reads lines from standard input and deletes duplicate
   lines. All non-duplicate lines are printed to standard output.
   
   The program assumes that all lines have length at most MAX_LINE (defined below).
  
   B. Bird - 05/26/2016
*/

#include <stdio.h>
#include <string.h>
#include "string_list.h"

#define MAX_LINE 1000

int main(){

	//To keep track of lines that have already been seen, keep all
	//of the input lines in a linked list.
	StringList InputLines;
	
	StringList_Init(&InputLines);
	
	char line[MAX_LINE+1];
	
	while(fgets(line,MAX_LINE+1,stdin)){
		if (StringList_InList(&InputLines, line)){
			//Duplicate line: ignore
		}else{
			StringList_AddBack(&InputLines, line);
			//No need to add \n to the printf since the line
			//array will contain a \n character from fgets.
			printf("%s",line);
		}
	}
	
	StringList_Destroy(&InputLines);

}

