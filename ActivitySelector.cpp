#include "StdAfx.h"
#include "ActivitySelector.h"



ActivitySelector::ActivitySelector(void)
{
}


ActivitySelector::~ActivitySelector(void)
{
}
/**
 * �ݹ�������
 * @param s ��ʼʱ��
 * @param f ����ʱ��
 * @param k ��ǰ����
 * @param n ��ǰ�����
 * @param list ���ڼ�¼�
 */
void ActivitySelector::RecursiveActivitySelector(int start[],int end[],int currentIndex,int count,vector<int>& list)
{
	//��һ��������
	int nextIndex=currentIndex+1;
	while(nextIndex<=count&&start[nextIndex]<end[currentIndex])
	{
		nextIndex=nextIndex+1;
	}
	if(nextIndex<=count)
	{
		list.push_back(nextIndex);
		RecursiveActivitySelector(start,end,nextIndex,count,list);
	}
}

void ActivitySelector::GreedyActivitySelector(int start[],int end[],int count,vector<int>& list)
{
	list.push_back(start[1]);
	int currentIndex=1;
	for(int nextIndex=2;nextIndex<=count;++nextIndex)
	{
		if(start[nextIndex]>=end[currentIndex])
		{
			list.push_back(nextIndex);
			currentIndex=nextIndex;
		}
	}

}