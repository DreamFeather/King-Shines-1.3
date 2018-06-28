#ifndef Tower_H
#define Tower_H
#include"geth.h"
#include<iostream>
#include<time.h>
#include"pos.h"
using namespace std;
class tower:public kar
{
		bool destroyed;						//������� 
		bool main;
	public:
		double nowblood,Maxblood,attack;	//Maxblood���Ѫ��,nowblood��ǰѪ��,attack�������� 
		pos p;
		int hurtRNG;						//��Ӫ,hurtRNG������Χ��range����ռ�ط�Χ
		tower(int blood,int at,int hr,int x,int y,int r,bool m);		
		void scanhit(kar **B);				//ɨ����� 
		double attacked(double value);		//����� 
		int ifdestr();						//ͨ��Ѫ���жϱ�û��	
		void runtower();					//��������
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

void tower::scanhit(kar **B)			//ɨ��֮����//���� ɨ��С��, ��ɨ��Ӣ��,ֱ��ÿ�����һ���˺� 
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

	nowblood-=value/buff;					//Ѫ������ 
	if(nowblood<=0)							//�պñ�ը 
	{
		ifdestr();
		return grade*20+2*attack*buff+Maxblood/5;//���ظ���ľ���ֵ 
	}
	return grade*20;						//���ؾ���ֵ 
}

#endif
