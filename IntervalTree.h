#pragma once
#include <algorithm>
#include "IntervalTreeNode.h"

using namespace std;

template<typename T>
class IntervalTree
{
public:
	IntervalTree()
	{
		_nil=new IntervalTreeNode<T>();
		//哨兵的其它属性并不重要
		_nil->Color=IntervalTreeNode<T>::Black;
		_nil->Low=0;
		_nil->High=0;
		_nil->Max=0;
		_root=_nil;
	}
	~IntervalTree()
	{
		IntervalTreeNode<T>* node=_root;
		DeletePoint(_root);
		delete _nil;
	}
	//添加
    void Insert(T low,T high)
	{
		IntervalTreeNode<T>* node=new IntervalTreeNode<T>();
		node->Low=low;
		node->High=high;
		node->Max=high;
		Insert(node);
	}
	//删除
	void Delete(IntervalTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		//用于替代x结点的后继结点y
		IntervalTreeNode<T>* fillNodeY=_nil;
		//用于替代y结点的子结点z
		IntervalTreeNode<T>* fillNodeZ=_nil;
		//具有双重颜色的结点
		IntervalTreeNode<T>* doubleColorNode=_nil;
		//color表示当前损失的颜色
		bool color;
		//对于前两个判断，因为仅仅交换了x和y结点，并没有将y的颜色赋值为x结点，所以原先x结点的颜色损失掉了，y作为双重颜色结点
		if(nodeX->Left==_nil)
		{
			color=nodeX->Color;
			//y结点可能是nil，但是nil的parent会在Transplant方法中赋值，供后续方法使用
			fillNodeY=nodeX->Right;
			Transplant(nodeX,fillNodeY);
			doubleColorNode=fillNodeY;
		}
		else if(nodeX->Right==_nil)
		{
			color=nodeX->Color;
			fillNodeY=nodeX->Left;
			Transplant(nodeX,fillNodeY);
			doubleColorNode=fillNodeY;
		}
		//当xyz结点都具备时，因为y会赋值为x的颜色，而z替换y，所以损失了y的颜色，z作为双重颜色结点
		else
		{
			//找到x的后继
			fillNodeY=Minimum(nodeX->Right);
			color=fillNodeY->Color;
			fillNodeZ=fillNodeY->Right;
			//这个判断主要是应对z结点为nil的情况，因为nil的parent是随意的
			//但是后续DeleteFixUp是需要用到parent属性，所以要对其赋值，其它处都有Transplant进行赋值
			//而对于非nil结点，那么z结点的parent本身就是y，此句代码无意义
			if(fillNodeY->Parent==nodeX)
			{
				fillNodeZ->Parent=fillNodeY;
			}
			else
			{
				//如果后继y不是z的结点则交换y和z
				Transplant(fillNodeY,fillNodeZ);
				fillNodeY->Right=nodeX->Right;
				fillNodeY->Right->Parent=fillNodeY;
			}
			//交换y和x
			Transplant(nodeX,fillNodeY);
			fillNodeY->Left=nodeX->Left;
			fillNodeY->Left->Parent=fillNodeY;
			fillNodeY->Color=nodeX->Color;
			doubleColorNode=fillNodeZ;
		}
		//减少Size
		//当前结点z是最底层更改的结点，并且它是向上移动的，所以从z开始往上到根的简单路径依次减1
		RefreshMax(fillNodeZ);
		fillNodeZ=fillNodeZ->Parent;
		while(fillNodeZ!=_nil)
		{
			RefreshMax(fillNodeZ);
			fillNodeZ=fillNodeZ->Parent;
		}

		//如果损失了黑色，那么就针对具有双重颜色的结点进行修复
		if(color==IntervalTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	//搜索
	IntervalTreeNode<T>* Search(int low,int high)
	{
		IntervalTreeNode<T>* node=_root;
		while(node!=_nil&&(low>=node->High||high<=node->Low))
		{
			if(node->Left!=_nil&&node->Left->Max>=low)
			{
				node=node->Left;
			}
			else
			{
				node=node->Right;
			}
		}
		return node;
	}
	//是否是空结点
	bool IsNil(IntervalTreeNode<T>* node)
	{
		return node==_nil;
	}
	//获得空结点
	IntervalTreeNode<T>* Root()
	{
		return _root;
	}
private:
	//哨兵
	IntervalTreeNode<T>* _nil;
	//根结点
	IntervalTreeNode<T>* _root;
	//左旋转
	void LeftRotate(IntervalTreeNode<T>* parent)
	{
		//右结点的左结点作为父结点的右结点
		IntervalTreeNode<T> *right=parent->Right;
		parent->Right=right->Left;
		if(right->Left!=_nil)
		{
			right->Left->Parent=parent;
		}
		//右结点成为父结点
		right->Parent=parent->Parent;
		if(parent->Parent==_nil)
		{
			_root=right;
		}
		else if(parent==parent->Parent->Left)
		{
			parent->Parent->Left=right;
		}
		else
		{
			parent->Parent->Right=right;
		}
		//父结点成为左结点
		right->Left=parent;
		parent->Parent=right;
		//更新max
		RefreshMax(parent);
		RefreshMax(right);
		
	}
	//右旋转
	void RightRotate(IntervalTreeNode<T>* parent)
	{
		//左结点的右结点作为父结点的左结点
		IntervalTreeNode<T> *left=parent->Left;
		parent->Left=left->Right;
		if(left->Right!=_nil)
		{
			left->Right->Parent=parent;
		}
		//左结点作为父结点
		left->Parent=parent->Parent;
		if(parent->Parent==_nil)
		{
			_root=left;
		}
		else if(parent==parent->Parent->Right)
		{
			parent->Parent->Right=left;
		}
		else
		{
			parent->Parent->Left=left;
		}
		//父结点作为右结点
		left->Right=parent;
		parent->Parent=left;
		//更新max
		RefreshMax(parent);
		RefreshMax(left);
	}
	//添加
    void Insert(IntervalTreeNode<T>* node)
	{
		//找到正确位置
		IntervalTreeNode<T>* tempNode=_nil;
		IntervalTreeNode<T>* currentNode=_root;
		while(currentNode!=_nil)
		{
			//更新max
			if(currentNode->Max<node->High)
			{
				currentNode->Max=node->High;
			}
			tempNode=currentNode;
			if(node->Low<currentNode->Low)
			{
				currentNode=currentNode->Left;
			}
			else
			{
				currentNode=currentNode->Right;
			}
		}
		//更新结点信息
		//第一个结点添加时，tempNode为nil，此时就保证了root的parent为nil
		node->Parent=tempNode;
		if(tempNode==_nil)
		{
			_root=node;
		}
		else if(node->Low<tempNode->Low)
		{
			tempNode->Left=node;
		}
		else 
		{
			tempNode->Right=node;
		}
		//这里保证了每个叶结点的子结点为nil
		node->Left=_nil;
		node->Right=_nil;
		//置为红色
		node->Color=IntervalTreeNode<T>::Red;
		InsertFixUp(node);
	}
	//添加恢复
	void InsertFixUp(IntervalTreeNode<T>* node)
	{
		//默认node为红色
		//当父结点为红色
		while(node->Parent->Color==IntervalTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				//叔结点
				IntervalTreeNode<T>* uncle=node->Parent->Parent->Right;
				//1.如果当前结点为红色，叔结点为红色，则需要把父结点和树结点置为黑色，祖父结点置为红色
				if(uncle->Color==IntervalTreeNode<T>::Red)
				{
					node->Parent->Color=IntervalTreeNode<T>::Black;
					uncle->Color=IntervalTreeNode<T>::Black;
					node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				//2.叔结点为黑色且node是右结点
				else if(node==node->Parent->Right)
				{
					//左旋转后node成为父结点，父结点成为左结点
					LeftRotate(node->Parent);
					node=node->Left;
				}
				//3.叔节点为黑色且node是左节点
				node->Parent->Color=IntervalTreeNode<T>::Black;
				node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				IntervalTreeNode<T>* uncle=node->Parent->Parent->Left;
				//1.如果当前结点为红色，叔结点为红色，则需要把父结点和树结点置为黑色，祖父结点置为红色
				if(uncle->Color==IntervalTreeNode<T>::Red)
				{
					node->Parent->Color=IntervalTreeNode<T>::Black;
					uncle->Color=IntervalTreeNode<T>::Black;
					node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				//2.叔结点为黑色且node是右结点
				else if(node==node->Parent->Left)
				{
					//右旋转后node成为父结点，父结点成为右结点
					RightRotate(node->Parent);
					node=node->Right;
				}
				//3.叔节点为黑色且node是左节点
				node->Parent->Color=IntervalTreeNode<T>::Black;
				node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=IntervalTreeNode<T>::Black;
	}
	//删除恢复
	//总的思想是将双重结点上升，知道省道一个红结点或根结点
	void DeleteFixUp(IntervalTreeNode<T>* node)
	{
		//兄弟结点
		IntervalTreeNode<T>* brother=_nil;
		//当双重结点为红色结点时，原来结点黑色权重为0，设置后黑色权重为1
		//当双重结点为即使这个结点具备多重权重也不会影响后续的所有结点，因为每个结点都增加了1
		while(node!=_root&&node->Color==IntervalTreeNode<T>::Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				//1.兄弟结点是红色，
				//旋转后，对于各个分支都保持原状，但兄弟结点变为黑色，可以使用234继续
				if(brother->Color==Red)
				{
					brother->Color=IntervalTreeNode<T>::Black;
					node->Parent->Color=Red;
					//左旋转后原结点上升
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				//2.兄弟结点是黑色，兄弟结点的两个子结点都是黑色
				//将兄弟结点置为红色后，兄弟结点分支少了一个黑色权重
				if(brother->Left->Color==IntervalTreeNode<T>::Black && brother->Right->Color==IntervalTreeNode<T>::Black)
				{
					brother->Color=Red;
					//上升结点
					node=node->Parent;
					continue;
				}
				//3.兄弟结点是黑色，兄弟结点的左结点红色，右结点是黑色
				//右转后，兄弟结点的左结点成为兄弟结点的右节点，符合4
				else if(brother->Right->Color==IntervalTreeNode<T>::Black)
				{
					brother->Left->Color=IntervalTreeNode<T>::Black;
					brother->Color=Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				//4.兄弟结点是黑色，兄弟结点的右孩子是红色
				//在结点分支上，增加了父结点的黑色，兄弟结点的替代也变成黑色，所以兄弟结点分支不变
				brother->Color=node->Parent->Color;
				node->Parent->Color=IntervalTreeNode<T>::Black;
				brother->Right->Color=IntervalTreeNode<T>::Black;
				LeftRotate(node->Parent);
				node=_root;
			}
			else
			{
				brother=node->Parent->Left;
				if(brother->Color==Red)
				{
					brother->Color=IntervalTreeNode<T>::Black;
					node->Parent->Color=Red;
					RightRotate(node->Parent);
					brother=node->Parent->Left;
				}
				if(brother->Left->Color==IntervalTreeNode<T>::Black && brother->Right->Color==IntervalTreeNode<T>::Black)
				{
					brother->Color=Red;
					node=node->Parent;
					continue;
				}
				else if(brother->Left->Color==IntervalTreeNode<T>::Black)
				{
					brother->Right->Color=IntervalTreeNode<T>::Black;
					brother->Color=Red;
					LeftRotate(brother);
					brother=node->Parent->Left;
				}
				brother->Color=node->Parent->Color;
				node->Parent->Color=IntervalTreeNode<T>::Black;
				brother->Left->Color=IntervalTreeNode<T>::Black;
				RightRotate(node->Parent);
				break;
			}
		}

		node->Color=IntervalTreeNode<T>::Black;
	}
	//移植结点
	void Transplant(IntervalTreeNode<T>* removeNode,IntervalTreeNode<T>* fillNode)
	{
		if(removeNode->Parent==_nil)
		{
			_root=fillNode;
		}
		else if(removeNode==removeNode->Parent->Left)
		{
			removeNode->Parent->Left=fillNode;
		}
		else
		{
			removeNode->Parent->Right=fillNode;
		}
		//这里不用判断fillNode，因为即使是nil，也不是NULL
		fillNode->Parent=removeNode->Parent;
		//更新max
		RefreshMax(fillNode);
	}
	//获得最小值
	IntervalTreeNode<T>* Minimum(IntervalTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	//更新结点的max属性
	void RefreshMax(IntervalTreeNode<T>* node)
	{
		if(node==_nil)
		{
			return;
		}
		node->Max=max(max(node->Left->Max,node->Right->Max),node->High);
	}
	//删除结点
	void DeletePoint(IntervalTreeNode<T>* node)
	{
		if(node==_nil)
		{
			return;
		}
		DeletePoint(node->Left);
		DeletePoint(node->Right);
		delete node;
	}
};