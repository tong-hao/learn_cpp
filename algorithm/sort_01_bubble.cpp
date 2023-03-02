// A simple C++ program to sort a linked list using
// bubble sort algorithm
#include <bits/stdc++.h>
using namespace std;

// A linked list node
struct Node {
	int data;
	Node *next;
};

/* Function to swap data of two nodes a and b*/
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// A utility function to get last node of linked list
struct Node *lastNode(Node *root) {
	while (root && root->next)
		root = root->next;
	return root;
}

// A utility function to print a linked list
void printList(Node *node) {
	while (node) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

// A function to merge two sorted linked lists so that
// resulting list is in increasing order.
Node *merge(Node *a, Node *b) {
	// If first list is empty, the second list is result
	if (!a)
		return b;

	// If second list is empty, the second list is result
	if (!b)
		return a;

	// Compare the data members of head nodes of both lists
	// and put the smaller one in result
	Node *result;
	if (a->data < b->data) {
		result = a;
		result->next = merge(a->next, b);
	} else {
		result = b;
		result->next = merge(a, b->next);
	}

	return result;
}

// A function to divide a linked list into two
void divide(Node *source, Node **frontRef, Node **backRef) {
	Node *fast;
	Node *slow;
	slow = source;
	fast = source->next;

	// Advance 'fast' two nodes, and advance 'slow' one node
	while (fast) {
		fast = fast->next;
		if (fast) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	// 'slow' is before the midpoint in the list, so split it in two
	// at that point.
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

// The main function that sorts a linked list using
// merge sort
void mergeSort(Node **headRef) {
	Node *head = *headRef;
	Node *a;
	Node *b;

	// If the list contains only one element,
	// do nothing
	if (!head || !head->next)
		return;

	// Split head into 'a' and 'b' sublists
	divide(head, &a, &b);

	// Recursively sort the sublists
	mergeSort(&a);
	mergeSort(&b);

	// merge the two sorted lists together
	*headRef = merge(a, b);
}

// Function to sort a linked list using bubble sort
void bubbleSort(struct Node *head) {
	// Initialize current node
	struct Node *current = head;

	// Initialize nodes needed for swapping
	struct Node *prev = NULL;
	struct Node *next = NULL;

	// Keep track of whether the list is sorted
	bool isSorted = false;

	// If the list is empty or contains only one node,
	// it is already sorted
	if (current == NULL || current->next == NULL)
		return;

	// While the list is not sorted, keep sorting
	while (!isSorted) {
		// Set the isSorted flag to true
		isSorted = true;

		// Set the current node to the head
		current = head;

		// Iterate over the list and swap adjacent nodes
		// if they are out of order
		while (current && current->next) {
			// Save a pointer to the next node
			next = current->next;

			// If the current node is larger than the next node,
			// swap the data values and set the isSorted flag
			// to false
			if (current->data > next->data) {
				swap(&current->data, &next->data);
				isSorted = false;
			}

			// Advance the pointers
			prev = current;
			current = current->next;
		}
	}
}

// Driver code
int main() {
	// Create a linked list with some test data
	Node *head = NULL;
	head = new Node;
	head->data = 5;
	head->next = new Node;
	head->next->data = 2;
	head->next->next = new Node;
	head->next->next->data = 4;
	head->next->next->next = new Node;
	head->next->next->next->data = 3;
	head->next->next->next->next = new Node;
	head->next->next->next->next->data = 1;

	// Print the unsorted list
	cout << "Unsorted: ";
	printList(head);

	// Sort the list
	bubbleSort(head);

	// Print the sorted list
	cout << "Sorted: ";
	printList(head);

	return 0;
}
