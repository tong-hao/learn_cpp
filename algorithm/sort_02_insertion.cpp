// A simple C++ program to sort a linked list using
// insertion sort algorithm
#include <bits/stdc++.h>
using namespace std;

// A linked list node
struct Node {
	int data;
	Node *next;
};

/* Function to insert a node at the beginning of the
   linked list */
void push(Node **head_ref, int new_data) {
	// Allocate new node
	Node *new_node = new Node;

	// Put in the data
	new_node->data = new_data;

	// Make next of new node as head
	new_node->next = (*head_ref);

	// Move the head to point to the new node
	(*head_ref) = new_node;
}

/* Function to print nodes in a given linked list */
void printList(Node *node) {
	while (node) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

/* Function to sort a linked list using insertion sort */
void insertionSort(Node **head_ref) {
	// Initialize sorted linked list
	Node *sorted = NULL;

	// Traverse the given linked list and insert every
	// node to sorted
	Node *current = *head_ref;
	while (current != NULL) {
		// Store next for next iteration
		Node *next = current->next;

		// insert current in sorted linked list
		sortedInsert(&sorted, current);

		// Update current
		current = next;
	}

	// Update head_ref to point to sorted linked list
	*head_ref = sorted;
}

/* function to insert a new_node in a list. Note that this
   function expects a pointer to head_ref as this can modify the
   head of the input linked list (similar to push())*/
void sortedInsert(Node **head_ref, Node *new_node) {
	Node *current;

	// Case 1 of the above algo
	if (*head_ref == NULL || (*head_ref)->data >= new_node->data) {
		new_node->next = *head_ref;
		*head_ref = new_node;
	} else {
		// Locate the node before the point of insertion
		current = *head_ref;
		while (current->next != NULL && current->next->data < new_node->data) {
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

// Driver code
int main() {
	// Start with the empty list
	Node *head = NULL;

	// Create a linked list with some test data
	push(&head, 5);
	push(&head, 2);
	push(&head, 4);
	push(&head, 3);
	push(&head, 1);

	// Print the unsorted linked list
	cout << "Unsorted: ";
	printList(head);

	// Sort the linked list
	insertionSort(&head);

	// Print the sorted linked list
	cout << "Sorted: ";
	printList(head);

	return 0;
}
