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
    initgraph(1920, 980);                              // ��ʼ������ʾһ������
    int n=0;                                           //�������¸߶�
    int m=0;                                           //�������ҿ��
    int speed=64;                                      //������ʱ
    char str[100];
    do
    {
        inputbox_getline("������", "�Թ��߶ȣ��س�ȷ�ϣ�", str, 100);
        n=atoi(str);
    }while(n==0);
    do
    {
        inputbox_getline("������", "�Թ���ȣ��س�ȷ�ϣ�", str, 100);
        m=atoi(str);
    }while(m==0);
    decsize(n,m);
    initmaze(n,m);
    print(n,m);
    printprompt_box();
    createentrance(n,m);
    createmaze(n-1,m-1,&speed);                                                    //0~n-1��n��
    Maze_optimization(n-1,m-1);
    createexit(n,m);
    cue();
    BFS(n-1,m-1);
    cue();
    showmaze(n,m);
    showroad();
    cue();
    closegraph(); // �ر�ͼ�ν���
    return 0;
}


