#pragma once
#include "LinkedListNode.h"
template <typename T>
class LinkedListEx
{
public:
	const LinkedListNode<T>* NIL;
	LinkedListEx(void)
	{
		_sentinel=new LinkedListNode<T>();
		_sentinel->Pre=_sentinel;
		_sentinel->Next=_sentinel;
		NIL=_sentinel;
	}

	~LinkedListEx(void)
	{
		LinkedListNode<T>* node=_sentinel->Next;
		while(node!=_sentinel)
		{
			LinkedListNode<T>* next=node->Next;
			delete node;
			node=next;
		} 
		delete _sentinel;
	}

	LinkedListNode<T>* GetFirst()
	{
		return _sentinel->Next;
	}
	LinkedListNode<T>* GetLast()
	{
		return _sentinel->Pre;
	}
	void AddFirst(T value)
	{
		LinkedListNode<T>* node=new LinkedListNode<T>(value);
		AddFirst(node);
	}
	void AddFirst(LinkedListNode<T>* node)
	{
		_sentinel->Next->Pre=node;
		node->Next=_sentinel->Next;
		_sentinel->Next=node;
		node->Pre=_sentinel->Next;
	}
	void AddLast(T value)
	{
		LinkedListNode<T>* node=new LinkedListNode<T>(value);
		AddLast(node);
	}
	void AddLast(LinkedListNode<T>* node)
	{
		_sentinel->Pre->Next=node;
		node->Pre=_sentinel->Pre;
		_sentinel->Pre=node;
		node->Next=_sentinel;
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
		
	}
	void Remove(LinkedListNode<T>* node)
	{
		node->Pre->Next=node->Next;
		node->Next->Pre=node->Pre;
	}
		
	LinkedListNode<T>* Search(T key)
	{
		LinkedListNode<T>* current=_sentinel->Next;
		while(current!=_sentinel&&current->Key!=key)
		{
			current=current->Next;
		}
		return current;
	}

	void Test()
	{
		LinkedListNode<T>* node=_sentinel->Next;
		while(node!=_sentinel)
		{
			cout<<node->Key<<" ";
			node=node->Next;
		}
		cout<<endl;
	}
private:
	LinkedListNode<T>* _sentinel;

	

};
