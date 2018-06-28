#ifndef pos_H
#define pos_H
#include<iostream>
#include<math.h> 
using namespace std;
class pos
{
	public:
		int ix,iy;						//ix,iy,,x,y坐标,
		int range;
		pos(int x=0,int y=0,int r=0):ix(x),iy(y),range(r){}	//初始化位置和范围 
		double operator -(pos &a);		//位置差 
		void operator =(const pos &a);		//赋值 
		
		pos(pos &a):ix(a.ix),iy(a.iy),range(a.range){}	//初始化 
		bool operator ==(const pos &a);		//比较是否相等 
};

double pos::operator -(pos &a) 
{
	int x1,y1,x2,y2,r=a.range,i,j;
	double min(10000);
	for(x1=ix-range;x1<=ix+range;x1++)
	{
		for(y1=iy-range;y1<=iy+range;y1++)
		{
			if(x1<0||y1<0)continue;
			for(x2=a.ix-r;x2<=a.ix+r;x2++)
			{
				for(y2=a.iy-r;y2<=a.iy+r;y2++)
				{
					if(x2<0||y2<0)continue;
					i=(x1-x2)*(x1-x2),j=(y1-y2)*(y1-y2);
					if(sqrt(i+j)<min)min=sqrt(i+j);
				}
			}
		}	
	}
	return min;	//返回勾股定理 两点差 
}

void pos::operator =(const pos &a)
{
	ix=a.ix;iy=a.iy;range=a.range;
}

bool pos::operator ==(const pos &a)		//比较是否相等 
{
	int x1,y1,x2,y2,r=a.range,i,j;
	for(x1=ix-range;x1<=ix+range;x1++)
	{
		for(y1=iy-range;y1<=iy+range;y1++)
		{
			if(x1<0||y1<0)continue;
			for(x2=a.ix-r;x2<=a.ix+r;x2++)
			{
				for(y2=a.iy-r;y2<=a.iy+r;y2++)
				{
					if(x2<0||y2<0)continue;
					if(x1==x2&&y1==y2)return true;
				}
			}
		}	
	}
	return false;
}

#endif
