#ifndef Tower_H
#define Tower_H
#include"geth.h"
#include<iostream>
#include<time.h>
#include"pos.h"
using namespace std;
class tower:public kar
{
		bool destroyed;						//沦陷与否 
		bool main;
	public:
		double nowblood,Maxblood,attack;	//Maxblood最大血量,nowblood当前血量,attack攻击能力 
		pos p;
		int hurtRNG;						//阵营,hurtRNG攻击范围，range建筑占地范围
		tower(int blood,int at,int hr,int x,int y,int r,bool m);		
		void scanhit(kar **B);				//扫描敌人 
		double attacked(double value);		//被打击 
		int ifdestr();						//通过血量判断爆没爆	
		void runtower();					//塔总运行
		double Get_blood(){return nowblood;} 
		double Get_Maxblood(){return Maxblood;} 
};

tower::tower(int bld,int at,int hr,int x,int y,int r,bool m):Maxblood(bld),nowblood(bld),hurtRNG(hr),attack(at),main(m),destroyed(false)
{
	nowpos=pos(x,y,r);
	prepos=-110;
	bg=clock();
	buff=1;
	grade=1;
	if(x<25)camp=1;
	else camp=2;
}

void tower::scanhit(kar **B)			//扫描之后打击//优先 扫描小兵, 再扫描英雄,直接每秒造成一定伤害 
{
	if(main)return ;
	ed=clock();
	if(ed-bg<2500)return ;
	bg=ed;
	int i(0);
	for(i=10;i<30;i++)
	{
		if(B[i]==NULL)continue;
		if(B[i]->camp!=camp&&B[i]->nowpos-nowpos<=hurtRNG)
		{
			B[i]->attacked(attack*buff);
			prepos=B[i]->nowpos;
			return ;
		}
	}
	for(i=0;i<2;i++)
	{
		if(B[i]==NULL)continue;
		if(B[i]->camp!=camp&&B[i]->nowpos-nowpos<=hurtRNG)
		{
			B[i]->attacked(attack*buff);
			prepos=B[i]->nowpos;
			return ;
		}
	}
	prepos=(-110);
}

int tower::ifdestr()
{
	if(nowblood<=0)
	{
		destroyed=true;
		if(nowpos.ix>=0)nowpos.ix-=100;
	}
	if(!destroyed)return 0; 
	if(destroyed&&main)return -1;
	else return 1;
}

double tower::attacked(double value)
{

	nowblood-=value/buff;					//血量减少 
	if(nowblood<=0)							//刚好爆炸 
	{
		ifdestr();
		return grade*20+2*attack*buff+Maxblood/5;//返回更多的经验值 
	}
	return grade*20;						//返回经验值 
}

#endif
