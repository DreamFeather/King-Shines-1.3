#ifndef kar_H
#define kar_H
#include<iostream>
#include"bullet.h"
using namespace std;
class kar
{
	public:
		string name;
		int grade,speed,EXP,dir,pos,attack;
		int time,last;
		double blood,buff,Maxblood,Basicblood;
		bullet *p[30];
		int attacted(int value);
		void move(char);
		void upgrade();
		void run();
		void ifkilled();
		void recover();
		void relive();
};

int kar::attacted(int value)
{
	if(blood<0)return 0;
	blood-=value;
	if(blood<0)return grade+attack*buff;
	return grade;
}

void kar::upgrade()
{
	grade=EXP/1000+1;if(grade>15)grade=15;
	buff=(grade+Maxblood/500+EXP/2000)/100.0+1;
	Maxblood=Basicblood+grade*10+EXP/100;
}

void kar::ifkilled()
{
	if(blood==-Maxblood)return ;
	last=time;
	if(blood<=0)
	{
		pos=-1,blood=-Maxblood;
	}
}

void kar::relive()
{
	if(time-last>10)
	{
		pos=0;blood=Maxblood;
	}
}

void kar::run()
{
	++time;
	upgrade();
	ifkilled();
	relive();
}

void kar::move(char c)
{
	if(blood>0)
	switch (c)
	{
		case 'a':dir=-1;pos+=speed*dir;if(pos<0)pos=0;break;
		case 'd':dir=1;pos+=speed*dir;if(pos>49)pos=49;break;
		case 'q':dir=-1;break;
		case 'e':dir=1;break;
	}
}
#endif
