#pragma once
#include <math.h>
#include "VEBNode.h"
/**
 * van Emde Boas��
 */
class VEBTree
{
public:
	VEBTree(void);
	~VEBTree(void);
	/**
	 * ����veb��
	 * @param size ȫ���С,��Ϊ2����
	 */
	void Create(int size);
	/**
	 * �����Сֵ
	 * @param node ���
	 * @return ��Сֵ
	 */
	int Minimum(VEBNode* node);
	/**
	 * ������ֵ
	 * @param node ���
	 * @return ���ֵ
	 */
	int Maximum(VEBNode* node);
	/**
	 * ָ�����Ƿ��������
	 * @param node ���
	 * @param key ��
	 * @return ���ڷ���true�����ڷ���false
	 */
	bool Member(VEBNode* node,int key);
	/**
	 * Ѱ�Һ��
	 * @param node ���
	 * @param key ��
	 * @return ��̼�����������ڷ���-1
	 */
	int Successor(VEBNode* node,int key);
	/**
	 * Ѱ��ǰ��
	 * @param node ���
	 * @param key ��
	 * @return ǰ�������������ڷ���-1
	 */
	int Predecessor(VEBNode* node,int key);
	/**
	 * ��Ӽ�
	 * @param node ��� 
	 * @param key ��
	 */
	void Insert(VEBNode* node,int key);
	/**
	 * ɾ����
	 * @param node ��� 
	 */
	void Delete(VEBNode* node,int key);
	/**
	 * ���ڵ�
	 */
	VEBNode* _root;
private:
	/**
	 * ���Ĵصı��
	 * @param key ��
	 * @param size ��ǰ���С
	 * @return ���
	 */
	int IndexOfCluster(int key,int size);
	/**
	 * ���ڴ��е�λ��
	 * @param key ��
	 * @param size ��ǰ���С
	 * @return ���
	 */
	int LocationInCluster(int key,int size);
	/**
	 * ��ü������еĴ�С
	 * @param index �صı��
	 * @param size ��ǰ���С
	 * @param location ���ڴ��е�λ��
	 * @return 
	 */
	int IndexInTree(int index,int size,int location);
	/**
	 * �����ڵ���Ϣ
	 * @param node ���
	 * @param size ���С
	 */
	void Create(VEBNode* node,int size);
	/**
	 * ��ӿ���
	 * @param node ���
	 * @param key ��
	 */
	void InitNode(VEBNode* node,int key);
	/**
	 * ���ֵ����ƽ����
	 * @param value 2����
	 * @return ��ƽ����
	 */
	int GetUpSqrt(int value);
	/**
	 * ���ֵ����ƽ����
	 * @param value 2����
	 * @return ��ƽ����
	 */
	int GetDownSqrt(int value);
};

