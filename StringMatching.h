#pragma once
#include <iostream>
using namespace std;
/**
 * 字符串匹配
 */
class StringMatching
{
public:
	StringMatching(void);
	~StringMatching(void);
	/**
	 * 穷尽比对字符串匹配算法
	 * @param t 字符串
	 * @param n 字符串长度
	 * @param p 匹配字符串
	 * @param m 匹配字符串长度
	 */
	void NaiveStringMatcher(char t[],int n,char p[],int m);
	/**
	 * 拉宾卡普匹配算法
	 * @param t 字符串
	 * @param n 字符串长度
	 * @param p 匹配字符串
	 * @param m 匹配字符串长度
	 * @param d 基数，可以使用字符组成的长度，例如英文共26个，所以基数可以使用26
	 * @param q 素数，用于减少匹配时使用的p和t中的字符对应的数字值，应取大于d的数，这样可以减少伪命中点
	 */
	void RabinKarpMatcher(int t[],int n,int p[],int m,int d,int q);
	/**
	 * 有限自动机匹配算法 
	 * @param t 字符串
	 * @param n 字符串长度
	 * @param p 匹配字符串
	 * @param m 匹配字符串长度
	 * @param c 匹配字符串中的字符组成
	 * @param l 匹配字符串中的字符组成长度
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
	 * 计算有限自动机转换函数
	 * @param p 匹配字符串
	 * @param m 匹配字符串长度
	 * @param c 匹配字符串中的字符组成
	 * @param l 匹配字符串中的字符组成长度
	 * @param finiteAutomaton 有限自动机
	 */
	void ComputeTransitionFunction(char p[],int m,char c[],int l,int* finiteAutomaton[]);
	
};

