#pragma once
#include "LinkedListNode.h"

#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:
	LinkedList::LinkedList(void)
		:_first(NULL),_last(NULL)
	{

	}

	LinkedList::~LinkedList(void)
	{
		LinkedListNode<T>* node=_first;
		while(node!=NULL)
		{
			LinkedListNode<T>* next=node->Next;
			delete node;
			node=next;
		} 
	}

	LinkedListNode<T>* GetFirst()
	{
		return _first;
	}
	LinkedListNode<T>* GetLast()
	{
		return _last;
	}
	void AddFirst(T value)
	{
		LinkedListNode<T>* node=new LinkedListNode<T>(value);
		AddFirst(node);
	}
	void AddFirst(LinkedListNode<T>* node)
	{
		if(_first!=NULL)
		{
			_first->Pre=node;
			node->Next=_first;
		}
		_first=node;
		if(_last==NULL)
		{
			_last=node;
		}
	}
	void AddLast(T value)
	{
		LinkedListNode<T>* node=new LinkedListNode<T>(value);
		AddLast(node);
	}
	void AddLast(LinkedListNode<T>* node)
	{
		if(_last!=NULL)
		{
			_last->Next=node;
			node->Pre=_last;
		}
		_last=node;
		if(_first==NULL)
		{
			_first=node;
		}
	}
	void AddAfter(LinkedListNode<T>* target,T value)
	{
		LinkedListNode<T>* node=new LinkedListNode<T>(value);
		AddAfter(target,node);

	}
	void AddAfter(LinkedListNode<T>* target,LinkedListNode<T>* value)
	{
		if(target->Next==value)
		{
			return;
		}
		target->Next->Pre=value;
		value->Next=target->Next;
		target->Next=value;
		value->Pre=target;
		if(_last==target)
		{
			_last=value;
		}

	}
	void AddBefore(LinkedListNode<T>* target,T value)
	{
		LinkedListNode<T>* node=new LinkedListNode<T>(value);
		AddBefore(target,node);

	}
	void AddBefore(LinkedListNode<T>* target,LinkedListNode<T>* value)
	{
		if(target->Pre==value)
		{
			return;
		}
		target->Pre->Next=value;
		value->Pre=target->Next;
		target->Pre=value;
		value->Next=target;
		if(_first==target)
		{
			_first=value;
		}

	}
	void Remove(LinkedListNode<T>* node)
	{
		if(node->Pre==NULL)
		{
			_first=node->Next;
		}
		else
		{
			node->Pre->Next=node->Next;
		}
		if(node->Next==NULL)
		{
			_first=node->Pre;
		}
		else
		{
			node->Next->Pre=node->Pre;
		}
	}

	LinkedListNode<T>* Search(T key)
	{
		LinkedListNode<T>* current=_first;
		while(current!=NULL&&current->Key!=key)
		{
			current=current->Next;
		}
		return current;
	}

	void Test()
	{
		LinkedListNode<T>* node=_first;
		while(node!=NULL)
		{
			cout<<node->Key<<" ";
			node=node->Next;
		}
		cout<<endl;
	}
private:
	LinkedListNode<T>* _first;
	LinkedListNode<T>* _last;


};
