#pragma once
#include "stdafx.h"
#include <map>
#include <vector>
using namespace std;
#include "Print.h"
#include "BuckedSort.h"
#include "CountingSort.h"
#include "MaxPriorityQueue.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "OrderStatistic.h"
#include "InsertionSort.h"
#include "FiveSeparate.h"
#include "Stack_.h"
#include "Queue_.h"
#include "Tree.h"
#include "RedBlackTree.h"
#include "OrderStatisticTree.h"
#include "IntervalTree.h"
#include "SteelCutting.h"
#include "MatrixChainMultiplication.h"
#include "LongestCommonSubSequence.h"
#include "OptimalBinarySearchTree.h"
#include "ActivitySelector.h"
#include "MinPriorityQueue.h"
#include "HuffmanCode.h"
#include "BTree.h"
#include "FibonacciHeap.h"
#include "VEBTree.h"
#include "Graph.h"
#include "MinimumSpanningTree.h"
#include "SingleSourceShortestPath.h"
#include "AllPairsShortestPaths.h"
#include "ElementaryGraphAlgorithms.h"
#include "MaximumFlow.h"
#include "StringMatching.h"
#include "Geometry.h"
#include "MergeSort.h"
#include "RandomArray.h"

int Line::SwapX;
Point* Point::BasePoint;
class Test
{
public:
	Test()
	{
		SYSTEMTIME sys;
		GetLocalTime( &sys ); 
		srand(sys.wMilliseconds);
	}
	static int TestGetIndex(int value)
	{
		return value%9;
	}
	void TestMergeSort()
	{
		int data[100]={0};
		RandomArray::GetRandomArray(data,100);

		MergeSort<int> ms;
		ms.Sort(data,0,99);
		Print::PrintArray(data,100);
	}
	void TestBuckedSort()
	{
		int data[20]={0};
		for(int i=0;i<20;++i)
		{
			data[i]=rand()%9;
		}
		Print::PrintArray(data,20);
		BuckedSort<int> bs;
		bs.Sort(data,20,Test::TestGetIndex);
		Print::PrintArray(data,20);
	}
	void TestCountingSort()
	{
		int data[20]={0};
		for(int i=0;i<20;++i)
		{
			data[i]=rand()%20;
		}
		CountingSort cs;
		Print::PrintArray(data,20);
		int result[20]={0};
		cs.Sort(data,result,20,19);
		Print::PrintArray(result,20);
	}
	void TestHeapPriorityQueue()
	{
		MaxPriorityQueue<int> hpq;
		MinPriorityQueue<int> mpq;
		int data[10]={6,8,1,3,5,2,4,12,10,7};

		for(int i=0;i<10;i++)
		{

			hpq.Insert(data[i]);
			mpq.Insert(data[i]);
		}

		for (int i=0;i<10;++i)
		{
			int max=mpq.ExtractMin();
			cout<<max<<" ";
		}
		cout<<endl;

		for (int i=0;i<10;++i)
		{
			int max=hpq.ExtractMax();
			cout<<max<<" ";
		}
		cout<<endl;
	}
	void TestHeapSort()
	{
		int data[10]={41,67,34,0,69,24,78,58,62,64};
		Print::PrintArray(data,10);
		HeapSort<int> hp;
		hp.Sort(data,10);
		Print::PrintArray(data,10);
	}
	void TestQuickSort()
	{
		int data[10]={41,67,34,0,69,24,78,58,62,64};
		Print::PrintArray(data,10);
		QuickSort<int> qs;
		qs.Sort(data,0,9);
		Print::PrintArray(data,10);
	}
	void TestRadixSort()
	{
		int data[20]={0};
		for(int i=0;i<20;++i)
		{
			data[i]=rand()%1000;
		}
		Print::PrintArray(data,20);
		RadixSort rs;
		rs.Sort(data,20);
		Print::PrintArray(data,20);
	}
	void TestOrderStatistic()
	{
		//int data[20]={41,17,34,0,19,24,28,8,12,14,5,45,31,27,11,41,45,42,27,36};
		int data[20]={0};
		for(int i=0;i<20;++i)
		{
			data[i]=rand()%71;
		}
		Print::PrintArray(data,20);
		OrderStatistic os;
		int rank=os.RandomizedSelect(data,0,19,7);
		cout<<rank<<endl;

		QuickSort<int> qs;
		qs.Sort(data,0,19);
		Print::PrintArray(data,20);
	}
	void TestInsertSort()
	{
		int data1[20]={0};
		for(int i=0;i<20;++i)
		{
			data1[i]=rand()%71;
		}
		Print::PrintArray(data1,20);
		InsertionSort<int> is;
		is.Sort(data1,6,11);
		Print::PrintArray(data1,20);
	}
	void TestFiveSeparate()
	{
		for(int i=0;i<100;++i)
		{
			map<int,int> m;
			int index=0;
			int data[26]={0};

			while(index<25)
			{
				int value=rand()%26;
				map<int,int>::const_iterator it=m.find(value);
				if(it==m.end()&&value!=0)
				{
					m[value]=0;
					data[index++]=value;

				}

			}

			FiveSeparate<int> fs;
			int result=fs.Select(data,0,24,9);
			if(data[result]!=9)
			{
				cout<<data[result]<<endl;
			}
		}
	}

	void TestStack()
	{
		Stack_<int> stack;
		stack.Push(2);
		stack.Push(1);
		stack.Push(3);
		stack.Push(4);
		stack.Push(6);
		stack.Push(7);
		stack.Push(9);
		stack.Push(5);
		stack.Push(8);
		stack.Push(10);

		while(!stack.Empty())
		{
			cout<<stack.Pop()<<endl;
		}

	}
	void TestQueue()
	{
		Queue_<int> queue;
		queue.Enqueue(1);
		queue.Dequeue();
		queue.Enqueue(2);
		queue.Enqueue(3);
		queue.Enqueue(4);
		queue.Enqueue(5);
		queue.Enqueue(6);
		queue.Enqueue(7);
		queue.Enqueue(8);
		queue.Enqueue(10);
		queue.Enqueue(9);
		queue.Enqueue(1);
		while(!queue.Empty())
		{
			cout<<queue.Dequeue()<<endl;
		}

	}

