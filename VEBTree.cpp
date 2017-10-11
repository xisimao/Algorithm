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
		//使用上平方根创建概要
		node->Summary=new VEBNode();
		Create(node->Summary,up);

		//共有上平方根个簇，每个簇有下平方根个值
		//因为上平方根*下平方根=全域大小
		//32=pow(2,5)=pow(2,3)*pow(2,2) 3为上平方根，2为下平方根
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
	//在基础情况中，
	if(node->Size==2)
	{
		//只有当键在第一个位置而后一个位置有值时，表示在基础情况中找到后继
		if(key==0&&node->Max==1)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	//如果不是基础情况，判断键是否小于最小值
	else if(node->Min!=-1&&key<node->Min)
	{
		return node->Min;
	}
	//查找后续簇
	else
	{
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		int maxLocation=Maximum(node->Cluster[index]);
		//如果值所在的簇中存在比键大的值，则在该簇中寻找
		if(maxLocation!=-1&&location<maxLocation)
		{
			int offset=Successor(node->Cluster[index],location);
			return IndexInTree(index,node->Size,offset);
		}
		else
		{
			//在概要中找到后续有值的簇的序号
			int succCluster=Successor(node->Summary,index);
			if(succCluster==-1)
			{
				return -1;
			}
			//如果存在后续有值的簇则在该簇中继续查找
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
	//基础情况下只有键是第二个位置而第一个位置有值的情况下存在前驱
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
	//不是基础的情况下先判断是否大于最大值，如果大于则无需向后继续进行
	else if(node->Max!=-1&&key>node->Max)
	{
		return node->Max;
	}
	else
	{
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		int minLocation=Minimum(node->Cluster[index]);
		//如果键的所在簇中存在比键小的，则在该簇中寻找
		if(minLocation!=-1&&location>minLocation)
		{
			int offset=Predecessor(node->Cluster[index],location);
			return IndexInTree(index,node->Size,offset);
		}
		//否则前驱可能是当前结点的最小值或在前驱簇中
		//因为最小值是不在簇中放置的
		else 
		{
			//在概要中寻找前序簇的序号
			int predCluster=Predecessor(node->Summary,index);
			//最小值不保存在簇中，所以即使存在最小值概要中也显示为nil
			//所以需要判断一次最小值
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
 * 初始化结点
 * @param node 结点 
 * @param key 键
 */
void VEBTree::InitNode(VEBNode* node,int key)
{
	node->Min=key;
	node->Max=key;
}
/**
 * 添加键
 * @param node 结点
 * @param key 键
 */
void VEBTree::Insert(VEBNode* node,int key)
{
	if(node->Min==-1)
	{
		InitNode(node,key);
	}
	else
	{
		//如果新键小于最小值则将键放置到最小值中，然后将原来的最小值作为新建添加
		if(key<node->Min)
		{
			int temp=key;
			key=node->Min;
			node->Min=temp;
		}
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		//如果并非基础情况
		if(node->Size>2)
		{
			//如果结点对应的簇不存在最小值，则需要更新概要，并初始化簇即可
			if(Minimum(node->Cluster[index])==-1)
			{
				Insert(node->Summary,index);
				InitNode(node->Cluster[index],location);
			}
			//否则直接将值添加到对应簇中
			else
			{
				Insert(node->Cluster[index],location);
			}
		}
		//更新结点的最大值
		if(key>node->Max)
		{
			node->Max=key;
		}
	}
}
/**
 * 删除键
 * @param node 结点
 * @param key 键
 */
void VEBTree::Delete(VEBNode* node,int key)
{
	//当结点最大值等于最小值时，表示结点中最多只有一个键
	//需要再删除一个键时需要把结点置为初始化状态
	if(node->Min==node->Max)
	{
		node->Min=-1;
		node->Max=-1;
	}
	//如果是基础情况并且结点中有两个值
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
		//如果键是当前结点最小值
		if(key==node->Min)
		{
			//在概要中找到最小的簇
			int firstCluster=Minimum(node->Summary);
			//根据簇的序号和在簇中的最小值得到值的后继
			key=IndexInTree(firstCluster,node->Size,Minimum(node->Cluster[firstCluster]));
			node->Min=key;
		}
		int index=IndexOfCluster(key,node->Size);
		int location=LocationInCluster(key,node->Size);
		//删除簇中的值
		Delete(node->Cluster[index],location);
		//如果簇中没有任何值，则需要删除概要信息
		if(Minimum(node->Cluster[index])==-1)
		{
			Delete(node->Summary,index);
			//如果当前值是最大值，但是当前簇中已经没有值，需要从概要中找到最大值的簇号
			if(key==node->Max)
			{
				int summaryMax=Maximum(node->Summary);
				//如果未找到最大值，表示当前结点的所有簇都已经为空
				//那么结点中只剩两种情况，一种为空，一种为只剩最小值
				if(summaryMax==-1)
				{
					node->Max=node->Min;
				}
				//如果存在则找到最大值
				else
				{
					node->Max=IndexInTree(summaryMax,node->Size,Maximum(node->Cluster[summaryMax]));
				}
			}
		}
		//如果当前值是最大值并且簇中仍有值，则在簇中寻找最大值
		else if(key==node->Max)
		{
			node->Max=IndexInTree(index,node->Size,Maximum(node->Cluster[index]));
		}
	}
}