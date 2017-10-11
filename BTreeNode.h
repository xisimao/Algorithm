#pragma once
class BTreeNode
{
public:
	BTreeNode(int minmumDegree)
	{
		Key=new int[minmumDegree*2];
		for(int i=1;i<minmumDegree*2;++i)
		{
			Key[i]=0;
		}
		Content=new BTreeNode*[minmumDegree*2+1];
		for(int i=1;i<minmumDegree*2+1;++i)
		{
			Content[i]=NULL;
		}
	}
	~BTreeNode(void)
	{
		delete[] Key;
		delete[] Content;
	}
	//��
	int* Key;
	//��������
	int KeyCount;
	//�Ƿ�ΪҶ���
	bool Leaf;
	//���ݣ�����c[i]�����м�<key[i]<c[i+1]�����м�
	BTreeNode** Content;
};

