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

/*
	IMPORTANT TO READ WHEN TRYING TO DEBUG AND CONFUSED ON THE OUTPUT
	For all these tests the strings in the list have been made as to explain where they are in the list and from where they were added, or there is a print statement
	in the test explaining where they were added from. As such when certain tests are failed they will print out what string (that is which node) your function returned
	and give what the expected string was (that is the expected node)
*/
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
	temp = list.head;
	if(strstr(temp->element,str) == NULL){
		printf("The head of the list does not point to the first element added from the back it was changed after adding to the back, it points to:\n%s\n",temp->element);
		printf("it should point to: %s\n",str);
		return TEST_FAILED;
	}
	if(temp->next == NULL){
		printf("the first element in the list that is head->next does not point to the next element, when it was added from the back it points to NULL\n");
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str2) == NULL){
		printf("the first element in the list does not point to the second element when both were added from the back, it points to: \n%s\n",temp->element);
		printf("it should point to: %s\n",str2);
		return TEST_FAILED;
	}
	printf("testing on 3 elements\n");
	char *str3 = "third string added to the list, it was added to the back";
	StringList_AddBack(&list,str3);
	size = StringList_Size(&list);
	if(size != 3){
		printf("did not add a third element to the list\n");
		return TEST_FAILED;
	}
	temp = list.head;
	temp = temp->next;
	if(temp->next == NULL){
		printf("did not set the next pointer of the second most recent element added from the back to the most recent element\n");
		return TEST_FAILED;
	}
	temp = list.tail;
	if(strstr(temp->element,str3) == NULL){
		printf("The tail does not point to the correct element when adding from the back, or the string was copied incorrectly, it points to:\n%s\n",temp->element);
		printf("it should point to: %s\n",str3);
		return TEST_FAILED;
	}
	if(temp->previous == NULL){
		printf("this previous pointer of the most recent element added to the back points to NULL\n");
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element, str2) == NULL){
		printf("the most recent element added to the back of the list does not point back to he proper element it points to:\n%s\n",temp->element);
		printf("it should point to: %s\n",str2);
	}
	
	printf("adding an element to the front\n");
	char *str4 = "fourth string added to the list, it was added to the front";
	StringList_AddFront(&list,str4);
	temp = list.head;
	if(temp->next == NULL){
		printf("When adding to the front of the list after adding from the back 3 times, list.head->next = NULL\n");
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str) == NULL){
		printf("The first element added to the front of the list does not point forwards to the first element added from the back it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str);
		return TEST_FAILED;
	}
	if(temp->previous == NULL){
		printf("The first element added from the back of the list does not point back towards the first element added from the front it points to NULL\n");
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element,str4) == NULL){
		printf("The first element added from the back of the list does not point back towards the first element added from the front it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n", str4);
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

int test3(){
	//Third test case: Basic functionality III
	//Test only the StringList_Init, StringList_Size,
	//StringList_AddFront and StringList_AddBack functions.
	//Use a different methodology for this test than test 2.
	StringList list;
	StringList_Init(&list);
	printf("Testing adding elements from the front then adding to the back...\n");
	char *str = "This is the first element added from the front";
	char *str2 = "This is the second element added from the front";
	char *str3 = "This is the third element added from the front";
	char *str4 = "This is the first element added from the back";
	char *str5 = "This is the fourth element added from the front";
	char *str6 = "This is the second element added from the back";

	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddBack(&list,str4);
	int size = StringList_Size(&list);
	if(size != 4){
		printf("failed to add 3 elements to the front and then 1 to the back, or incorrectly gave back the size on a 4 element list, size returned %d\n",size);
		return TEST_FAILED;;
	}
	StringListNode* temp;
	temp = list.tail;
	if(temp->previous == NULL){
		printf("The element added to the back does not point back to the first element added from the front it points to NULL");
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element,str) == NULL){
		printf("The element added to the back does not point back to the first element added from the front it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str);
		return TEST_FAILED;
	}
	if(temp->next == NULL){
		printf("The first element added from the front does not point forward to the first element added from the back it points to NULL\n");
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str4) == NULL){
		printf("The first element added from the front does not point forward to the first element added fromt the back it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str4);
	}
	StringList_AddFront(&list,str5);
	size = StringList_Size(&list);
	if(size != 5){
		printf("Failed to add another element to the front of the list of a 4 elements, or incorrectly gave back the size on a 5 element list, size returned %d\n",size);
		return TEST_FAILED;
	}
	StringList_AddBack(&list,str6);
	size = StringList_Size(&list);
	if(size != 6){
		printf("Failed to add another element to the back of the list of a 5 elements, or incorrectly gave back the size on a 6 element list, size returned %d\n",size);
		return TEST_FAILED;
	}
	temp = list.head;
	if(strstr(temp->element,str5) == NULL){
		printf("The head does not point to the most recent element added from the front after both an addfront and an addback have occured it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str5);
		return TEST_FAILED;
	}
	temp = list.tail;
	if(strstr(temp->element,str6) == NULL){
		printf("The tail does not point to the most recent element added from the back after both an addfront and an addback have occured it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str6);
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

int test4(){
	//Fourth test case: List membership I
	//Test the StringList_GetIndex function, using any of the functions
	//tested in previous test cases if necessary.
	StringList list;
	StringList_Init(&list);
	printf("Testing StringList_GetIndex...\n");

	StringListNode* temp;
	//remove these
	temp = StringList_GetIndex(&list,0);
	if(temp != NULL){
		printf("you don messed up on an empty list i = 0\n");
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,1);
	if(temp != NULL){
		printf("you don messed up on an empty list i = 1\n");
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,87);
	if(temp != NULL){
		printf("you don messed up on an empty list i = 87\n");
		return TEST_FAILED;
	}
	//down to here
	char *str = "This is the first element added from the front";
	char *str2 = "This is the second element added from the front";
	char *str3 = "This is the third element added from the front";
	char *str4 = "This is the first element added from the back";
	char *str5 = "This is the fourth element added from the front";
	char *str6 = "This is the second element added from the back";
	printf("testing on a 1 element list\n");
	StringList_AddFront(&list,str);
	temp = StringList_GetIndex(&list,0);
	if(temp == NULL){
		printf("returned NULL when getting the node at index 0 of a 1 element list\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str) == NULL){
		printf("Did not return the proper element at index 0 of a 1 element list, returned:\n%s\n",temp->element);
		printf("It should have returned: %s\n",str);
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,1);
	if(temp != NULL){
		printf("returned a non-NULL value when getting the node at index 1 of a 1 element list, i.e. an out of bounds index\n reminder the first element of the list should be at index 0 not 1\n");
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,2);
	if(temp != NULL){
		printf("returned a non-NULL value when trying to index an out of bounds index, trying to get the value at index 2 on a 1 element list\n");
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,50);
	if(temp != NULL){
		printf("returned a non-NULL value when trying to index an out of bounds index, trying to get the value at index 50 on a 1 element list\n");
		return TEST_FAILED;
	}
	printf("testing on a 2 element list\n");
	StringList_AddFront(&list,str2);
	temp = StringList_GetIndex(&list,1);
	if(temp == NULL){
		printf("returned NULL when trying to get the element at index 1 of a 2 element list\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str) == NULL){
		printf("did not return the correct node at index 1 of a 2 element list, returned:\n%s\n",temp->element);
		printf("should have returned,: %s\n",str);
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,2);
	if(temp != NULL){
		printf("returned a non-NULL value when trying to index and out of bounds index, trying to get the vaue at index 2 on a 2 element list\n");
		return TEST_FAILED;
	}
	printf("testing on a 6 element list\n");
	StringList_AddFront(&list,str3);
	StringList_AddBack(&list,str4);
	StringList_AddFront(&list,str5);
	StringList_AddBack(&list,str6);
	temp = StringList_GetIndex(&list,5);
	if(temp == NULL){
		printf("returned NULL when trying to get the node at index 5 of a 6 element list\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str6) == NULL){
		printf("returned the wrong node when getting the node at index 5 of a 6 element list, returned:\n%s\n",temp->element);
		printf("It should of returned: %s\n",str6);
		return TEST_FAILED;
	}
	temp = StringList_GetIndex(&list,0);
	if(temp == NULL){
		printf("returned NULL when trying to get the node at index 0 of a 6 element list\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str5) == NULL){
		printf("returned the wrong node when getting the node at index 0 of a 6 element list, returned:\n%s\n",temp->element);
		printf("It should of returned: %s\n",str5);
		return TEST_FAILED;
	}

	temp = StringList_GetIndex(&list,1);
	if(temp == NULL){
		printf("returned NULL when trying to get the node at index 1 of a 6 element list\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str3) == NULL){
		printf("returned the wrong node when getting the node at index 1 of a 6 element list, returned:\n%s\n",temp->element);
		printf("It should of returned: %s\n",str3);
		return TEST_FAILED;
	}
	return TEST_PASSED;
}
//need to make sure that it returns the first one, by checking the node before it is the correct node
int test5(){
	//Fifth test case: List membership II
	//Test the StringList_InList function, using any of the functions
	//tested in previous test cases if necessary.
	
	StringList list;
	StringList_Init(&list);
	printf("Testing StringList_InList...\n");
	StringListNode* temp;
	
	char *empty = ""; //remove
	char *str = "This is the first element added from the front";
	char *str2 = "This is the second element added from the front";
	char *str3 = "This is the third element added from the front";
	char *str4 = "This is the fourth element added from the front";
	char *str5 = "This is the fifth element added from the front";
	char *str6 = "This is the sixth element added from the front";
	char *not_In = "This string is not in the list";
	//remove from here
	temp = StringList_InList(&list,empty);
	if(temp != NULL){
		printf("empty list first dun goof");
		return TEST_FAILED;
	}
	temp = StringList_InList(&list,str);
	if(temp != NULL){
		printf("empty list dun good second");
		return TEST_FAILED;
	}
	//to here
	printf("testing on a 2 element list with the search element in the list only once\n");
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	temp = StringList_InList(&list,str2);
	if(temp == NULL){
		printf("returned NULL when the string was in the list\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str2) == NULL){
		printf("returned the wrong node returned: %s\n", temp->element);
		printf("It should of returned: %s\n",str2);
		return TEST_FAILED;
	}
	
	printf("testing on an 8 element list, with multiple elements containing the same string\n");
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	StringList_AddFront(&list,str5);
	StringList_AddFront(&list,str6);
	StringList_AddFront(&list,str2);
	
	temp = StringList_InList(&list,str2);
	temp = temp->next;
	if(strstr(temp->element,str6) == NULL){
		printf("Did not return the first element containg the search string\n");
		return TEST_FAILED;
	}
	printf("testing searching for a string that is not in the list\n");
	temp = StringList_InList(&list,not_In);
	if(temp != NULL){
		printf("did not return NULL when searching for an element that is not in the list, returned:\n%s\n",temp->element);
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

int test6(){
	//Sixth test case: Deletion I
	//Test the StringList_Remove and StringList_RemoveNode functions,
	//using any of the functions tested in previous test cases if necessary.
	
	StringList list;
	StringList_Init(&list);
	printf("Testing StringList_Remove and StringList_RemoveNode...\n");
	StringListNode* temp;
	char *str = "This is the first element added from the front";
	char *str2 = "This is the second element added from the front";
	char *str3 = "This is the third element added from the front";
	char *str4 = "This is the fourth element added from the front";
	char *str5 = "This is the fifth element added from the front";
	char *str6 = "This is the sixth element added from the front";
	char *not_In = "This string is not in the list";
	StringList_AddFront(&list,str);
	int flag = StringList_Remove(&list,str);
	printf("testing remove on a 1 element list\n");
	if(list.head != NULL && list.tail != NULL){
		printf("Did not remove the only node in a 1 element list correctly");
		return TEST_FAILED;
	}
	
	printf("testing removeNode on a 1 element list\n");
	StringList_AddFront(&list,str);
	temp = list.head;
	StringList_RemoveNode(&list,temp);
	if(list.head != NULL && list.tail != NULL){
		printf("Did not remove the only node in a 1 element list correctly");
		return TEST_FAILED;
	}
	
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	StringList_AddFront(&list,str5);
	StringList_AddFront(&list,str6);
	//testing removing the head
	printf("testing remove and removeNode on removing the head of a multi-element list\n");
	flag = StringList_Remove(&list,str6);
	temp = list.head;
	if(temp == NULL){
		printf("Set the head to NULL when removing the first element in the list using Remove\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str5) == NULL){
		printf("we removed: %s\n",str6);
		printf("When removing the head using Remove did not set head to the correct element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str5);
		return TEST_FAILED;
	}
	StringList_RemoveNode(&list,temp);
	temp = list.head;
	if(temp == NULL){
		printf("Set the head to NULL when removing the first element in the list using RemoveNode\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str4) == NULL){
		printf("we removed: %s\n",str5);
		printf("When removing the head using RemoveNode did not set head to the correct element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str4);
		return TEST_FAILED;
	}
	//testing removing the tail
	printf("testing remove and removeNode on removing the tail of a multi-element list\n");
	flag = StringList_Remove(&list,str);
	temp = list.tail;
	if(temp == NULL){
		printf("Set the tail to NULL when removing the last element in the list using Remove\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str2) == NULL){
		printf("we removed: %s\n",str);
		printf("When removing the tail using Remove did not set tail to the correct element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str2);
		return TEST_FAILED;
	}
	temp = list.tail;
	StringList_RemoveNode(&list,temp);
	temp = list.tail;
	if(temp == NULL){
		printf("Set the tail to NULL when removing the last element in the list using RemoveNode\n");
		return TEST_FAILED;
	}
	if(strstr(temp->element,str3) == NULL){
		printf("we removed: %s\n",str2);
		printf("When removing the tail using RemoveNode did not set tail to the correct element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str3);
		return TEST_FAILED;
	}
	StringList_AddBack(&list,str2);
	StringList_AddBack(&list,str);
	StringList_AddFront(&list,str5);
	StringList_AddFront(&list,str6);
	//removing a node that is in the middle of the list
	printf("removing a node that is in the middle of a 6 and then 5 element list all added from the front, using removeNode and remove\n");
	//remove function
	flag = StringList_Remove(&list,str3);
	temp = StringList_InList(&list,str4);
	if(temp->next == NULL){
		printf("when removing an element in the middle of the list using remove, did not set the element previous to the removed node to point at the next element, it points at NULL\n");
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str2) == NULL){
		printf("we removed: %s\n",str3);
		printf("When removing the 4th element using remove the element behind it points forward to the wrong element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str2);
		return TEST_FAILED;
	}
	if(temp->previous == NULL){
		printf("when removing an element in the middle of the list using remove, did not set the element in front of the removed node to point at the previous element, it points at NULL\n");
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element,str4) == NULL){
		printf("we removed: %s\n",str3);
		printf("When removing the 4th element using remove the element in front of it points back to the wrong element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str4);
		return TEST_FAILED;
	}
	
	//removeNode function
	temp = StringList_InList(&list,str4);
	StringList_RemoveNode(&list,temp);
	temp = StringList_InList(&list,str5);
	if(temp->next == NULL){
		printf("when removing an element in the middle of the list using removeNode, did not set the element previous to the removed node to point at the next element, it points at NULL\n");
		return TEST_FAILED;
	}
	temp = temp->next;
	if(strstr(temp->element,str2) == NULL){
		printf("we removed: %s\n",str4);
		printf("When removing the 3rd element using removeNode the element behind it points forward to the wrong element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str2);
		return TEST_FAILED;
	}
	if(temp->previous == NULL){
		printf("when removing an element in the middle of the list using removeNode, did not set the element in front of the removed node to point at the previous element, it points at NULL\n");
		return TEST_FAILED;
	}
	temp = temp->previous;
	if(strstr(temp->element,str5) == NULL){
		printf("we removed: %s\n",str4);
		printf("When removing the 3rd element using removeNode the element in front of it points back to the wrong element it points to:\n%s\n",temp->element);
		printf("It should point to: %s\n",str5);
		return TEST_FAILED;
	}
	
	//testing remove on a string that is not in the list
	printf("testing remove on an element that is not in the list\n");
	int size = StringList_Size(&list);
	flag = StringList_Remove(&list,not_In);
	
	if(size != 4){
		printf("remove, removed a node when given a string that was not in the list\n");
		return TEST_FAILED;
	}
	if(flag){
		printf("Remove returned true when it did not remove a node");
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

int test7(){
	//Seventh test case: Deletion II
	//Test the StringList_Remove, StringList_RemoveNode and StringList_Destroy functions,
	//using any of the functions tested in previous test cases if necessary.
	//Use a different methodology for this test than test 6.
	
	StringList list;
	StringList_Init(&list);
	printf("Testing StringList_Remove, StringList_RemoveNode, and StringList_Destroy...\n");
	char *str = "This is the first element added from the front";
	char *str2 = "This is the second element added from the front";
	char *str3 = "This is the third element added from the front";
	char *str4 = "This is the fourth element added from the front";
	char *str5 = "This is the fifth element added from the front";
	char *str6 = "This is the sixth element added from the front";
	
	//destroy tests
	printf("Testing Destroy\n");
	StringList_AddFront(&list,str);
	StringList_Destroy(&list);
	if(list.head != NULL && list.tail != NULL){
		printf("Did not properly destroy a 1 element, list head !=NULL or tail != NULL\n");
		return TEST_FAILED;
	}
	
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	StringList_AddFront(&list,str5);
	StringList_AddFront(&list,str6);
	StringList_Destroy(&list);
	if(list.head != NULL && list.tail != NULL){
		printf("Did not properly destroy a multi-item list, head !=NULL or tail != NULL\n");
		return TEST_FAILED;
	}
	
	//remove 
	printf("testing remve on a 1 element list\n");
	//testing remove on removing an element from a 1 element list
	StringList_AddFront(&list,str);
	int flag = StringList_Remove(&list,str);
	int size = StringList_Size(&list);
	if(!flag){
		printf("remove reported that is did not remove a node from a one element list when the string given was in the list\n");
		if(size != 0){
			printf("remove actually did not remove a node containing a string that was in the list, but reported that it did\n");
			return TEST_FAILED;
		}
		return TEST_FAILED;
	}

	StringListNode* temp;
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	StringList_AddFront(&list,str5);
	StringList_AddFront(&list,str6);
	//removeNode, removing an element in the middle of the list
	printf("testing removeNode on an element in the middle of the list\n");
	temp = StringList_InList(&list,str4);
	StringList_RemoveNode(&list,temp);
	temp = StringList_InList(&list,str4);
	if(temp != NULL){
		printf("removeNode did not properly remove a given node in the middle of the list, the node is still in the list\n");
		return TEST_FAILED;
	}
	//remove, removing an element in the middle of the list
	flag = StringList_Remove(&list,str3);
	temp = StringList_InList(&list,str3);
	if(!flag){
		printf("remove reported that is did not remove a node in the middle of a list when the string given was in the list\n");
		if(temp != NULL){
			printf("remove actually did not remove the node from the list\n");
			return TEST_FAILED;
		}
		return TEST_FAILED;
	}
	
	//removeNode removing an element at the tail
	printf("testing removeNode on an element at the tail of the list\n");
	temp = StringList_InList(&list,str);
	StringList_RemoveNode(&list,temp);
	temp = StringList_InList(&list,str);	
	if(temp != NULL){
		printf("removeNode did not properly remove a given node at the tail of the list, the node is still in the list\n");
		return TEST_FAILED;
	}
	//remove, removing an element at the head of the list
	printf("testing remove on an element at the head of the list\n");
	flag = StringList_Remove(&list,str6);
	temp = StringList_InList(&list,str6);
	if(!flag){
		printf("remove reported that is did not remove a node at the head of the list when the string given was in the list\n");
		if(temp != NULL){
			printf("remove actually did not remove the node from the list\n");
			return TEST_FAILED;
		}
		return TEST_FAILED;
	}
	//destroying the rest of the list
	printf("destroying the remaining elements in the list\n");
	StringList_Destroy(&list);
	size = StringList_Size(&list);
	if(size != 0){
		printf("Destroy did not properly destroy the list\n");
		return TEST_FAILED;
	}
	if(list.tail != NULL){
		printf("did not set the tail to NULL when destroying the list\n");
		return TEST_FAILED;
	}
	if(list.head != NULL){
		printf("did not set the tail to NULL when destroying the list\n");
		return TEST_FAILED;
	}
	return TEST_PASSED;
}

//the order of the strings in this test start to get out of order so will no be printing them to stdout
int test8(){
	//Eighth test case: Stress Test
	//Test all of the methods of the StringList, in an attempt to simulate the
	//actual use of the data structure in practice. For logistical reasons, 
	//keep in mind that your test must complete within 30 seconds for the 
	//automated system, so some types of exhaustive testing are not practical
	//here.
	StringListNode* temp;
	StringList list;
	StringList_Init(&list);
	printf("Running stress test\n");
	char *str = "This is the first element added from the front";
	char *str2 = "This is the second element added from the front";
	char *str3 = "This is the third element added from the front";
	char *str4 = "This is the fourth element added from the front";
	char *str5 = "This is the fifth element added from the front";
	char *str6 = "This is the sixth element added from the front";
	char *str7 = "This is the first element added from the back";
	char *str8 = "This is the second element added from the back";
	StringList_AddFront(&list,str3);
	StringList_AddBack(&list,str7);
	StringList_AddBack(&list,str8);
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str5);
	StringList_AddFront(&list,str6);
	StringList_AddFront(&list,str3);
	//removing all duplicates including the original
	printf("filling a list with multiple nodes containing the same string, then removing all the duplicates\n");
	int i;
	for(i = 0; i < 5; i++){
		temp = StringList_InList(&list, str3);
		if(temp != NULL){
			StringList_RemoveNode(&list,temp);
		}
	}
	temp = StringList_InList(&list, str3);
	if(temp != NULL){
		printf("did not remove all the duplicate nodes\n");
		return TEST_FAILED;
	}
	//removing a node at an index
	printf("removing a node at an index\n");
	temp = StringList_GetIndex(&list,5);
	StringList_RemoveNode(&list,temp);
	temp = StringList_GetIndex(&list,5);
	if(strstr(temp->element,str8) == NULL){
		printf("Did not remove the node at the specified index\n");
		return TEST_FAILED;
	}
	printf("now testing if size still gives back the correct value\n");
	int size = StringList_Size(&list);
	if(size != 6){
		printf("Did not give back the proper size");
		return TEST_FAILED;
	}
	//removing the head using remove
	printf("removing the head using the remove\n");
	int flag = StringList_Remove(&list,str);
	if(!flag){
		printf("Remove returned it did not remove a node\n");
		temp = StringList_InList(&list,str);
		if(temp == NULL){
			printf("remove actually did remove the node just reported it didnt\n");
		}else{
			printf("remove actually did not remove the node\n");
		}
		return TEST_FAILED;
	}
	StringList_AddBack(&list,str3);
	printf("testing size again");
	size = StringList_Size(&list);
	if(size != 6){
		printf("size did not give back the proper value\n");
		return TEST_FAILED;
	}
	printf("destroying the list then adding elements back into it and seeig if they are there\n");
	StringList_Destroy(&list);
	size = StringList_Size(&list);
	if(size != 0){
		printf("did not destroy the list\n");
		return TEST_FAILED;
	}
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	size = StringList_Size(&list);
	if(size != 4){
		printf("Did not properly add back in elements after destroying the list\n");
		return TEST_FAILED;
	}
	
	printf("getting the head using GetIndex and then removing it with removeNode\n");
	temp = StringList_GetIndex(&list,0);
	StringList_RemoveNode(&list,temp);
	temp = StringList_InList(&list,str4);
	if(temp != NULL){
		printf("did not remove the head\n");
		return TEST_FAILED;
	}
	printf("removing all elements using removeNode\n");
	temp = list.head;
	while(temp != NULL){
		StringList_RemoveNode(&list,temp);
		temp = list.head;
	}
	
	size = StringList_Size(&list);
	if(size != 0){
		printf("did not remove all the elements\n");
		return TEST_FAILED;
	}
	
	printf("Adding the same element into the list multiple times and then removing all of the duplicate strings which should be the whole list\n");
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str);
	temp = StringList_InList(&list,str);
	while(temp != NULL){
		StringList_RemoveNode(&list,temp);
		temp = StringList_InList(&list,str);
	}
	
	size = StringList_Size(&list);
	if(size != 0){
		printf("did not remove all the elements\n");
		return TEST_FAILED;
	}
	printf("adding some elements back into the list, then removing the tail using remove. Then destroying the list\n");
	StringList_AddFront(&list,str);
	StringList_AddFront(&list,str2);
	StringList_AddFront(&list,str3);
	StringList_AddFront(&list,str4);
	StringList_AddFront(&list,str5);
	flag = StringList_Remove(&list,str);
	if(!flag){
		printf("Remove returned it did not remove the tail\n");
		temp = StringList_InList(&list,str);
		if(temp == NULL){
			printf("remove actually did remove the tail just reported it didnt\n");
		}else{
			printf("remove actually did not remove the tail\n");
		}
		return TEST_FAILED;
	}
	StringList_Destroy(&list);
	size = StringList_Size(&list);
	if(size != 0){
		printf("did not destroy all the elements in the list\n");
		return TEST_FAILED;
	}
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