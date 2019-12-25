#pragma once

//the node struct with a template
/* MEMBERS
 * the content 
 * a pointer to the next node
 */
template <typename T>
struct Node {
	T content;
	Node* next;
};

//a single linked list class with a template
template <typename T>
class SLinkedList {
private:
	//the head data member, pointing to the node at the front of the list
	Node<T>* head;
	
public:
	//the single linked list destructor
	~SLinkedList<T>() {
		while (!empty())
			removeFront();
	}

	//default constructor
	SLinkedList<T>() {
		head = nullptr;
	}

	//the empty function - returns a boolean value for whether or not the list is empty
	bool empty() {
		return (head == nullptr);
	}

	//the front function - returns the content of the node at the front of the list (the head)
	T front() {
		return head->content;
	}

	//the insertFront function - inserts a node at the front of the list with the given content
	void insertFront(T data) {
		//creating a new node and detting the content
		Node<T>* temp = new Node<T>();
		temp->content = data;

		//making the head the next for this node
		temp->next = head;

		//making the head this node
		head = temp;
	}

	//the removeFront function - removes the node at the front of the list and makes the next ndoe the head
	void removeFront() {
		//making a temporary variable point to the head
		Node<T>* temp = head;

		//making the head the next of the head
		head = head->next;

		//deleting the old head (which is pointed to by the temp variable)
		delete temp;
	}
};