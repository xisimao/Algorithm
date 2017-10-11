#pragma once



template <typename T>
class RedBlackTreeNode
{
public:
	enum NodeColor
	{
		Red,
		Black
	};
	RedBlackTreeNode()
	{
	}
	~RedBlackTreeNode()
	{
	}
	NodeColor Color;
	T Key;
	RedBlackTreeNode<T>* Parent;
	RedBlackTreeNode<T>* Left;
	RedBlackTreeNode<T>* Right;
};
