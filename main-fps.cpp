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
char warning[]="�ܱ�Ǹ,��Ϸ�����쳣,�����˳�!";
char teller[]="�ļ�ȱʧ"; 
char NPC[7][11]={"С��","������","����","�����","����","����"};
string file[7]={"С��.txt","������.txt","����.txt","�����.txt","����.txt","����.txt"};
ifstream ope[7];
char screen[2000];
char *now=screen;
void write(const char *p);

void Scrinit()				//���ڳ�ʼ�� 
{
	system("title ���߹�ҫ ����Ӣ������");
	system("mode con cols=140 lines=40");
	system("color fc");
}

struct info			//�����ݴ�Ӣ�ۻ�����Ϣ 
{
	string name;		//���� 
	double blood;		//����Ѫ�� 
	double attack;		//�������� 
	int speed;			//�ٶ� 
}N[7];					//6������ 

void loadhero(const int &i,const int &j)		//ѡ����ɫ���ʼ�� 
{
	*s=new kar(N[i].name,N[i].blood,N[i].attack,N[i].speed,0,2);	 
	*l=new kar(N[j].name,N[j].blood,N[j].attack,N[j].speed,49,2);	//����������ս����,����������Ϊ��ʼλ�� 
	
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

void loadinfo()									//���ļ�������Ӣ����Ϣ 
{
	int x;
	for(x=0;x<6;x++)
	{
		system("cls"); 
		ope[x].open(file[x].c_str());
		if(ope[x]==NULL)				//�ļ���ʧ�� 
		{
			MessageBox(NULL,TEXT(warning),TEXT(teller),MB_OK|MB_ICONWARNING);
			exit(0); 
		}
		ope[x]>>N[x].name>>N[x].blood>>N[x].attack>>N[x].speed;
		cout<<"		����������..."<<x+1<<"/"<<6;
		ope[x].close();
	}
	cout<<endl<<"		�������";
}

void write(const char *p)				//�����������д����������� 
{
	int i(0);
	while(p[i]!='\0')
	{
		*now++=p[i++];
	}
	*now='\0';
}

void Selecthero()								//��Ӧѡ��Ӣ�۽��� 
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
			if(i==x)write("		��");
			else write("		 ");
			write("		 ");
			write(NPC[x]);
			if(j==x)write("		��");
			else write("		 "); 
			write("\n");
		}
		Set_mouse(0,0);
		cout<<"��ѡ��Ӣ��---(Enterȷ��)"<<endl<<endl;
		printf(screen);
		cout<<endl<<endl<<"		"<<"player1:"<<NPC[i]<<"    		"<<"player2:"<<NPC[j]<<"    "<<endl;
		cout<<endl<<"		"<<"����"<<"		"<<"����"<<"		"<<"����"<<endl<<endl;
		for(x=0;x<6;x++)
		{
			cout<<N[x].name<<"		"<<N[x].blood<<"		"<<N[x].attack<<"		"<<N[x].speed<<endl<<endl;
		}			//��ʾӢ�۲����Թ�ѡ��ο� 
	}
} 

void initial()					//�����ʼ�� 
{
	Scrinit();					// ������ 
	Hide_mouse();				//���ع�� 
	Selecthero();				//���ѡ��Ӣ�� 
	system("cls");
}

