#pragma once
/*
implementation of a node like the normal one with additional data member
priority to be used in the implementation of the priority queue
*/
template < typename T>
class PriorityNode
{
private :
	T item; // A data item
	int Priority; //priority of the node
	PriorityNode<T>* next; // Pointer to next PriorityNode
public :
	PriorityNode();
	PriorityNode( const T & r_Item, int p);	//passing by const ref.
	PriorityNode( const T & r_Item, int p, PriorityNode<T>* nextPriorityNodePtr);
	void setItem( const T & r_Item);
	void setPriority(int P);
	void setNext(PriorityNode<T>* nextPriorityNodePtr);
	T getItem() const ;
	int getPriority();
	PriorityNode<T>* getNext() const ;
}; // end PriorityNode


template < typename T>
PriorityNode<T>::PriorityNode() 
{
	next = nullptr;
} 

template < typename T>
PriorityNode<T>::PriorityNode( const T& r_Item , int p)
{
	item = r_Item;
	Priority = p;
	next = nullptr;
} 

template < typename T>
PriorityNode<T>::PriorityNode( const T& r_Item, int p, PriorityNode<T>* nextPriorityNodePtr)
{
	item = r_Item;
	Priority = p;
	next = nextPriorityNodePtr;
}
template < typename T>
void PriorityNode<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void PriorityNode<T>::setNext(PriorityNode<T>* nextPriorityNodePtr)
{
	next = nextPriorityNodePtr;
} 

template < typename T>
T PriorityNode<T>::getItem() const
{
	return item;
} 

template < typename T>
PriorityNode<T>* PriorityNode<T>::getNext() const
{
	return next;
} 

template <typename T>
void PriorityNode<T>::setPriority(int P)
{
	Priority = p;
}

template <typename T>
int PriorityNode<T>::getPriority()
{
	return Priority;
}