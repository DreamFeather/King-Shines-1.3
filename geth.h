#ifndef kar_H
#define kar_H
#include<iostream>
#include"pos.h"
#include"method.cpp"
#include<time.h>
#include<stdlib.h>
class bullet;
using namespace std;
class kar
{
	public:
		string name;
		int grade,speed,EXP,dir,attack;				//dir 1,x正 ,-1,x负 , -2y负,2y正
		int kills;									//击杀数 
		pos prepos,nowpos;							//初始位置和当前位置
		int camp;									//隶属阵营
		int time,last;
		clock_t bg,ed,live,die,move1,move2;
		double blood,buff,Maxblood,Basicblood;		//当前血量,加成,最大血量,基础血量
		bullet *b[6];
		kar(string &n,double Bblood,int atta,int spe,int px,int py):name(n),Basicblood(Bblood),attack(atta),speed(spe),prepos(px,py)
		{
			live=clock();
			bg=clock();
			move1=clock();
			kills=0; 
			buff=1;
			nowpos=prepos;				//初始化当前位置 
			EXP=0;						//初始化经验为0 
			grade=1;					//初始化等级为1 
			blood=Maxblood=Basicblood;	//初始化血量 
			if(prepos.ix>25)			//初始化阵营与开场方向 
			{
				dir=-1;
				camp=2;
			}
			else
			{
				dir=1;
				camp=1;
			}
			time=0;						//当前记录时间 
			last=-11;					//上次复活时间 
			int i(0);
			for(; i<6; i++)b[i]=NULL;	//子弹位置初始化 
		}
		kar()						//无参初始化 
		{
			live=clock();
			bg=clock();
		}
		virtual double attacked(double value);		//受击,并且返回经验值给攻击方 
		void move(char);				//移动 
		void operate(char);				//操作 
		void move(int);
		void upgrade();					//升级 
		void run();						//每次总运行 
		void ifkilled();				//被杀 
		void recover();					//回血 
		void relive();					//复活 
		void shoot();					//射击 
		void runbullet(kar **B);		//处理子弹 
		int scanbullet(int locx,int locy);		//子弹计数 
		void display(char *p);
		void loadguard(kar **x);
		void Gmove(kar **x);
		bool gen(kar **x,const int p);
		void runG(kar **x);
		virtual int ifdestr(){}
		virtual void scanhit(kar **B){}
		virtual double Get_blood(){return blood;}
		virtual double Get_Maxblood(){return Maxblood;}
};

void kar::recover()
{
	if(blood>0)
	{
		blood+=(Maxblood/800)*buff;
	}
	if(camp==1)
	{
		if(nowpos==pos(0,2,2)&&blood>0)
		{
			double add=Maxblood/10;
			add*=buff;
			if(add>700)add=700;
			blood+=add; 
		}
	}
	else
	{
		if(nowpos==pos(49,2,2)&&blood>0)
		{
			double add=Maxblood/10;
			add*=buff;
			if(add>700)add=700;
			blood+=add;
		}
	}
	if(blood>Maxblood)blood=Maxblood;
}

void kar::runG(kar **x)
{
	loadguard(x);
	Gmove(x);
}

bool kar::gen(kar **x,const int p)
{
	int i;
	string a="guard";
	for(i=p;i<p+3;i++)
	{
		if(x[i]!=NULL)return false;
	}
	for(i=p;i<p+3;i++)
	{
		if(p>=20)
		x[i]=new kar(a,820,100,1,42,i-p+1);
		else
		x[i]=new kar(a,820,100,1,7,i-p+1);
	}
	return true;
}

void kar::loadguard(kar **x)			//小兵 
{
	die=clock();
	if(die-live<15000)return;
	live=die;
	if(!gen(x,10))
	{
		if(!gen(x,13))
			gen(x,16);
	}
	if(!gen(x,20))
	{
		if(!gen(x,23))
			gen(x,26);
	}
}

void kar::Gmove(kar **x)
{
	ed=clock();
	if(ed-bg<1000)return ;
	bg=ed;
	pos *itsp;
	int p=0,flag=1,i;
	for(i=10;i<29;i++)
	{
		if(x[i]==NULL)continue;
		itsp=new pos(x[i]->nowpos);
		itsp->ix+=x[i]->dir;
		for(p=0;p<29;p++)
		{
			if(x[p]==NULL)continue;
			if(x[p]->camp!=x[i]->camp&&x[p]->nowpos==*itsp)
			{
				x[p]->attacked(x[i]->attack);
				break;
			}
		}
		delete itsp;
		if(x[i]->blood<=0)
		{
			delete x[i];x[i]=NULL;continue;
		}
		if(p==29)x[i]->move(x[i]->dir);
	}
}

