#pragma once
#include "TreeNode.h"

template <typename T>
class Tree
{
public:
	Tree()
		:_root(NULL)
	{
	}
	~Tree()
	{
		TreeNode<T>* node=_root;
		DeletePoint(_root);
	}

	TreeNode<T>*Search(T key)
	{
		return Search(_root,key);
	}
	TreeNode<T>* Minimum()
	{
		return Minimum(_root);
	}
	TreeNode<T>* Maximum()
	{
		return Maximum(_root);
	}


	TreeNode<T>* Successor(TreeNode<T>* node)
	{
		if(node==NULL)
		{
			return NULL;
		}
		if(node->Right!=NULL)
		{
			return Minimum(node->Right);
		}
		TreeNode<T>* parent=node->Parent;
		while(parent!=NULL&&node==parent->Right)
		{
			node=parent;
			parent=parent->Parent;
		}
		return parent;
	}

	TreeNode<T>* Predecessor(TreeNode<T>* node)
	{
		int tempKey=node->Key;
		TreeNode<T>* temp=node;
		if(node==NULL)
		{
			return NULL;
		}
		if(node->Left!=NULL)
		{
			return Maximum(node->Left);
		}
		
		

		TreeNode<T>* parent=node->Parent;
		
		while(parent!=NULL&&node==parent->Left)
		{
			node=parent;
			parent=parent->Parent;
		}
		return parent;
	}
	void Insert(T value)
	{
		TreeNode<T>* node=new TreeNode<T>();
		node->Key=value;
		Insert(node);
	}

	void Delete(TreeNode<T>* node)
	{
		if(node==NULL)
		{
			return;
		}
		//���û�����ӽ�������ҽڵ����
		if(node->Left==NULL)
		{
			Transplant(node,node->Right);
		}
		//���û�����ӽ�������������
		else if(node->Right==NULL)
		{
			Transplant(node,node->Left);
		}
		else
		{
			TreeNode<T>* successor=Minimum(node->Right);
			//ɾ��ʱ�����ҽ�㲻�����̣����ú�̵��ҽ�������̣��ٽ��Ҽ�����Ϊ��̵��Ҽ���
			if(successor->Parent!=node)
			{
				Transplant(successor,successor->Right);
				successor->Right=node->Right;
				successor->Right->Parent=successor;
			}
			//ɾ��ʱ�����ҽڵ�������̻��������ж��н�����������������ҽڵ��滻
			Transplant(node,successor);
			successor->Left=node->Left;
			successor->Left->Parent=successor;
		}
		delete node;
	}
	TreeNode<T>* Root()
	{
		return _root;
	}
private:
	//�����
	TreeNode<T>* _root;
	//��ֲ���
	void Transplant(TreeNode<T>* removeNode,TreeNode<T>* fillNode)
	{
		if(removeNode->Parent==NULL)
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
		if(fillNode!=NULL)
		{
			fillNode->Parent=removeNode->Parent;
		}
	}
	TreeNode<T>* Search(TreeNode<T>* node,T key)
	{
		if(node==NULL||node->Key==key)
		{
			return node;
		}
		if(key<node->Key)
		{
			return Search(node->Left,key);
		}
		return Search(node->Right,key);
	}
	TreeNode<T>* IterativeSearch(TreeNode<T>* node,T key)
	{
		while(node!=null&&node->Key!=key)
		{
			if(key<node->key)
			{
				node=node->left;
			}
			else
			{
				node=node->right;
			}
		}
		return node;
	}
	TreeNode<T>* Minimum(TreeNode<T>* node)
	{
		while(node->Left!=NULL)
		{
			node=node->Left;
		}
		return node;
	}
	TreeNode<T>* Maximum(TreeNode<T>* node)
	{
 		while(node->Right!=NULL)
		{
			node=node->Right;
		}
		return node;
	}
	void Insert(TreeNode<T>* node)
	{
		TreeNode<T>* temp=_root;
		TreeNode<T>* tempBak=NULL;
		while(temp!=NULL)
		{
			tempBak=temp;
			if(node->Key<temp->Key)
			{
				temp=temp->Left;
			}
			else
			{
				temp=temp->Right;
			}
		}
		node->Parent=tempBak;
		if(tempBak==NULL)
		{
			_root=node;
		}
		else if(node->Key<tempBak->Key)
		{
			tempBak->Left=node;
		}
		else
		{
			tempBak->Right=node;
		}
	}
	    //ɾ�����
	void DeletePoint(TreeNode<T>* node)
	{
		if(node==NULL)
		{
			return;
		}
		DeletePoint(node->Left);
		DeletePoint(node->Right);
		delete node;
	}
};