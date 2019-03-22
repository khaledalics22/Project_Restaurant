#pragma once

#include"Node.h"
template<class T>
class List 
{
	Node<T>* Head;
	Node<T>* tail; 
public: 
	List();										//sets Head &  tail to nullptr
	List(T );									//Creates a list and set parameter itme at the begining 											
	bool InsertEnd(const T &);					//return false if couldn't create a Node
	bool Remove(const T & );					// return false if the item is not exist 
	bool IsEmpty();								//return true if Head points to nullptr
	void Clear();								//delete all Nodes and set Head & tail to nullptr
	~List();									//call Clear() fn 
};

template<class T>
List<T>::List()
{
	Head=nullptr; 
	tail==nullptr;

}
template<class T>
List<T>::List(T item)						
{
	Node<T>* ptr=new Node<T>(item); 
	ptr->setNext(nullptr); 
	Head=ptr; 
	tail=Head; 
}
template<class T>
bool List<T>::InsertEnd(const T & item)		// it inserts at the end of the list NOT at the begining 
{
	Node<T>* ptr=new Node<T>(item);
	if (ptr==nullptr) return false; 
	if (IsEmpty())
	{
		Head=ptr; 
		tail=Head; 
	}
	else 
	{
	tail->setNext(ptr); 
	tail=ptr;
	}
	tail->setNext(nullptr); 
	return true ;
}
template<class T>
bool List<T>::IsEmpty()
{
	if (Head==nullptr)
		return true; 
	return false; 
}
template<class T>
bool List<T>::Remove (const T & item )       
{
	Node<T>* ptr=Head;

	if (Head->getItem()==item)				  
	{
		Head=Head->getNext();				
		delete ptr;								
		ptr=nullptr; 							
		return true; 							
	}
	ptr=ptr->getNext();							
	Node<T>* before=Head;						
	while (ptr!=nullptr)
	{
		if (ptr->getItem()==item)                  
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

void List<T>::Clear()
{
	Node<T>* ptr=Head; 
	while (Head!=nullptr)
	{
		Head=Head->getNext();
		delete ptr ; 
		ptr=Head; 
	}
	tail=nullptr; 
}
template<class T>
List<T>::~List()
{
	Clear(); 
}