void kar::move(int d)
{
	switch(d){
		case 1:nowpos.ix+=speed;break;
		case -1:nowpos.ix-=speed;break;
	}
} 

void kar::display(char *p)
{
	Set_mouse(2*nowpos.ix,2+nowpos.iy+1);
	switch(dir)
	{
		case 1:cout<<"→";break;
		case -1:cout<<"←";break;
		case -2:cout<<"↑";break;
		case 2:cout<<"↓";break;
	}
}

double kar::attacked(double value)
{
	if(blood==-Maxblood)return 0;		//已死亡状态,不受伤害 
	blood-=value/buff;					//血量减少 
	if(blood<=0)							//刚好死亡 
	{
		ifkilled();
		return grade*50+attack*buff+Maxblood/10;//返回更多的经验值 
	}
	return grade*10*buff;						//返回经验值 
}

void kar::upgrade()						//检查是否升级 
{
	grade=EXP/1000+1;
	if(grade>15)grade=15;
	Maxblood=Basicblood+(grade-1)*10+EXP/100;
	buff=(grade-1+Maxblood/800+EXP/1000)/100.0+1;
	if(buff>3)buff=3;
}

void kar::ifkilled()					
{
	if(blood==-Maxblood)return ;				//已经死亡,跳过计时 
	die=clock();						//计时 
	if(blood<=0)							//处理死亡位置 
	{
		nowpos.ix=-prepos.ix-1,blood=-Maxblood;	//使之不在地图上显示 
	}
}

void kar::relive()						//复活 
{
	live=clock();
	if(live-die>10000+grade*buff)					//复活时间已到 
	{
		nowpos=prepos;					//位置为初始位置 
		blood=Maxblood;					//满血复活 
	}
}

void kar::run()							//英雄总操作 
{
	++time;								//时间+1 
	upgrade();							//级别处理 
	ifkilled();							//死亡是否可复活 
	relive();							//复活 
	if(blood>0)
	{
		ed=clock();
		if(ed-bg>1000)
		{
			bg=ed;
			recover();
			shoot();				//没死就开枪 
		}
	}
	//display();
}

void kar::move(char c)
{
	move2=clock();
	//if(move2-move1<(1000/speed))return ;		//移动冷却时间 
	switch(c)
	{
		case 'a':dir=-1;nowpos.ix+=dir;if(nowpos.ix<0)nowpos.ix=0;break;
		case 'd':dir=1;nowpos.ix+=dir;if(nowpos.ix>49)nowpos.ix=49;break;
		case 'w':dir=-2;nowpos.iy+=dir/2;if(nowpos.iy<0)nowpos.iy=0;break;
		case 's':dir=2;nowpos.iy+=dir/2;if(nowpos.iy>4)nowpos.iy=4;break;
			
		case 0x4B:dir=-1;nowpos.ix+=dir;if(nowpos.ix<0)nowpos.ix=0;break;
		case 0x4D:dir=1;nowpos.ix+=dir;if(nowpos.ix>49)nowpos.ix=49;break;
		case 0x48:dir=-2;nowpos.iy+=dir/2;if(nowpos.iy<0)nowpos.iy=0;break;
		case 0x50:dir=2;nowpos.iy+=dir/2;if(nowpos.iy>4)nowpos.iy=4;break;
			
		case '1':dir=-1;nowpos.ix+=dir;if(nowpos.ix<0)nowpos.ix=0;break;
		case '3':dir=1;nowpos.ix+=dir;if(nowpos.ix>49)nowpos.ix=49;break;
		case '5':dir=-2;nowpos.iy+=dir/2;if(nowpos.iy<0)nowpos.iy=0;break;
		case '2':dir=2;nowpos.iy+=dir/2;if(nowpos.iy>4)nowpos.iy=4;break;
			
		case 'A':dir=-1;nowpos.ix+=dir;if(nowpos.ix<0)nowpos.ix=0;break;
		case 'D':dir=1;nowpos.ix+=dir;if(nowpos.ix>49)nowpos.ix=49;break;
		case 'W':dir=-2;nowpos.iy+=dir/2;if(nowpos.iy<0)nowpos.iy=0;break;
		case 'S':dir=2;nowpos.iy+=dir/2;if(nowpos.iy>4)nowpos.iy=4;break;
			
		default:return ;
	}
	move1=move2;
} 

