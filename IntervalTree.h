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
		//�ڱ����������Բ�����Ҫ
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
	//���
    void Insert(T low,T high)
	{
		IntervalTreeNode<T>* node=new IntervalTreeNode<T>();
		node->Low=low;
		node->High=high;
		node->Max=high;
		Insert(node);
	}
	//ɾ��
	void Delete(IntervalTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		//�������x���ĺ�̽��y
		IntervalTreeNode<T>* fillNodeY=_nil;
		//�������y�����ӽ��z
		IntervalTreeNode<T>* fillNodeZ=_nil;
		//����˫����ɫ�Ľ��
		IntervalTreeNode<T>* doubleColorNode=_nil;
		//color��ʾ��ǰ��ʧ����ɫ
		bool color;
		//����ǰ�����жϣ���Ϊ����������x��y��㣬��û�н�y����ɫ��ֵΪx��㣬����ԭ��x������ɫ��ʧ���ˣ�y��Ϊ˫����ɫ���
		if(nodeX->Left==_nil)
		{
			color=nodeX->Color;
			//y��������nil������nil��parent����Transplant�����и�ֵ������������ʹ��
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
		//��xyz��㶼�߱�ʱ����Ϊy�ḳֵΪx����ɫ����z�滻y��������ʧ��y����ɫ��z��Ϊ˫����ɫ���
		else
		{
			//�ҵ�x�ĺ��
			fillNodeY=Minimum(nodeX->Right);
			color=fillNodeY->Color;
			fillNodeZ=fillNodeY->Right;
			//����ж���Ҫ��Ӧ��z���Ϊnil���������Ϊnil��parent�������
			//���Ǻ���DeleteFixUp����Ҫ�õ�parent���ԣ�����Ҫ���丳ֵ������������Transplant���и�ֵ
			//�����ڷ�nil��㣬��ôz����parent�������y���˾����������
			if(fillNodeY->Parent==nodeX)
			{
				fillNodeZ->Parent=fillNodeY;
			}
			else
			{
				//������y����z�Ľ���򽻻�y��z
				Transplant(fillNodeY,fillNodeZ);
				fillNodeY->Right=nodeX->Right;
				fillNodeY->Right->Parent=fillNodeY;
			}
			//����y��x
			Transplant(nodeX,fillNodeY);
			fillNodeY->Left=nodeX->Left;
			fillNodeY->Left->Parent=fillNodeY;
			fillNodeY->Color=nodeX->Color;
			doubleColorNode=fillNodeZ;
		}
		//����Size
		//��ǰ���z����ײ���ĵĽ�㣬�������������ƶ��ģ����Դ�z��ʼ���ϵ����ļ�·�����μ�1
		RefreshMax(fillNodeZ);
		fillNodeZ=fillNodeZ->Parent;
		while(fillNodeZ!=_nil)
		{
			RefreshMax(fillNodeZ);
			fillNodeZ=fillNodeZ->Parent;
		}

		//�����ʧ�˺�ɫ����ô����Ծ���˫����ɫ�Ľ������޸�
		if(color==IntervalTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	//����
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
	//�Ƿ��ǿս��
	bool IsNil(IntervalTreeNode<T>* node)
	{
		return node==_nil;
	}
	//��ÿս��
	IntervalTreeNode<T>* Root()
	{
		return _root;
	}
private:
	//�ڱ�
	IntervalTreeNode<T>* _nil;
	//�����
	IntervalTreeNode<T>* _root;
	//����ת
	void LeftRotate(IntervalTreeNode<T>* parent)
	{
		//�ҽ���������Ϊ�������ҽ��
		IntervalTreeNode<T> *right=parent->Right;
		parent->Right=right->Left;
		if(right->Left!=_nil)
		{
			right->Left->Parent=parent;
		}
		//�ҽ���Ϊ�����
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
		//������Ϊ����
		right->Left=parent;
		parent->Parent=right;
		//����max
		RefreshMax(parent);
		RefreshMax(right);
		
	}
	//����ת
	void RightRotate(IntervalTreeNode<T>* parent)
	{
		//������ҽ����Ϊ����������
		IntervalTreeNode<T> *left=parent->Left;
		parent->Left=left->Right;
		if(left->Right!=_nil)
		{
			left->Right->Parent=parent;
		}
		//������Ϊ�����
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
		//�������Ϊ�ҽ��
		left->Right=parent;
		parent->Parent=left;
		//����max
		RefreshMax(parent);
		RefreshMax(left);
	}
	//���
    void Insert(IntervalTreeNode<T>* node)
	{
		//�ҵ���ȷλ��
		IntervalTreeNode<T>* tempNode=_nil;
		IntervalTreeNode<T>* currentNode=_root;
		while(currentNode!=_nil)
		{
			//����max
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
		//���½����Ϣ
		//��һ��������ʱ��tempNodeΪnil����ʱ�ͱ�֤��root��parentΪnil
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
		//���ﱣ֤��ÿ��Ҷ�����ӽ��Ϊnil
		node->Left=_nil;
		node->Right=_nil;
		//��Ϊ��ɫ
		node->Color=IntervalTreeNode<T>::Red;
		InsertFixUp(node);
	}
	//��ӻָ�
	void InsertFixUp(IntervalTreeNode<T>* node)
	{
		//Ĭ��nodeΪ��ɫ
		//�������Ϊ��ɫ
		while(node->Parent->Color==IntervalTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				//����
				IntervalTreeNode<T>* uncle=node->Parent->Parent->Right;
				//1.�����ǰ���Ϊ��ɫ������Ϊ��ɫ������Ҫ�Ѹ������������Ϊ��ɫ���游�����Ϊ��ɫ
				if(uncle->Color==IntervalTreeNode<T>::Red)
				{
					node->Parent->Color=IntervalTreeNode<T>::Black;
					uncle->Color=IntervalTreeNode<T>::Black;
					node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				//2.����Ϊ��ɫ��node���ҽ��
				else if(node==node->Parent->Right)
				{
					//����ת��node��Ϊ����㣬������Ϊ����
					LeftRotate(node->Parent);
					node=node->Left;
				}
				//3.��ڵ�Ϊ��ɫ��node����ڵ�
				node->Parent->Color=IntervalTreeNode<T>::Black;
				node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				IntervalTreeNode<T>* uncle=node->Parent->Parent->Left;
				//1.�����ǰ���Ϊ��ɫ������Ϊ��ɫ������Ҫ�Ѹ������������Ϊ��ɫ���游�����Ϊ��ɫ
				if(uncle->Color==IntervalTreeNode<T>::Red)
				{
					node->Parent->Color=IntervalTreeNode<T>::Black;
					uncle->Color=IntervalTreeNode<T>::Black;
					node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				//2.����Ϊ��ɫ��node���ҽ��
				else if(node==node->Parent->Left)
				{
					//����ת��node��Ϊ����㣬������Ϊ�ҽ��
					RightRotate(node->Parent);
					node=node->Right;
				}
				//3.��ڵ�Ϊ��ɫ��node����ڵ�
				node->Parent->Color=IntervalTreeNode<T>::Black;
				node->Parent->Parent->Color=IntervalTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=IntervalTreeNode<T>::Black;
	}
	//ɾ���ָ�
	//�ܵ�˼���ǽ�˫�ؽ��������֪��ʡ��һ�����������
	void DeleteFixUp(IntervalTreeNode<T>* node)
	{
		//�ֵܽ��
		IntervalTreeNode<T>* brother=_nil;
		//��˫�ؽ��Ϊ��ɫ���ʱ��ԭ������ɫȨ��Ϊ0�����ú��ɫȨ��Ϊ1
		//��˫�ؽ��Ϊ��ʹ������߱�����Ȩ��Ҳ����Ӱ����������н�㣬��Ϊÿ����㶼������1
		while(node!=_root&&node->Color==IntervalTreeNode<T>::Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				//1.�ֵܽ���Ǻ�ɫ��
				//��ת�󣬶��ڸ�����֧������ԭ״�����ֵܽ���Ϊ��ɫ������ʹ��234����
				if(brother->Color==Red)
				{
					brother->Color=IntervalTreeNode<T>::Black;
					node->Parent->Color=Red;
					//����ת��ԭ�������
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				//2.�ֵܽ���Ǻ�ɫ���ֵܽ��������ӽ�㶼�Ǻ�ɫ
				//���ֵܽ����Ϊ��ɫ���ֵܽ���֧����һ����ɫȨ��
				if(brother->Left->Color==IntervalTreeNode<T>::Black && brother->Right->Color==IntervalTreeNode<T>::Black)
				{
					brother->Color=Red;
					//�������
					node=node->Parent;
					continue;
				}
				//3.�ֵܽ���Ǻ�ɫ���ֵܽ��������ɫ���ҽ���Ǻ�ɫ
				//��ת���ֵܽ��������Ϊ�ֵܽ����ҽڵ㣬����4
				else if(brother->Right->Color==IntervalTreeNode<T>::Black)
				{
					brother->Left->Color=IntervalTreeNode<T>::Black;
					brother->Color=Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				//4.�ֵܽ���Ǻ�ɫ���ֵܽ����Һ����Ǻ�ɫ
				//�ڽ���֧�ϣ������˸����ĺ�ɫ���ֵܽ������Ҳ��ɺ�ɫ�������ֵܽ���֧����
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
	//��ֲ���
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
		//���ﲻ���ж�fillNode����Ϊ��ʹ��nil��Ҳ����NULL
		fillNode->Parent=removeNode->Parent;
		//����max
		RefreshMax(fillNode);
	}
	//�����Сֵ
	IntervalTreeNode<T>* Minimum(IntervalTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	//���½���max����
	void RefreshMax(IntervalTreeNode<T>* node)
	{
		if(node==_nil)
		{
			return;
		}
		node->Max=max(max(node->Left->Max,node->Right->Max),node->High);
	}
	//ɾ�����
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