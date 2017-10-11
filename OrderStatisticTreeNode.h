#pragma once



template <typename T>
class OrderStatisticTreeNode
{
public:
	enum NodeColor
	{
		Red,
		Black
	};
	OrderStatisticTreeNode()
	{
	}
	~OrderStatisticTreeNode()
	{
	}
	int Size;
	NodeColor Color;
	T Key;
	OrderStatisticTreeNode<T>* Parent;
	OrderStatisticTreeNode<T>* Left;
	OrderStatisticTreeNode<T>* Right;
};