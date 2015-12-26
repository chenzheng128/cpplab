#include<stdio.h>          //常规库头文件
#include<conio.h>          //控制台输入输出流头文件
#include<stdlib.h>         //系统函数头文件
#include<time.h>           //时间函数头文件
#include<windows.h>        //windows函数库
//主菜单模块
 
#define U 1
#define D 2
#define L 3 
#define R 4       //蛇的状态，U：上 ；D：下；L:左 R：右
 
typedef struct SNAKE //蛇身的一个节点
{
    int x;
    int y;
    struct SNAKE *next;
}snake;
 
//全局变量//
int score=0,add=10;//总得分与每次吃食物得分。
int status,sleeptime=200;//每次运行的时间间隔
snake *head, *food;//蛇头指针，食物指针
snake *q;//遍历蛇的时候用到的指针
int endgamestatus=0; //游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。
 
//声明全部函数//
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
 
void Pos(int x,int y)//设置光标位置
{
    COORD pos;
	HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}
void initsnake()//初始化蛇身
{
    snake *tail;
    int i;
    tail=(snake*)malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
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
    while(tail!=NULL)//从头到为，输出蛇身
    {
        Pos(tail->x,tail->y);
        printf("■");
        tail=tail->next;
    }
}
 
int biteself()//判断是否咬到了自己
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
 
void createfood1()//随机出现食物
{
    snake *food_1;
    srand((unsigned)time(NULL));
    food_1=(snake*)malloc(sizeof(snake));
    while((food_1->x%2)!=0)    //保证其为偶数，使得食物能与蛇头对其
    {
        food_1->x=rand()%52+2;
    }
    food_1->y=rand()%24+1;
    q=head;
    while(q->next==NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y) //判断蛇身是否与食物重合
        {
            free(food_1);
            createfood1();
        }
        q=q->next;
    }
    Pos(food_1->x,food_1->y);
    food=food_1;
    printf("■");
}
void createfood2()//随机出现食物
{
    snake *food_1;
    srand((unsigned)time(NULL));
     food_1=(snake*)malloc(sizeof(snake));
    food_1->x = 1;
    food_1->y = 20;

    while((food_1->x%2)!=0||food_1->x==14||food_1->x==36)    //保证其为偶数，使得食物能与蛇头对其
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
    printf("■");
    while(q->next==NULL)
    {
        if(q->x==food_1->x && q->y==food_1->y) //判断蛇身是否与食物重合
        {
            free(food_1);
            createfood2();
        }
        q=q->next;
    }
    
}
 void endgame()//结束游戏
{
     
    system("cls");
    Pos(24,12);
    if(endgamestatus==1)
    {
        printf("对不起，您撞到墙了。游戏结束.");
    }
    else if(endgamestatus==2)
    {
        printf("对不起，您咬到自己了。游戏结束.");
    }
    else if(endgamestatus==3)
    {
        printf("您的已经结束了游戏。");
    }
    Pos(24,13);
    printf("您的得分是%d\n",score);
	getchar();
	exit(0);
}
 
void cantcrosswall()//不能穿墙
{  
    if(head->x==0 || head->x==56 ||head->y==0 || head->y==26)
    {
        endgamestatus=1;
        endgame();
    }
}
void cantcrosswall2()//不能穿墙2
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
 
void snakemove()//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
    cantcrosswall();
    
    nexthead=(snake*)malloc(sizeof(snake));
    if(status==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        if(nexthead->x==food->x && nexthead->y==food->y)//如果下一个有食物//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood1();
        }
        else                                               //如果没有食物//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
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
        if(nexthead->x==food->x && nexthead->y==food->y)  //有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood1();
        }
        else                               //没有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
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
        if(nexthead->x==food->x && nexthead->y==food->y)//有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood1();
        }
        else                                //没有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
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
        if(nexthead->x==food->x && nexthead->y==food->y)//有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood1();
        }
        else                                         //没有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(biteself()==1)       //判断是否会咬到自己
    {
        endgamestatus=2;
        endgame();
    }
}
 
