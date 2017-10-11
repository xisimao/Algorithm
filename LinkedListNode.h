#pragma once

template <typename T>
class LinkedListNode
{
public:
	LinkedListNode()
		:Pre(NULL),Next(NULL)
	{
	}
	LinkedListNode(T k)
		:Key(k),Pre(NULL),Next(NULL)
	{
	}
	~LinkedListNode(void)
	{
	}
	LinkedListNode<T>* Pre;
	LinkedListNode<T>* Next;
	T Key;
	
};

