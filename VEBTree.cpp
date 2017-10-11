#include "StdAfx.h"
#include "VEBTree.h"


VEBTree::VEBTree(void)
{
}


VEBTree::~VEBTree(void)
{
}
int VEBTree::GetUpSqrt(int value)
{
	return pow(2.0,ceil(sqrt((double)value)/2.0));
}
int VEBTree::GetDownSqrt(int value)
{
	return pow(2.0,floor(sqrt((double)value)/2.0));
}
int inline VEBTree::IndexOfCluster(int key,int size)
{
	return key/GetDownSqrt(size);
}

int inline VEBTree::LocationInCluster(int key,int size)
{
	return key%GetDownSqrt(size);
}

int VEBTree::IndexInTree(int index,int size,int location)
{
	return index*GetDownSqrt(size)+location;
}
void VEBTree::Create(int size)
{
	_root=new VEBNode();
	Create(_root,size);
}
void VEBTree::Create(VEBNode* node,int size)
{

	node->Size=size;
	if(size>2)
	{
		int up=GetUpSqrt(size);
		int down=GetDownSqrt(size);
		//ʹ����ƽ����������Ҫ
		node->Summary=new VEBNode();
		Create(node->Summary,up);

		//������ƽ�������أ�ÿ��������ƽ������ֵ
		//��Ϊ��ƽ����*��ƽ����=ȫ���С
		//32=pow(2,5)=pow(2,3)*pow(2,2) 3Ϊ��ƽ������2Ϊ��ƽ����
		node->Cluster=new VEBNode*[up];
		for(int i=0;i<up;++i)
		{
			node->Cluster[i]=new VEBNode();
			Create(node->Cluster[i],down);
		}
	}
	
}

int VEBTree::Minimum(VEBNode* node)
{
	return node->Min;
}

int VEBTree::Maximum(VEBNode* node)
{
	return node->Max;
}

bool VEBTree::Member(VEBNode* node,int key)
{
	if(key==node->Min ||key==node->Max)
	{
		return true;
	}
	else if(node->Size==2)
	{
		return false;
	}
	else
	{
		return Member(node->Cluster[IndexOfCluster(key,node->Size)],LocationInCluster(key,node->Size));
	}
}

