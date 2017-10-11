#pragma once
#include <string>
#include <iostream>

using namespace std;

class Print
{
public:
	Print()
	{
	}
	~Print(void)
	{
	}
	static void PrintArray(int data[],int length,string text="")
	{
		cout<<text;
		for(int i=0;i<length;++i)
		{
			cout<<data[i]<<" ";
		}
		cout<<endl;
	}
};

