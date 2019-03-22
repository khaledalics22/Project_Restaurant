#pragma once
/* 
implementation of the Priority Queue using Linked list
inserting complexity is O(n) 
extract max priority complexity is O(1)
*/

#include "PriorityNode.h"
template <class T>
class Priority_Queue
{
private:
	PriorityNode<T>* frontptr; //pointer to the first element in the queue
public:
	Priority_Queue();
	bool isEmpty() const ;
	bool enqueue(const T& newEntry, int p); // insert to be sorted with respect to priority
	bool dequeue(T& frntEntry);  //dequeue the highest priority in the queue
	bool peekFront(T& frntEntry)  const; // return the highest priority node without deleting it from the queue
	~Priority_Queue();
};

/*
Function: Priority_Queue()
The constructor of the Priority_Queue class.

*/

template <class T>
Priority_Queue<T>::Priority_Queue()
{
	frontptr = NULL;
}

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/

template <class T>
bool Priority_Queue<T>::isEmpty() const 
{
	return !frontptr;
}

/*Function:enqueue
Adds newEntry at its right place with respect to its priority.

Input: newEntry , priority.
Output: True if the operation is successful; otherwise false.
*/
template <class T>
bool Priority_Queue<T>::enqueue(const T& newEntry, int p)
{
	PriorityNode<T>* trav = frontptr;	//traverse pointer
	PriorityNode<T>* newNode = new PriorityNode<T>(newEntry, p);	// the node to insert
	// case the queue is empty
	if(!frontptr)
	{
		frontptr = newNode;
		return true;
	}
	// case the priority of the new node bigger than the first node of the queue
	if(trav->getPriority() < p)
	{
		newNode->setNext(frontptr);
		frontptr = newNode;
		return true;
	}
	// normal case
	while (trav->getNext())
	{
		if(trav->getNext()->getPriority() < p)
		{
			newNode->setNext(trav->getNext());
			trav->setNext(newNode);
			return true;
		}
		trav = trav->getNext();
	}
	// case the priority of the new node less than all nodes in the queue
	trav->setNext(newNode);
	return true;
}

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <class T>
bool Priority_Queue<T>::dequeue(T& frntEntry)
{
	// if the queue is empty won't dequeue anything
	if(isEmpty())
		return false;
	// queue is not empty remove the highest priority in the queue
	PriorityNode<T>* nodeToDeletePtr = frontptr;
	frntEntry = frontptr->getItem();
	frontptr = frontptr->getNext();
	delete nodeToDeletePtr;
	return true;
}

/*
Function: peekFront
gets the highest priority of this queue. The operation does not modify the queue.

Input: None.
Output: The highest priority of the queue.
return: false if Queue is empty
*/

template <class T>
bool Priority_Queue<T>::peekFront(T& frntEntry) const
{
	if(isEmpty())
		return false;

	frntEntry = frontptr->getItem();
	return true;
}
template <class T>
Priority_Queue<T>::~Priority_Queue()
{
}