int VEBTree::Successor(VEBNode* node,int key)
{
	//�ڻ�������У�
	if(node->Size==2)
	{
		//ֻ�е����ڵ�һ��λ�ö���һ��λ����ֵʱ����ʾ�ڻ���������ҵ����
		if(key==0&&node->Max==1)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	//������ǻ���������жϼ��Ƿ�С����Сֵ
	else if(node->Min!=-1&&key<node->Min)
	{
		return node->Min;
	}
	//���Һ�����
	else
	{
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		int maxLocation=Maximum(node->Cluster[index]);
		//���ֵ���ڵĴ��д��ڱȼ����ֵ�����ڸô���Ѱ��
		if(maxLocation!=-1&&location<maxLocation)
		{
			int offset=Successor(node->Cluster[index],location);
			return IndexInTree(index,node->Size,offset);
		}
		else
		{
			//�ڸ�Ҫ���ҵ�������ֵ�Ĵص����
			int succCluster=Successor(node->Summary,index);
			if(succCluster==-1)
			{
				return -1;
			}
			//������ں�����ֵ�Ĵ����ڸô��м�������
			else
			{
				int offset=Minimum(node->Cluster[succCluster]);
				return IndexInTree(succCluster,node->Size,offset);
			}
		}
	}
}

int VEBTree::Predecessor(VEBNode* node,int key)
{
	//���������ֻ�м��ǵڶ���λ�ö���һ��λ����ֵ������´���ǰ��
	if(node->Size==2)
	{
		if(key==1&&node->Min==0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	//���ǻ�������������ж��Ƿ�������ֵ�������������������������
	else if(node->Max!=-1&&key>node->Max)
	{
		return node->Max;
	}
	else
	{
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		int minLocation=Minimum(node->Cluster[index]);
		//����������ڴ��д��ڱȼ�С�ģ����ڸô���Ѱ��
		if(minLocation!=-1&&location>minLocation)
		{
			int offset=Predecessor(node->Cluster[index],location);
			return IndexInTree(index,node->Size,offset);
		}
		//����ǰ�������ǵ�ǰ������Сֵ����ǰ������
		//��Ϊ��Сֵ�ǲ��ڴ��з��õ�
		else 
		{
			//�ڸ�Ҫ��Ѱ��ǰ��ص����
			int predCluster=Predecessor(node->Summary,index);
			//��Сֵ�������ڴ��У����Լ�ʹ������Сֵ��Ҫ��Ҳ��ʾΪnil
			//������Ҫ�ж�һ����Сֵ
			if(predCluster==-1)
			{
				if(node->Min!=-1&&key>node->Min)
				{
					return node->Min;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				int offset=Maximum(node->Cluster[predCluster]);
				return IndexInTree(predCluster,node->Size,offset);
			}
		}
	}
}
/**
 * ��ʼ�����
 * @param node ��� 
 * @param key ��
 */
void VEBTree::InitNode(VEBNode* node,int key)
{
	node->Min=key;
	node->Max=key;
}
/**
 * ��Ӽ�
 * @param node ���
 * @param key ��
 */
void VEBTree::Insert(VEBNode* node,int key)
{
	if(node->Min==-1)
	{
		InitNode(node,key);
	}
	else
	{
		//����¼�С����Сֵ�򽫼����õ���Сֵ�У�Ȼ��ԭ������Сֵ��Ϊ�½����
		if(key<node->Min)
		{
			int temp=key;
			key=node->Min;
			node->Min=temp;
		}
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		//������ǻ������
		if(node->Size>2)
		{
			//�������Ӧ�Ĵز�������Сֵ������Ҫ���¸�Ҫ������ʼ���ؼ���
			if(Minimum(node->Cluster[index])==-1)
			{
				Insert(node->Summary,index);
				InitNode(node->Cluster[index],location);
			}
			//����ֱ�ӽ�ֵ��ӵ���Ӧ����
			else
			{
				Insert(node->Cluster[index],location);
			}
		}
		//���½������ֵ
		if(key>node->Max)
		{
			node->Max=key;
		}
	}
}
/**
 * ɾ����
 * @param node ���
 * @param key ��
 */
void VEBTree::Delete(VEBNode* node,int key)
{
	//��������ֵ������Сֵʱ����ʾ��������ֻ��һ����
	//��Ҫ��ɾ��һ����ʱ��Ҫ�ѽ����Ϊ��ʼ��״̬
	if(node->Min==node->Max)
	{
		node->Min=-1;
		node->Max=-1;
	}
	//����ǻ���������ҽ����������ֵ
	else if(node->Size==2)
	{
		if(key==0)
		{
			node->Min=1;
		}
		else
		{
			node->Min==0;
		}
		node->Max=node->Min;
	}
	else
	{
		//������ǵ�ǰ�����Сֵ
		if(key==node->Min)
		{
			//�ڸ�Ҫ���ҵ���С�Ĵ�
			int firstCluster=Minimum(node->Summary);
			//���ݴص���ź��ڴ��е���Сֵ�õ�ֵ�ĺ��
			key=IndexInTree(firstCluster,node->Size,Minimum(node->Cluster[firstCluster]));
			node->Min=key;
		}
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		//ɾ�����е�ֵ
		Delete(node->Cluster[index],location);
		//�������û���κ�ֵ������Ҫɾ����Ҫ��Ϣ
		if(Minimum(node->Cluster[index])==-1)
		{
			Delete(node->Summary,index);
			//�����ǰֵ�����ֵ�����ǵ�ǰ�����Ѿ�û��ֵ����Ҫ�Ӹ�Ҫ���ҵ����ֵ�Ĵغ�
			if(key==node->Max)
			{
				int summaryMax=Maximum(node->Summary);
				//���δ�ҵ����ֵ����ʾ��ǰ�������дض��Ѿ�Ϊ��
				//��ô�����ֻʣ���������һ��Ϊ�գ�һ��Ϊֻʣ��Сֵ
				if(summaryMax==-1)
				{
					node->Max=node->Min;
				}
				//����������ҵ����ֵ
				else
				{
					node->Max=IndexInTree(summaryMax,node->Size,Maximum(node->Cluster[summaryMax]));
				}
			}
		}
		//�����ǰֵ�����ֵ���Ҵ�������ֵ�����ڴ���Ѱ�����ֵ
		else if(key==node->Max)
		{
			node->Max=IndexInTree(index,node->Size,Maximum(node->Cluster[index]));
		}
	}
}