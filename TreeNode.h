#pragma once
template <typename T>
class TreeNode
{
public:
	TreeNode()
		:Parent(NULL),Left(NULL),Right(NULL),Text(' ')
	{
	}
	~TreeNode()
	{
	}
	TreeNode<T>* Parent;
	TreeNode<T>* Left;
	TreeNode<T>* Right;
	T Key;
	char Text;
	bool operator == (const TreeNode<T>& right) const
	{
		return Key==right.Key;
	}
	bool operator != (const TreeNode<T>& right) const
	{
		return !(*this == right);
	}
	bool operator < (const TreeNode<T>& right) const
	{
		return Key<right.Key;
	}
	bool operator > (const TreeNode<T>& right) const
	{
		return right < *this;
	}
	bool operator <= (const TreeNode<T>& right) const
	{
		return !(right < *this);
	}
	bool operator >= (const TreeNode<T>& right) const
	{
		return !(*this < right);
	}
};
