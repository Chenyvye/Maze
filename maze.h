#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include<time.h>
#include<conio.h>
#include "graphics.h"

struct
{
    int right;                                      //右边界墙,有墙为1，没墙为0
    int down;                                       //下边界墙,有墙为1，没墙为0
    int f;                                          //是否访问过 0为未访问，1为已访问(创建时);1为未访问，2为已访问（遍历时)
}maze[200][200];

struct
{
    int x;
    int y;
}entrance,exitpoint;

struct Loc
{
    int x,y;                                        //用于记录当前节点的坐标
    int key;                                        //用于记录父亲节点在队中位置
};

struct
{
    Loc data[40000];
    int frontt,rear;
}SqQueue;

struct
{
    int pwidth;
    int pheight;
}sizee;

void decsize(int n,int m)
{
    sizee.pwidth = 1300 / (2*(m+10)), sizee.pheight = 980 / (2*(n+10));
    if (sizee.pwidth > sizee.pheight) sizee.pwidth = sizee.pheight;
    else sizee.pheight = sizee.pwidth;
    if (sizee.pwidth > 50)
    {
        sizee.pwidth = 50;
        sizee.pheight = 50;
    }
}

void initmaze(int n,int m)
{
    int i,j;
    for (i=0;i<=n+1;i++)
    {
        for (j=0;j<=m+1;j++)
        {
            maze[i][j].right=1;                                 //有墙为1，没墙为0
            maze[i][j].down=1;
            maze[i][j].f=0;
        }
    }
}

void printprompt_box()
{
    setfillcolor(EGERGB(0x00, 0xFF, 0xFF));
    bar(1200, 0 , 1920, 980);
    //文字颜色
    setfont(30,0xFF0000, "宋体");
    setbkmode(TRANSPARENT);
    outtextxy(1350, 100, "迷宫");
    setfont(18,0xFF0000, "宋体");
    setcolor(EGERGB(0xFF, 0x00, 0x00));
    outtextxy(1300, 150, "加速按方向上键%(↑%)");
    outtextxy(1300, 170, "减速按方向下键%(↓%)");
}

void createentrance(int n,int m)
{
    setfillcolor(EGERGB(0xFF, 0xFF, 0x00));
    int a;
    a=rand()%4+1;                       //1为上边，2为右边，3为下边，4为左边
    if (a==1)
    {
        entrance.x=0;
        entrance.y=rand() % m + 1;
        bar((entrance.y * 2 - 1) * sizee.pwidth, entrance.x * sizee.pheight , entrance.y * 2 * sizee.pwidth, (entrance.x + 1) *  sizee.pheight);
        entrance.y-=1;
    }
    else if (a==2)
    {
        entrance.y=m;
        entrance.x=rand() % n + 1;
        bar(entrance.y * 2 * sizee.pwidth, (entrance.x * 2 - 1) * sizee.pheight , (entrance.y * 2 + 1) * sizee.pwidth,  entrance.x * 2 * sizee.pheight);
        entrance.x-=1;entrance.y-=1;
    }
    else if (a==3)
    {
        entrance.x=n;
        entrance.y=rand() % m + 1;
        bar((entrance.y * 2 - 1) * sizee.pwidth, entrance.x * 2 * sizee.pheight , entrance.y * 2 * sizee.pwidth,  (entrance.x * 2 + 1) * sizee.pheight);
        entrance.y-=1;entrance.x-=1;
    }
    else
    {
        entrance.y=0;
        entrance.x=rand() % n + 1;
        bar(entrance.y * sizee.pwidth, (entrance.x * 2 - 1) * sizee.pheight , (entrance.y + 1) * sizee.pwidth, entrance.x * 2 * sizee.pheight);
        entrance.x-=1;
    }
}

