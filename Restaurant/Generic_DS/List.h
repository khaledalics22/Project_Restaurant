#pragma once

#include"Node.h"
template<class T>
class List 
{
	Node<T>* Header;
	Node<T>* back; 
public: 
	List(); 
	List(T );																						//  only for  orders
	//T * getitem(int ID);
	//Node<T> * promote(int ID);																		//  only for  orders
	bool insert(const T &);						//return false if couldn't create a Node
	bool remove (const T & );					// return false if the item is not exist 
	bool isEmpty(); 
	void clear(); 
	~List(); 
};

template<class T>
List<T>::List()
{
	Header=nullptr; 
	back=nullptr;

}
template<class T>
List<T>::List(T item)
{
	Node<T>* ptr=new Node(item); 
	ptr->setNext(nullptr); 
	Header=ptr; 
	back=Header; 
}
template<class T>
bool List<T>::insert(const T & item)		//insert at the end of the list NOT at the begining 
{
	Node<T>* ptr=new Node(item);
	if (ptr==nullptr) return false; 
	if (isEmpty())
	{
		Header=ptr; 
		back=Header; 
	}
	else 
	{
	back->setNext(ptr); 
	back=ptr;
	}
	back->setNext(nullptr); 
	return true ;
}
template<class T>
bool List<T>::isEmpty()
{
	if (Header==nullptr)
		return true; 
	return false; 
}
template<class T>
bool List<T>::remove (const T & item )				// here the file will give only the ID of the order so whoever want to delete it he can't unless he get the item first
{
	Node<T>* ptr=Header;

	if (Header->getItem()==item)				  // needs operator overloeading 
	{
		Header=Header->getItem();				
		delete ptr;								
		ptr=nullptr; 							
		return true; 							
	}
	ptr=ptr->getNext();							
	Node<T>* before=Header;						
	while (ptr!=nullptr)
	{
		if (ptr->getItem()==item)            // needs operator overloeading 
		{	
			before->setNext(ptr->getNext());
			delete ptr ; 
			ptr=before->getNext();
			return true; 
		}
		before=ptr; 
		ptr=ptr->getNext(); 
	}
	return false; 
}
template<class T>

void List<T>::clear()
{
	Node<T>* ptr=Header; 
	while (Header!=nullptr)
	{
		Header=Header->getNext;
		delete ptr ; 
		ptr=Header; 
	}
	back=nullptr; 
}
template<class T>
List<T>::~List()
{
	clear(); 
}
template<class T>

// ------------------------------------------------------how could we know the order using its ID