	void TestTree()
	{
		for(int i=0;i<1;++i)
		{
			Tree<int> t;
			map<int,int> m;
			int index=0;
			int data[20]={15,8,10,13,2,14,6,19,12,1,7,11,20,18,16,5,4,9,17,3};
			/*for(int i=0;i<20;++i)
			{
			t.Insert(data[i]);
			}*/
			while(index<20)
			{
				int value=rand()%21;
				map<int,int>::const_iterator it=m.find(value);
				if(it==m.end()&&value!=0)
				{
					m[value]=0;
					t.Insert(value);
					data[index++]=value;
				}
			}
			Print::PrintArray(data,20);
			TreeNode<int>* node;
			for(int i=0;i<20;++i)
			{
				InorderWalk(t.Root());
				cout<<endl;
				node=t.Search(i+1);
				/*TreeNode<int>* node2=t.Successor(node);
				if(node2==NULL)
				{
				if(node->Key!=20)
				{
				cout<<"S"<<node->Key<<" "<<endl;
				}
				}
				else if(node2->Key!=node->Key+1)
				{
				cout<<"S"<<node->Key<<" "<<node2->Key<<endl;
				}
				node2=t.Predecessor(node);

				if(node2==NULL)
				{
				if(node->Key!=1)
				{
				cout<<"P"<<node->Key<<" "<<endl;
				}
				}
				else if(node2->Key!=node->Key-1)
				{
				cout<<"P"<<node->Key<<" "<<node2->Key<<endl;
				}*/
				t.Delete(node);
			}

		}
	}

	void InorderWalk(TreeNode<int>* node)
	{
		if(node==NULL)
		{
			return;
		}
		cout<<node->Key<<" "<<node->Text<<endl;
		InorderWalk(node->Left);
		InorderWalk(node->Right);
	}
	void InorderWalk(RedBlackTree<int>* tree,RedBlackTreeNode<int>* node)
	{
		if(tree->IsNil(node))
		{
			return;
		}
		cout<<node->Key<<"-"<<(node->Color?"R":"B")<<"  ";
		if(!tree->IsNil(node->Left))
		{
			cout<<node->Left->Key<<"-"<<(node->Left->Color?"R":"B")<<"  ";
		}
		else
		{
			cout<<"     ";
		}
		if(!tree->IsNil(node->Right))
		{
			cout<<node->Right->Key<<"-"<<(node->Right->Color?"R":"B")<<"  ";
		}
		else
		{
			cout<<"     ";
		}
		cout<<endl;
		InorderWalk(tree,node->Left);
		InorderWalk(tree,node->Right);
	}

	
	void TestRedBlackTree()
	{
		/*for(int j=0;j<10;++j)
		{*/
			RedBlackTree<int> tree;
			int data[10]={8,3,6,9,4,2,1,5,7,0};
			//RandomArray::GetRandomArray(data,10);
			for(int i=0;i<10;++i)
			{
				tree.Insert(data[i]);
				int value1=tree.CheckRedBlack();
				cout<<value1<<"  ";
			}
			cout<<endl;
			RedBlackTreeNode<int>* node= tree.Minimum(tree.Root());
			while(!tree.IsNil(node))
			{
				//point=points.Successor(point);
				tree.Delete(node);
				int value=tree.CheckRedBlack();
				cout<<value<<"  ";
				node=tree.Minimum(tree.Root());
			}
		//}
	}

	void InorderWalk(OrderStatisticTree<int>* tree,OrderStatisticTreeNode<int>* node)
	{
		if(tree->IsNil(node))
		{
			return;
		}
		cout<<node->Key<<"-"<<node->Size<<"-"<<(node->Color?"R":"B")<<"  ";
		if(!tree->IsNil(node->Left))
		{
			cout<<node->Left->Key<<"-"<<node->Left->Size<<"-"<<(node->Left->Color?"R":"B")<<"  ";
		}
		else
		{
			cout<<"     ";
		}
		if(!tree->IsNil(node->Right))
		{
			cout<<node->Right->Key<<"-"<<node->Right->Size<<"-"<<(node->Right->Color?"R":"B")<<"  ";
		}
		else
		{
			cout<<"     ";
		}
		cout<<endl;
		InorderWalk(tree,node->Left);
		InorderWalk(tree,node->Right);
	}
	void InorderWalk1(OrderStatisticTree<int>* tree,OrderStatisticTreeNode<int>* node)
	{
		if(tree->IsNil(node))
		{
			return;
		}
	
		InorderWalk1(tree,node->Left);
		cout<<node->Key<<" ";
		InorderWalk1(tree,node->Right);
	}
	void TestOrderTree()
	{
		int data[20]={0};
		RandomArray::GetRandomArray(data,20);
		OrderStatisticTree<int> tree;
		for(int i=0;i<20;++i)
		{
			cout<<data[i]<<" ";
			tree.Insert(data[i]);
		}
		cout<<endl;
		InorderWalk1(&tree,tree.Root());
		cout<<endl;
		for(int i=0;i<20;++i)
		{
			OrderStatisticTreeNode<int>* node=tree.Select(i+1);
			cout<<tree.Rank(node)<<" ";
		}

	}
	void InorderWalk(IntervalTree<int>* tree,IntervalTreeNode<int>* node)
	{
		if(tree->IsNil(node))
		{
			return;
		}
		cout<<node->Low<<"-"<<node->High<<"-"<<node->Max<<"-"<<(node->Color?"R":"B")<<"  ";
		if(!tree->IsNil(node->Left))
		{
			cout<<node->Left->Low<<"-"<<node->Left->High<<"-"<<node->Left->Max<<"-"<<(node->Left->Color?"R":"B")<<"  ";
		}
		else
		{
			cout<<"     ";
		}
		if(!tree->IsNil(node->Right))
		{
			cout<<node->Right->Low<<"-"<<node->Right->High<<"-"<<node->Right->Max<<"-"<<(node->Right->Color?"R":"B")<<"  ";
		}
		else
		{
			cout<<"     ";
		}
		cout<<endl;
		InorderWalk(tree,node->Left);
		InorderWalk(tree,node->Right);
	}
	void TestIntervalTree()
	{
		IntervalTree<int> tree;
		int data[20]={0};
		RandomArray::GetRandomArray(data,20);
		for(int i=0;i<10;++i)
		{
			cout<<data[i]<<" ";
			tree.Insert(i,i+5);
		}
		cout<<endl;
		InorderWalk(&tree,tree.Root());

		IntervalTreeNode<int>* node=tree.Search(8,9);
		cout<<node->Low<<" "<<node->High;
	}

	void TestSteelCutting()
	{
		SteelCutting sc;
		for(int i=1;i<11;++i)
		{
			cout<<sc.BottomUpCutRot(i)<<endl;
		}
		
	}

	void TestMatrixChain()
	{
		MatrixChainMultiplication m;
		int p[4]={10,100,5,50};
		m.MemoizedMatrixChain(p,4);
	}


