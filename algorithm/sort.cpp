struct Node {
	int value;
	Node* next;
};

Node* sort(Node* head) {
	// shuffer

	Node* end = head;
	while (end->next) {
		end = end->next;
	}

	sortCore(head->next, end);

	return head;
}

void sortCore(Node* begin, Node* end) {
	if (begin == nullptr || end == nullptr || begin == end) {
		return;
	}
	int len = 0;
	Node* temp = begin;
	while (temp->next) {
		temp = temp->next;
		++len;
	}

	// patition
	Node* v = partition(begin, end, len);

	// sort part1
	sortCore(begin, v);

	if (v == nullptr)
		return;

	// sort part2
	sortCore(v->next, end);
}

Node* partition(Node* begin, Node* end, int len) {
	if (begin == nullptr || end == nullptr)
		return nullptr;
	if (len == 1)
		return begin;

	Node* v = begin;
	Node* i = begin->next;

	int half_len = len / 2;
	Node* j = i;
	while (half_len > 0) {
		j = i->next;
	}

	while (i != j) {
		Node* i_pre = i;
		Node* j_pre = j;

		while (i->value < v->value) {
			i_pre = i;
			i = i->next;
			if (i == end)
				break;
		}
		while (j->value > v->value) {
			j_pre = j;
			j = j->next;
			if (j == begin)
				break;
		}

		if (i != begin->next || j != end->next) {
			// swap i and j
			// i_pre -> i ->i_next ...  j_pre -> j -> j_next
			// i_pre -> j ->i_next ...  j_pre -> i -> j-next

			i_pre->next = j;
			j->next = i->next;

			j_pre->next = i;
			i->next = j->next;
		}
	}

	return v;
}
