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
		int grade,speed,EXP,dir,attack;				//dir 1,x�� ,-1,x�� , -2y��,2y��
		int kills;									//��ɱ�� 
		pos prepos,nowpos;							//��ʼλ�ú͵�ǰλ��
		int camp;									//������Ӫ
		int time,last;
		clock_t bg,ed,live,die,move1,move2;
		double blood,buff,Maxblood,Basicblood;		//��ǰѪ��,�ӳ�,���Ѫ��,����Ѫ��
		bullet *b[6];
		kar(string &n,double Bblood,int atta,int spe,int px,int py):name(n),Basicblood(Bblood),attack(atta),speed(spe),prepos(px,py)
		{
			live=clock();
			bg=clock();
			move1=clock();
			kills=0; 
			buff=1;
			nowpos=prepos;				//��ʼ����ǰλ�� 
			EXP=0;						//��ʼ������Ϊ0 
			grade=1;					//��ʼ���ȼ�Ϊ1 
			blood=Maxblood=Basicblood;	//��ʼ��Ѫ�� 
			if(prepos.ix>25)			//��ʼ����Ӫ�뿪������ 
			{
				dir=-1;
				camp=2;
			}
			else
			{
				dir=1;
				camp=1;
			}
			time=0;						//��ǰ��¼ʱ�� 
			last=-11;					//�ϴθ���ʱ�� 
			int i(0);
			for(; i<6; i++)b[i]=NULL;	//�ӵ�λ�ó�ʼ�� 
		}
		kar()						//�޲γ�ʼ�� 
		{
			live=clock();
			bg=clock();
		}
		virtual double attacked(double value);		//�ܻ�,���ҷ��ؾ���ֵ�������� 
		void move(char);				//�ƶ� 
		void operate(char);				//���� 
		void move(int);
		void upgrade();					//���� 
		void run();						//ÿ�������� 
		void ifkilled();				//��ɱ 
		void recover();					//��Ѫ 
		void relive();					//���� 
		void shoot();					//��� 
		void runbullet(kar **B);		//�����ӵ� 
		int scanbullet(int locx,int locy);		//�ӵ����� 
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

void kar::loadguard(kar **x)			//С�� 
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
		case 1:cout<<"��";break;
		case -1:cout<<"��";break;
		case -2:cout<<"��";break;
		case 2:cout<<"��";break;
	}
}

double kar::attacked(double value)
{
	if(blood==-Maxblood)return 0;		//������״̬,�����˺� 
	blood-=value/buff;					//Ѫ������ 
	if(blood<=0)							//�պ����� 
	{
		ifkilled();
		return grade*50+attack*buff+Maxblood/10;//���ظ���ľ���ֵ 
	}
	return grade*10*buff;						//���ؾ���ֵ 
}

void kar::upgrade()						//����Ƿ����� 
{
	grade=EXP/1000+1;
	if(grade>15)grade=15;
	Maxblood=Basicblood+(grade-1)*10+EXP/100;
	buff=(grade-1+Maxblood/800+EXP/1000)/100.0+1;
	if(buff>3)buff=3;
}

void kar::ifkilled()					
{
	if(blood==-Maxblood)return ;				//�Ѿ�����,������ʱ 
	die=clock();						//��ʱ 
	if(blood<=0)							//��������λ�� 
	{
		nowpos.ix=-prepos.ix-1,blood=-Maxblood;	//ʹ֮���ڵ�ͼ����ʾ 
	}
}

void kar::relive()						//���� 
{
	live=clock();
	if(live-die>10000+grade*buff)					//����ʱ���ѵ� 
	{
		nowpos=prepos;					//λ��Ϊ��ʼλ�� 
		blood=Maxblood;					//��Ѫ���� 
	}
}

void kar::run()							//Ӣ���ܲ��� 
{
	++time;								//ʱ��+1 
	upgrade();							//������ 
	ifkilled();							//�����Ƿ�ɸ��� 
	relive();							//���� 
	if(blood>0)
	{
		ed=clock();
		if(ed-bg>1000)
		{
			bg=ed;
			recover();
			shoot();				//û���Ϳ�ǹ 
		}
	}
	//display();
}

void kar::move(char c)
{
	move2=clock();
	//if(move2-move1<(1000/speed))return ;		//�ƶ���ȴʱ�� 
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
	if(blood<=0)return ;				//���������ƶ� 
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

class bullet							//�ӵ��� 
{
	public:							
		int dir,speed,range,camp,len;			//����,�ٶ�,��Χ,��Ӫ,�����о��� 
		pos prepos,nowpos;						//��ʼλ��,����λ�� 
		bool boom;								//��ը��� 
		double attack;							//������ 
		kar *k;									//���䷽(Ӣ��) 
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
		double  hit(kar *p);				//���Ӣ�� 
		void run(kar **B);				//ɨ�賡��Ӣ��
		void display() ;
};

void bullet::display()
{
	Set_mouse(2*nowpos.ix,nowpos.iy+2+1);
	switch(dir)
	{
		case 1:cout<<"��";break;
		case -1:cout<<"��";break;
		case -2:cout<<"��";break;
		case 2:cout<<"v";break;
	}
}

void bullet::run(kar **B)
{
	int i(0);
	for(; i<30; i++)				//���ӵ��ƶ�ǰ���Ƿ���Ӣ��ײ�� 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	if(boom)return ;				//�Ѿ���ը ���������� 
	if(dir==1||dir==-1)				//����һ�� 
	{
		nowpos.ix+=dir*speed;
	}
	else
	{
		nowpos.iy+=dir*speed/2;
	}
	if(nowpos-prepos>=len)boom=true;
	if(nowpos.ix>52||nowpos.ix<-3)boom=true;			//��������ͼ��Χ 
	if(nowpos.iy<0||nowpos.iy>4)boom=true;				//Ĭ�ϱ�ը,�ȴ�ɾ�� 
	if(boom)return ;
	for(i=0; i<30; i++)								// ����֮�����ж��Ƿ���� 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	return ;
}

double bullet::hit(kar *p)								//����Ӣ�� 
{		
	if(p->camp==camp||p->Get_blood()==0)return 0;			//ͬ��Ӫ,�������Ĳ��� 
	if(!boom)										//û��ը,��ɻ����˺� 
	{
		if(p->nowpos==nowpos)
		{
			boom=true;								//�ѱ�ը 
			double  hurt=p->attacked(attack);
			if(p->blood==0)
			k->kills++;
			return hurt	;			//��������˺���õľ���ֵ 
		}
	}
	else if(p->nowpos-nowpos<=range)				//�ѱ�ը��ɷ�Χ�˺� 
	{
		double hurt=p->attacked(attack);
		if(p->blood==0)
		k->kills++;
		return hurt;			//��������˺���õľ���ֵ 
	}
	return 0;
}

void kar::shoot()								//Ӣ�ۿ�ǹ 
{
	int i(0);
	for(; i<6; i++)
	{
		if(b[i]==NULL)						//�ҵ���λ 
		{
			b[i]=new bullet(this);			//����һ�� 
			return ;
		}
	}
}

int kar::scanbullet(int locx,int locy=-1)			//����ĳλ�õ��ӵ� 
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

void kar::runbullet(kar **B)				//�ӵ������� 
{
	int i(0);
	for(; i<6; i++)
	{
		if(b[i]!=NULL)
		{
			b[i]->run(B);
			if(b[i]->boom||b[i]->nowpos-b[i]->prepos>=b[i]->len)
			{
				delete b[i];				//��ը�˻��߳������з�Χ���ӵ���Ҫ���� 
				b[i]=NULL;
			}
		}
	}
	
}
#endif
