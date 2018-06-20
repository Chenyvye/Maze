#include "graphics.h"
#include<stdio.h>
#include<stdlib.h>
#include <tchar.h>
#include"maze.h"
#include<time.h>
#include<conio.h>
#include <windows.h>


int main(void)
{
    srand((unsigned int)time(NULL));
    initgraph(1920, 980);                              // 初始化，显示一个窗口
    int n=0;                                           //代表上下高度
    int m=0;                                           //代表左右宽度
    int speed=64;                                      //运行延时
    char str[100];
    do
    {
        inputbox_getline("请输入", "迷宫高度（回车确认）", str, 100);
        n=atoi(str);
    }while(n==0);
    do
    {
        inputbox_getline("请输入", "迷宫宽度（回车确认）", str, 100);
        m=atoi(str);
    }while(m==0);
    decsize(n,m);
    initmaze(n,m);
    print(n,m);
    printprompt_box();
    createentrance(n,m);
    createmaze(n-1,m-1,&speed);                                                    //0~n-1共n个
    Maze_optimization(n-1,m-1);
    createexit(n,m);
    cue();
    BFS(n-1,m-1);
    cue();
    showmaze(n,m);
    showroad();
    cue();
    closegraph(); // 关闭图形界面
    return 0;
}


