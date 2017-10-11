#include "StdAfx.h"
#include "ActivitySelector.h"



ActivitySelector::ActivitySelector(void)
{
}


ActivitySelector::~ActivitySelector(void)
{
}
/**
 * 递归求活动调度
 * @param s 开始时间
 * @param f 结束时间
 * @param k 当前活动序号
 * @param n 当前活动总数
 * @param list 用于记录活动
 */
void ActivitySelector::RecursiveActivitySelector(int start[],int end[],int currentIndex,int count,vector<int>& list)
{
	//下一个活动的序号
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