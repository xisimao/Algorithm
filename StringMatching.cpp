#include "StdAfx.h"
#include "StringMatching.h"


StringMatching::StringMatching(void)
{

}
StringMatching::~StringMatching()
{

}

void StringMatching::NaiveStringMatcher(char t[],int n,char p[],int m)
{
	for(int s=0;s<=n-m;++s)
	{
		bool allMatching=true;
		for(int j=0;j<m;++j)
		{
			if(p[j]!=t[s+j])
			{
				allMatching=false;
				break;
			}
		}
		if (allMatching)
		{
			cout<<s<<endl;
		}
	}
}
void StringMatching::RabinKarpMatcher(int t[],int n,int p[],int m,int d,int q)
{
	//表示以d为基数的m位数字，最高位对应的量值
	//如果是5位数字基数为10，那第一位表示的是10的4次方，10000
	int h=((int)pow((double)d,m-1))%q;

	//初始化p对应数字的余数
	//初始化t中第一个需要比对的子字符串对应数字的余数
	int p0=0;
	int t0=0;
	for(int i=0;i<m;++i)
	{
		p0=d*p0+p[i];
		t0=d*t0+t[i];
	}
	p0=p0%q;
	t0=t0%q;


	for(int s=0;s<=n-m;++s)
	{
		//如果余数相同则比对t的子字符串和p，因为如果素数小于基数则有可能是伪命中点
		if(p0==t0)
		{
			bool allMatching=true;
			for(int j=0;j<m;++j)
			{
				if(p[j]!=t[s+j])
				{
					allMatching=false;
					break;
				}
			}
			if (allMatching)
			{
				cout<<s<<endl;
			}
		}
		//向后偏移一位的子字符串对应的余数
		t0=((t0-h*t[s])*d+t[s+m])%q;
		//如果余数小于0则需要增加一个素数
		if(t0<0)
		{
			t0+=q;
		}
	}
}
void StringMatching::ComputeTransitionFunction(char p[],int m,char c[],int l,int* finiteAutomaton[])
{
	//q表示当前已经输入的匹配子字符串长度
	//因为状态为0-m，表示当前有几个字符已经满足匹配，所以自动机的行需要有m+1行
	for(int q=0;q<m+1;++q)
	{
		//i表示下一个输入的字符串
		for(int i=0;i<l;++i)
		{
			//p[0-q]+c[i]表示当前总的输入字符串
			//p[0-k]表示比对的后缀字符串，因为自动机的行数为m+1，因为包含在全部匹配后，最后一个字符
			//k依次减小，检查p[0-k]是否满足输入字符串的后缀，如果满足说明当前输入有k个长度值得留下继续下一次输入的匹配
			int k=min(m,q+1);
			for(;k>0;--k)
			{
				//字符不同直接减少k
				if(p[k-1]!=c[i])
				{
					continue;
				}
				//检查p[0-k]是否是输入字符串的后缀
				bool flag=true;
				for(int j=k-2,index=q-1;j>=0&&index>=0;--j,--index)
				{
					if(p[j]!=p[index])
					{
						flag=false;
						break;
					}
				}
				//如果是则记录k否则减少k继续检查
				if(flag)
				{
					finiteAutomaton[q][i]=k;
					//cout<<k<<"  ";
					break;
				}
			}
			//没有任何字符匹配
			if(k==0)
			{
				finiteAutomaton[q][i]=k;
				//cout<<k<<"  ";
			}
		}
		//cout<<endl;
	}

}
void StringMatching::FiniteAutomatonMatcher(char t[],int n,char p[],int m,char c[],int l)
{
	//有限自动机，可以获得针对一个状态下各个输入的下一个状态，
	//行表示状态，即当前有几个字符已经满足匹配，列表示输入
	int** finiteAutomaton=new int*[m+1];
	for(int i=0;i<m+1;++i)
	{
		finiteAutomaton[i]=new int[l];
		memset(finiteAutomaton[i],0,sizeof(int)*l);
	}
	ComputeTransitionFunction(p,m,c,l,finiteAutomaton);
	int q=0;
	for(int i=0;i<n;++i)
	{
		//针对当前字符的输入得到自动机的状态
		q=finiteAutomaton[q][t[i]-'a'];
		//m为有效状态，表示当前匹配成功的长度
		//也可以理解为在输入t[i]后，有几个字符可以留下做下一次匹配
		if(q==m)
		{
			cout<<i-m+1<<endl;
		}
	}
	for(int i=0;i<m+1;++i)
	{
		delete[] finiteAutomaton[i];
	}
	delete[] finiteAutomaton;
}
void StringMatching::ComputePrefixFunction(char p[],int m,int pie[])
{
	//pie表示对于p[0-n]可以保留几个后缀满足p的前缀，因为如果要匹配字符串，至少得是匹配字符串的前缀才可能继续
	//当p[0-n]增加一个输入时匹配失败，如果p[0-n]为m，则在向右移动0到n-m的范围内，必然是无效匹配
	//例如有abcacb，有p[0-3]=1，当p[0-4]同abcab匹配，此时比较的是p[4]和b，匹配失败，因为只有1个字符满足p的前缀
	//可以表示为对于从0号开始的匹配失败，从1号和2号开始的匹配不符合匹配的前缀，必然匹配不成功，
	//所以第一个可能匹配成功的位置在3号，由于保留了1个字符，所以现在要匹配的是p[1]和b，如果匹配则继续，如果不匹配则再次找到p[0-1]的值为0
	//当为0时表示对于原p[0-n]没有值得留下的字符用于匹配，可以直接略过，所以直接从输入字符的下一个和p[0]比较重新开始
	pie[0]=0;
	cout<<pie[0]<<"  ";
	//k表示当前值得留下的字符数量
	int k=0;
	//检查p[1-q]的后缀最大有几个字符可以作为p的前缀
	for(int q=1;q<m;++q)
	{
		//如果匹配失败先检查是否可以保留一些字符
		while(k>0&&p[k]!=p[q])
		{
			k=pie[k];
		}
		//匹配成功则增加一个字符
		if(p[k]==p[q])
		{
			k+=1;
		}
		pie[q]=k;
		cout<<k<<"  ";
	}
	cout<<endl;
}
void StringMatching::KmpMatcher(char t[],int n,char p[],int m)
{
	int* pie=new int[m+1];
	ComputePrefixFunction(p,m,pie);
	//q表示当前已经匹配的数量
	int q=0;
	for(int i=0;i<n;++i)
	{
		//匹配失败时找到值得留下的字符数量q，然后匹配字符串中这些字符的后面一个（p[q],因为q是从0开始）同输入比较
		//如果再次失败则继续查找值得留下的，直到q为0，表示没有任何值得留下的，则从后续输入和p[0]重新开始比较
		//因为q=0时，pie[q]=0,所以无需在循环中体现也可以得到正确结果
		while(q>0&&p[q]!=t[i])
		{
			q=pie[q-1];
		}
		//如果比较成功则增加一个q的序号
		if(p[q]==t[i])
		{
			q+=1;
		}
		//满足匹配
		if(q==m)
		{
			cout<<i-m+1<<endl;
			q=pie[q-1];
		}

	}
	delete[] pie;
}