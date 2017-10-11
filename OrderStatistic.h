#pragma once
#include <windows.h>


class OrderStatistic
{
public:
	OrderStatistic()
	{
		SYSTEMTIME sys;
		GetLocalTime( &sys ); 
		srand(sys.wMilliseconds);
	}
	~OrderStatistic()
	{
	}
	int RandomizedSelect(int data[],int start,int end,int rank)
	{
		if(start==end)
		{
			return data[start];
		}
		int randomIndex=RandomizedPartition(data,start,end);
		int randomRank=randomIndex-start+1;
		if(rank==randomRank)
		{
			return data[randomIndex];
		}
		else if(rank<randomRank)
		{
			return RandomizedSelect(data,start,randomIndex-1,rank);
		}
		else
		{
			return RandomizedSelect(data,randomIndex+1,end,rank-randomRank);
		}
	}
private:     
	int RandomizedPartition(int data[],int start,int end)
	{
		int index=rand()%(end-start)+start;
		int key=data[index];
		Swap(data,index,end);
		int largeIndex=start;
		for(int i=start;i<end;++i)
		{
			if(data[i]<key)
			{
				Swap(data,largeIndex,i);
				largeIndex++;
			}
		}
		Swap(data,largeIndex,end);
		return largeIndex;
	}
	void Swap(int data[],int index1,int index2)
 	{
		if(index1==index2)
		{
			return;
		}
		int temp=data[index1];
		data[index1]=data[index2];
		data[index2]=temp;
	}
};