void scan()							//ɨ���ͼ����ͼ 
{
	now=screen;
	register int i(0),j(0);
	int p,q,w;write("\n");
	int r;
	for(i=0;i<100;i++)				//���Ƶ�ͼ�ϱ߿� 
	{
		if(i>1&&i<98)
		{
			if(i%2==0)write("��");
			else write("��");
		}
		if(i==0||i==98)write("�X");
		if(i==1||i==99)write("�[");
	}
	
	write("\n");
	
	for(i=0;i<50;i++)					//ͻ�����1Ӣ��λ�� 
	{
		if((*s)->nowpos.ix==i)write("��");
		else if((*s)->scanbullet(i))write("��");
		else write("��");
	}
	write("\n");
	
	
	for(r=0;r<5;r++)					//ս������ 
	{
		for(i=0;i<50;i++)
		{
			for(w=2;w<10;w++)			//��������ʾ 
			{
				if(x[w]==NULL)continue;
				if(x[w]->prepos==pos(i,r))
				{
					write("��");break;
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
					write("�J");
					else write("�I");
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
				write("��");
				else write("��");
				continue;
			}
			if(q)
			{
				if(q==1)
				write(" �b");
				else write(" �e");
				continue;
			}
			if((*s)->nowpos==pos(i,r))
			{
				if((*s)->dir==1)write("��");
				else write("��");
				continue;
			}
			if((*l)->nowpos==pos(i,r))
			{
				if((*l)->dir==1)write("��");
				else write("��");
				continue;
			}
			for(w=2;w<10;w++)
			{
				if(x[w]==NULL)continue;
				if(x[w]->nowpos==pos(i,r))
				{
					write("��");break;
				}
			}
			if(w!=10)continue;
			write("  ");
		}
		write("\n");
	}
	
	for(i=0;i<50;i++)					//ͻ�����2Ӣ��λ�� 
	{
		if((*l)->nowpos.ix==i)write("��");
		else if((*l)->scanbullet(i))write("��");
		else write("��");
	}
	
	write("\n");
	
	for(i=0;i<100;i++)					//���Ƶ�ͼ�±߿� 
	{
		if(i>1&&i<98)
		{
			if(i%2==0)write("��");
			else write("��");
		}
		if(i==0||i==98)write("�^");
		if(i==1||i==99)write("�a");
	}
	write("\n");
}

void disp()								//���ʵʱ��ս˫����Ϣ 
{
	int blood1= (*s)->blood,blood2=(*l)->blood;
	if(blood1<0)blood1=0;if(blood2<0)blood2=0;
	double boo[16];
	Set_mouse(0,0);				//��귵����λ�� 
	printf(screen);
	cout<<"���:		"<<(*s)->name<<"				"<<(*l)->name<<endl;
	cout<<"Ѫ��:		"<<blood1<<"/"<<(*s)->Maxblood<<"                 "<<blood2<<"/"<<(*l)->Maxblood<<"                      "<<endl;
	cout<<"�����ӳ�:	"<<(*s)->buff*100<<"%"<<"                   "<<(*l)->buff*100<<"%            "<<endl;
	cout<<"EXP:		"<<(*s)->EXP<<"				"<<(*l)->EXP<<"			"<<endl;
	int count(kar *);
	cout<<"�ȼ�:		"<<(*s)->grade<<"				"<<(*l)->grade<<endl;
	cout<<"��ɱ��:		"<<(*s)->kills<<"				"<<(*l)->kills<<endl;
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
	cout<<"��:"<<endl; 
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
	cout<<"���ʤ��!";
	Sleep(1500);
	Set_mouse(42,24);
	cout<<"��ESC�˳���Ϸ"<<endl; 
	char a;
	while(1)
	{
		a=getch();
		if(a==27)break;
	}
	exit(0);
}



void play(char &A,char &B)			//�������� 
{
	(*s)->runbullet(x);				//1������ӵ� 
	(*l)->runbullet(x);				//2������ӵ� 
	if(A)							 
	(*s)->operate(A);					//1����Ҳ��� 
	if(B)							
	(*l)->operate(B);					//2����Ҳ��� 
	(*s)->run();					// 1��������� 
	(*l)->run();					// 2��������� 
	x[40]->runG(x);					//С�� 
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

int count(kar *z)				//���ӵ� 
{
	bullet **a=z->b;
	int i,j(0);
	for(i=0;i<6;i++)if(a[i]!=NULL)j++;
	return j;
}

int main()
{
	
	initial();				//�����ʼ�� 
	char move1,move2,m;
	int m1(0),m2(0);
	scan();					
	disp();// ɨ�貢�����ʼ����ĵ�ͼ 
	while(1)
	{
		m1=m2=0;
		if(kbhit())
		{
			m=getch();
			if(m==27)EXIT();			//ESC�˳���ʾ 
			if(m>90)move1=m;
			else	move2=m;
		}
		bg=clock();				//�����ʱ 
		play(move1,move2);//����
		scan();				
		disp();				//�����ͼ 
		ed=clock();
		//Set_mouse(0,16);
		//cout<<"�ӳ�:"<<(ed-bg)<<endl;
		//cout<<"֡��:"<<1000.0/(ed-bg)<<endl; 
	}
}