	void TestLCS()
	{
		char a[10]={'D','C','E','D','A','C','D','C','B','E'};
		char b[10]={'B','D','E','D','C','C','E','A','D','E'};

		for(int i=0;i<10;++i)
		{
			//a[i]=65+rand()%5;
			cout<<a[i]<<" ";
		}
		cout<<endl;
		for(int i=0;i<10;++i)
		{
			//b[i]=65+rand()%5;
			cout<<b[i]<<" ";
		}
		cout<<endl;
		LongestCommonSubSequence lcs;
		lcs.LCSLength(a,10,b,10);
		
	}

	void TestBST()
	{
		float p[6]={0,0.15,0.10,0.05,0.10,0.20};
		float q[6]={0.05,0.10,0.05,0.05,0.05,0.10};
		OptimalBinarySearchTree obst;
		obst.OpatimalBST(p,q,5);
	}

	void TestActivity()
	{
		int s[12]={0,1,3,0,5,3,5,6,8,8,2,12};
		int f[12]={0,4,5,6,7,9,9,10,11,12,14,16};

		ActivitySelector as;
		vector<int> list;
		as.GreedyActivitySelector(s,f,11,list);
		for(int i=0;i<list.size();++i)
		{
			cout<<list[i]<<endl;
		}
	}
	
	void TestHuffman()
	{
		HuffmanCode hc;

		TreeNode<int> nodes[6];


		nodes[0].Key=5;
		nodes[0].Text='f';


		nodes[1].Key=9;
		nodes[1].Text='e';


		nodes[2].Key=12;
		nodes[2].Text='c';


		nodes[3].Key=13;
		nodes[3].Text='b';


		nodes[4].Key=16;
		nodes[4].Text='d';


		nodes[5].Key=45;
		nodes[5].Text='a';
	
		TreeNode<int> root=hc.Build(nodes,6);
	 
		InorderWalk(&root);
		DeleteNode(root.Left);
		DeleteNode(root.Right);

	}
	void DeleteNode(TreeNode<int>* node)
	{
		if(node==NULL)
		{
			return;
		}
		DeleteNode(node->Left);
		DeleteNode(node->Right);
		delete node;
	}

	void TestBTree()
	{
		
		/*BTreeNode* node1=new BTreeNode(3);
		node1->Key[1]=1;
		node1->Key[2]=2;
		node1->KeyCount=2;
		
		BTreeNode* node2=new BTreeNode(3);
		node2->Key[1]=4;
		node2->Key[2]=5;
		node2->Key[3]=6;
		node2->KeyCount=3;

		BTreeNode* node3=new BTreeNode(3);
		node3->Key[1]=10;
		node3->Key[2]=11;
		node3->Key[3]=12;
		node3->KeyCount=3;

		BTreeNode* node4=new BTreeNode(3);
		node4->Key[1]=14;
		node4->Key[2]=15;
		node4->KeyCount=2;

		BTreeNode* node5=new BTreeNode(3);
		node5->Key[1]=3;
		node5->Key[2]=7;
		node5->Key[3]=13;
		node5->KeyCount=3;
		node5->Content[1]=node1;
		node5->Content[2]=node2;
		node5->Content[3]=node3;
		node5->Content[4]=node4;
		node5->Leaf=false;

		BTreeNode* node6=new BTreeNode(3);
		node6->Key[1]=17;
		node6->Key[2]=18;
		node6->Key[3]=19;
		node6->KeyCount=3;

		BTreeNode* node7=new BTreeNode(3);
		node7->Key[1]=21;
		node7->Key[2]=22;
		node7->KeyCount=2;

		BTreeNode* node8=new BTreeNode(3);
		node8->Key[1]=25;
		node8->Key[2]=26;
		node8->KeyCount=2;

		BTreeNode* node9=new BTreeNode(3);
		node9->Key[1]=20;
		node9->Key[2]=24;
		node9->KeyCount=2;
		node9->Content[1]=node6;
		node9->Content[2]=node7;
		node9->Content[3]=node8;
		node9->Leaf=false;

		BTreeNode* node10=new BTreeNode(3);
		node10->Key[1]=16;
		node10->KeyCount=1;
		node10->Content[1]=node5;
		node10->Content[2]=node9;
		node10->Leaf=false;
		BTree tree;
		tree._root=node10;
		tree.Delete(tree._root,'F'-'A'+1);
		tree.Delete(tree._root,'M'-'A'+1);
		tree.Delete(tree._root,'G'-'A'+1);
		tree.Delete(tree._root,'D'-'A'+1);
		tree.Delete(tree._root,'B'-'A'+1);*/
		BTree tree;
		tree.Create(3);
		tree.Insert(1);
		tree.Insert(2);
		tree.Insert(3);
		tree.Insert(4);
		tree.Insert(5);
		tree.Insert(6);
	}

	void TestFibonacci()
	{
		FibonacciHeap heap;
		for(int i=0;i<16;++i)
		{
			heap.Insert(i);

		}
		heap.ExtractMin();
		HeapNode<int>* node=heap.Search(7);
		heap.Delete(node);
		node=heap.Search(6);
		heap.Delete(node);
		for(int i=0;i<13;++i)
		{
			HeapNode<int>* node=heap.ExtractMin();
			cout<<node->Key<<endl;
		}
	}

	void TestVanEmbeBoasTree()
	{
		VEBTree tree;
		tree.Create(16);
		tree.Insert(tree._root,2);
		tree.Insert(tree._root,3);
		//tree.Insert(tree._root,4);
		//tree.Insert(tree._root,5);
		tree.Insert(tree._root,7);
		//tree.Insert(tree._root,14);
		//tree.Insert(tree._root,15);


		//cout<<tree.Minimum(tree._root)<<endl;
		//cout<<tree.Maximum(tree._root)<<endl;
		//cout<<tree.Member(tree._root,5)<<endl;
		//cout<<tree.Member(tree._root,6)<<endl;
		//cout<<tree.Predecessor(tree._root,14)<<endl;
		//cout<<tree.Successor(tree._root,5)<<endl;
		tree.Delete(tree._root,7);
		//cout<<tree.Successor(tree._root,5)<<endl;
	}

