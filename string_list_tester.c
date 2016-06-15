/* string_list_tester.c
  
   SENG 265 - Summer 2016
   Assignment 2
   
   Template for a tester for the StringList datatype.
   
   Do not change any of the function signatures or the contents
   of main() or your submission may be invalid.
  
   B. Bird - 05/26/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_list.h"

#define TEST_FAILED 0
#define TEST_PASSED 1

/* Each of the test functions below should return TEST_FAILED if the test fails
   and TEST_PASSED if the test is passed.
*/
//need to ask bill if it should exit the test once a single things has been failed or if it should try to continue onto the others.
int test1(){
	//First test case: Basic functionality I
	//Test only the StringList_Init, StringList_Size,
	//and StringList_AddFront functions.
	//(Note that since you cannot use StringList_Destroy, this function
	// will produce a memory leak. However, this is acceptable in a testing
	// context).
	
	StringList list;
	StringList_Init(&list);
	if(list.head != NULL){
		printf("failed to intialize head to NULL.\n");
		return TEST_FAILED;
	}
	if(list.tail != NULL){
		printf("failed to intialize tail to NULL.\n");
		return TEST_FAILED;
	}
	
	int size = StringList_Size(&list);
	if(size != 0){
		printf("Incorrectly gave back the size of an empty list, returned: \n%d\n", size);
		return TEST_FAILED;
	}
	
	char *str = "this was the first element inserted into an empty list";
	StringList_AddFront(&list,str);
	
	if(list.head == NULL){
		printf("did not add a new node to the front of an empty list correctly, head = NULL\n");
		return TEST_FAILED;
	}
	if(list.tail == NULL){
		printf("did not add a new node to the front of an empty list correctly, tail = NULL\n");
		return TEST_FAILED;
	}
	
	size = StringList_Size(&list);
	if(size != 1){
		printf("did not properly return the size of a 1 element list, returned: \n%d\n", size);
		return TEST_FAILED;
	}
	
	StringListNode* temp = list.head;
	if(temp->element == NULL){
		printf("did not put the string into the new node(new_node->element = NULL).\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str) == NULL){
		printf("did not properly copy the string into the new node, you copied in: \n%s\n",temp->element);
		printf("the correct output is: \n%s\n",str);
		return TEST_FAILED;
	}
	
	//check if tail is pointing to the first node as well
	//this test possibly redundant and may want to just remove.
	temp = list.tail;
	if(strstr(temp->element,str) == NULL){
		printf("failed to set the tail to the first element in a list containing 1 node.\n");
		return TEST_FAILED;
	}
	// add more items to the list and do some more checks, check if tail is pointing to correct item
	char *str2 = "this was the second element inserted into the list";
	StringList_AddFront(&list,str2);
	
	temp = list.head;
	if(strstr(temp->element,str2) == NULL){
		printf("did not add a second node to the front of a list containing 1 node.\n The head of the list points to: \n%s\n",temp->element);
		return TEST_FAILED;
	}
	
	temp = list.tail;
	if(strstr(temp->element,str) == NULL){
		printf("The tail was changed when adding a second element to the front of the list, it was changed to:\n%s\n",temp->element);
		printf("It should have been: %s\n",str);
		return TEST_FAILED;
	}
	//need to make more cases for the second item added
	size = StringList_Size(&list);
	if(size != 2){
		printf("Did not properly return the size of a 2 item list, returned: %d\n",size);
		return TEST_FAILED;
	}

	//can test iterating through both forwards and backwards and seeing if at any given point it gives back the proper value.
	return TEST_PASSED;
}

int test2(){
	//Second test case: Basic functionality II
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	
	return TEST_PASSED;
}

int test3(){
	//Third test case: Basic functionality III
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	//Use a different methodology for this test than test 2.
	return TEST_PASSED;
}

int test4(){
	//Fourth test case: List membership I
	//Test the StringList_GetIndex function, using any of the functions
	//tested in previous test cases if necessary.
	return TEST_PASSED;
}

int test5(){
	//Fifth test case: List membership II
	//Test the StringList_InList function, using any of the functions
	//tested in previous test cases if necessary.
	return TEST_PASSED;
}

int test6(){
	//Sixth test case: Deletion I
	//Test the StringList_Remove and StringList_RemoveNode functions,
	//using any of the functions tested in previous test cases if necessary.
	return TEST_PASSED;
}

int test7(){
	//Seventh test case: Deletion II
	//Test the StringList_Remove, StringList_RemoveNode and StringList_Destroy functions,
	//using any of the functions tested in previous test cases if necessary.
	//Use a different methodology for this test than test 6.
	return TEST_PASSED;
}

int test8(){
	//Eighth test case: Stress Test
	//Test all of the methods of the StringList, in an attempt to simulate the
	//actual use of the data structure in practice. For logistical reasons, 
	//keep in mind that your test must complete within 30 seconds for the 
	//automated system, so some types of exhaustive testing are not practical
	//here.
	
	
	//char *strings[]{}
	//try an array of pointers to strings and then fill that array and then fill the list.
	return TEST_PASSED;
}




/* Do not change any of the code below, to ensure consistency during all vs. all testing */

void show_usage(){
	fprintf(stderr,"Usage: ./string_list_tester <test_number>\n");
	fprintf(stderr,"Where <test_number> is an integer between 1 and 8.\n");
}

int main(int argc, char** argv){
	if (argc < 2){
		show_usage();
		return 0;
	}
	//The atoi function converts a string to an integer (and returns 0 if
	//the conversion fails).
	int test_number = atoi(argv[1]);
	
	if (test_number <= 0 || test_number >= 8){
		show_usage();
		return 0;
	}
	
	int result = 1;
	switch(test_number){
		case 1:
			result = test1();
			break;
		case 2:
			result = test2();
			break;
		case 3:
			result = test3();
			break;
		case 4:
			result = test4();
			break;
		case 5:
			result = test5();
			break;
		case 6:
			result = test6();
			break;
		case 7:
			result = test7();
			break;
		case 8:
			result = test8();
			break;
	}
	
	if (result == TEST_PASSED){
		printf("\nTEST PASSED\n");
	}else{
		printf("\nTEST FAILED\n");
	}
	
	return 0;
}