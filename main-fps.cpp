#include<iostream>
#include<fstream>
#include"geth.h"
#include"method.cpp"
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include"tower.h"
clock_t bg,ed;
using namespace std;
kar *x[100],**s=&x[0],**l=&x[1];
char warning[]="很抱歉,游戏遇到异常,即将退出!";
char teller[]="文件缺失"; 
char NPC[7][11]={"小乔","孙尚香","廉颇","孙悟空","后羿","刘邦"};
string file[7]={"小乔.txt","孙尚香.txt","廉颇.txt","孙悟空.txt","后羿.txt","刘邦.txt"};
ifstream ope[7];
char screen[2000];
char *now=screen;
void write(const char *p);

void Scrinit()				//窗口初始化 
{
	system("title 王者光耀 ——英狼制作");
	system("mode con cols=140 lines=40");
	system("color fc");
}

struct info			//用来暂存英雄基础信息 
{
	string name;		//名字 
	double blood;		//基础血量 
	double attack;		//基础攻击 
	int speed;			//速度 
}N[7];					//6个人物 

void loadhero(const int &i,const int &j)		//选定角色后初始化 
{
	*s=new kar(N[i].name,N[i].blood,N[i].attack,N[i].speed,0,2);	 
	*l=new kar(N[j].name,N[j].blood,N[j].attack,N[j].speed,49,2);	//构造两个对战人物,后面两个数为初始位置 
	
	tower *p;
	p=new tower(1000000,2000,3,0,2,2,false);x[2]=p;
	p=new tower(6500,100,3,5,2,1,true);x[3]=p;
	p=new tower(4500,630,3,10,2,1,false);x[4]=p;
	p=new tower(4000,630,3,14,2,1,false);x[5]=p;
	
	p=new tower(1000000,2000,3,49,2,2,false);x[6]=p;
	p=new tower(6500,100,3,44,2,1,true);x[7]=p;
	p=new tower(4500,630,3,39,2,1,false);x[8]=p;
	p=new tower(4000,630,3,34,2,1,false);x[9]=p;
	
	x[40]=new kar;
	x[40]->runG(x);
}

void loadinfo()									//从文件中载入英雄信息 
{
	int x;
	for(x=0;x<6;x++)
	{
		system("cls"); 
		ope[x].open(file[x].c_str());
		if(ope[x]==NULL)				//文件打开失败 
		{
			MessageBox(NULL,TEXT(warning),TEXT(teller),MB_OK|MB_ICONWARNING);
			exit(0); 
		}
		ope[x]>>N[x].name>>N[x].blood>>N[x].attack>>N[x].speed;
		cout<<"		数据载入中..."<<x+1<<"/"<<6;
		ope[x].close();
	}
	cout<<endl<<"		载入完成";
}

void write(const char *p)				//将待输出内容写入输出缓冲区 
{
	int i(0);
	while(p[i]!='\0')
	{
		*now++=p[i++];
	}
	*now='\0';
}

void Selecthero()								//对应选择英雄界面 
{
	int x;
	loadinfo();
	now=screen;
	cout<<endl<<endl<<"			Press any key to start!"<<endl; 
	int i(0),j(5);
	char g=0;
	if(g=getch())system("cls");
	while(1)
	{
		g=getch();
		switch(g)
		{
			case 0x4B:j-=1;break;//left
			case 0x48:j-=1;break;//up
			case 0x4D:j+=1;break;//right
			case 0x50:j+=1;break;//down
			//case  224:break;
			case   97:i-=1;break;//a
			case  119:i-=1;break;//w
			case  100:i+=1;break;//d
			case  115:i+=1;break;//s
			case   27:EXIT();break;
			case   13:loadhero(i,j);return ;
		}
		i=(i+6)%6;j=(j+6)%6;
		now=screen;
		for(x=0;x<6;x++)
		{
			if(i==x)write("		◆");
			else write("		 ");
			write("		 ");
			write(NPC[x]);
			if(j==x)write("		◇");
			else write("		 "); 
			write("\n");
		}
		Set_mouse(0,0);
		cout<<"请选择英雄---(Enter确认)"<<endl<<endl;
		printf(screen);
		cout<<endl<<endl<<"		"<<"player1:"<<NPC[i]<<"    		"<<"player2:"<<NPC[j]<<"    "<<endl;
		cout<<endl<<"		"<<"生命"<<"		"<<"攻击"<<"		"<<"移速"<<endl<<endl;
		for(x=0;x<6;x++)
		{
			cout<<N[x].name<<"		"<<N[x].blood<<"		"<<N[x].attack<<"		"<<N[x].speed<<endl<<endl;
		}			//显示英雄参数以供选择参考 
	}
} 

