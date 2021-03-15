#pragma once
#include <iostream>
class Stack_LL {
private:
	// topPtr points to the top element of the stack
    class Node {
    public:
    	int data;
    	Node* next;
    	Node(int val) {data = val; next = nullptr;}
    	Node(int val, Node* node) {data = val; next = node;}
    };
    Node* head;
    Node* tail;
public:
	Stack_LL();
	~Stack_LL();

	bool isEmpty() const;
	void push(int newItem);
	void pop();
	int peek() const;
    void PrintAll() const;
};

Stack_LL::Stack_LL() {
    head = nullptr;
    tail = nullptr; 
}

Stack_LL::~Stack_LL() {
    Node* node = head;
    Node* prev;
    while(node != nullptr) {
        prev = node;
        node = node->next;
        delete prev;
    }
}

bool Stack_LL::isEmpty() const {
    if (head == nullptr) {
        return true;
    } else {
        return false;
    }
}

void Stack_LL::push(int newItem) {
    Node* node = new Node(newItem);
    if (isEmpty()) {
        head = node;
        tail = node;
        return;
    }
    tail->next = node;
    tail = tail->next;
}

void Stack_LL::pop() {
    if (isEmpty()) {
        return;
    } else if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node* node = head; 
    while(node->next != tail) {
        node = node->next;
    }
    delete node->next;
    node->next = nullptr;
    tail = node;
}

int Stack_LL::peek() const {
    return tail->data;
}

void Stack_LL::PrintAll() const {
    Node* node = head;
    while (node != nullptr) {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << std::endl;
}