#include<stdio.h>          //�����ͷ�ļ�
#include<conio.h>          //����̨���������ͷ�ļ�
#include<stdlib.h>         //ϵͳ����ͷ�ļ�
#include<time.h>           //ʱ�亯��ͷ�ļ�
#include<windows.h>        //windows������
//���˵�ģ��
 
#define U 1
#define D 2
#define L 3 
#define R 4       //�ߵ�״̬��U���� ��D���£�L:�� R����
 
typedef struct SNAKE //�����һ���ڵ�
{
    int x;
    int y;
    struct SNAKE *next;
}snake;
 
//ȫ�ֱ���//
int score=0,add=10;//�ܵ÷���ÿ�γ�ʳ��÷֡�
int status,sleeptime=200;//ÿ�����е�ʱ����
snake *head, *food;//��ͷָ�룬ʳ��ָ��
snake *q;//�����ߵ�ʱ���õ���ָ��
int endgamestatus=0; //��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��
 
//����ȫ������//
void Pos();
void initsnake();
int biteself();
void createfood1();
void cantcrosswall();
void snakemove();
void pause();
void gamecircle();
void welcometogame();
void endgame();
void gamestart();
 
void Pos(int x,int y)//���ù��λ��
{
    COORD pos;
	HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}
void initsnake()//��ʼ������
{
    snake *tail;
    int i;
    tail=(snake*)malloc(sizeof(snake));//����β��ʼ��ͷ�巨����x,y�趨��ʼ��λ��//
    tail->x=24;
    tail->y=5;
    tail->next=NULL;
    for(i=1;i<=4;i++)
    {
        head=(snake*)malloc(sizeof(snake));
        head->next=tail;
        head->x=24+2*i;
        head->y=5;
        tail=head;
    }
    while(tail!=NULL)//��ͷ��Ϊ���������
    {
        Pos(tail->x,tail->y);
        printf("��");
        tail=tail->next;
    }
}
 
int biteself()//�ж��Ƿ�ҧ�����Լ�
{
    snake *self;
    self=head->next;
    while(self!=NULL)
    {
        if(self->x==head->x && self->y==head->y)
        {
            return 1;
        }
        self=self->next;
    }
    return 0;
}
 
void createfood1()//�������ʳ��
{
    snake *food_1;
    srand((unsigned)time(NULL));
    food_1=(snake*)malloc(sizeof(snake));
    while((food_1->x%2)!=0)    //��֤��Ϊż����ʹ��ʳ��������ͷ����
    {
        food_1->x=rand()%52+2;
    }
    food_1->y=rand()%24+1;
    q=head;
    while(q->next==NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y) //�ж������Ƿ���ʳ���غ�
        {
            free(food_1);
            createfood1();
        }
        q=q->next;
    }
    Pos(food_1->x,food_1->y);
    food=food_1;
    printf("��");
}
void createfood2()//�������ʳ��
{
    snake *food_1;
    srand((unsigned)time(NULL));
     food_1=(snake*)malloc(sizeof(snake));
    food_1->x = 1;
    food_1->y = 20;

    while((food_1->x%2)!=0||food_1->x==14||food_1->x==36)    //��֤��Ϊż����ʹ��ʳ��������ͷ����
    {
        food_1->x=rand()%52+2;
    }
    while(food_1->y==20)
    {
 	   food_1->y=rand()%24+1;
    }

    q=head;
	Pos(food_1->x,food_1->y);
    food=food_1;
    printf("��");
    while(q->next==NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y) //�ж������Ƿ���ʳ���غ�
        {
            free(food_1);
            createfood2();
        }
        q=q->next;
    }
    
}
 void endgame()//������Ϸ
{
     
    system("cls");
    Pos(24,12);
    if(endgamestatus==1)
    {
        printf("�Բ�����ײ��ǽ�ˡ���Ϸ����.");
    }
    else if(endgamestatus==2)
    {
        printf("�Բ�����ҧ���Լ��ˡ���Ϸ����.");
    }
    else if(endgamestatus==3)
    {
        printf("�����Ѿ���������Ϸ��");
    }
    Pos(24,13);
    printf("���ĵ÷���%d\n",score);
	getchar();
	exit(0);
}
 
