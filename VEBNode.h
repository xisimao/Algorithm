#pragma once
/**
 * van Emde Boas�����
 */
class VEBNode
{
public:
	VEBNode()
		:Min(-1),Max(-1),Size(0)
	{
	}
	/**
	 * ��Сֵ
	 */
	int Min;
	/**
	 * ���ֵ
	 */
	int Max;
	/**
	 * ȫ��(universe)�Ĵ�С
	 */
	int Size;
	/**
	 * ��Ҫ�ṹָ�룬���ڼ�¼�صı��
	 */
	VEBNode* Summary;
	/**
	 * ��
	 */
	VEBNode** Cluster;
};

