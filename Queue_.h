#pragma once

template <typename T>
class Queue_
{
public:
	Queue_()
		:_head(0),_tail(0)
	{
	}
	~Queue_()
	{
	}
	void Enqueue(T value)
	{
		if(_head==_tail+1||(_head==0&&_tail==QueueLength))
		{
			throw out_of_range("stack is full");
		}
		_data[_tail]=value;
		if(_tail==QueueLength)
		{
			_tail=0;
		}
		else
		{
			++_tail;
		}
	}
	T Peek()
	{
		if(Empty())
		{
			throw out_of_range("stack is empty");
		}
		return _data[_head];
	}
	T Dequeue()
	{
		if(Empty())
		{
			throw out_of_range("stack is empty");
		}
		T temp=_data[_head];
		if(_head==QueueLength)
		{
			_head=0;
		}
		else
		{
			++_head;
		}
		return temp;
	}
	bool Empty()
	{
		return _head==_tail;
	}
private:
	static const int QueueLength=10;
	T _data[QueueLength+1];
	int _head;
	int _tail;
};