void pause()//暂停
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
void snakemove2()//蛇前进,上U,下D,左L,右R
{
	snake * nexthead;
    cantcrosswall2();
    
    nexthead=(snake*)malloc(sizeof(snake));
    if(status==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
        if(nexthead->x==food->x && nexthead->y==food->y)//如果下一个有食物//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood2();
        }
        else                                               //如果没有食物//
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
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
        if(nexthead->x==food->x && nexthead->y==food->y)  //有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood2();
        }
        else                               //没有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
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
        if(nexthead->x==food->x && nexthead->y==food->y)//有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood2();
        }
        else                                //没有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
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
        if(nexthead->x==food->x && nexthead->y==food->y)//有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;
            }
            score=score+add;
			if(sleeptime>=50)
            {
                sleeptime=sleeptime-30;
                add=add+2;
                if(sleeptime==320)
                {
                    add=2;//防止减到1之后再加回来有错
                }
            }
            createfood2();
        }
        else                                         //没有食物
        {
            nexthead->next=head;
            head=nexthead;
            q=head;
            while(q->next->next!=NULL)
            {
                Pos(q->x,q->y);
                printf("■");
                q=q->next;        
            }
            Pos(q->next->x,q->next->y);
            printf("  ");
            free(q->next);
            q->next=NULL;
        }
    }
    if(biteself()==1)       //判断是否会咬到自己
    {
        endgamestatus=2;
        endgame();
    }
}
 
void gamecircle()//控制游戏        
{

    Pos(64,15);
    printf("不能穿墙，不能咬到自己\n");
    Pos(64,16);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    Pos(64,17);
    printf("ESC ：退出游戏.space：暂停游戏.");
	status=R;
    while(1)
    {
        Pos(64,10);
        printf("得分：%d  ",score);
        Pos(64,11);
        printf("每个食物得分：%d分",add);
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
void gamecircle2()//控制游戏        
{

   Pos(64,15);
    printf("不能穿墙，不能咬到自己\n");
    Pos(64,16);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    Pos(64,17);
    printf("ESC ：退出游戏.space：暂停游戏.");
	status=R;
    while(1)
    {
        Pos(64,10);
        printf("得分：%d  ",score);
        Pos(64,11);
        printf("每个食物得分：%d分",add);
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
    for(i=0;i<58;i+=2)//打印上下边框
    {
        Pos(i,0);
        printf("★");
        Pos(i,26);
        printf("★");
    }
    for(i=1;i<26;i++)//打印左右边框
    {
        Pos(0,i);
        printf("★");                        
        Pos(56,i);
        printf("★");        
    }
	initsnake();
    createfood1();
	gamecircle();
}

void map2()
{
	system("cls");
	int i;
    for(i=0;i<58;i+=2)//打印上下边框
    {
        Pos(i,0);
        printf("★");
        Pos(i,26);
        printf("★");
    }
    for(i=1;i<26;i++)//打印左右边框
    {
        Pos(0,i);
        printf("★");                        
        Pos(56,i);
        printf("★"); 
	
    }
	 for(i=10;i<16;i++)//打印障碍
    {
        Pos(14,i);
        printf("★");                        
        Pos(36,i);
        printf("★"); 
	
    }
	 for(i=12;i<39;i+=2)//打印障碍
    {
        Pos(i,20);
        printf("★");
    }
	 initsnake();
    createfood2();
	gamecircle2();
}
void map3()
{
	system("cls");
	int i;
    for(i=0;i<58;i+=2)//打印上下边框
    {
        Pos(i,0);
        printf("★");
        Pos(i,26);
        printf("★");
    }
    for(i=1;i<26;i++)//打印左右边框
    {
        Pos(0,i);
        printf("★");                        
        Pos(56,i);
        printf("★"); 
	
    }
	 for(i=8;i<20;i++)//打印障碍
    {
        Pos(15,i);
        printf("★");                        
        Pos(35,i);
        printf("★"); 
	
    }
	 for(i=15;i<25;i+=2)//打印障碍
    {
        Pos(i,8);
        printf("★");
		 Pos(i,12);
        printf("★");
    }
	 for(i=9;i<12;i++)//打印障碍
    {
        Pos(24,i);
        printf("★");
    }
	 for(i=35;i<45;i+=2)//打印障碍
    {
        Pos(i,8);
        printf("★");
		 Pos(i,12);
        printf("★");
    }
	 for(i=9;i<12;i++)//打印障碍
    {
        Pos(44,i);
        printf("★");
	 }
}
void map()
{
system("cls");
printf("请输入1或者2来选择你想游戏的地图\n");
int a;
scanf("%d",&a);
switch(a)
{
case 1:map1();break;
case 2:map2();break;
case 3:map3();break;
default:printf("没有找到相关的地图");
}
}
void explain()
{
	system("cls");
	printf("                                 贪吃蛇的说明\n");
	printf("                            操作:\n");
	printf("                                 1.一个玩家模式：方向键↑ ↓ ← →控制上下左右\n");
	printf("                                 2.两个玩家模式：玩家二字母键W, S, A, D 分别控制上、下、左、右\n\n");
	printf("                                                                            按下回车进入游戏地图选择\n");
	getch();
	map();
}
void menu()
{
	  system("mode con cols=100 lines=30"); //定义所需要的显示背景空间
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
	  printf("请按下回车键进入游戏说明");
	  getchar();
	  explain();
}

int main()
{
	menu();
return 0;
}
