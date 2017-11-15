#include <stdio.h>
#include <time.h>
int main()
{
    again:printf("");
    srand(time(NULL));
    char maze[80][80]={};
    int i,k ;
    int startpoint[2][2]={};
    int oop;
    char *hpointer;
    int *jpointer;
    int mazewidth,mazeheight;

    printf("   set your maze's height(<80)\n");
    scanf("%d",&mazeheight);
    if(mazeheight>=80)
    {
        printf("  out of screen!!\n");
        return 0 ;
    }

    printf("   set your maze's width(<80)\n");
    scanf("%d",&mazewidth);
    if(mazewidth>=80)
    {
         printf("  out of screen");
         return 0;
    }

     for(i=0;i<mazeheight;i++)
        for(k=0;k<mazewidth;k++)
           {
               hpointer=&maze[i][k];
               *hpointer='<';
           }


    int widrandom,heightrandom;

    widrandom=mazewidth-2;
    heightrandom=mazeheight-2;
    int startwhere;
    int whichblock ;
    int firstland ;
    int isend(int nowx,int nowy,int endx,int endy);
    int isempty(char maze[80][80],int nowx,int nowy,int width,int height);

   for(oop=0;oop<2;oop++)
   {


     if(oop==0)
     {
          startwhere=rand()%4;
     firstland=startwhere;
     }

     else
     {
         if(firstland==1||firstland==0)
            startwhere=firstland+2;
         else startwhere=firstland-2;
     }

    switch(startwhere)
    {
        case 0 : startwhere=rand()%widrandom +1;
                 hpointer=&maze[0][startwhere];
                 *hpointer='.';
                 jpointer=&startpoint[oop][0];
                 *jpointer=0;
                 jpointer=&startpoint[oop][1];
                 *jpointer=startwhere;
                 break;
        case 1 : startwhere=rand()%heightrandom +1;
                 hpointer=&maze[startwhere][mazewidth-1];
                 *hpointer='.';
                 jpointer=&startpoint[oop][0];
                 *jpointer=startwhere;
                 jpointer=&startpoint[oop][1];
                 *jpointer=mazewidth-1;
                 break;
        case 2 : startwhere=rand()%widrandom +1;
                 hpointer=&maze[mazeheight-1][startwhere];
                 *hpointer='.';
                 jpointer=&startpoint[oop][0];
                 *jpointer=mazeheight-1;
                 jpointer=&startpoint[oop][1];
                 *jpointer=startwhere;
                  break;
        case 3 : startwhere=rand()%heightrandom +1;
                 hpointer=&maze[startwhere][0];
                 *hpointer='.';
                 jpointer=&startpoint[oop][0];
                 *jpointer=startwhere;
                 jpointer=&startpoint[oop][1];
                 *jpointer=0;
                 break;

    }
    if(startpoint[1][0]==startpoint[0][0]&&startpoint[1][1]==startpoint[1][1])
        oop=0;

   }

     printf("\n  start is %d %d\n",startpoint[0][0],startpoint[0][1]);
         printf("  end is %d %d\n",startpoint[1][0],startpoint[1][1]);
   //start ...
   int gentime=0;
   restart:gentime++;
   int stx,sty;
   stx=startpoint[0][0];
   sty=startpoint[0][1];
   hpointer=&maze[stx][sty];
   *hpointer='S';

   if(stx==0)
    stx+=1;
   if(stx==mazeheight-1)
    stx-=1;
   if(sty==0)
    sty+=1;
   if(sty==mazewidth-1)
    sty-=1;

   hpointer=&maze[stx][sty];
   *hpointer='.';



   //......fill now
   int counter=0;

   int endx,endy;
   int symbol;
   symbol=0;
   int whichdirect;
   endx=startpoint[1][0];
   endy=startpoint[1][1];
    hpointer=&maze[endx][endy];
   *hpointer='E';
   int nowx,nowy;
   nowx=stx;
   nowy=sty;
   int label[4]={};
   int explabel;
   explabel=0;
   int from ;
   int wayerror(int label[4]);


for(k=0;k<4000;k++)
{
    if(isend(nowx+1,nowy,endx,endy)==1)
    {
        hpointer=&maze[nowx+1][nowy];
        *hpointer='.';
        break ;
    }
      if(isend(nowx-1,nowy,endx,endy)==1)
      {
          hpointer=&maze[nowx-1][nowy];
        *hpointer='.';
        break ;
      }
      if(isend(nowx,nowy+1,endx,endy)==1)
      {
        hpointer=&maze[nowx][nowy+1];
        *hpointer='.';
        break ;
      }
       if(isend(nowx,nowy-1,endx,endy)==1)
       {
        hpointer=&maze[nowx][nowy-1];
        *hpointer='.';
        break ;
       }

     while(symbol!=1)
       {
           if(wayerror(label)==1)
           {
                for(i=0;i<4;i++)
           {
           jpointer=&label[i];
           *jpointer=0;
           }
              for(i=1;i<mazeheight-1;i++)
                for(k=1;k<mazewidth-1;k++)
              {
                  hpointer=&maze[i][k];
                  *hpointer='>';
              }
             goto restart;
           }
           whichdirect=rand()%4;
           switch(whichdirect)
   {
       //up
       case 0 :
           from=0;
           if(nowx==1)
            {
            jpointer=&label[0];
           *jpointer=-1;
           break;
            }
       nowx--;
       symbol=isempty(maze,nowx,nowy,mazewidth,mazeheight);
       if(symbol==0)
       {
           jpointer=&label[0];
           *jpointer=-1;
           nowx++;
       }
       break ;
       //down
       case 1 :
           from=1;
           if(nowx==mazeheight-2)
           {
                jpointer=&label[1];
                *jpointer=-1;
               break ;
           }

       nowx++ ;
       symbol=isempty(maze,nowx,nowy,mazewidth,mazeheight);
        if(symbol==0)
       {
           jpointer=&label[1];
           *jpointer=-1;
           nowx--;
       }
       break;
       //right
       case 2 :
           from=2;
           if(nowy==mazewidth-2)
           {
            jpointer=&label[2];
           *jpointer=-1;
           break;
           }

       nowy++ ;
       symbol=isempty(maze,nowx,nowy,mazewidth,mazeheight);
        if(symbol==0)
       {
           jpointer=&label[2];
           *jpointer=-1;
           nowy--;
       }
       break;
       //left
       case 3 :
           from=3;
           if(nowy==1)
           {
            jpointer=&label[3];
           *jpointer=-1;
             break;
           }

       nowy-- ;
       symbol=isempty(maze,nowx,nowy,mazewidth,mazeheight);
        if(symbol==0)
       {
           jpointer=&label[3];
           *jpointer=-1;
           nowy++ ;
       }
       break ;



   }
       }


       counter++;

       symbol=0;
       for(i=0;i<4;i++)
       {
           jpointer=&label[i];
           *jpointer=0;
       }


   //$$$$$$$$$$$$$$$$

}

char answer[100][100]={};
for(i=1;i<mazeheight-1;i++)
    for(k=1;k<mazewidth-1;k++)
  {
    if(maze[i][k]=='.')
    {
        hpointer=&answer[i][k];
        *hpointer=1;
    }
  }
long toyoo ;
toyoo=300000;
while(toyoo>0)
{
    i=rand()%(mazeheight-2)+1;
    k=rand()%(mazewidth-2)+1;
    symbol=isempty(maze,i,k,mazewidth,mazeheight);
    toyoo--;
}




   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // print the maze
printf("  you can only walk on continuous '.'\n");
         printf("  you can not move as\n");
         printf("  . >\n  > .\n");
         printf("  ____ y\n");
         printf(" |\n |\n x\n");
         printf("\n  start is (%d,%d)\n",startpoint[0][0],startpoint[0][1]);
         printf("  end is (%d,%d)\n",startpoint[1][0],startpoint[1][1]);
         printf("  start is 'S' and end is 'E'\n");
printf("\n");
    for(i=0;i<mazeheight;i++)
        for(k=0;k<mazewidth;k++)
         {if(k==0)
          printf("    ");
             printf("%c ",maze[i][k]);
             if(k==mazewidth-1)
                printf("\n");

         }

         int xho;
         printf("\n  need answer? 1 to show your answer 2 to skip this maze\n");
         scanf("%d",&xho);
         switch (xho)
         {
         case 1 :
            for(i=1;i<mazeheight-1;i++)
                for(k=1;k<mazewidth-1;k++)
            {
                if(answer[i][k]==1)
                {
                    hpointer=&maze[i][k];
                    *hpointer='/';
                }
            }

            printf("\n");
    for(i=0;i<mazeheight;i++)
        for(k=0;k<mazewidth;k++)
         {if(k==0)
          printf("    ");
             printf("%c ",maze[i][k]);
             if(k==mazewidth-1)
                printf("\n");

         }
         break ;
         case 2 : break ;
         default :break ;
         }
         printf("  play again? press 1 to restart and 2 to quit\n");
         int num ;

         scanf("%d",&num);
         switch(num)
         {
             case 1 : goto again ;
             default :
             printf("written by tropical fish in 2017 Nov. in SYSU \n");
             printf("press any key to quit\n");
             scanf("%d",&num);
              return 0 ;
         }

}

int isend(int nowx,int nowy,int endx,int endy)
{
    int result=0;

    if(nowx==endx&&(nowy-endy>=-1&&nowy-endy<=1))
        result=1;
    if(nowy==endy&&(nowx-endx>=-1&&nowx-endx<=1))
        result=1;


    return result;
}

int isempty(char maze[80][80],int nowx,int nowy,int width,int height)
{
    int counter;
    int form ;
    int result=0;
    form=3;
    char *hpointer;
    counter=0;
   if(maze[nowx-1][nowy]-'>'==0)
    counter++;
   if(maze[nowx+1][nowy]-'>'==0)
    counter++;
   if(maze[nowx][nowy+1]-'>'==0)
    counter++;
   if(maze[nowx][nowy-1]-'>'==0)
    counter++;

   if(counter==form)
   {
       hpointer=&maze[nowx][nowy];
       *hpointer='.';
       result=1;
   }

   return result;
}

int wayerror(int label[4])
{
    int result;
    int sum=0;
    int i=0;
    for(i=0;i<4;i++)
        sum+=label[i];
    if(sum==-4)
        result=1;
    else
        result=0;


    return result ;
}
