#pragma once
#include <vector>

#include "RedBlackTreeNode.h"

using namespace std;

template <typename T>
//性质1 每个结点是红色或者黑色
//性质2 根结点是黑色
//性质3 叶结点（NIL）是黑色的
//性质4 如果结点为红色，则它的两个子结点都为黑色
//性质5 对每个结点，从该结点到其后代叶结点的简单路径上，均包含相同数目的黑色结点。
class RedBlackTree
{
public:
	RedBlackTree()
	{
		_nil=new RedBlackTreeNode<T>();
		//哨兵的其它属性并不重要
		_nil->Color=RedBlackTreeNode<T>::Black;
		//可以省掉判断
		_nil->Left=_nil;
		_nil->Right=_nil;
		_nil->Parent=_nil;
		_root=_nil;
	}
	~RedBlackTree()
	{
		RedBlackTreeNode<T>* node=_root;
		DeletePoint(_root);
		delete _nil;
	}

	//添加
    RedBlackTreeNode<T>* Insert(T key)
	{
		RedBlackTreeNode<T>* node=new RedBlackTreeNode<T>();
		node->Key=key;
		Insert(node);
		return node;
	}

	//删除
	void Delete(RedBlackTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		//用于替代x结点的后继结点y
		RedBlackTreeNode<T>* fillNodeY=_nil;
		//用于替代y结点的子结点z
		RedBlackTreeNode<T>* fillNodeZ=_nil;
		//具有双重颜色的结点
		RedBlackTreeNode<T>* doubleColorNode=_nil;
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
		//如果损失了黑色，那么就针对具有双重颜色的结点进行修复
		if(color==RedBlackTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	//搜索
	RedBlackTreeNode<T>* Search(T key)
	{
		return Search(_root,key);
	}
	//检查红黑树性质
	int CheckRedBlack()
	{
		//根节点应为黑色
		if(_root->Color==RedBlackTreeNode<T>::Red)
		{
			return 2;
		}
		//每个叶结点为黑色
		if(_nil->Color==RedBlackTreeNode<T>::Red)
		{
			return 3;
		}
		vector<RedBlackTreeNode<T>*> error4;
		Check4(_root,error4);
		if(!error4.empty())
		{
			return 4;
		}
		vector<RedBlackTreeNode<T>*> error5;
		Check5(_root,error5);
		return error5.empty()?0:5;
	}
	//是否是空结点
	bool IsNil(RedBlackTreeNode<T>* node)
	{
		return node==_nil;
	}
	//获得空结点
	RedBlackTreeNode<T>* Root()
	{
		return _root;
	}
	/**
	 * 获得后继结点
	 * @param node 结点
	 * @return 如果有后继结点则返回，否则返回哨兵
	 */
	RedBlackTreeNode<T>* Successor(RedBlackTreeNode<T>* node)
	{
		if(node==_nil)
		{
			return _nil;
		}
		if(node->Right!=_nil)
		{
			return Minimum(node->Right);
		}
		RedBlackTreeNode<T>* parent=node->Parent;
		while(parent!=_nil&&node==parent->Right)
		{
			node=parent;
			parent=parent->Parent;
		}
		return parent;
	}
	/**
	 * 获得前续结点
	 * @param node 结点
	 * @return 如果有前续结点则返回，否则返回哨兵
	 */
	RedBlackTreeNode<T>* Predecessor(RedBlackTreeNode<T>* node)
	{
		T tempKey=node->Key;
		RedBlackTreeNode<T>* temp=node;
		if(node==_nil)
		{
			return _nil;
		}
		if(node->Left!=_nil)
		{
			return Maximum(node->Left);
		}

		RedBlackTreeNode<T>* parent=node->Parent;

		while(parent!=_nil&&node==parent->Left)
		{
			node=parent;
			parent=parent->Parent;
		}
		return parent;
	}
	/**
	 * 获得最小值
	 * @param node 结点
	 * @return 最小值结点，没有最小值时返回哨兵
	 */
	RedBlackTreeNode<T>* Minimum(RedBlackTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	/**
	 * 获得最大值
	 * @param node 结点
	 * @return 最大值结点，没有最大值时返回哨兵
	 */
	RedBlackTreeNode<T>* Maximum(RedBlackTreeNode<T>* node)
	{
		while(node->Right!=_nil)
		{
			node=node->Right;
		}
		return node;
	}
private:
	//哨兵
	RedBlackTreeNode<T>* _nil;
	//根结点
	RedBlackTreeNode<T>* _root;
	//左旋转
	void LeftRotate(RedBlackTreeNode<T>* parent)
	{
		//右结点的左结点作为父结点的右结点
		RedBlackTreeNode<T> *right=parent->Right;
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
	}
	//右旋转
	void RightRotate(RedBlackTreeNode<T>* parent)
	{
		//左结点的右结点作为父结点的左结点
		RedBlackTreeNode<T> *left=parent->Left;
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
	}
	//添加
    void Insert(RedBlackTreeNode<T>* node)
	{
		//找到正确位置
		RedBlackTreeNode<T>* tempNode=_nil;
		RedBlackTreeNode<T>* currentNode=_root;
		while(currentNode!=_nil)
		{
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
		node->Color=RedBlackTreeNode<T>::Red;
		InsertFixUp(node);
	}
	//添加恢复
	void InsertFixUp(RedBlackTreeNode<T>* node)
	{
		//默认node为红色
		//当父结点为红色
		while(node->Parent->Color==RedBlackTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				//叔结点
				RedBlackTreeNode<T>* uncle=node->Parent->Parent->Right;
				//1.如果当前结点为红色，叔结点为红色，则需要把父结点和树结点置为黑色，祖父结点置为红色
				if(uncle->Color==RedBlackTreeNode<T>::Red)
				{
					node->Parent->Color=RedBlackTreeNode<T>::Black;
					uncle->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
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
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				RedBlackTreeNode<T>* uncle=node->Parent->Parent->Left;
				//1.如果当前结点为红色，叔结点为红色，则需要把父结点和树结点置为黑色，祖父结点置为红色
				if(uncle->Color==RedBlackTreeNode<T>::Red)
				{
					node->Parent->Color=RedBlackTreeNode<T>::Black;
					uncle->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
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
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=RedBlackTreeNode<T>::Black;
	}
	//删除恢复
	//总的思想是将双重结点上升，知道省道一个红结点或根结点
	void DeleteFixUp(RedBlackTreeNode<T>* node)
	{
		//兄弟结点
		RedBlackTreeNode<T>* brother=_nil;
		//当双重结点为红色结点时，原来结点黑色权重为0，设置后黑色权重为1
		//当双重结点为即使这个结点具备多重权重也不会影响后续的所有结点，因为每个结点都增加了1
		while(node!=_root&&node->Color==RedBlackTreeNode<T>::Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				//1.兄弟结点是红色，
				//旋转后，对于各个分支都保持原状，但兄弟结点变为黑色，可以使用234继续
				if(brother->Color==RedBlackTreeNode<T>::Red)
				{
					brother->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Color=RedBlackTreeNode<T>::Red;
					//左旋转后原结点上升
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				//2.兄弟结点是黑色，兄弟结点的两个子结点都是黑色
				//将兄弟结点置为红色后，兄弟结点分支少了一个黑色权重
				if(brother->Left->Color==RedBlackTreeNode<T>::Black && brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Color=RedBlackTreeNode<T>::Red;
					//上升结点
					node=node->Parent;
					continue;
				}
				//3.兄弟结点是黑色，兄弟结点的左结点红色，右结点是黑色
				//右转后，兄弟结点的左结点成为兄弟结点的右节点，符合4
				else if(brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Left->Color=RedBlackTreeNode<T>::Black;
					brother->Color=RedBlackTreeNode<T>::Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				//4.兄弟结点是黑色，兄弟结点的右孩子是红色
				//在结点分支上，增加了父结点的黑色，兄弟结点的替代也变成黑色，所以兄弟结点分支不变
				brother->Color=node->Parent->Color;
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				brother->Right->Color=RedBlackTreeNode<T>::Black;
				LeftRotate(node->Parent);
				node=_root;
			}
			else
			{
				brother=node->Parent->Left;
				if(brother->Color==RedBlackTreeNode<T>::Red)
				{
					brother->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Color=RedBlackTreeNode<T>::Red;
					RightRotate(node->Parent);
					brother=node->Parent->Left;
				}
				if(brother->Left->Color==RedBlackTreeNode<T>::Black && brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Color=RedBlackTreeNode<T>::Red;
					node=node->Parent;
					continue;
				}
				else if(brother->Left->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Right->Color=RedBlackTreeNode<T>::Black;
					brother->Color=RedBlackTreeNode<T>::Red;
					LeftRotate(brother);
					brother=node->Parent->Left;
				}
				brother->Color=node->Parent->Color;
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				brother->Left->Color=RedBlackTreeNode<T>::Black;
				RightRotate(node->Parent);
				break;
			}
		}
		node->Color=RedBlackTreeNode<T>::Black;
	}
	//移植结点
	void Transplant(RedBlackTreeNode<T>* removeNode,RedBlackTreeNode<T>* fillNode)
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
	}
	//搜索
	RedBlackTreeNode<T>* Search(RedBlackTreeNode<T>* node,T key)
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
	//检查性质4
	void Check4(RedBlackTreeNode<T>* node,vector<RedBlackTreeNode<T>*>& error)
	{
		if(node==_nil)
		{
			return ;
		}
		if(node->Color==RedBlackTreeNode<T>::Red&&(node->Left->Color==RedBlackTreeNode<T>::Red||node->Right->Color==RedBlackTreeNode<T>::Red))
		{
			error.push_back(node);
		}
		Check4(node->Left,error);
		Check4(node->Right,error);
	}
	//检查性质5
	void Check5(RedBlackTreeNode<T>* node,vector<RedBlackTreeNode<T>*>& error)
	{
		if(node==_nil)
		{
			return; 
		}
		vector<int> list;
		GetBlackCount(node,list,0);
		int temp=-1;
		for(int i=0;i<list.size();++i)
		{
			if(temp==-1)
			{
				temp=list.at(i);
			}
			else if(temp==list.at(i))
			{
				continue;
			}
			else 
			{
				error.push_back(node);
				break;
			}
		}
		Check5(node->Left,error);
		Check5(node->Right,error);
	}
	//获取到每个叶结点的黑色结点数量
	void GetBlackCount(RedBlackTreeNode<T>* node,vector<int>& list,int count)
	{
		if(node==_nil)
		{
			list.push_back(count);
			return;
		}
		if(node->Color==RedBlackTreeNode<T>::Black)
		{
			++count;
		}
		GetBlackCount(node->Left,list,count);
		GetBlackCount(node->Right,list,count);
	}
	//删除结点
	void DeletePoint(RedBlackTreeNode<T>* node)
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