	void Test1()
	{
		TreeNode<int> node1;
		node1.Key=1;
		node1.Parent=&node1;
		TreeNode<int> node2;
		node2.Key=2;
		node2.Parent=&node1;
		TreeNode<int> node3;
		node3.Key=3;
		node3.Parent=&node2;
		TreeNode<int> node4;
		node4.Key=4;
		node4.Parent=&node3;

		TreeNode<int>* n=FindSet(&node4);
	}
	TreeNode<int>* FindSet(TreeNode<int>* node)
	{
		if(node!=node->Parent)
		{
			node->Parent=FindSet(node->Parent);
		}
		return node->Parent;
	}
	void InitBFSGraph(Graph& g)
	{
		Vertex* s=new Vertex();
		s->Text="s";
		Vertex* r=new Vertex();
		r->Text="r";
		Vertex* v=new Vertex();
		v->Text="v";
		Vertex* w=new Vertex();
		w->Text="w";
		Vertex* t=new Vertex();
		t->Text="t";
		Vertex* u=new Vertex();
		u->Text="u";
		Vertex* x=new Vertex();
		x->Text="x";
		Vertex* y=new Vertex();
		y->Text="y";
			Vertex** V=new Vertex*[8];
		V[0]=s;
		V[1]=r;
		V[2]=v;
		V[3]=w;
		V[4]=t;
		V[5]=u;
		V[6]=x;
		V[7]=y;

		Edge* edge1=new Edge;
		edge1->Start=s;
		edge1->End=r;
		edge1->Weight=1;

		Edge* edge2=new Edge;
		edge2->Start=s;
		edge2->End=w;
		edge2->Weight=1;

		Edge* edge3=new Edge;
		edge3->Start=r;
		edge3->End=s;
		edge3->Weight=1;

		Edge* edge4=new Edge;
		edge4->Start=r;
		edge4->End=v;
		edge4->Weight=1;

		Edge* edge5=new Edge;
		edge5->Start=v;
		edge5->End=r;
		edge5->Weight=1;

		Edge* edge6=new Edge;
		edge6->Start=w;
		edge6->End=s;
		edge6->Weight=1;

		Edge* edge7=new Edge;
		edge7->Start=w;
		edge7->End=t;
		edge7->Weight=1;

		Edge* edge8=new Edge;
		edge8->Start=w;
		edge8->End=x;
		edge8->Weight=1;

		Edge* edge9=new Edge;
		edge9->Start=t;
		edge9->End=w;
		edge9->Weight=1;

		Edge* edge10=new Edge;
		edge10->Start=t;
		edge10->End=u;
		edge10->Weight=1;

		Edge* edge11=new Edge;
		edge11->Start=t;
		edge11->End=x;
		edge11->Weight=1;

		Edge* edge12=new Edge;
		edge12->Start=u;
		edge12->End=t;
		edge12->Weight=1;

		Edge* edge13=new Edge;
		edge13->Start=u;
		edge13->End=x;
		edge13->Weight=1;

		Edge* edge14=new Edge;
		edge14->Start=u;
		edge14->End=y;
		edge14->Weight=1;

		Edge* edge15=new Edge;
		edge15->Start=x;
		edge15->End=w;
		edge15->Weight=1;

		Edge* edge16=new Edge;
		edge16->Start=x;
		edge16->End=t;
		edge16->Weight=1;

		Edge* edge17=new Edge;
		edge17->Start=x;
		edge17->End=u;
		edge17->Weight=1;

		Edge* edge18=new Edge;
		edge18->Start=x;
		edge18->End=y;
		edge18->Weight=1;

		Edge* edge19=new Edge;
		edge19->Start=y;
		edge19->End=u;
		edge19->Weight=1;

		Edge* edge20=new Edge;
		edge20->Start=y;
		edge20->End=x;
		edge20->Weight=1;

		Edge* edges[20]={edge1,edge2,edge3,edge4,edge5,edge6,edge7,edge8,edge9,edge10,edge11,edge12,edge13,edge14,edge15,edge16,edge17,edge18,edge19,edge20};
		g.Init(V,8,edges,20);
	}
	void InitDFSGraph(Graph& g)
	{
		Vertex* u=new Vertex();
		u->Text="u";
		Vertex* v=new Vertex();
		v->Text="v";
		Vertex* w=new Vertex();
		w->Text="w";
		Vertex* x=new Vertex();
		x->Text="x";
		Vertex* y=new Vertex();
		y->Text="y";
		Vertex* z=new Vertex();
		z->Text="z";

		Vertex** V=new Vertex*[8];
		V[0]=u;
		V[1]=v;
		V[2]=w;
		V[3]=x;
		V[4]=y;
		V[5]=z;

		

		Edge* edge1=new Edge;
		edge1->Start=u;
		edge1->End=v;
		edge1->Weight=1;

		Edge* edge2=new Edge;
		edge2->Start=u;
		edge2->End=x;
		edge2->Weight=1;

		Edge* edge3=new Edge;
		edge3->Start=v;
		edge3->End=y;
		edge3->Weight=1;

		Edge* edge4=new Edge;
		edge4->Start=w;
		edge4->End=y;
		edge4->Weight=1;

		Edge* edge5=new Edge;
		edge5->Start=w;
		edge5->End=z;
		edge5->Weight=1;

		Edge* edge6=new Edge;
		edge6->Start=x;
		edge6->End=v;
		edge6->Weight=1;

		Edge* edge7=new Edge;
		edge7->Start=y;
		edge7->End=x;
		edge7->Weight=1;

		Edge* edge8=new Edge;
		edge8->Start=z;
		edge8->End=z;
		edge8->Weight=1;

		Edge** edges=new Edge*[8];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;

		g.Init(V,6,edges,8);
	}
	void InitTSGraph(Graph& g)
	{

		Vertex* n=new Vertex();
		n->Text="n";
		Vertex* w=new Vertex();
		w->Text="w";
		Vertex* k=new Vertex();
		k->Text="k";
		Vertex* x=new Vertex();
		x->Text="x";
		Vertex* s=new Vertex();
		s->Text="s";
		Vertex* y=new Vertex();
		y->Text="y";
		Vertex* c=new Vertex();
		c->Text="c";
		Vertex* l=new Vertex();
		l->Text="l";
		Vertex* j=new Vertex();
		j->Text="j";

		Vertex** V=new Vertex*[9];
		V[0]=n;
		V[1]=w;
		V[2]=k;
		V[3]=x;
		V[4]=s;
		V[5]=y;
		V[6]=c;
		V[7]=l;
		V[8]=j;


		Edge* edge1=new Edge;
		edge1->Start=n;
		edge1->End=k;
		edge1->Weight=1;

		Edge* edge2=new Edge;
		edge2->Start=n;
		edge2->End=x;
		edge2->Weight=1;

		Edge* edge3=new Edge;
		edge3->Start=w;
		edge3->End=x;
		edge3->Weight=1;

		Edge* edge4=new Edge;
		edge4->Start=k;
		edge4->End=x;
		edge4->Weight=1;

		Edge* edge5=new Edge;
		edge5->Start=k;
		edge5->End=y;
		edge5->Weight=1;

		Edge* edge6=new Edge;
		edge6->Start=y;
		edge6->End=j;
		edge6->Weight=1;

		Edge* edge7=new Edge;
		edge7->Start=c;
		edge7->End=y;
		edge7->Weight=1;

		Edge* edge8=new Edge;
		edge8->Start=c;
		edge8->End=l;
		edge8->Weight=1;

		Edge* edge9=new Edge;
		edge9->Start=l;
		edge9->End=j;
		edge9->Weight=1;

		Edge** edges=new Edge*[9];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;
		g.Init(V,9,edges,9);
	}
	void InitSCC(Graph& gr)
	{
		Vertex* a=new Vertex();
		a->Text="a";
		a->Index=0;
		Vertex* b=new Vertex();
		b->Text="b";
		b->Index=1;
		Vertex* c=new Vertex();
		c->Text="c";
		c->Index=2;
		Vertex* d=new Vertex();
		d->Text="d";
		d->Index=3;
		Vertex* e=new Vertex();
		e->Text="e";
		e->Index=4;
		Vertex* f=new Vertex();
		f->Text="f";
		f->Index=5;
		Vertex* g=new Vertex();
		g->Text="g";
		g->Index=6;
		Vertex* h=new Vertex();
		h->Text="h";
		h->Index=7;

		Vertex** V=new Vertex*[8];
		V[0]=a;
		V[1]=b;
		V[2]=c;
		V[3]=d;
		V[4]=e;
		V[5]=f;
		V[6]=g;
		V[7]=h;

	

		Edge* edge1=new Edge;
		edge1->Start=a;
		edge1->End=b;

		Edge* edge2=new Edge;
		edge2->Start=b;
		edge2->End=c;

		Edge* edge3=new Edge;
		edge3->Start=b;
		edge3->End=e;

		Edge* edge4=new Edge;
		edge4->Start=b;
		edge4->End=f;

		Edge* edge5=new Edge;
		edge5->Start=c;
		edge5->End=d;

		Edge* edge6=new Edge;
		edge6->Start=c;
		edge6->End=g;

		Edge* edge7=new Edge;
		edge7->Start=d;
		edge7->End=c;

		Edge* edge8=new Edge;
		edge8->Start=d;
		edge8->End=h;

		Edge* edge9=new Edge;
		edge9->Start=e;
		edge9->End=a;

		Edge* edge10=new Edge;
		edge10->Start=e;
		edge10->End=f;

		Edge* edge11=new Edge;
		edge11->Start=f;
		edge11->End=g;

		Edge* edge12=new Edge;
		edge12->Start=g;
		edge12->End=f;

		Edge* edge13=new Edge;
		edge13->Start=g;
		edge13->End=h;

		Edge* edge14=new Edge;
		edge14->Start=h;
		edge14->End=h;

		Edge** edges=new Edge*[14];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;
		edges[9]=edge10;
		edges[10]=edge11;
		edges[11]=edge12;
		edges[12]=edge13;
		edges[13]=edge14;
		gr.Init(V,8,edges,14);
	}
	void ShowAdj(Graph &g)
	{
		cout<<"  ";
		for(int i=0;i<g._verCount;++i)
		{
			cout<<g._verteies[i]->Text<<"  ";
		}
		cout<<endl;
		for(int i=0;i<g._verCount;++i)
		{
			cout<<g._verteies[i]->Text<<" ";
			for(int j=0;j<g._verCount;++j)
			{
				if(g._adj[i][j]==INT_MAX)
				{
					cout<<"¡Þ ";
				}
				else
				{
					cout<<g._adj[i][j]<<"  ";
				}
			}
			cout<<endl;
		}
	}
	void TestElementary()
	{
		ElementaryGraphAlgorithms e;

		/*Graph g;

		
		InitBFSGraph(g);
		e.BFS(g,g._verteies[0]);
		for(int i=0;i<g._verCount;++i)
		{
			cout<<g._verteies[i]->Text<<" "<<g._verteies[i]->Discover<<endl;
		}
		cout<<endl;

		Graph g2;
		InitDFSGraph(g2);
		e.DFS(g2);
		for(int i=0;i<g2._verCount;++i)
		{
			cout<<g2._verteies[i]->Text<<" "<<g2._verteies[i]->Discover<<" "<<g2._verteies[i]->Finish<<endl;
		}
		cout<<endl;*/
		Graph g3;
		InitTSGraph(g3);
		e.TopologicalSort(g3);
		for(int i=0;i<g3._verCount;++i)
		{
			cout<<g3._verteies[i]->Text<<" "<<g3._verteies[i]->Discover<<" "<<g3._verteies[i]->Finish<<endl;
		}

		/*Graph g4;
		InitSCC(g4);

		e.StronglyConnectedComponents(g4);


		for(int i=0;i<g4._verCount;++i)
		{
			cout<<g4._verteies[i]->Text;
			if(g4._verteies[i]->Pre==NULL)
			{
				cout<<endl;
			}
			else
			{
				cout<<"  "<<g4._verteies[i]->Pre->Text<<endl;
			}
		}*/
	}
	void InitMST(Graph& gr)
	{
		Vertex* a=new Vertex;
		a->Text="a";

		Vertex* b=new Vertex;
		b->Text="b";

		Vertex* c=new Vertex;
		c->Text="c";

		Vertex* d=new Vertex;
		d->Text="d";

		Vertex* e=new Vertex;
		e->Text="e";

		Vertex* f=new Vertex;
		f->Text="f";

		Vertex* g=new Vertex;
		g->Text="g";

		Vertex* h=new Vertex;
		h->Text="h";

		Vertex* i=new Vertex;
		i->Text="i";

		Edge* edge1=new Edge;
		edge1->Start=a;
		edge1->End=b;
		edge1->Weight=4;

		Edge* edge2=new Edge;
		edge2->Start=a;
		edge2->End=h;
		edge2->Weight=9;

		Edge* edge3=new Edge;
		edge3->Start=b;
		edge3->End=c;
		edge3->Weight=8;

		Edge* edge4=new Edge;
		edge4->Start=b;
		edge4->End=h;
		edge4->Weight=11;

		Edge* edge5=new Edge;
		edge5->Start=c;
		edge5->End=d;
		edge5->Weight=7;

		Edge* edge6=new Edge;
		edge6->Start=c;
		edge6->End=f;
		edge6->Weight=4;

		Edge* edge7=new Edge;
		edge7->Start=c;
		edge7->End=i;
		edge7->Weight=2;

		Edge* edge8=new Edge;
		edge8->Start=d;
		edge8->End=e;
		edge8->Weight=9;

		Edge* edge9=new Edge;
		edge9->Start=d;
		edge9->End=f;
		edge9->Weight=14;

		Edge* edge10=new Edge;
		edge10->Start=e;
		edge10->End=f;
		edge10->Weight=10;

		Edge* edge11=new Edge;
		edge11->Start=f;
		edge11->End=g;
		edge11->Weight=2;

		Edge* edge12=new Edge;
		edge12->Start=g;
		edge12->End=h;
		edge12->Weight=1;

		Edge* edge13=new Edge;
		edge13->Start=g;
		edge13->End=i;
		edge13->Weight=6;

		Edge* edge14=new Edge;
		edge14->Start=h;
		edge14->End=i;
		edge14->Weight=7;

		Vertex** V=new Vertex*[9];
		V[0]=a;
		V[1]=b;
		V[2]=c;
		V[3]=d;
		V[4]=e;
		V[5]=f;
		V[6]=g;
		V[7]=h;
		V[8]=i;

		Edge** edges=new Edge*[28];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;
		edges[9]=edge10;
		edges[10]=edge11;
		edges[11]=edge12;
		edges[12]=edge13;
		edges[13]=edge14;

		for(int i=0;i<14;++i)
		{
			edges[i+14]=new Edge;
			edges[i+14]->Start=edges[i]->End;
			edges[i+14]->End=edges[i]->Start;
			edges[i+14]->Weight=edges[i]->Weight;
		}
		gr.Init(V,9,edges,28);
	}
	void TestMST()
	{
		MinimumSpanningTree mst;
		Graph g4;
		InitMST(g4);

		Edge* list[20];
		memset(list,0,20*sizeof(Edge*));
		mst.Kruskal(g4,list);
		for(int i=0;i<20;++i)
		{
		if(list[i]==NULL)
		{
		break;
		}
		cout<<list[i]->Start->Text<<"-"<<list[i]->End->Text<<"-"<<list[i]->Weight<<endl;
		}
		cout<<endl;
		mst.Prim(g4,g4._verteies[0]);
	
		for(int i=0;i<g4._verCount;++i)
		{
			cout<<g4._verteies[i]->Text<<" "<<(g4._verteies[i]->Pre==NULL?"null":g4._verteies[i]->Pre->Text)<<endl;
		}
	}
	void InitBellmanFord(Graph& g)
	{
		Vertex* s=new Vertex;
		s->Text="s";
		Vertex* t=new Vertex;
		t->Text="t";
		Vertex* x=new Vertex;
		x->Text="x";
		Vertex* z=new Vertex;
		z->Text="z";
		Vertex* y=new Vertex;
		y->Text="y";
		Vertex** v=new Vertex*[5];
		v[0]=s;
		v[1]=t;
		v[2]=x;
		v[3]=y;
		v[4]=z;
		Edge* edge1=new Edge;
		edge1->Start=s;
		edge1->End=t;
		edge1->Weight=6;

		Edge* edge2=new Edge;
		edge2->Start=s;
		edge2->End=y;
		edge2->Weight=7;

		Edge* edge3=new Edge;
		edge3->Start=t;
		edge3->End=y;
		edge3->Weight=8;

		Edge* edge4=new Edge;
		edge4->Start=t;
		edge4->End=x;
		edge4->Weight=5;

		Edge* edge5=new Edge;
		edge5->Start=t;
		edge5->End=z;
		edge5->Weight=-4;

		Edge* edge6=new Edge;
		edge6->Start=y;
		edge6->End=z;
		edge6->Weight=9;

		Edge* edge7=new Edge;
		edge7->Start=y;
		edge7->End=x;
		edge7->Weight=-3;

		Edge* edge8=new Edge;
		edge8->Start=x;
		edge8->End=t;
		edge8->Weight=-2;

		Edge* edge9=new Edge;
		edge9->Start=z;
		edge9->End=s;
		edge9->Weight=2;

		Edge* edge10=new Edge;
		edge10->Start=z;
		edge10->End=x;
		edge10->Weight=7;

		Edge** e=new Edge*[10];
		e[0]=edge1;
		e[1]=edge2;
		e[2]=edge3;
		e[3]=edge4;
		e[4]=edge5;
		e[5]=edge6;
		e[6]=edge7;
		e[7]=edge8;
		e[8]=edge9;
		e[9]=edge10;
		g.Init(v,5,e,10);
	}
	void InitDag(Graph& g)
	{
		Vertex* s=new Vertex;
		s->Text="s";
		Vertex* t=new Vertex;
		t->Text="t";
		Vertex* x=new Vertex;
		x->Text="x";
		Vertex* z=new Vertex;
		z->Text="z";
		Vertex* y=new Vertex;
		y->Text="y";
		Vertex* r=new Vertex;
		r->Text="r";

		Vertex** v=new Vertex*[6];
		v[0]=s;
		v[1]=t;
		v[2]=x;
		v[3]=z;
		v[4]=y;
		v[5]=r;

		Edge* edge1=new Edge;
		edge1->Start=r;
		edge1->End=s;
		edge1->Weight=5;

		Edge* edge2=new Edge;
		edge2->Start=r;
		edge2->End=t;
		edge2->Weight=3;

		Edge* edge3=new Edge;
		edge3->Start=s;
		edge3->End=t;
		edge3->Weight=2;

		Edge* edge4=new Edge;
		edge4->Start=s;
		edge4->End=x;
		edge4->Weight=6;

		Edge* edge5=new Edge;
		edge5->Start=t;
		edge5->End=x;
		edge5->Weight=7;

		Edge* edge6=new Edge;
		edge6->Start=t;
		edge6->End=y;
		edge6->Weight=4;

		Edge* edge7=new Edge;
		edge7->Start=t;
		edge7->End=z;
		edge7->Weight=2;

		Edge* edge8=new Edge;
		edge8->Start=x;
		edge8->End=y;
		edge8->Weight=-1;

		Edge* edge9=new Edge;
		edge9->Start=x;
		edge9->End=z;
		edge9->Weight=1;

		Edge* edge10=new Edge;
		edge10->Start=y;
		edge10->End=z;
		edge10->Weight=-2;

		Edge** edges=new Edge*[10];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;
		edges[9]=edge10;
		g.Init(v,6,edges,10);
	}
	void InitDijkstra(Graph& g)
	{
		Vertex* s=new Vertex;
		s->Text="s";
		Vertex* t=new Vertex;
		t->Text="t";
		Vertex* x=new Vertex;
		x->Text="x";
		Vertex* z=new Vertex;
		z->Text="z";
		Vertex* y=new Vertex;
		y->Text="y";

		Vertex** v=new Vertex*[5];
		v[0]=s;
		v[1]=t;
		v[2]=x;
		v[3]=z;
		v[4]=y;
		Edge* edge1=new Edge;
		edge1->Start=s;
		edge1->End=t;
		edge1->Weight=10;

		Edge* edge2=new Edge;
		edge2->Start=s;
		edge2->End=y;
		edge2->Weight=5;

		Edge* edge3=new Edge;
		edge3->Start=t;
		edge3->End=y;
		edge3->Weight=2;

		Edge* edge4=new Edge;
		edge4->Start=t;
		edge4->End=x;
		edge4->Weight=1;

		Edge* edge5=new Edge;
		edge5->Start=y;
		edge5->End=x;
		edge5->Weight=9;

		Edge* edge6=new Edge;
		edge6->Start=y;
		edge6->End=z;
		edge6->Weight=2;

		Edge* edge7=new Edge;
		edge7->Start=y;
		edge7->End=t;
		edge7->Weight=3;

		Edge* edge8=new Edge;
		edge8->Start=x;
		edge8->End=z;
		edge8->Weight=4;

		Edge* edge9=new Edge;
		edge9->Start=z;
		edge9->End=x;
		edge9->Weight=6;

		Edge* edge10=new Edge;
		edge10->Start=z;
		edge10->End=s;
		edge10->Weight=7;

		Edge** edges=new Edge*[10];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;
		edges[9]=edge10;
		g.Init(v,5,edges,10);
	}
	void TestSingleSource()
	{
		SingleSourceShortestPath ss1;
		Graph g;
		InitBellmanFord(g);
		bool result=ss1.BellmanFord(g,g._verteies[0]);
		cout<<result<<endl;

		for(int i=0;i<g._verCount;++i)
		{
			cout<<g._verteies[i]->Text<<"  "<<g._verteies[i]->WeightEstimate<<endl;
		}
		cout<<endl;

		Graph g1;
		InitDag(g1);
		ss1.DagShortestPaths(g1,g1._verteies[0]);

		for(int i=0;i<g1._verCount;++i)
		{
			cout<<g1._verteies[i]->Text<<"  "<<g1._verteies[i]->WeightEstimate<<endl;
		}
		cout<<endl;

		Graph g2;
		InitDijkstra(g2);
		ss1.Dijkstra(g2,g2._verteies[0]);
		for(int i=0;i<g2._verCount;++i)
		{
			cout<<g2._verteies[i]->Text<<"  "<<g2._verteies[i]->WeightEstimate<<endl;
		}
	}
	void InitAllPairs(Graph& g)
	{
		Vertex* v1=new Vertex;
		v1->Text="1";
		Vertex* v2=new Vertex;
		v2->Text="2";
		Vertex* v3=new Vertex;
		v3->Text="3";
		Vertex* v4=new Vertex;
		v4->Text="4";
		Vertex* v5=new Vertex;
		v5->Text="5";

		Vertex** v=new Vertex*[5];
		v[0]=v1;
		v[1]=v2;
		v[2]=v3;
		v[3]=v4;
		v[4]=v5;
		Edge* edge1=new Edge;
		edge1->Start=v1;
		edge1->End=v2;
		edge1->Weight=3;

		Edge* edge2=new Edge;
		edge2->Start=v1;
		edge2->End=v3;
		edge2->Weight=8;

		Edge* edge3=new Edge;
		edge3->Start=v1;
		edge3->End=v5;
		edge3->Weight=-4;

		Edge* edge4=new Edge;
		edge4->Start=v2;
		edge4->End=v4;
		edge4->Weight=1;

		Edge* edge5=new Edge;
		edge5->Start=v2;
		edge5->End=v5;
		edge5->Weight=7;

		Edge* edge6=new Edge;
		edge6->Start=v3;
		edge6->End=v2;
		edge6->Weight=4;

		Edge* edge7=new Edge;
		edge7->Start=v4;
		edge7->End=v1;
		edge7->Weight=2;

		Edge* edge8=new Edge;
		edge8->Start=v4;
		edge8->End=v3;
		edge8->Weight=-5;

		Edge* edge9=new Edge;
		edge9->Start=v5;
		edge9->End=v4;
		edge9->Weight=6;

		Edge** edges=new Edge*[9];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;
		g.Init(v,5,edges,9);
	}
	void InitClosure(Graph& g)
	{
		Vertex* v1=new Vertex;
		v1->Text=1;
		Vertex* v2=new Vertex;
		v2->Text=2;
		Vertex* v3=new Vertex;
		v3->Text=3;
		Vertex* v4=new Vertex;
		v4->Text=4;

		Vertex** v=new Vertex*[4];
		v[0]=v1;
		v[1]=v2;
		v[2]=v3;
		v[3]=v4;
		Edge* edge1=new Edge;
		edge1->Start=v2;
		edge1->End=v3;

		Edge* edge2=new Edge;
		edge2->Start=v2;
		edge2->End=v4;

		Edge* edge3=new Edge;
		edge3->Start=v4;
		edge3->End=v3;

		Edge* edge4=new Edge;
		edge4->Start=v4;
		edge4->End=v1;

		Edge* edge5=new Edge;
		edge5->Start=v3;
		edge5->End=v2;

		Edge** edges=new Edge*[5];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		g.Init(v,4,edges,5);
	}
	void TestAllPairs()
	{
		AllPairsShortestPaths ss;
		Graph g;
		InitAllPairs(g);
		ss.SlowAllPairs(g);
		cout<<endl;

		ss.RepeatSquare(g);
		cout<<endl;
		ss.FloydWarshall(g);
		cout<<endl;
		ss.Johnson(g);

		Graph g1;
		InitClosure(g1);
		ss.TransitiveClosure(g1);
	}

