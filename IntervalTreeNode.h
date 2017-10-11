#pragma once
template<typename T>
class IntervalTreeNode
{
public:
	enum NodeColor{Red,Black};
	T Low;
	T High;
	T Max;
	IntervalTreeNode<T>* Parent;
	IntervalTreeNode<T>* Left;
	IntervalTreeNode<T>* Right;
	NodeColor Color;
};