void kar::operate(char c)
{
	if(blood<=0)return ;				//死亡不可移动 
	switch (c)
	{
		case 'q':dir=-1;break;
		case 'e':dir=1;break;
		
		case 'Q':dir=-1;break;
		case 'E':dir=1;break;
		
		case '4':dir=-1;break;
		case '6':dir=1;break;
		
		default:move(c);break;
	}
}

class bullet							//子弹类 
{
	public:							
		int dir,speed,range,camp,len;			//方向,速度,范围,阵营,最大飞行距离 
		pos prepos,nowpos;						//初始位置,现在位置 
		bool boom;								//爆炸与否 
		double attack;							//攻击力 
		kar *k;									//发射方(英雄) 
		bullet(){}
		bullet(kar *A):k(A),boom(false),len(3),dir(A->dir),speed(1),range(0),attack(A->attack*A->buff),camp(A->camp)
		{
			prepos=A->nowpos;
			switch (A->dir)
			{
				case -1:--prepos.ix;break;
				case -2:--prepos.iy;break;
				case  1:++prepos.ix;break;
				case  2:++prepos.iy;break;
			}
			nowpos=prepos;
		}
		double  hit(kar *p);				//打击英雄 
		void run(kar **B);				//扫描场上英雄
		void display() ;
};

void bullet::display()
{
	Set_mouse(2*nowpos.ix,nowpos.iy+2+1);
	switch(dir)
	{
		case 1:cout<<"≯";break;
		case -1:cout<<"≮";break;
		case -2:cout<<"Λ";break;
		case 2:cout<<"v";break;
	}
}

void bullet::run(kar **B)
{
	int i(0);
	for(; i<30; i++)				//在子弹移动前看是否有英雄撞上 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	if(boom)return ;				//已经爆炸 不再往下走 
	if(dir==1||dir==-1)				//飞行一次 
	{
		nowpos.ix+=dir*speed;
	}
	else
	{
		nowpos.iy+=dir*speed/2;
	}
	if(nowpos-prepos>=len)boom=true;
	if(nowpos.ix>52||nowpos.ix<-3)boom=true;			//若超出地图范围 
	if(nowpos.iy<0||nowpos.iy>4)boom=true;				//默认爆炸,等待删除 
	if(boom)return ;
	for(i=0; i<30; i++)								// 走完之后再判断是否击中 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	return ;
}

double bullet::hit(kar *p)								//遇到英雄 
{		
	if(p->camp==camp||p->Get_blood()==0)return 0;			//同阵营,已死亡的不算 
	if(!boom)										//没爆炸,造成击中伤害 
	{
		if(p->nowpos==nowpos)
		{
			boom=true;								//已爆炸 
			double  hurt=p->attacked(attack);
			if(p->blood==0)
			k->kills++;
			return hurt	;			//返回造成伤害获得的经验值 
		}
	}
	else if(p->nowpos-nowpos<=range)				//已爆炸造成范围伤害 
	{
		double hurt=p->attacked(attack);
		if(p->blood==0)
		k->kills++;
		return hurt;			//返回造成伤害获得的经验值 
	}
	return 0;
}

void kar::shoot()								//英雄开枪 
{
	int i(0);
	for(; i<6; i++)
	{
		if(b[i]==NULL)						//找到空位 
		{
			b[i]=new bullet(this);			//发射一颗 
			return ;
		}
	}
}

int kar::scanbullet(int locx,int locy=-1)			//计算某位置的子弹 
{
	int i(0);
	pos p(locx,locy);
	for(; i<6; i++)
	{
		if(locy==-1)
		{
			if(b[i]&&b[i]->nowpos.ix==locx)return 1;
		}
		else
		if(b[i]&&b[i]->nowpos==p)
		{
			return b[i]->dir;
		}
	}
	return 0;
}

void kar::runbullet(kar **B)				//子弹总运行 
{
	int i(0);
	for(; i<6; i++)
	{
		if(b[i]!=NULL)
		{
			b[i]->run(B);
			if(b[i]->boom||b[i]->nowpos-b[i]->prepos>=b[i]->len)
			{
				delete b[i];				//爆炸了或者超出飞行范围的子弹需要销毁 
				b[i]=NULL;
			}
		}
	}
	
}
#endif