void initial()					//总体初始化 
{
	Scrinit();					// 进程名 
	Hide_mouse();				//隐藏光标 
	Selecthero();				//玩家选择英雄 
	system("cls");
}

void scan()							//扫描地图并绘图 
{
	now=screen;
	register int i(0),j(0);
	int p,q,w;write("\n");
	int r;
	for(i=0;i<100;i++)				//绘制地图上边框 
	{
		if(i>1&&i<98)
		{
			if(i%2==0)write("┌");
			else write("┐");
		}
		if(i==0||i==98)write("╔");
		if(i==1||i==99)write("╗");
	}
	
	write("\n");
	
	for(i=0;i<50;i++)					//突出玩家1英雄位置 
	{
		if((*s)->nowpos.ix==i)write("▼");
		else if((*s)->scanbullet(i))write("●");
		else write("∧");
	}
	write("\n");
	
	
	for(r=0;r<5;r++)					//战斗区域 
	{
		for(i=0;i<50;i++)
		{
			for(w=2;w<10;w++)			//塔攻击警示 
			{
				if(x[w]==NULL)continue;
				if(x[w]->prepos==pos(i,r))
				{
					write("⊕");break;
				}
			}
			if(w!=10)continue;
			for(p=10;p<29;p++)
			{
				w=0;
				if(x[p]==NULL)continue;
				if(x[p]->nowpos==pos(i,r))
				{
					if(x[p]->dir==1)
					write("↗");
					else write("↖");
					w=1;
					break;
				}
			}
			if(w)continue;
			j=(*s)->scanbullet(i,r);
			q=(*l)->scanbullet(i,r);
			if(j)
			{
				if(j==1)
				write("≯");
				else write("≮");
				continue;
			}
			if(q)
			{
				if(q==1)
				write(" ╞");
				else write(" ╡");
				continue;
			}
			if((*s)->nowpos==pos(i,r))
			{
				if((*s)->dir==1)write("→");
				else write("←");
				continue;
			}
			if((*l)->nowpos==pos(i,r))
			{
				if((*l)->dir==1)write("→");
				else write("←");
				continue;
			}
			for(w=2;w<10;w++)
			{
				if(x[w]==NULL)continue;
				if(x[w]->nowpos==pos(i,r))
				{
					write("▓");break;
				}
			}
			if(w!=10)continue;
			write("  ");
		}
		write("\n");
	}
	
	for(i=0;i<50;i++)					//突出玩家2英雄位置 
	{
		if((*l)->nowpos.ix==i)write("▲");
		else if((*l)->scanbullet(i))write("◆");
		else write("∨");
	}
	
	write("\n");
	
	for(i=0;i<100;i++)					//绘制地图下边框 
	{
		if(i>1&&i<98)
		{
			if(i%2==0)write("└");
			else write("┘");
		}
		if(i==0||i==98)write("╚");
		if(i==1||i==99)write("╝");
	}
	write("\n");
}