	void TestMaxFlow()
	{
		Vertex* s=new Vertex;
		s->Text="s";
		Vertex* v1=new Vertex;
		v1->Text="v1";
		Vertex* v2=new Vertex;
		v2->Text="v2";
		Vertex* v3=new Vertex;
		v3->Text="v3";
		Vertex* v4=new Vertex;
		v4->Text="v4";
		Vertex* t=new Vertex;
		t->Text="t";

		Vertex** v=new Vertex*[6];
		v[0]=s;
		v[1]=v1;
		v[2]=v2;
		v[3]=v3;
		v[4]=v4;
		v[5]=t;

		Edge* edge1=new Edge;
		edge1->Start=s;
		edge1->End=v1;
		edge1->Capacity=16;

		Edge* edge2=new Edge;
		edge2->Start=s;
		edge2->End=v2;
		edge2->Capacity=13;

		Edge* edge3=new Edge;
		edge3->Start=v2;
		edge3->End=v1;
		edge3->Capacity=4;

		Edge* edge4=new Edge;
		edge4->Start=v1;
		edge4->End=v3;
		edge4->Capacity=12;

		Edge* edge5=new Edge;
		edge5->Start=v3;
		edge5->End=v2;
		edge5->Capacity=9;

		Edge* edge6=new Edge;
		edge6->Start=v2;
		edge6->End=v4;
		edge6->Capacity=14;

		Edge* edge7=new Edge;
		edge7->Start=v4;
		edge7->End=v3;
		edge7->Capacity=7;

		Edge* edge8=new Edge;
		edge8->Start=v4;
		edge8->End=t;
		edge8->Capacity=4;	

		Edge* edge9=new Edge;
		edge9->Start=v3;
		edge9->End=t;
		edge9->Capacity=20;

		Edge** edges=new Edge*[9];
		edges[0]=edge1;
		edges[1]=edge2;
		edges[2]=edge3;
		edges[3]=edge4;
		edges[4]=edge5;
		edges[5]=edge6;
		edges[6]=edge7;
		edges[7]=edge8;
		edges[8]=edge9;

		Graph g;
		g.Init(v,6,edges,9);
		MaximumFlow mf;
		//cout<<mf.EdmondsKarp(g,s,t)<<endl;
		//cout<<mf.GenericPushRelabel(g,s,t)<<endl;
		//cout<<mf.RelabelToFront(g,s,t)<<endl;
	}