void cantcrosswall()//���ܴ�ǽ
{  
    if(head->x==0 || head->x==56 ||head->y==0 || head->y==26)
    {
        endgamestatus=1;
        endgame();
    }
}
void cantcrosswall2()//���ܴ�ǽ2
{  
    if(head->x==0 || head->x==56 ||head->y==0 || head->y==26)
    {
        endgamestatus=1;
        endgame();
    }
	else if(head->x==14&&(head->y==10||head->y==11||head->y==12||head->y==13||head->y==14||head->y==15))
    {
        endgamestatus=1;
        endgame();
    }
	else if(head->x==36&&(head->y==10||head->y==11||head->y==12||head->y==13||head->y==14||head->y==15))
    {
        endgamestatus=1;
        endgame();
    }
	else if(head->y==20&&(head->x==12||head->x==14||head->x==16||head->x==18||head->x==20||head->x==22||head->x==24||head->x==26||head->x==28||head->x==30||head->x==32||head->x==34||head->x==36||head->x==38))
    {
        endgamestatus=1;
        endgame();
    }
}
 
void snakemove()//��ǰ��,��U,��D,��L,��R
{
	snake * nexthead;
    cantcrosswall();
    
    nexthead=(snake*)malloc(sizeof(snake));
    if(status==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        if(nexthead->x==food->x && nexthead->y==food->y)//�����һ����ʳ��//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood1();
        }
        else                                               //���û��ʳ��//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==D)
    {
        nexthead->x=head->x;
        nexthead->y=head->y+1;
        if(nexthead->x==food->x && nexthead->y==food->y)  //��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood1();
        }
        else                               //û��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==L)
    {
        nexthead->x=head->x-2;
        nexthead->y=head->y;
        if(nexthead->x==food->x && nexthead->y==food->y)//��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood1();
        }
        else                                //û��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==R)
    {
        nexthead->x=head->x+2;
        nexthead->y=head->y;
        if(nexthead->x==food->x && nexthead->y==food->y)//��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood1();
        }
        else                                         //û��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(biteself()==1)       //�ж��Ƿ��ҧ���Լ�
    {
        endgamestatus=2;
        endgame();
    }
}
 
void pause()//��ͣ
{
    while(1)
    {
        Sleep(300);
        if(GetAsyncKeyState(VK_SPACE))
        {
            break;
        }
         
    }
}
void snakemove2()//��ǰ��,��U,��D,��L,��R
{
	snake * nexthead;
    cantcrosswall2();
    
    nexthead=(snake*)malloc(sizeof(snake));
    if(status==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        if(nexthead->x==food->x && nexthead->y==food->y)//�����һ����ʳ��//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood2();
        }
        else                                               //���û��ʳ��//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==D)
    {
        nexthead->x=head->x;
        nexthead->y=head->y+1;
        if(nexthead->x==food->x && nexthead->y==food->y)  //��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood2();
        }
        else                               //û��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==L)
    {
        nexthead->x=head->x-2;
        nexthead->y=head->y;
        if(nexthead->x==food->x && nexthead->y==food->y)//��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood2();
        }
        else                                //û��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(status==R)
    {
        nexthead->x=head->x+2;
        nexthead->y=head->y;
        if(nexthead->x==food->x && nexthead->y==food->y)//��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//��ֹ����1֮���ټӻ����д�
                }
            }
            createfood2();
        }
        else                                         //û��ʳ��
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("��");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(biteself()==1)       //�ж��Ƿ��ҧ���Լ�
    {
        endgamestatus=2;
        endgame();
    }
}
 
