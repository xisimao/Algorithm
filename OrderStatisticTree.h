#pragma once
#include "OrderStatisticTreeNode.h"
template <typename T>
class OrderStatisticTree
{
public:
	OrderStatisticTree()
	{
		_nil=new OrderStatisticTreeNode<T>();
		//�ڱ����������Բ�����Ҫ
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
	//���
    void Insert(T key)
	{
		OrderStatisticTreeNode<T>* node=new OrderStatisticTreeNode<T>();
		node->Key=key;
		Insert(node);
	}
	//ɾ��
	void Delete(OrderStatisticTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		//�������x���ĺ�̽��y
		OrderStatisticTreeNode<T>* fillNodeY=_nil;
		//�������y�����ӽ��z
		OrderStatisticTreeNode<T>* fillNodeZ=_nil;
		//����˫����ɫ�Ľ��
		OrderStatisticTreeNode<T>* doubleColorNode=_nil;
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
		fillNodeZ->Size-=1;
		fillNodeZ=fillNodeZ->Parent;
		while(fillNodeZ!=_nil)
		{
			fillNodeZ->Size-=1;
			fillNodeZ=fillNodeZ->Parent;
		}

		//�����ʧ�˺�ɫ����ô����Ծ���˫����ɫ�Ľ������޸�
		if(color==OrderStatisticTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	//����
	OrderStatisticTreeNode<T>* Search(T key)
	{
		return Search(_root,key);
	}
	//ѡ��ָ����
	OrderStatisticTreeNode<T>* Select(int i)
	{
		return Select(_root,i);
	}
	//ȷ����
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
	//�жϽ���Ƿ�Ϊ��
	bool IsNil(OrderStatisticTreeNode<T>* node)
	{
		return node==_nil;
	}
	//��ÿս��
	OrderStatisticTreeNode<T>* Root()
	{
		return _root;
	}

private:
	//�ڱ�
	OrderStatisticTreeNode<T>* _nil;
	//�����
	OrderStatisticTreeNode<T>* _root;
	//���
	void Insert(OrderStatisticTreeNode<T>* node)
	{
		//��ʼ��Size
		node->Size=1;
		//�ҵ���ȷλ��
		OrderStatisticTreeNode<T>* tempNode=_nil;
		OrderStatisticTreeNode<T>* currentNode=_root;
		while(currentNode!=_nil)
		{
			//����Size
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
		//���½����Ϣ
		//��һ��������ʱ��tempNodeΪnil����ʱ�ͱ�֤��root��parentΪnil
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
		//���ﱣ֤��ÿ��Ҷ�����ӽ��Ϊnil
		node->Left=_nil;
		node->Right=_nil;
		//��Ϊ��ɫ
		node->Color=OrderStatisticTreeNode<T>::Red;
		InsertFixUp(node);
	}
	//��ӻָ�
	void InsertFixUp(OrderStatisticTreeNode<T>* node)
	{
		//Ĭ��nodeΪ��ɫ
		//�������Ϊ��ɫ
		while(node->Parent->Color==OrderStatisticTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				//����
				OrderStatisticTreeNode<T>* uncle=node->Parent->Parent->Right;
				//1.�����ǰ���Ϊ��ɫ������Ϊ��ɫ������Ҫ�Ѹ������������Ϊ��ɫ���游�����Ϊ��ɫ
				if(uncle->Color==OrderStatisticTreeNode<T>::Red)
				{
					node->Parent->Color=OrderStatisticTreeNode<T>::Black;
					uncle->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
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
				node->Parent->Color=OrderStatisticTreeNode<T>::Black;
				node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				OrderStatisticTreeNode<T>* uncle=node->Parent->Parent->Left;
				//1.�����ǰ���Ϊ��ɫ������Ϊ��ɫ������Ҫ�Ѹ������������Ϊ��ɫ���游�����Ϊ��ɫ
				if(uncle->Color==OrderStatisticTreeNode<T>::Red)
				{
					node->Parent->Color=OrderStatisticTreeNode<T>::Black;
					uncle->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
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
				node->Parent->Color=OrderStatisticTreeNode<T>::Black;
				node->Parent->Parent->Color=OrderStatisticTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=OrderStatisticTreeNode<T>::Black;
	}
	//����ת
	void LeftRotate(OrderStatisticTreeNode<T>* parent)
	{
		//�ҽ���������Ϊ�������ҽ��
		OrderStatisticTreeNode<T> *right=parent->Right;
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
		//����Size
		right->Size=parent->Size;
		parent->Size=parent->Left->Size+parent->Right->Size+1;
	}
	//����ת
	void RightRotate(OrderStatisticTreeNode<T>* parent)
	{
		//������ҽ����Ϊ����������
		OrderStatisticTreeNode<T> *left=parent->Left;
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
		//����Size
		left->Size=parent->Size;
		parent->Size=parent->Left->Size+parent->Right->Size+1;
	}
	//ɾ���ָ�
	//�ܵ�˼���ǽ�˫�ؽ��������֪��ʡ��һ�����������
	void DeleteFixUp(OrderStatisticTreeNode<T>* node)
	{
		//�ֵܽ��
		OrderStatisticTreeNode<T>* brother=_nil;
		//��˫�ؽ��Ϊ��ɫ���ʱ��ԭ������ɫȨ��Ϊ0�����ú��ɫȨ��Ϊ1
		//��˫�ؽ��Ϊ��ʹ������߱�����Ȩ��Ҳ����Ӱ����������н�㣬��Ϊÿ����㶼������1
		while(node!=_root&&node->Color==Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				//1.�ֵܽ���Ǻ�ɫ��
				//��ת�󣬶��ڸ�����֧������ԭ״�����ֵܽ���Ϊ��ɫ������ʹ��234����
				if(brother->Color==OrderStatisticTreeNode<T>::Red)
				{
					brother->Color=OrderStatisticTreeNode<T>::Black;
					node->Parent->Color=OrderStatisticTreeNode<T>::Red;
					//����ת��ԭ�������
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				//2.�ֵܽ���Ǻ�ɫ���ֵܽ��������ӽ�㶼�Ǻ�ɫ
				//���ֵܽ����Ϊ��ɫ���ֵܽ���֧����һ����ɫȨ��
				if(brother->Left->Color==OrderStatisticTreeNode<T>::Black && brother->Right->Color==OrderStatisticTreeNode<T>::Black)
				{
					brother->Color=OrderStatisticTreeNode<T>::Red;
					//�������
					node=node->Parent;
					continue;
				}
				//3.�ֵܽ���Ǻ�ɫ���ֵܽ��������ɫ���ҽ���Ǻ�ɫ
				//��ת���ֵܽ��������Ϊ�ֵܽ����ҽڵ㣬����4
				else if(brother->Right->Color==OrderStatisticTreeNode<T>::Black)
				{
					brother->Left->Color=OrderStatisticTreeNode<T>::Black;
					brother->Color=OrderStatisticTreeNode<T>::Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				//4.�ֵܽ���Ǻ�ɫ���ֵܽ����Һ����Ǻ�ɫ
				//�ڽ���֧�ϣ������˸����ĺ�ɫ���ֵܽ������Ҳ��ɺ�ɫ�������ֵܽ���֧����
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
	//��ֲ���
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
		//���ﲻ���ж�fillNode����Ϊ��ʹ��nil��Ҳ����NULL
		fillNode->Parent=removeNode->Parent;
		//����Size
		fillNode->Size=removeNode->Size;
	}
	//�����Сֵ
	OrderStatisticTreeNode<T>* Minimum(OrderStatisticTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	//����
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
	//ѡ��
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
    //ɾ�����
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

