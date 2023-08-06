#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

typedef struct Node {
	Node* prev;
	Node* next;
	char* val;
} Node; 

// insert creates a new node with val at the front of the linked list head
// returning the head of the new linked list
Node* insert(Node* head, char* val) {
	// create a new node by allocating node on heap, then allocate
	// that node's string value
	Node* node = calloc(1, sizeof(Node));
	node->val = malloc(strlen(val)+1);
	strcpy(node->val, val); 
	node->next = head;
	if (head != NULL) head->prev = node;
	return node;
}

// find returns a pointer to a node containing val if it exists, else NULL
Node* find(Node* head, char* val) {
	while (head != NULL && strcmp(head->val, val) != 0) {
		head = head->next;
	}
	return head;
}

// delete will attempt to delete whatever node head points to from the linked list in-place
void delete(Node* head) {
	if (head->prev == NULL) { // at the head of the list
		if (head->next != NULL)
			head->next->prev = NULL;
	} else {
		if (head->next == NULL) { // at the tail of the list
			head->prev->next = NULL;
		} else { // between two nodes
			head->prev->next = head->next;
			head->next->prev = head->prev;
		}
	}
	free(head->val);
	free(head);
}


int main() {
	Node* head = insert(NULL, "test");
	Node* begin = head;
	head = insert(head, "test1");
	head = insert(head, "test2");

	printf("%p\n", find(head,"test"));
	delete(find(head,"test"));
	printf("%p\n", find(head, "test"));
	return 0;
}