void createexit(int n,int m)
{
    /*--------------------------获取图片并改变大小---------------------------------------*/
    PIMAGE img=newimage(200,400);
    getimage(img,"exit.jpg",0,0);
    //Resize image to pwidth*pheight
    PIMAGE save=gettarget();
    //Get image size
    settarget(img);
    int width,height;
    width=getwidth();
    height=getheight();
    settarget(save);

    PIMAGE backproc=newimage(sizee.pwidth,sizee.pheight);
    //Resize
    putimage(backproc,0,0,sizee.pwidth,sizee.pheight,img,0,0,width,height);
    getimage(img,backproc,0,0,sizee.pwidth,sizee.pheight);
    delimage(backproc);
/*--------------------------获取图片并改变大小---------------------------------------*/
    int a;
    do
    {
        a=rand()%4+1;                       //1为上边，2为右边，3为下边，4为左边
        if (a==1)
        {
            exitpoint.x=0;
            exitpoint.y=rand() % m + 1;
            if ((!(exitpoint.x==entrance.x && exitpoint.y==entrance.y)) && (!(exitpoint.x==entrance.x && exitpoint.y-1==entrance.y)))
            {
                putimage((exitpoint.y * 2 - 1) * sizee.pwidth,exitpoint.x * sizee.pheight , img);
            }
            exitpoint.y-=1;
        }
        else if (a==2)
        {
            exitpoint.y=m;
            exitpoint.x=rand() % n + 1;
            if ((!(exitpoint.x==entrance.x && exitpoint.y==entrance.y))&& (!(exitpoint.x-1==entrance.x && exitpoint.y-1==entrance.y)))
            {
                putimage(exitpoint.y * 2 * sizee.pwidth, (exitpoint.x * 2 - 1) * sizee.pheight , img);
            }
            exitpoint.x-=1;exitpoint.y-=1;
        }
        else if (a==3)
        {
            exitpoint.x=n;
            exitpoint.y=rand() % m + 1;
            if ((!(exitpoint.x==entrance.x && exitpoint.y==entrance.y)) && (!(exitpoint.x-1==entrance.x && exitpoint.y-1==entrance.y)))
            {
                putimage((exitpoint.y * 2 - 1) * sizee.pwidth, exitpoint.x * 2 * sizee.pheight , img);
            }
            exitpoint.y-=1;exitpoint.x-=1;
        }
        else
        {
            exitpoint.y=0;
            exitpoint.x=rand() % n + 1;
            if ((!(exitpoint.x==entrance.x && exitpoint.y==entrance.y)) &&  (!(exitpoint.x-1==entrance.x && exitpoint.y==entrance.y)))
            {
                putimage(exitpoint.y * sizee.pwidth, (exitpoint.x * 2 - 1) * sizee.pheight , img);
            }
            exitpoint.x-=1;
        }
    }while(exitpoint.x==entrance.x && exitpoint.y==entrance.y);
}

void Maze_optimization(int n,int m)
{
    int i=0,j=0;
    int x,y;
    setfillcolor(EGERGB(0x00, 0x00, 0x00));
    while((i<(int)(n*m/10)) && j<n*m)
    {
        x=rand()%n;y=rand()%m;
        if (maze[x][y].right==1)
        {
            maze[x][y].right=0;
            bar((y * 2 + 2) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y * 2 + 3) * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
            i++;
        }
        else if (maze[x][y].down==1)
        {
            maze[x][y].down=0;
            bar((y * 2 + 1) * sizee.pwidth, (x + 1) * 2 * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x * 2 + 3) * sizee.pheight);
            i++;
        }
        j++;
    }
}

