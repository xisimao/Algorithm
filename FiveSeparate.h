#pragma once
#include "InsertionSort.h"

template<typename T>
class FiveSeparate
{
public:
	FiveSeparate()
	{

	}
	~FiveSeparate()
	{
	}

	InsertionSort<T> is;

	int Select(T data[],int start,int end,int rank)
	{
		//��λ������λ���ڻ������������
		int medianIndexInData;
		if(end-start<6)
		{
			is.Sort(data,start,end);
			return start+rank-1;
		}
		else
		{
			//ÿһ�������
			int count=(end+1-start)/5;
			//ʣ�������
			int less=(end+1-start)%5;
			//��λ���ڸı�����λ�������е����
			int medianIndexInChange;
			//��λ���ڱ��ݵ���λ�������е����
			int medianIndexInBak;
			//��λ������
			int changeMiddles[6]={0};
			//��λ���������飬������λ�������ڲ�����λ��ʱ��ı�˳��������Ҫ����������ȷ����λ����ԭ�������˳��
			int bakMiddles[6]={0};

			//��ÿһ���������
			for(int i=0;i<5;i++)
			{
				is.Sort(data,start+i*count,start+(i+1)*count-1);
				changeMiddles[i]=data[start+i*count+count/2];
				bakMiddles[i]=data[start+i*count+count/2];
			}
			is.Sort(data,start+(5*count),start+(5*count)+less-1);

			//�ҳ���λ�������е���λ�����
			if(less>0)
			{
				changeMiddles[5]=data[start+(5*count)+(less+1)/2];
				bakMiddles[5]=data[start+(5*count)+(less+1)/2];
				medianIndexInChange= Select(changeMiddles,0,5,3);
			}
			else
			{
				medianIndexInChange= Select(changeMiddles,0,4,3);
			}
						
			for(int i=0;i<6;i++)
			{
				if(bakMiddles[i]==changeMiddles[medianIndexInChange])
				{
					medianIndexInBak=i;
					break;
				}
			}

			//���������õ�����Ҫ�����黮��
			if(medianIndexInBak==5)
			{
				medianIndexInData=Partition(data,start,end,start+5*count+less/2);
			}
			else
			{
				medianIndexInData=Partition(data,start,end,start+medianIndexInBak*count+count/2);
			}
		}

		//���ݻ��ֵĽ�������ݹ�
		if(rank==medianIndexInData-start+1)
		{
			return medianIndexInData;
		}
		else if(rank<medianIndexInData-start+1)
		{
			return Select(data,start,medianIndexInData-1,rank);
		}
		else
		{
			return Select(data,medianIndexInData+1,end,rank-(medianIndexInData-start)-1);
		}
	}

private:
	int Partition(T data[],int start,int end,int index)
	{
		
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
	void Swap(T data[],int index1,int index2)
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

