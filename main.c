#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include"maze.h"


int main(void)
 {
     int n,m;                                     //√‘π¨¥Û–°
     printf("«Î ‰»Î√‘π¨≥§£¨øÌ£∫")
     scanf("%d %d",&m,&n);
     createmaze(n,m);
     fullscrean();
     return 0;
 }