void DFS(int x,int y,int n,int m,int *speed)
{
    char str;
    if(kbhit())
    {
        str=getch();
        if (str==40 && (*speed)<512) (*speed)*=2;
        else if (str==38 && (*speed)>1) (*speed)/=2;
    }
    Sleep(*speed);
    maze[x][y].f=1;
    setfillcolor(EGERGB(0x00, 0x00, 0x00));
    int a=rand()%4;                                                    //0为上边，1为右边，2为下边，3为左边
    while(1)
    {
        if (x<=0 && y<=0 && maze[x][y+1].f==1 && maze[x+1][y].f==1) return;
        else if (x<=0 && y>=m && maze[x][y-1].f==1 && maze[x+1][y].f==1) return;
        else if (x<=0 && maze[x][y-1].f==1 && maze[x][y+1].f==1 && maze[x+1][y].f==1) return;
        else if (y<=0 && x>=n && maze[x-1][y].f==1 && maze[x][y+1].f==1) return;
        else if (y<=0 && maze[x-1][y].f==1 && maze[x+1][y].f==1 && maze[x][y+1].f==1) return;
        else if (x>=n && y>=m && maze[x][y-1].f==1 && maze[x-1][y].f==1) return;
        else if (x>=n && maze[x][y-1].f==1 && maze[x][y+1].f==1 && maze[x-1][y].f==1) return;
        else if (y>=m && maze[x-1][y].f==1 && maze[x+1][y].f==1 && maze[x][y-1].f==1) return;
        else if (maze[x-1][y].f==1 && maze[x+1][y].f==1 && maze[x][y-1].f==1 && maze[x][y+1].f==1) return;
        if (a==0)
        {
            if (x==0 || (x>0 && maze[x-1][y].f==1))  a=1;
            else
            {
                bar((y * 2 + 1) * sizee.pwidth, (x * 2) * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x * 2 + 1) * sizee.pheight);
                bar((y * 2 + 1) * sizee.pwidth, (x * 2 - 1) * sizee.pheight , (y + 1) * 2 * sizee.pwidth, x * 2 * sizee.pheight);
                maze[x-1][y].down=0;
                DFS(x-1,y,n,m,speed);
            }
        }
        if (a==1)
        {
            if (y==m || (y<=m && maze[x][y+1].f==1))  a=2;
            else
            {
                bar((y * 2 + 2) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y * 2 + 3) * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
                bar((y * 2 + 3) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y * 2 + 4) * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
                maze[x][y].right=0;
                DFS(x,y+1,n,m,speed);
            }
        }
        if (a==2)
        {
            if (x==n || (x<n && maze[x+1][y].f==1))  a=3;
            else
            {
                bar((y * 2 + 1) * sizee.pwidth, (x + 1) * 2 * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x * 2 + 3) * sizee.pheight);
                bar((y * 2 + 1) * sizee.pwidth, (x * 2 + 3) * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x * 2 + 4) * sizee.pheight);
                maze[x][y].down=0;
                DFS(x+1,y,n,m,speed);
            }
        }
        if (a==3)
        {
            if (y==0 || (y>0 && maze[x][y-1].f==1))  a=0;
            else
            {
                bar((y * 2 ) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y * 2 + 1) * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
                bar((y * 2 ) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y * 2 - 1) * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
                maze[x][y-1].right=0;
                DFS(x,y-1,n,m,speed);
            }
        }
    }
}

void createmaze(int n,int m,int *speed)
{
    int x=entrance.x,y=entrance.y;
    setfillcolor(EGERGB(0x00, 0x00, 0x00));
    bar((y * 2 + 1) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
    DFS(x,y,n,m,speed);
}

void print(int n,int m)
{
/*--------------------------获取图片并改变大小---------------------------------------*/
    PIMAGE img=newimage(200,400);
    getimage(img,"qiang.jpg",0,0);
    //Resize image to pwidth*pheight
    PIMAGE save=gettarget();
    //Get image size
    settarget(img);
    int width,height;
    width=getwidth();
    height=getheight();
    settarget(save);

    PIMAGE backproc=newimage(sizee.pwidth,sizee.pheight);
    //Resize
    putimage(backproc,0,0,sizee.pwidth,sizee.pheight,img,0,0,width,height);
    getimage(img,backproc,0,0,sizee.pwidth,sizee.pheight);
    delimage(backproc);
/*--------------------------获取图片并改变大小---------------------------------------*/
    int i,j;
    for (i=0;i<2*n+1;i++)
    {
        for (j=0;j<2*m+1;j++)
        {
            putimage(j*sizee.pwidth, i*sizee.pheight, img);
        }
    }
}

void showmaze(int n,int m)
{
    int x,y;
    setfillcolor(EGERGB(0x00, 0x00, 0x00));
    for (x=0;x<n;x++)
    {
        for (y=0;y<m;y++)
        {
            bar((y * 2 + 1) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x + 1) * 2 * sizee.pheight);
            if (maze[x][y].down==0)
            {
                bar((y * 2 + 1) * sizee.pwidth, (x * 2 + 2) * sizee.pheight , (y + 1) * 2 * sizee.pwidth, (x * 2 + 3) * sizee.pheight);
            }
            if (maze[x][y].right==0)
            {
                bar((y * 2 + 2) * sizee.pwidth, (x * 2 + 1) * sizee.pheight , (y * 2 + 3) * sizee.pwidth, (x * 2 + 2) * sizee.pheight);
            }
        }
    }
}

