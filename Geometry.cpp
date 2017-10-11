#include "StdAfx.h"
#include "Geometry.h"

int Compare(Point* p1,Point* p2)
{
	if(!p1->flag||!p2->flag)
	{
		return 0;
	}
	int x= (p1->X-Point::BasePoint->X)*(p2->Y-Point::BasePoint->Y)-(p2->X-Point::BasePoint->X)*(p1->Y-Point::BasePoint->Y);
	if(x==0)
	{
		p1->flag=p1->Y>p2->Y;
		p2->flag=!p1->flag;
	}
	return -x;
}

Geometry::Geometry(void)
{
}


Geometry::~Geometry(void)
{
}

int Geometry::CrossProducts(Point p0,Point p1,Point p2)
{
	return (p1.X-p0.X)*(p2.Y-p0.Y)-(p2.X-p0.X)*(p1.Y-p0.Y);
}
bool Geometry::OnSegment(Line line,Point p)
{
	return min(line.P1.X,line.P2.X)<=p.X&&p.X<=max(line.P1.X,line.P2.X)&&min(line.P1.Y,line.P2.Y)<=p.Y&&p.Y<=max(line.P1.Y,line.P2.Y);
}
bool Geometry::SegmentsIntersect(Line l1,Line l2)
{
	//如果两条直线相交，若连接p3,p1和p3,p2。此时p3,p1,p2组成一个三角形，而直线l2穿过这个三角形，
	//所以对于l2则两条新直线必然一条是顺时针一条是逆时针
	//相反l2则不穿过三角形，此时两条直线必然都是顺时针或者逆时针
	int d1=CrossProducts(l2.P1,l2.P2,l1.P1);
	int d2=CrossProducts(l2.P1,l2.P2,l1.P2);
	
	int d3=CrossProducts(l1.P1,l1.P2,l2.P1);
	int d4=CrossProducts(l1.P1,l1.P2,l2.P2);
	if(d1*d2<0&&d3*d4<0)
	{
		return true;
	}
	//如果有共线情况则判断是否有一条直线的点在另一条直线上的边界情况
	if(d1==0&&OnSegment(l2,l1.P1))
	{
		return true;
	}
	if(d2==0&&OnSegment(l2,l1.P2))
	{
		return true;
	}
	if(d3==0&&OnSegment(l1,l2.P1))
	{
		return true;
	}
	if(d4==0&&OnSegment(l1,l2.P2))
	{
		return true;
	}
	return false;
}
bool Geometry::AnySegmentsIntersect(Line* s[],int length)
{
	//for(int i=0;i<length;++i)
	//{
	//	cout<<"("<<s[i]->P1.X<<","<<s[i]->P1.Y<<")-("<<s[i]->P2.X<<","<<s[i]->P2.Y<<")"<<endl;
	//}

	//根据点的x坐标，左右位置和y坐标的顺序排序
	Point* points=new Point[length*2];
	for(int i=0;i<length;++i)
	{
		points[2*i]=s[i]->P1;
		points[2*i+1]=s[i]->P2;
	}
	InsertionSort<Point> is;
	is.Sort(points,length*2);

	RedBlackTree<Line> lines;
	for(int i=0;i<length*2;++i)
	{
		/*cout<<points[i].X<<" ";
		RedBlackTreeNode<Line>* temp=lines.Minimum(lines.Root());
		while(!lines.IsNil(temp))
		{
			cout<<temp->Key.Text<<" ";
			temp=lines.Successor(temp);
		}
		cout<<endl;*/

		//更新当前扫除线的x坐标
		Line::SwapX=points[i].X;
		//如果是左点则添加到完全前序关系中，判断上下两条直线是否和当前直线相交
		if(points[i].Location==Point::Left)
		{
			RedBlackTreeNode<Line>* newNode=lines.Insert(*(Line*)points[i].ParentLine);
			RedBlackTreeNode<Line>* above=lines.Predecessor(newNode);
			RedBlackTreeNode<Line>* below=lines.Successor(newNode);
			if(!lines.IsNil(above)&&SegmentsIntersect(above->Key,newNode->Key)||
				!lines.IsNil(below)&&SegmentsIntersect(below->Key,newNode->Key))
			{
				return true;
			}
		}
		//如果是右点则从完全前序关系中删除并判断线段旁边两条直线是否相交
		else
		{
			RedBlackTreeNode<Line>* node=lines.Search(*(Line*)points[i].ParentLine);
			RedBlackTreeNode<Line>* above=lines.Predecessor(node);
			RedBlackTreeNode<Line>* below=lines.Successor(node);
			if(!lines.IsNil(above)&&!lines.IsNil(below)&&SegmentsIntersect(above->Key,below->Key))
			{
				return true;
			}
			lines.Delete(node);
		}
	}	
	return false;
}
void Geometry::GrahamScan(Point* points[],int length)
{
	Point::BasePoint=new Point;
	Point::BasePoint->X=0;
	Point::BasePoint->Y=0;
	Point* pp1=new Point;
	pp1->X=0;
	pp1->Y=5;
	Point* pp2=new Point;
	pp2->X=5;
	pp2->Y=0;
	int t=Compare(pp1,pp2);
	if(length<3)
	{
		return;
	}
	int min=0;
	//cout<<points[0].X<<"  "<<points[0].Y<<endl;
	for(int i=1;i<length;++i)
	{
		//cout<<points[i].X<<"  "<<points[i].Y<<endl;
		if (points[i]->Y<points[min]->Y||points[i]->Y==points[min]->Y&&points[i]->X<points[min]->X)
		{
			min=i;
		}
	}
	//cout<<"min"<<points[min].X<<"  "<<points[min].Y<<endl;
	Point::BasePoint=points[min];
	points[min]=points[0];
	points[0]=Point::BasePoint;
	InsertionSort<Point*> is;
	is.Sort(points+1,length-1,Compare);

	for(int i=0;i<length;++i)
	{
		cout<<points[i]->X<<"  "<<points[i]->Y<<"  "<<points[i]->flag<<endl;
	}
	cout<<endl;
	Stack_<Point*> s;
	int index=0;
	int count=0;
	for(;index<length;++index)
	{
		if(count==3)
		{
			break;
		}
		if(points[index]->flag)
		{
			s.Push(points[index]);
			count+=1;
		}
	}

	for(;index<length;++index)
	{
		if(!points[index]->flag)
		{
			continue;
		}
		Point* t=s.Pop();
		Point* n=s.Peek();
		while(CrossProducts(*Point::BasePoint,*n,*t)>=0)
		{
			t=s.Pop();
			n=s.Peek();
		}
		s.Push(t);
		s.Push(points[index]);
	}
	while(!s.Empty())
	{
		Point* p=s.Pop();
		cout<<p->X<<"  "<<p->Y<<"  "<<p->flag<<endl;
	}
}