void disp()								//输出实时对战双方信息 
{
	int blood1= (*s)->blood,blood2=(*l)->blood;
	if(blood1<0)blood1=0;if(blood2<0)blood2=0;
	double boo[16];
	Set_mouse(0,0);				//光标返回首位置 
	printf(screen);
	cout<<"玩家:		"<<(*s)->name<<"				"<<(*l)->name<<endl;
	cout<<"血量:		"<<blood1<<"/"<<(*s)->Maxblood<<"                 "<<blood2<<"/"<<(*l)->Maxblood<<"                      "<<endl;
	cout<<"攻击加成:	"<<(*s)->buff*100<<"%"<<"                   "<<(*l)->buff*100<<"%            "<<endl;
	cout<<"EXP:		"<<(*s)->EXP<<"				"<<(*l)->EXP<<"			"<<endl;
	int count(kar *);
	cout<<"等级:		"<<(*s)->grade<<"				"<<(*l)->grade<<endl;
	cout<<"击杀数:		"<<(*s)->kills<<"				"<<(*l)->kills<<endl;
	int i,j;
	for(i=2;i<10;i++,j+=2)
	{
		if(x[i]==NULL)
		{
			boo[j]=boo[j+1]=0;
		}
		else
		{
			boo[j]=x[i]->Get_blood();boo[j+1]=x[i]->Get_Maxblood();
		}
	}
	cout<<"塔:"<<endl; 
	for(i=0;i<8;i+=2)
	{
		cout<<boo[i]<<"      ";
	} 
	cout<<"                        ";
	for(i=15;i>7;i-=2)
	{
		cout<<boo[i-1]<<"     ";
	}
}

void winner(int i)
{
	system("color 70");
	Sleep(40);
	system("color cf");
	Sleep(40);
	system("color c0"); 
	Sleep(40);
	system("color 0c");
	//system("cls");
	Set_mouse(42,20);
	cout<<"Player "<<i+1<<":"<<x[i]->name;
	Set_mouse(41,22);
	cout<<"获得胜利!";
	Sleep(1500);
	Set_mouse(42,24);
	cout<<"按ESC退出游戏"<<endl; 
	char a;
	while(1)
	{
		a=getch();
		if(a==27)break;
	}
	exit(0);
}



void play(char &A,char &B)			//操作处理 
{
	(*s)->runbullet(x);				//1号玩家子弹 
	(*l)->runbullet(x);				//2号玩家子弹 
	if(A)							 
	(*s)->operate(A);					//1号玩家操作 
	if(B)							
	(*l)->operate(B);					//2号玩家操作 
	(*s)->run();					// 1号玩家运行 
	(*l)->run();					// 2号玩家运行 
	x[40]->runG(x);					//小兵 
	A=B=0;
	int i,j;
	for(i=2;i<10;i++)
	{
		if(x[i]==NULL)continue;
		j=x[i]->ifdestr();
		if(j==1)
		{
			delete x[i];x[i]=NULL;continue;
		}
		if(j==-1)
		{
			if(i==3)winner(1);
			else winner(0);
		}
		x[i]->scanhit(x);
	}
}

int count(kar *z)				//数子弹 
{
	bullet **a=z->b;
	int i,j(0);
	for(i=0;i<6;i++)if(a[i]!=NULL)j++;
	return j;
}

int main()
{
	
	initial();				//总体初始化 
	char move1,move2,m;
	int m1(0),m2(0);
	scan();					
	disp();// 扫描并输出初始化后的地图 
	while(1)
	{
		m1=m2=0;
		if(kbhit())
		{
			m=getch();
			if(m==27)EXIT();			//ESC退出提示 
			if(m>90)move1=m;
			else	move2=m;
		}
		bg=clock();				//计算耗时 
		play(move1,move2);//操作
		scan();				
		disp();				//输出绘图 
		ed=clock();
		//Set_mouse(0,16);
		//cout<<"延迟:"<<(ed-bg)<<endl;
		//cout<<"帧率:"<<1000.0/(ed-bg)<<endl; 
	}
}