void BFS(int n,int m)
{
/*--------------------------获取图片并改变大小---------------------------------------*/
    PIMAGE img=newimage(200,400);
    getimage(img,"ren.jpg",0,0);
    //Resize image to pwidth*pheight
    PIMAGE save=gettarget();
    //Get image size
    settarget(img);
    int width,height;
    width=getwidth();
    height=getheight();
    settarget(save);

    PIMAGE backproc=newimage(sizee.pwidth,sizee.pheight);
    //Resize
    putimage(backproc,0,0,sizee.pwidth,sizee.pheight,img,0,0,width,height);
    getimage(img,backproc,0,0,sizee.pwidth,sizee.pheight);
    delimage(backproc);
/*--------------------------获取图片并改变大小---------------------------------------*/
    char str;
    int speed=64;
    SqQueue.frontt=0;
    SqQueue.rear=0;
    SqQueue.data[0].key=-1;
    SqQueue.data[0].x=entrance.x;SqQueue.data[0].y=entrance.y;
    putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
    do
    {
        if ((!(SqQueue.data[SqQueue.frontt].x==exitpoint.x && SqQueue.data[SqQueue.frontt].y==exitpoint.y)) && SqQueue.data[SqQueue.rear].x>0 && maze[SqQueue.data[SqQueue.rear].x-1][SqQueue.data[SqQueue.rear].y].down==0 && maze[SqQueue.data[SqQueue.rear].x-1][SqQueue.data[SqQueue.rear].y].f==1)
        {
            SqQueue.frontt++;
            SqQueue.data[SqQueue.frontt].x=SqQueue.data[SqQueue.rear].x-1;SqQueue.data[SqQueue.frontt].y=SqQueue.data[SqQueue.rear].y;
            maze[SqQueue.data[SqQueue.rear].x-1][SqQueue.data[SqQueue.frontt].y].f=2;
            SqQueue.data[SqQueue.frontt].key=SqQueue.rear;
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 2) * sizee.pheight , img);
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
        }
        if ((!(SqQueue.data[SqQueue.frontt].x==exitpoint.x && SqQueue.data[SqQueue.frontt].y==exitpoint.y)) && SqQueue.data[SqQueue.rear].y<m && maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y].right==0 && maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y+1].f==1)
        {
            SqQueue.frontt++;
            SqQueue.data[SqQueue.frontt].x=SqQueue.data[SqQueue.rear].x;SqQueue.data[SqQueue.frontt].y=SqQueue.data[SqQueue.rear].y+1;
            SqQueue.data[SqQueue.frontt].key=SqQueue.rear;
            maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y+1].f=2;
            putimage((SqQueue.data[SqQueue.frontt].y * 2 ) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
        }
        if ((!(SqQueue.data[SqQueue.frontt].x==exitpoint.x && SqQueue.data[SqQueue.frontt].y==exitpoint.y)) && SqQueue.data[SqQueue.rear].x<n && maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y].down==0 && maze[SqQueue.data[SqQueue.rear].x+1][SqQueue.data[SqQueue.rear].y].f==1)
        {
            SqQueue.frontt++;
            SqQueue.data[SqQueue.frontt].x=SqQueue.data[SqQueue.rear].x+1;SqQueue.data[SqQueue.frontt].y=SqQueue.data[SqQueue.rear].y;
            SqQueue.data[SqQueue.frontt].key=SqQueue.rear;
            maze[SqQueue.data[SqQueue.rear].x+1][SqQueue.data[SqQueue.rear].y].f=2;
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 ) * sizee.pheight , img);
        }
        if ((!(SqQueue.data[SqQueue.frontt].x==exitpoint.x && SqQueue.data[SqQueue.frontt].y==exitpoint.y)) && SqQueue.data[SqQueue.rear].y>0 && maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y-1].right==0 && maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y-1].f==1)
        {
            SqQueue.frontt++;
            SqQueue.data[SqQueue.frontt].x=SqQueue.data[SqQueue.rear].x;SqQueue.data[SqQueue.frontt].y=SqQueue.data[SqQueue.rear].y-1;
            SqQueue.data[SqQueue.frontt].key=SqQueue.rear;
            maze[SqQueue.data[SqQueue.rear].x][SqQueue.data[SqQueue.rear].y-1].f=2;
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 1) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
            putimage((SqQueue.data[SqQueue.frontt].y * 2 + 2) * sizee.pwidth, (SqQueue.data[SqQueue.frontt].x * 2 + 1) * sizee.pheight , img);
        }
        if(kbhit())
        {
            str=getch();
            if (str==40 && speed<512) speed*=2;
            else if (str==38 && speed>1) speed/=2;
        }
        if (SqQueue.data[SqQueue.rear].key != SqQueue.data[SqQueue.rear-1].key) Sleep(speed);
        SqQueue.rear++;
    }while((!(SqQueue.data[SqQueue.frontt].x==exitpoint.x && SqQueue.data[SqQueue.frontt].y==exitpoint.y)));
}

