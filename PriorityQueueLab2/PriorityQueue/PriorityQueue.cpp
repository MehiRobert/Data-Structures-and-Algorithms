
#include "PriorityQueue.h"
#include <exception>
#include <iostream>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
	
	this->head = NULL;
	this->relation = r;
}


void PriorityQueue::push(TElem e, TPriority p) {
	if (this->head == NULL || this->relation(p,this->head->priority) == true)
	{
		Node* newnode = new Node();
		newnode->data = e;
		newnode->priority = p;
		newnode->next = this->head;
		this->head = newnode;
		
		
	}
	else
	{
		Node* currentNode = this->head;
		Node* prevNode = currentNode;
		while (this->relation(p, currentNode->priority) == false && currentNode->next != NULL)
		{
			prevNode = currentNode;
			currentNode = currentNode->next;
		}
		if (this->relation(p, currentNode->priority) == true)
		{
			Node* newnode = new Node();
			newnode->data = e;
			newnode->priority = p;
			newnode->next = currentNode;
			prevNode->next = newnode;
		}
		else if (currentNode->next == NULL && this->relation(p, currentNode->priority) == false)
		{
			Node* newnode = new Node();
			newnode->data = e;
			newnode->priority = p;
			newnode->next = NULL;
			currentNode->next = newnode;
		}
		
	}
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	if (this->head == NULL)
		throw exception();
	Node* n = this->head;
	pair <TElem, TPriority> Pair1(n->data,n->priority);
	return Pair1;
}

Element PriorityQueue::pop() {
	if (this->head == NULL)
		throw exception();
	Node* temp = this->head->next;
	pair <TElem, TPriority> Pair1(this->head->data, this->head->priority);
	delete this->head;
	this->head = temp;
	return Pair1;
}

bool PriorityQueue::isEmpty() const {

	return (this->head == NULL);
}


PriorityQueue::~PriorityQueue() {
	Node* current = this->head;
	while (current != NULL)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
	this->head = NULL;
}
TPriority PriorityQueue::changePriority(TElem elem, TPriority newPriority)
{
	Node* current = this->head;
	Node* PrevNode = NULL;
	while (current->data != elem && current->next != NULL)
	{
		PrevNode = current;
		current = current->next;
	}
	if (current->data != elem)
	{
		return -1;
	}
	else if (PrevNode == NULL)
	{
		this->head = current->next;
	}
	else
	{
		PrevNode->next = current->next;
	}
	push(current->data, newPriority);
}
;

