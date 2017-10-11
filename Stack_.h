#pragma once

template <typename T>
class Stack_
{
public:
	Stack_()
		:_index(-1)
	{
	}
	~Stack_()
	{
	}
	bool Empty()
	{
		return _index<0;
	}
	void Push(T value)
	{
		if(_index>=StackLength-1)
		{
			throw out_of_range("stack is full");
		}
		_data[++_index]=value;
	}
	T Pop()
	{
		if(Empty())
		{
			throw out_of_range("stack is empty");
		}
		return _data[_index--];
	}
	T Peek()
	{
		if(Empty())
		{
			throw out_of_range("stack is empty");
		}
		return _data[_index];
	}
private:
	static const int StackLength=20;
	T _data[StackLength];
	int _index;
};

