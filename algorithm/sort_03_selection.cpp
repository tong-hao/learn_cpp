// A simple C++ program to sort a linked list using
// selection sort algorithm
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

/* Function to sort a linked list using selection sort */
void selectionSort(Node **head_ref) {
	Node *current = *head_ref;

	// Traverse the list
	while (current->next) {
		// Find minimum element from the rest of the
		// unsorted list
		Node *min = current;
		Node *node = current->next;

		while (node) {
			if (node->data < min->data)
				min = node;
			node = node->next;
		}

		// Put the minimum element in the current node
		swap(current->data, min->data);

		// Move to the next node
		current = current->next;
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
	selectionSort(&head);

	// Print the sorted linked list
	cout << "Sorted: ";
	printList(head);

	return 0;
}
