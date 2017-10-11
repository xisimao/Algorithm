#pragma once
#include "OrderStatisticTreeNode.h"
template <typename T>
class OrderStatisticTree
{
public:
	OrderStatisticTree()
	{
		_nil=new OrderStatisticTreeNode<T>();
		//哨兵的其它属性并不重要
		_nil->Color=OrderStatisticTreeNode<T>::Black;
		_nil->Size=0;
		_root=_nil;
	}
	~OrderStatisticTree()
	{
		OrderStatisticTreeNode<T>* node=_root;
		DeletePoint(_root);
		delete _nil;
	}
	//添加
    void Insert(T key)
	{
		OrderStatisticTreeNode<T>* node=new OrderStatisticTreeNode<T>();
		node->Key=key;
		Insert(node);
	}
	//删除
	void Delete(OrderStatisticTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		//用于替代x结点的后继结点y
		OrderStatisticTreeNode<T>* fillNodeY=_nil;
		//用于替代y结点的子结点z
		OrderStatisticTreeNode<T>* fillNodeZ=_nil;
		//具有双重颜色的结点
		OrderStatisticTreeNode<T>* doubleColorNode=_nil;
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
		fillNodeZ->Size-=1;
		fillNodeZ=fillNodeZ->Parent;
		while(fillNodeZ!=_nil)
		{
			fillNodeZ->Size-=1;
			fillNodeZ=fillNodeZ->Parent;
		}

		//如果损失了黑色，那么就针对具有双重颜色的结点进行修复
		if(color==OrderStatisticTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	//搜索
	OrderStatisticTreeNode<T>* Search(T key)
	{
		return Search(_root,key);
	}
	//选择指定秩
	OrderStatisticTreeNode<T>* Select(int i)
	{
		return Select(_root,i);
	}
	//确定秩
	int Rank(OrderStatisticTreeNode<T>* node)
	{
		int rank=node->Left->Size+1;

		while(node!=_root)
		{
			if(node==node->Parent->Right)
			{
				rank=rank+node->Parent->Left->Size+1;
			}
			node=node->Parent;
		}
		return rank;
	}
	//判断结点是否为空
	bool IsNil(OrderStatisticTreeNode<T>* node)
	{
		return node==_nil;
	}
	//获得空结点
	OrderStatisticTreeNode<T>* Root()
	{
		return _root;
	}

private:
	//哨兵
	OrderStatisticTreeNode<T>* _nil;
	//根结点
	OrderStatisticTreeNode<T>* _root;
	//添加
	void Insert(OrderStatisticTreeNode<T>* node)
	{
		//初始化Size
		node->Size=1;
		//找到正确位置
		OrderStatisticTreeNode<T>* tempNode=_nil;
		OrderStatisticTreeNode<T>* currentNode=_root;
		while(currentNode!=_nil)
		{
			//增加Size
			currentNode->Size+=1;
			tempNode=currentNode;
			if(node->Key<currentNode->Key)
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
		else if(node->Key<tempNode->Key)
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
		node->Color=OrderStatisticTreeNode<T>::Red;
		InsertFixUp(node);
	}
	//添加恢复
	void InsertFixUp(OrderStatisticTreeNode<T>* node)
	{
		//默认node为红色
		//当父结点为红色
		while(node->Parent->Color==OrderStatisticTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				//叔结点
				OrderStatisticTreeNode<T>* uncle=node->Parent->Parent->Right;
				//1.如果当前结点为红色，叔结点为红色，则需要把父结点和树结点置为黑色，祖父结点置为红色
				if(uncle->Color==OrderStatisticTreeNode<T>::Red)
				{
					node->Parent->Color=OrderStatisticTreeNode<T>::Black;
					uncle->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
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
				node->Parent->Color=OrderStatisticTreeNode<T>::Black;
				node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				OrderStatisticTreeNode<T>* uncle=node->Parent->Parent->Left;
				//1.如果当前结点为红色，叔结点为红色，则需要把父结点和树结点置为黑色，祖父结点置为红色
				if(uncle->Color==OrderStatisticTreeNode<T>::Red)
				{
					node->Parent->Color=OrderStatisticTreeNode<T>::Black;
					uncle->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
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
				node->Parent->Color=OrderStatisticTreeNode<T>::Black;
				node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=OrderStatisticTreeNode<T>::Black;
	}
	//左旋转
	void LeftRotate(OrderStatisticTreeNode<T>* parent)
	{
		//右结点的左结点作为父结点的右结点
		OrderStatisticTreeNode<T> *right=parent->Right;
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
		//更新Size
		right->Size=parent->Size;
		parent->Size=parent->Left->Size+parent->Right->Size+1;
	}
	//右旋转
	void RightRotate(OrderStatisticTreeNode<T>* parent)
	{
		//左结点的右结点作为父结点的左结点
		OrderStatisticTreeNode<T> *left=parent->Left;
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
		//更新Size
		left->Size=parent->Size;
		parent->Size=parent->Left->Size+parent->Right->Size+1;
	}
	//删除恢复
	//总的思想是将双重结点上升，知道省道一个红结点或根结点
	void DeleteFixUp(OrderStatisticTreeNode<T>* node)
	{
		//兄弟结点
		OrderStatisticTreeNode<T>* brother=_nil;
		//当双重结点为红色结点时，原来结点黑色权重为0，设置后黑色权重为1
		//当双重结点为即使这个结点具备多重权重也不会影响后续的所有结点，因为每个结点都增加了1
		while(node!=_root&&node->Color==Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				//1.兄弟结点是红色，
				//旋转后，对于各个分支都保持原状，但兄弟结点变为黑色，可以使用234继续
				if(brother->Color==OrderStatisticTreeNode<T>::Red)
				{
					brother->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Color=OrderStatisticTreeNode<T>::Red;
					//左旋转后原结点上升
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				//2.兄弟结点是黑色，兄弟结点的两个子结点都是黑色
				//将兄弟结点置为红色后，兄弟结点分支少了一个黑色权重
				if(brother->Left->Color==OrderStatisticTreeNode<T>::Black && brother->Right->Color==OrderStatisticTreeNode<T>::Black)
				{
					brother->Color=OrderStatisticTreeNode<T>::Red;
					//上升结点
					node=node->Parent;
					continue;
				}
				//3.兄弟结点是黑色，兄弟结点的左结点红色，右结点是黑色
				//右转后，兄弟结点的左结点成为兄弟结点的右节点，符合4
				else if(brother->Right->Color==OrderStatisticTreeNode<T>::Black)
				{
					brother->Left->Color=OrderStatisticTreeNode<T>::Black;
					brother->Color=OrderStatisticTreeNode<T>::Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				//4.兄弟结点是黑色，兄弟结点的右孩子是红色
				//在结点分支上，增加了父结点的黑色，兄弟结点的替代也变成黑色，所以兄弟结点分支不变
				brother->Color=node->Parent->Color;
				node->Parent->Color=OrderStatisticTreeNode<T>::Black;
				brother->Right->Color=OrderStatisticTreeNode<T>::Black;
				LeftRotate(node->Parent);
				node=_root;
			}
			else
			{
				brother=node->Parent->Left;
				if(brother->Color==OrderStatisticTreeNode<T>::Red)
				{
					brother->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Color=OrderStatisticTreeNode<T>::Red;
					RightRotate(node->Parent);
					brother=node->Parent->Left;
				}
				if(brother->Left->Color==OrderStatisticTreeNode<T>::Black && brother->Right->Color==Black)
				{
					brother->Color=OrderStatisticTreeNode<T>::Red;
					node=node->Parent;
					continue;
				}
				else if(brother->Left->Color==OrderStatisticTreeNode<T>::Black)
				{
					brother->Right->Color=OrderStatisticTreeNode<T>::Black;
					brother->Color=OrderStatisticTreeNode<T>::Red;
					LeftRotate(brother);
					brother=node->Parent->Left;
				}
				brother->Color=node->Parent->Color;
				node->Parent->Color=OrderStatisticTreeNode<T>::Black;
				brother->Left->Color=OrderStatisticTreeNode<T>::Black;
				RightRotate(node->Parent);
				break;
			}
		}
		node->Color=OrderStatisticTreeNode<T>::Black;
	}
	//移植结点
	void Transplant(OrderStatisticTreeNode<T>* removeNode,OrderStatisticTreeNode<T>* fillNode)
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
		//更新Size
		fillNode->Size=removeNode->Size;
	}
	//获得最小值
	OrderStatisticTreeNode<T>* Minimum(OrderStatisticTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	//搜索
	OrderStatisticTreeNode<T>* Search(OrderStatisticTreeNode<T>* node,T key)
	{
		if(node==_nil||node->Key==key)
		{
			return node;
		}
		if(key<node->Key)
		{
			return Search(node->Left,key);
		}
		return Search(node->Right,key);
	}
	//选择
	OrderStatisticTreeNode<T>* Select(OrderStatisticTreeNode<T>* node,int i)
	{
		int rank=node->Left->Size+1;
		if(i==rank)
		{
			return node;
		}
		else if(i<rank)
		{
			return Select(node->Left,i);
		}
		else
		{
			return Select(node->Right,i-rank);
		}
	}
    //删除结点
	void DeletePoint(OrderStatisticTreeNode<T>* node)
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

