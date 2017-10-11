#pragma once
//快速排序
template<typename T>
class QuickSort
{
public:
	void QuickSort::Sort(T data[],int start,int end)
	{
		if(start>=end)
		{
			return;
		}
		int index=Partition(data,start,end);
		Sort(data,start,index-1);
		Sort(data,index+1,end);
	}
	//将数组划分为小于关键值，关键值和大于关键值三部分，这样关键值的顺序是一定的
	int QuickSort::Partition(T data[],int start,int end)
	{
		int key=data[end];
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
	void QuickSort::Swap(T data[],int index1,int index2)
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