	void TestStringMatching()
	{
		StringMatching sm;
		/*char s[9]={'a','c','a','a','b','c','a','a','b'};
		char t[3]={'a','a','b'};
		sm.NaiveStringMatcher(s,9,t,3);*/
		//int t[19]={2,3,5,9,0,2,3,1,4,1,5,2,6,7,2,1,4,1,5};
		//int p[5]={2,1,4,1,5};
		//sm.RabinKarpMatcher(t,19,p,5,26,29);
		char t[18]={'a','b','c','a','b','c','a','c','b','a','c','a','b','a','b','a','c','a'};
		char p[7]= {'a','b','a','b','a','c','a'};
		char c[3]={'a','b','c'};
		sm.FiniteAutomatonMatcher(t,18,p,7,c,3);
		sm.KmpMatcher(t,18,p,7);
	}

	void TestGeometry()
	{
		
		Geometry g;
		Point p1;
		p1.X=18;
		p1.Y=90;
		Point p2;
		p2.X=41;
		p2.Y=40;
		if(p1.X<p2.X)
		{
			p1.Location=Point::Left;
			p2.Location=Point::Right;
		}
		else
		{
			p1.Location=Point::Right;
			p2.Location=Point::Left;
		}
		Point p3;
		p3.X=4;
		p3.Y=79;
		Point p4;
		p4.X=30;
		p4.Y=73;
		if(p3.X<p4.X)
		{
			p3.Location=Point::Left;
			p4.Location=Point::Right;
		}
		else
		{
			p3.Location=Point::Right;
			p4.Location=Point::Left;
		}
		Point p5;
		p5.X=97;
		p5.Y=33;
		Point p6;
		p6.X=10;
		p6.Y=99;
		if(p5.X<p6.X)
		{
			p5.Location=Point::Left;
			p6.Location=Point::Right;
		}
		else
		{
			p5.Location=Point::Right;
			p6.Location=Point::Left;
		}
		Point p7;
		p7.X=30;
		p7.Y=45;
		Point p8;
		p8.X=77;
		p8.Y=76;
		if(p7.X<p8.X)
		{
			p7.Location=Point::Left;
			p8.Location=Point::Right;
		}
		else
		{
			p7.Location=Point::Right;
			p8.Location=Point::Left;
		}
		Point p9;
		p9.X=70;
		p9.Y=45;
		Point p10;
		p10.X=11;
		p10.Y=42;
		if(p9.X<p10.X)
		{
			p9.Location=Point::Left;
			p10.Location=Point::Right;
		}
		else
		{
			p9.Location=Point::Right;
			p10.Location=Point::Left;
		}
		Line* l1=new Line;
		Line* l2=new Line;
		Line* l3=new Line;
		Line* l4=new Line;
		Line* l5=new Line;
		l1->Text="a";
		l2->Text="b";
		l3->Text="c";
		l4->Text="d";
	    l5->Text="e";
		p1.ParentLine=l1;
		p2.ParentLine=l1;
		l1->P1=p1;
		l1->P2=p2;
		p3.ParentLine=l2;
		p4.ParentLine=l2;
		l2->P1=p3;
		l2->P2=p4;
		p5.ParentLine=l3;
		p6.ParentLine=l3;
		l3->P1=p5;
		l3->P2=p6;
		p7.ParentLine=l4;
		p8.ParentLine=l4;
		l4->P1=p7;
		l4->P2=p8;
		p9.ParentLine=l5;
		p10.ParentLine=l5;
		l5->P1=p9;
		l5->P2=p10;

		Line* l[5]={l1,l2,l3,l4,l5};
		bool result=g.AnySegmentsIntersect(l,5);
		cout<<result<<endl;
	}
	void TestConvexHull()
	{
		Point* points[11];
		Point* p0=new Point;
		p0->X=0;
		p0->Y=0;

		Point* p1=new Point;
		p1->X=1;
		p1->Y=5;

		Point* p2=new Point;
		p2->X=1;
		p2->Y=2;

		Point* p3=new Point;
		p3->X=1;
		p3->Y=8;

		Point* p4=new Point;
		p4->X=3;
		p4->Y=6;

		Point* p5=new Point;
		p5->X=4;
		p5->Y=7;

		Point* p6=new Point;
		p6->X=8;
		p6->Y=4;
		Point* p7=new Point;
		p7->X=6;
		p7->Y=9;
		Point* p8=new Point;
		p8->X=6;
		p8->Y=5;
		Point* p9=new Point;
		p9->X=8;
		p9->Y=4;
		Point* p10=new Point;
		p10->X=4;
		p10->Y=1;
		points[0]=p1;
		points[1]=p2;
		points[2]=p7;
		points[3]=p0;
		points[4]=p4;
		points[5]=p5;
		points[6]=p3;
		points[7]=p6;
		points[8]=p8;
		points[9]=p9;
		points[10]=p10;

		/*for(int i=0;i<10;++i)
		{
			points[i]=new Point;
			points[i]->X=rand()%10;
			points[i]->Y=rand()%10;
		}
		points[10]=new Point;
		points[10]->X=0;
		points[10]->Y=0;*/
		
		Geometry g;
		g.GrahamScan(points,11);
	}
};
