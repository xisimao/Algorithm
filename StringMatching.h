#pragma once
#include <iostream>
using namespace std;
/**
 * �ַ���ƥ��
 */
class StringMatching
{
public:
	StringMatching(void);
	~StringMatching(void);
	/**
	 * ��ȶ��ַ���ƥ���㷨
	 * @param t �ַ���
	 * @param n �ַ�������
	 * @param p ƥ���ַ���
	 * @param m ƥ���ַ�������
	 */
	void NaiveStringMatcher(char t[],int n,char p[],int m);
	/**
	 * ��������ƥ���㷨
	 * @param t �ַ���
	 * @param n �ַ�������
	 * @param p ƥ���ַ���
	 * @param m ƥ���ַ�������
	 * @param d ����������ʹ���ַ���ɵĳ��ȣ�����Ӣ�Ĺ�26�������Ի�������ʹ��26
	 * @param q ���������ڼ���ƥ��ʱʹ�õ�p��t�е��ַ���Ӧ������ֵ��Ӧȡ����d�������������Լ���α���е�
	 */
	void RabinKarpMatcher(int t[],int n,int p[],int m,int d,int q);
	/**
	 * �����Զ���ƥ���㷨 
	 * @param t �ַ���
	 * @param n �ַ�������
	 * @param p ƥ���ַ���
	 * @param m ƥ���ַ�������
	 * @param c ƥ���ַ����е��ַ����
	 * @param l ƥ���ַ����е��ַ���ɳ���
	 */
	void FiniteAutomatonMatcher(char t[],int n,char p[],int m,char c[],int l);
	/**
	 * 
	 * @param 
	 * @return 
	 */
	void KmpMatcher(char t[],int n,char p[],int m);

private:
	/**
	 * 
	 * @param 
	 * @return 
	 */
	void ComputePrefixFunction(char p[],int m,int pie[]);
	/**
	 * ���������Զ���ת������
	 * @param p ƥ���ַ���
	 * @param m ƥ���ַ�������
	 * @param c ƥ���ַ����е��ַ����
	 * @param l ƥ���ַ����е��ַ���ɳ���
	 * @param finiteAutomaton �����Զ���
	 */
	void ComputeTransitionFunction(char p[],int m,char c[],int l,int* finiteAutomaton[]);
	
};

