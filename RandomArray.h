#pragma  once
#include <map>
using namespace std;
class RandomArray
{
public:
	static void  GetRandomArray(int list[],int length)
	{
		map<int,int> m;
		int index=0;
		while(index<length)
		{
			int value=rand()%length+1;
			map<int,int>::const_iterator it=m.find(value);
			if(it==m.end())
			{
				m[value]=0;
				list[index++]=value;
			}
		}
	}
};