#pragma once
#include <math.h>
#include "VEBNode.h"
/**
 * van Emde Boas树
 */
class VEBTree
{
public:
	VEBTree(void);
	~VEBTree(void);
	/**
	 * 创建veb树
	 * @param size 全域大小,需为2的幂
	 */
	void Create(int size);
	/**
	 * 获得最小值
	 * @param node 结点
	 * @return 最小值
	 */
	int Minimum(VEBNode* node);
	/**
	 * 获得最大值
	 * @param node 结点
	 * @return 最大值
	 */
	int Maximum(VEBNode* node);
	/**
	 * 指定键是否存在树中
	 * @param node 结点
	 * @param key 键
	 * @return 存在返回true不存在返回false
	 */
	bool Member(VEBNode* node,int key);
	/**
	 * 寻找后继
	 * @param node 结点
	 * @param key 键
	 * @return 后继键，如果不存在返回-1
	 */
	int Successor(VEBNode* node,int key);
	/**
	 * 寻找前驱
	 * @param node 结点
	 * @param key 键
	 * @return 前序键，如果不存在返回-1
	 */
	int Predecessor(VEBNode* node,int key);
	/**
	 * 添加键
	 * @param node 结点 
	 * @param key 键
	 */
	void Insert(VEBNode* node,int key);
	/**
	 * 删除键
	 * @param node 结点 
	 */
	void Delete(VEBNode* node,int key);
	/**
	 * 根节点
	 */
	VEBNode* _root;
private:
	/**
	 * 键的簇的编号
	 * @param key 键
	 * @param size 当前域大小
	 * @return 编号
	 */
	int IndexOfCluster(int key,int size);
	/**
	 * 键在簇中的位置
	 * @param key 键
	 * @param size 当前域大小
	 * @return 编号
	 */
	int LocationInCluster(int key,int size);
	/**
	 * 获得键在树中的大小
	 * @param index 簇的编号
	 * @param size 当前域大小
	 * @param location 键在簇中的位置
	 * @return 
	 */
	int IndexInTree(int index,int size,int location);
	/**
	 * 创建节点信息
	 * @param node 结点
	 * @param size 域大小
	 */
	void Create(VEBNode* node,int size);
	/**
	 * 添加空树
	 * @param node 结点
	 * @param key 键
	 */
	void InitNode(VEBNode* node,int key);
	/**
	 * 获得值的上平方根
	 * @param value 2的幂
	 * @return 上平方根
	 */
	int GetUpSqrt(int value);
	/**
	 * 获得值的下平方根
	 * @param value 2的幂
	 * @return 上平方根
	 */
	int GetDownSqrt(int value);
};