void gamecircle()//������Ϸ        
{

    Pos(64,15);
    printf("���ܴ�ǽ������ҧ���Լ�\n");
    Pos(64,16);
    printf("�á�.��.��.���ֱ�����ߵ��ƶ�.");
    Pos(64,17);
    printf("ESC ���˳���Ϸ.space����ͣ��Ϸ.");
	status=R;
    while(1)
    {
        Pos(64,10);
        printf("�÷֣�%d  ",score);
        Pos(64,11);
        printf("ÿ��ʳ��÷֣�%d��",add);
        if(GetAsyncKeyState(VK_UP) && status!=D)
        {
            status=U;
        }
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)
        {
            status=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
        {
            status=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
        {
            status=R;
        }
        else if(GetAsyncKeyState(VK_SPACE))
        {
            pause();
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus=3;
            break;
        }
        Sleep(sleeptime);
        snakemove();
    }
}
void gamecircle2()//������Ϸ        
{

   Pos(64,15);
    printf("���ܴ�ǽ������ҧ���Լ�\n");
    Pos(64,16);
    printf("�á�.��.��.���ֱ�����ߵ��ƶ�.");
    Pos(64,17);
    printf("ESC ���˳���Ϸ.space����ͣ��Ϸ.");
	status=R;
    while(1)
    {
        Pos(64,10);
        printf("�÷֣�%d  ",score);
        Pos(64,11);
        printf("ÿ��ʳ��÷֣�%d��",add);
        if(GetAsyncKeyState(VK_UP) && status!=D)
        {
            status=U;
        }
        else if(GetAsyncKeyState(VK_DOWN) && status!=U)
        {
            status=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
        {
            status=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
        {
            status=R;
        }
        else if(GetAsyncKeyState(VK_SPACE))
        {
            pause();
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus=3;
            break;
        }
        Sleep(sleeptime);
        snakemove2();
    }
}
 

void map1()
{
	system("cls");
	 int i;
    for(i=0;i<58;i+=2)//��ӡ���±߿�
    {
        Pos(i,0);
        printf("��");
        Pos(i,26);
        printf("��");
    }
    for(i=1;i<26;i++)//��ӡ���ұ߿�
    {
        Pos(0,i);
        printf("��");                        
        Pos(56,i);
        printf("��");        
    }
	initsnake();
    createfood1();
	gamecircle();
}

void map2()
{
	system("cls");
	int i;
    for(i=0;i<58;i+=2)//��ӡ���±߿�
    {
        Pos(i,0);
        printf("��");
        Pos(i,26);
        printf("��");
    }
    for(i=1;i<26;i++)//��ӡ���ұ߿�
    {
        Pos(0,i);
        printf("��");                        
        Pos(56,i);
        printf("��"); 
	
    }
	 for(i=10;i<16;i++)//��ӡ�ϰ�
    {
        Pos(14,i);
        printf("��");                        
        Pos(36,i);
        printf("��"); 
	
    }
	 for(i=12;i<39;i+=2)//��ӡ�ϰ�
    {
        Pos(i,20);
        printf("��");
    }
	 initsnake();
    createfood2();
	gamecircle2();
}
void map3()
{
	system("cls");
	int i;
    for(i=0;i<58;i+=2)//��ӡ���±߿�
    {
        Pos(i,0);
        printf("��");
        Pos(i,26);
        printf("��");
    }
    for(i=1;i<26;i++)//��ӡ���ұ߿�
    {
        Pos(0,i);
        printf("��");                        
        Pos(56,i);
        printf("��"); 
	
    }
	 for(i=8;i<20;i++)//��ӡ�ϰ�
    {
        Pos(15,i);
        printf("��");                        
        Pos(35,i);
        printf("��"); 
	
    }
	 for(i=15;i<25;i+=2)//��ӡ�ϰ�
    {
        Pos(i,8);
        printf("��");
		 Pos(i,12);
        printf("��");
    }
	 for(i=9;i<12;i++)//��ӡ�ϰ�
    {
        Pos(24,i);
        printf("��");
    }
	 for(i=35;i<45;i+=2)//��ӡ�ϰ�
    {
        Pos(i,8);
        printf("��");
		 Pos(i,12);
        printf("��");
    }
	 for(i=9;i<12;i++)//��ӡ�ϰ�
    {
        Pos(44,i);
        printf("��");
	 }
}
void map()
{
system("cls");
printf("������1����2��ѡ��������Ϸ�ĵ�ͼ\n");
int a;
scanf("%d",&a);
switch(a)
{
case 1:map1();break;
case 2:map2();break;
case 3:map3();break;
default:printf("û���ҵ���صĵ�ͼ");
}
}
void explain()
{
	system("cls");
	printf("                                 ̰���ߵ�˵��\n");
	printf("                            ����:\n");
	printf("                                 1.һ�����ģʽ��������� �� �� ��������������\n");
	printf("                                 2.�������ģʽ����Ҷ���ĸ��W, S, A, D �ֱ�����ϡ��¡�����\n\n");
	printf("                                                                            ���»س�������Ϸ��ͼѡ��\n");
	getch();
	map();
}
void menu()
{
	  system("mode con cols=100 lines=30"); //��������Ҫ����ʾ�����ռ�
	  system("color E9");  
	  printf("           ###                        #                             #             \n");
      printf("          #   #                      ##########                      #            \n");
	  printf("         #     #                    #                          #############      \n");
	  printf("        #   #   #                  #                    #      #           #      \n");
	  printf("      ##   ####  ###       #####     ########           #      #    #      #      \n");
	  printf("             #             #   #           #         ########       #             \n");
	  printf("           #               #   #          #          #  #   #       #             \n");
	  printf("        ##########         #   #         #           ########       #    #        \n");
	  printf("        #        #         #####        #               #           #   #         \n");
	  printf("        #    #   #                     #                #  #        #  #          \n");
	  printf("        #    #   #                    #               #######       # #           \n");
	  printf("        #    #   #                   #                       #      #             \n");
	  printf("            # #                     #                               #             \n");
	  printf("           #   #                   #                                #             \n");
	  printf("          #     #                  #            #                   #         #   \n");
	  printf("         #       #                  #############                   ###########   \n");
	  printf("�밴�»س���������Ϸ˵��");
	  getchar();
	  explain();
}

int main()
{
	menu();
return 0;
}