void showroad()
{
/*--------------------------获取图片并改变大小---------------------------------------*/
    PIMAGE img=newimage(200,400);
    getimage(img,"ren.jpg",0,0);
    //Resize image to pwidth*pheight
    PIMAGE save=gettarget();
    //Get image size
    settarget(img);
    int width,height;
    width=getwidth();
    height=getheight();
    settarget(save);

    PIMAGE backproc=newimage(sizee.pwidth,sizee.pheight);
    //Resize
    putimage(backproc,0,0,sizee.pwidth,sizee.pheight,img,0,0,width,height);
    getimage(img,backproc,0,0,sizee.pwidth,sizee.pheight);
    delimage(backproc);
/*--------------------------获取图片并改变大小---------------------------------------*/
    int k;
    k=SqQueue.frontt;
    putimage((SqQueue.data[k].y * 2 + 1) * sizee.pwidth, (SqQueue.data[k].x * 2 + 1) * sizee.pheight , img);
    do
    {
        if (SqQueue.data[SqQueue.data[k].key].x < SqQueue.data[k].x)
        {
            putimage((SqQueue.data[k].y * 2 + 1) * sizee.pwidth, (SqQueue.data[k].x * 2) * sizee.pheight , img);
            putimage((SqQueue.data[k].y * 2 + 1) * sizee.pwidth, (SqQueue.data[k].x * 2 - 1) * sizee.pheight , img);
        }
        else if (SqQueue.data[SqQueue.data[k].key].x > SqQueue.data[k].x )
        {
            putimage((SqQueue.data[k].y * 2 + 1) * sizee.pwidth, (SqQueue.data[k].x * 2 + 2) * sizee.pheight , img);
            putimage((SqQueue.data[k].y * 2 + 1) * sizee.pwidth, (SqQueue.data[k].x * 2 + 3) * sizee.pheight , img);
        }
        else if (SqQueue.data[SqQueue.data[k].key].y < SqQueue.data[k].y)
        {
            putimage((SqQueue.data[k].y * 2) * sizee.pwidth, (SqQueue.data[k].x * 2 + 1) * sizee.pheight , img);
            putimage((SqQueue.data[k].y * 2 - 1) * sizee.pwidth, (SqQueue.data[k].x * 2 + 1) * sizee.pheight , img);
        }
        else if (SqQueue.data[SqQueue.data[k].key].y > SqQueue.data[k].y)
        {
            putimage((SqQueue.data[k].y * 2 + 2) * sizee.pwidth, (SqQueue.data[k].x * 2 + 1) * sizee.pheight , img);
            putimage((SqQueue.data[k].y * 2 + 3) * sizee.pwidth, (SqQueue.data[k].x * 2 + 1) * sizee.pheight , img);
        }
        k=SqQueue.data[k].key;
    }while(!(SqQueue.data[k].x==entrance.x && SqQueue.data[k].y==entrance.y));
}

void cue()
{
    setfont(13,0xFF0000, "宋体");
    outtextxy(1300, 500, "press any key to continue");
    getch();
    printprompt_box();
}

#endif // MAZE_H_INCLUDED
