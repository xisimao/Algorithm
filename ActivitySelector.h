#pragma once
#include <vector>
using namespace std;
class ActivitySelector
{
public:
	ActivitySelector(void);
	~ActivitySelector(void);
	void RecursiveActivitySelector(int[],int[],int,int,vector<int>&);
	void GreedyActivitySelector(int[],int[],int,vector<int>&);
};

