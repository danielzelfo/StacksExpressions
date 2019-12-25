#include "SLinkedList.h"

//the stack class with a template
template <typename T>
class Stack {
private:
	//the only data member is a single linked list that will hold all the data
	SLinkedList<T>* data;

public:
	//default contructor
	Stack() {
		data = new SLinkedList<T>;
	}

	//destructor
	~Stack() {
		delete data;
	}

	//the empty function - returns a boolean for whether or not the stack is empty
	bool empty() {
		return data->empty();
	}

	//the top function - returns the top of the stack
	T top() {
		return data->front();
	}

	//the push function - adds to the top of the stack
	void push(T content) {
		data->insertFront(content);
	}

	//the pop function - removes one from the top of the stack
	void pop() {
		data->removeFront();
	}

};