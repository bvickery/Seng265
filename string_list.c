/*  string_list.c
	Seng 265 Summer 2016
	Brandon Vickery
	06/11/16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_list.h"

/* StringList_init(L)
   Initialize the provided StringList instance.
   
   Pre-conditions:
     L is a pointer to a StringList struct.
   Post-conditions:
     The head and tail pointers of L have been
     initialized to NULL.
*/ 
void StringList_Init(StringList* L){
	L->head = NULL;
	L->tail = NULL;
}

/* StringList_destroy(L)
   Free all storage associated with each node of the StringList
   object and reset all pointers to NULL.
   
   Pre-conditions:
     L is a pointer to a StringList struct which has been
	 initialized with StringList_init and has not already
	 been destroyed.
   Post-conditions:
     Each node of L, and its associated string, has been freed.
	 The head and tail pointers of L have been set to NULL.
*/
void StringList_Destroy(StringList* L){
	while(L->head!= NULL){
		StringList_RemoveNode(L,L->head);
	}
}

/* StringList_size(L)
   Return the number of nodes in the list L
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
   Return value:
     The number of nodes in L.
*/ 
int StringList_Size(StringList* L){
	int size = 0;
	if(L->head == NULL){
		return size;
	}
	StringListNode* temp = L->head;
	size++;
	while(temp->next != NULL){
		size++;
		temp = temp->next;
	}
	return size;
}

/* StringList_AddFront(L, str)
   Create a new list node containing a copy of the string str and
   add the node to the front (head) of the list L.
   
   Note: The created node must not contain a pointer to the string
   str. Instead, it should contain a pointer to a new array containing
   a copy of str.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     A new node containing a copy of str has been attached
	 to the beginning of the list L.
   Return value:
     A pointer to the created node.
*/ 
StringListNode* StringList_AddFront(StringList* L, char* str){
	StringListNode* new_node = (StringListNode*)malloc(sizeof(StringListNode));
	new_node->element = (char*)malloc(strlen(str));
	strcpy(new_node->element, str);
	
	new_node->previous = NULL;
	if(L->head == NULL){
		L->tail = new_node;
		new_node->next = NULL;
	}else{
		L->head->previous = new_node;
		new_node->next = L->head;
	}
	L->head = new_node;

	return new_node;
}

/* StringList_AddBack(L, str)
   Create a new list node containing a copy of the string str and
   add the node to the back (tail) of the list L.
   
   Note: The created node must not contain a pointer to the string
   str. Instead, it should contain a pointer to a new array containing
   a copy of str.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     A new node containing a copy of str has been attached
	 to the end of the list L.
   Return value:
     A pointer to the created node.
*/ 
StringListNode* StringList_AddBack(StringList* L, char* str){
	StringListNode* new_node = (StringListNode*)malloc(sizeof(StringListNode));
	new_node->element = (char*)malloc(strlen(str));
	strcpy(new_node->element, str);
	new_node->next = NULL;
	if(L->tail == NULL){
		L->head = new_node;
		new_node->previous = NULL;
	}else{
		L->tail->next = new_node;
		new_node->previous = L->tail;
	}
	L->tail = new_node;
	return new_node;
}

/* StringList_remove(L, str)
   Search the list L for a node containing the provided string str
   and remove the first such node if it is present.
   
   Note that the removal process should free all storage associated
   with the node and the string it contains.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Post-conditions:
     If a node containing str was found, it has been removed
	 from the list L.
   Return value:
     1 if a node containing str was found.
	 0 otherwise.
 */
int StringList_Remove(StringList* L, char* str){
	int flag = 0;
	StringListNode* temp = StringList_InList(L,str);
	if(temp != NULL){
		StringList_RemoveNode(L,temp);
		flag = 1;
	}
	return flag;
}

/* StringList_RemoveNode(L, node)
   Remove the provided node from the list L.
   
   Note that the removal process should free all storage associated
   with the node and the string it contains.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 node points to a valid node in L.
   Post-conditions:
     node has been removed from L.
*/
// for testing this get it to remove the first and last items in the list
// also can test by getting it to destroy the list by repetadly calling this function rather than destroy
void StringList_RemoveNode(StringList* L, StringListNode* node){
	//need to check if previous is null and if next is null
	if(L->head != NULL){
		StringListNode* temp = node;
		if(temp->previous != NULL){
			temp->previous->next = temp->next;
		}else{
			//first item in list
			L->head = temp->next;
		}
		if(temp->next != NULL){
			temp->next->previous = temp->previous;
		}else{
			//last item in teh list
			L->tail = temp->previous;
		}
		//free the memory
		node = NULL;
		free(temp->element);
		free(temp);
	}
}

/* StringList_InList(L, str)
   Search the list L for a node containing the provided string str
   and return a pointer to the first node containing str if it is found.
   
   The "first" node, in this context, refers to the first node encountered
   on a forward traversal of the list starting at the head.
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
	 str points to a valid null terminated C string.
   Return value:
     A pointer to the first node containing str if it was found in the list.
	 NULL otherwise.
*/
StringListNode* StringList_InList(StringList* L, char* str){
	int i;
	StringListNode* temp = L->head;
	for(i = 0; i < StringList_Size(L); i++){
		if(strstr(temp->element,str) != NULL){
			return temp;
		}
		temp = temp->next;
	}
	temp = NULL;
	return temp;
}

/* StringList_GetIndex(L, i)
   Return the node at the provided index i (where index 0 is 
   the node at the head of the list).
   
   
   Pre-conditions:
     L is a pointer to an initialized StringList struct.
   Return value:
     A pointer to node i if 0 <= i <= size - 1 (where size is the
	 number of elements in the list.
	 NULL if i is not a valid index into the list.
*/
StringListNode* StringList_GetIndex(StringList* L, int i){
	StringListNode* temp = NULL;
	if(StringList_Size(L) - 1 < i){
		return temp;
	}
	int j;
	temp = L->head;
	for(j = 0;j <= i;j++){
		temp = temp->next;
	}
	return temp;
}
