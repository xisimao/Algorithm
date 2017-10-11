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
	//��ʾ��dΪ������mλ���֣����λ��Ӧ����ֵ
	//�����5λ���ֻ���Ϊ10���ǵ�һλ��ʾ����10��4�η���10000
	int h=((int)pow((double)d,m-1))%q;

	//��ʼ��p��Ӧ���ֵ�����
	//��ʼ��t�е�һ����Ҫ�ȶԵ����ַ�����Ӧ���ֵ�����
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
		//���������ͬ��ȶ�t�����ַ�����p����Ϊ�������С�ڻ������п�����α���е�
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
		//���ƫ��һλ�����ַ�����Ӧ������
		t0=((t0-h*t[s])*d+t[s+m])%q;
		//�������С��0����Ҫ����һ������
		if(t0<0)
		{
			t0+=q;
		}
	}
}
void StringMatching::ComputeTransitionFunction(char p[],int m,char c[],int l,int* finiteAutomaton[])
{
	//q��ʾ��ǰ�Ѿ������ƥ�����ַ�������
	//��Ϊ״̬Ϊ0-m����ʾ��ǰ�м����ַ��Ѿ�����ƥ�䣬�����Զ���������Ҫ��m+1��
	for(int q=0;q<m+1;++q)
	{
		//i��ʾ��һ��������ַ���
		for(int i=0;i<l;++i)
		{
			//p[0-q]+c[i]��ʾ��ǰ�ܵ������ַ���
			//p[0-k]��ʾ�ȶԵĺ�׺�ַ�������Ϊ�Զ���������Ϊm+1����Ϊ������ȫ��ƥ������һ���ַ�
			//k���μ�С�����p[0-k]�Ƿ����������ַ����ĺ�׺���������˵����ǰ������k������ֵ�����¼�����һ�������ƥ��
			int k=min(m,q+1);
			for(;k>0;--k)
			{
				//�ַ���ֱͬ�Ӽ���k
				if(p[k-1]!=c[i])
				{
					continue;
				}
				//���p[0-k]�Ƿ��������ַ����ĺ�׺
				bool flag=true;
				for(int j=k-2,index=q-1;j>=0&&index>=0;--j,--index)
				{
					if(p[j]!=p[index])
					{
						flag=false;
						break;
					}
				}
				//��������¼k�������k�������
				if(flag)
				{
					finiteAutomaton[q][i]=k;
					//cout<<k<<"  ";
					break;
				}
			}
			//û���κ��ַ�ƥ��
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
	//�����Զ��������Ի�����һ��״̬�¸����������һ��״̬��
	//�б�ʾ״̬������ǰ�м����ַ��Ѿ�����ƥ�䣬�б�ʾ����
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
		//��Ե�ǰ�ַ�������õ��Զ�����״̬
		q=finiteAutomaton[q][t[i]-'a'];
		//mΪ��Ч״̬����ʾ��ǰƥ��ɹ��ĳ���
		//Ҳ�������Ϊ������t[i]���м����ַ�������������һ��ƥ��
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
	//pie��ʾ����p[0-n]���Ա���������׺����p��ǰ׺����Ϊ���Ҫƥ���ַ��������ٵ���ƥ���ַ�����ǰ׺�ſ��ܼ���
	//��p[0-n]����һ������ʱƥ��ʧ�ܣ����p[0-n]Ϊm�����������ƶ�0��n-m�ķ�Χ�ڣ���Ȼ����Чƥ��
	//������abcacb����p[0-3]=1����p[0-4]ͬabcabƥ�䣬��ʱ�Ƚϵ���p[4]��b��ƥ��ʧ�ܣ���Ϊֻ��1���ַ�����p��ǰ׺
	//���Ա�ʾΪ���ڴ�0�ſ�ʼ��ƥ��ʧ�ܣ���1�ź�2�ſ�ʼ��ƥ�䲻����ƥ���ǰ׺����Ȼƥ�䲻�ɹ���
	//���Ե�һ������ƥ��ɹ���λ����3�ţ����ڱ�����1���ַ�����������Ҫƥ�����p[1]��b�����ƥ��������������ƥ�����ٴ��ҵ�p[0-1]��ֵΪ0
	//��Ϊ0ʱ��ʾ����ԭp[0-n]û��ֵ�����µ��ַ�����ƥ�䣬����ֱ���Թ�������ֱ�Ӵ������ַ�����һ����p[0]�Ƚ����¿�ʼ
	pie[0]=0;
	cout<<pie[0]<<"  ";
	//k��ʾ��ǰֵ�����µ��ַ�����
	int k=0;
	//���p[1-q]�ĺ�׺����м����ַ�������Ϊp��ǰ׺
	for(int q=1;q<m;++q)
	{
		//���ƥ��ʧ���ȼ���Ƿ���Ա���һЩ�ַ�
		while(k>0&&p[k]!=p[q])
		{
			k=pie[k];
		}
		//ƥ��ɹ�������һ���ַ�
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
	//q��ʾ��ǰ�Ѿ�ƥ�������
	int q=0;
	for(int i=0;i<n;++i)
	{
		//ƥ��ʧ��ʱ�ҵ�ֵ�����µ��ַ�����q��Ȼ��ƥ���ַ�������Щ�ַ��ĺ���һ����p[q],��Ϊq�Ǵ�0��ʼ��ͬ����Ƚ�
		//����ٴ�ʧ�����������ֵ�����µģ�ֱ��qΪ0����ʾû���κ�ֵ�����µģ���Ӻ��������p[0]���¿�ʼ�Ƚ�
		//��Ϊq=0ʱ��pie[q]=0,����������ѭ��������Ҳ���Եõ���ȷ���
		while(q>0&&p[q]!=t[i])
		{
			q=pie[q-1];
		}
		//����Ƚϳɹ�������һ��q�����
		if(p[q]==t[i])
		{
			q+=1;
		}
		//����ƥ��
		if(q==m)
		{
			cout<<i-m+1<<endl;
			q=pie[q-1];
		}

	}
	delete[] pie;
}