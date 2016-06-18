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
//what does different methodology mean?
//
int test1(){
	//First test case: Basic functionality I
	//Test only the StringList_Init, StringList_Size,
	//and StringList_AddFront functions.
	//(Note that since you cannot use StringList_Destroy, this function
	// will produce a memory leak. However, this is acceptable in a testing
	// context).
	//1 and no element tests
	printf("testing StringList_Init and StringList_Size...\n");
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
	printf("testing StringList_AddFront as well...\n");
	printf("testing on 1 element\n");
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
	// 2 element tests
	printf("testing on 2 elements\n");
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
	size = StringList_Size(&list);
	if(size != 2){
		printf("Did not properly return the size of a 2 item list, returned: %d\n",size);
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(temp == NULL){
		printf("Did not assign the previous pointer from the first element added at the front of the list to the second element added to the front of the list\n that is element 1 previous = NULL but should equal element 2.");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str2) == NULL){
		printf("Did not assign the previous pointer from the last element in the list to the first element, it points to element: \n%s\n",temp->element);
		return TEST_FAILED;
	}
	temp = list.head;
	if(temp->next == NULL){
		printf("Did not assign the next pointer from the first element in the list to the second, its value is NULL.\n");
		return TEST_FAILED;
	}
	//3 element tests
	printf("testing on 3 elements\n");
	char *str3 = "this was the third element inserted into the list.";
	StringList_AddFront(&list,str3);
	size = StringList_Size(&list);
	if(size != 3){
		printf("Did not properly return the size of a 3 element list, returned: %d\n",size);
		return TEST_FAILED;
	}
	
	temp = list.head;
	if(strstr(temp->element,str3) == NULL){
		printf("The first element in the list does not point to the newest element in the list, it points to:\n%s\n", temp->element);
		printf("The element should have been: \n%s\n",str3);
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str2) == NULL){
		printf("The first element in the list added from the front does not point to the second element added, it points to:\n%s\n",temp->element);
		printf("It should point to:\n%s\n",str2);
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str) == NULL){
		printf("The second element in added into the front of a list of size 3 does not point to the last element it points to:\n%s\n",temp->element);
		printf("It should point to: \n%s\n",str);
		return TEST_FAILED;
	}
	
	temp = list.tail;
	temp = temp->previous;
	if(strstr(temp->element,str2) == NULL){
		printf("The last element in the list does not point back to the element to the second element added from the front\n it points to: %s\n",temp->element);
		printf("It should point to: \n%s\n",str2);
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element,str3) == NULL){
		printf("The middle element in a 3 element list does not point back to the last element added to the front of the list \nit points to: %s\n",temp->element);
		printf("It should point to: \n%s\n",str3);
		return TEST_FAILED;
	}

	return TEST_PASSED;
}

//this test glassbox testing
int test2(){
	//Second test case: Basic functionality II
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	printf("testing StringList_AddBack...\n");
	StringList list;
	StringList_Init(&list);
	printf("tesing on 1 element\n");
	char *str = "First string added to the list, it was added from the back";
	StringList_AddBack(&list,str);
	if(list.head == NULL){
		printf("failed to point the head to the first element added to an empty list using AddBack\n");
		return TEST_FAILED;
	}
	if(list.tail == NULL){
		printf("failed to point the tail to the first element added to an empty list using AddBack.\n");
		return TEST_FAILED;
	}
	int size = StringList_Size(&list);
	if(size != 1){
		printf("Did not correctly give back the size of a 1 element list, returned: %d",size);
		return TEST_FAILED;
	}
	printf("testing on 2 elements\n");
	char *str2 = "Second string added to the list, it was added from the back";
	StringList_AddBack(&list,str2);
	size = StringList_Size(&list);
	if(size != 2){
		printf("Did not correctly give back the size of a 2 element list, returned: %d",size);
		return TEST_FAILED;
	}
	
	StringListNode* temp;
	temp = list.tail;
	if(strstr(temp->element,str2) == NULL){
		printf("The tail does not point to the most recent element added from the back, it points to:\n%s\n",temp->element);
		printf("It should be pointing to: %s\n",str2);
		return TEST_FAILED;
	}
	if(temp->previous == NULL){
		printf("did not set the previous pointer on last element added from the back\n");
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element,str) == NULL){
		printf("The last element added from the back previous pointer does not point back to the proper element it points to:\n%s\n",temp->element);
		printf("It should poin to: %s\n",str);
		return TEST_FAILED;
	}
	
	return TEST_PASSED;
}
//this test blackbox testing
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
//this test glassbox testing
int test6(){
	//Sixth test case: Deletion I
	//Test the StringList_Remove and StringList_RemoveNode functions,
	//using any of the functions tested in previous test cases if necessary.
	return TEST_PASSED;
}
//this test blackbox testing
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
	
	//test adding empty strings and seeing how it handles that
	//char *strings[]{}
	//try an array of pointers to strings and then fill that array and then fill the list.
	//need to use sprintf to make the strings 
	//or can have it so that each string is of different length
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
	
	if (test_number <= 0 || test_number > 8){
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