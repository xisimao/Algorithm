#pragma once
/**
 * van Emde Boas树结点
 */
class VEBNode
{
public:
	VEBNode()
		:Min(-1),Max(-1),Size(0)
	{
	}
	/**
	 * 最小值
	 */
	int Min;
	/**
	 * 最大值
	 */
	int Max;
	/**
	 * 全域(universe)的大小
	 */
	int Size;
	/**
	 * 概要结构指针，用于记录簇的编号
	 */
	VEBNode* Summary;
	/**
	 * 簇
	 */
	VEBNode** Cluster;
};

