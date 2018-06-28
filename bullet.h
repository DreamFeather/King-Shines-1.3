#ifndef BULLET_H
#define BULLET_H
#include<iostream>
#include"kar.h"
using namespace std;
class bullet
{
	public:
		int dir,speed,pos;
		double attack;
		kar *k;
		int hit(kar	*p);
};

int bullet::hit(kar	*p)
{
	k=p;
	dir=p->dir;
	speed=1;
	attack=p->attack;
	pos=p->pos;
}

#endif
