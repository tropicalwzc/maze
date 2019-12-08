//
//  mazegenerator.h
//  mazesearch
//
//  Created by 王子诚 on 2019/11/17.
//  Copyright © 2019 王子诚. All rights reserved.
//

#ifndef mazegenerator_h
#define mazegenerator_h

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class mazegenerate
{
    /*
     * this generater has splendid speed even could generate one 500*500 or larger maze
     */
public:
    mazegenerate()
    {

    }
    int isend(int nowx, int nowy, int endx, int endy)
    {
        int result = 0;
        
        if (nowx == endx && (nowy - endy >= -1 && nowy - endy <= 1))
            result = 1;
        if (nowy == endy && (nowx - endx >= -1 && nowx - endx <= 1))
            result = 1;
        
        
        return result;
    }
    int recursive_empty(char maze[400][400], int nowx,int nowy,int width,int height)
    {
        int counter = 0;
        
        if (maze[nowx - 1][ nowy] - '#' == 0)
            counter++;
        
        if (maze[nowx + 1][ nowy] - '#' == 0)
            counter++;
        
        if (maze[nowx][ nowy + 1] - '#' == 0)
            counter++;
        
        if (maze[nowx][ nowy - 1] - '#' == 0)
            counter++;
        
        if (counter == 3)
        {
            maze[nowx][ nowy] = '.';
            int direction = rand()%4;
            switch(direction)
            {
                case 0:
                    if (nowx > 2)
                        nowx--;
                    else
                    {
                        return 1;
                    }
                    break;
                case 1:
                    if (nowy > 2)
                        nowy--;
                    else
                    {
                        return 1;
                    }
                    break;
                case 2:
                    if (nowx < height - 2)
                        nowx++;
                    else
                    {
                        return 1;
                    }
                    break;
                case 3:
                    if (nowy < width - 2)
                        nowy++;
                    else
                    {
                        return 1;
                    }
                    break;
                    
            }
            recursive_empty(maze, nowx, nowy, width, height);
            return 1;
        }
        return 0;
    }
    int isempty(char maze[400][400], int nowx, int nowy, int width, int height)
    {
        int counter = 0;
        
        if (maze[nowx - 1][ nowy] - '#' == 0)
            counter++;
        
        if (maze[nowx + 1][ nowy] - '#' == 0)
            counter++;
        
        if (maze[nowx][ nowy + 1] - '#' == 0 )
            counter++;
        
        if (maze[nowx][ nowy - 1] - '#' == 0)
            counter++;
        
        if (counter == 3)
        {
            maze[nowx][ nowy] = '.';
            return 1;
        }
        
        return 0;
    }
    
    int wayerror(int label[4])
    {
        int sum = 0;
        for (int i = 0; i < 4; i++)
            sum += label[i];
        if (sum == -4)
            return 1;
        else
            return 0;
    }
    void digdoor(char maze[400][400],int stx,int sty,int mazeheight,int mazewidth)
    {
        if (stx == 0)
            stx += 1;
        if (stx == mazeheight - 1)
            stx -= 1;
        if (sty == 0)
            sty += 1;
        if (sty == mazewidth - 1)
            sty -= 1;
        
        maze[stx][ sty] = '.';
    }
    void connect(char maze[400][400],int startx,int starty,int endx,int endy,int height,int width,int tower=100)
    {
        tower--;
        if (tower < 0)
            return;
        if (startx - endx > -2 && startx - endx < 2 && starty - endy > -2 && starty - endy < 2)
        {
            int way_right = 0;
            if (startx > 0 && startx < height - 1 && starty > 0 && starty < width - 1)
                if (maze[startx - 1][ starty] != '.' || maze[startx + 1][ starty] != '.' || maze[startx][ starty - 1] != '.' ||maze[startx][starty+1]!='.')
                {
                    maze[startx][ starty] = '.';
                    way_right++;
                }
            
            if(endx>0&&endx<height-1&&endy>0&&endy<width-1)
                if (maze[endx - 1][ endy] != '.' || maze[endx + 1][ endy] != '.' || maze[endx][ endy - 1] != '.' || maze[endx][ endy + 1] != '.')
                {
                    maze[endx][ endy] = '.';
                    way_right++;
                }
            if(way_right==2)
            {
                maze[starty][ endx] = '.';
                maze[startx][ endy] = '.';
            }
            
            return;
        }
        
        int midx = (startx+endx) / 2+  rand()%3-1;
        if (midx < 1)
            midx = 1;
        if (midx > height - 2)
            midx = height - 2;
        int midy = (starty+endy) / 2+rand()%3-1;
        if (midy > width - 2)
            midy = width - 2;
        if (midy < 1)
            midy = 1;
        
        connect(maze, startx, starty, midx, midy, height, width,tower-1);
        connect(maze, midx, midy, endx, endy, height, width,tower-1);
        return;
    }
    void copymaze(char maze[400][400],char extmaze[400][400],int size = 500)
    {
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
            {
                maze[i][ j] = extmaze[i][ j];
            }
    }
    void generatemaze(char maze[400][400], char answer[400][400], int mazeheight, int mazewidth)
    {
        int i, k;
        int startpoint [2][ 2];
        int oop;
        
        for (i = 0; i < mazeheight; i++)
            for (k = 0; k < mazewidth; k++)
            {
                maze[i][ k] = '#';
            }
        int widrandom, heightrandom;
        widrandom = mazewidth - 3;
        heightrandom = mazeheight - 3;
        int startwhere;
        
        int firstland = 2;
        for (oop = 0; oop < 2; oop++)
        {
            if (oop == 0)
            {
                startwhere = rand() % 4;
                firstland = startwhere;
            }
            else
            {
                if (firstland == 1 || firstland == 0)
                    startwhere = firstland + 2;
                else startwhere = firstland - 2;
            }
            
            switch (startwhere)
            {
                case 0:
                    startwhere = rand() % widrandom + 2;
                    maze[0][ startwhere] = '.';
                    startpoint[oop][ 0] = 0;
                    startpoint[oop][ 1] = startwhere;
                    break;
                case 1:
                    startwhere = rand() % heightrandom + 2;
                    maze[startwhere][ mazewidth - 1] = '.';
                    startpoint[oop][ 0] = startwhere;
                    startpoint[oop][ 1] = mazewidth - 1;
                    break;
                case 2:
                    startwhere = rand() % widrandom + 2;
                    maze[mazeheight - 1][ startwhere] = '.';
                    startpoint[oop][ 0] = mazeheight - 1;
                    startpoint[oop][ 1] = startwhere;
                    break;
                case 3:
                    startwhere = rand() % heightrandom + 2;
                    maze[startwhere][ 0] = '.';
                    startpoint[oop][ 0] = startwhere;
                    startpoint[oop][ 1] = 0;
                    break;
            }
            if (startpoint[1][ 0] == startpoint[0][ 0] && startpoint[1][ 1] == startpoint[1][ 1])
                oop = 0;
            if(oop == 1)
            {
                if((startpoint[0][0]-startpoint[1][0]> -mazeheight/2.5f&& startpoint[0][ 0] - startpoint[1][ 0] < mazeheight / 2.5f) || (startpoint[0][ 1] - startpoint[1][1] > -mazewidth / 2.5f && startpoint[0][ 1] - startpoint[1][ 1] < mazewidth / 2.5f))
                {
                    oop = 0;
                }
            }
        }
        maze[startpoint[0][ 0]][ startpoint[0][ 1]] = 'S';
        maze[startpoint[1][ 0]][ startpoint[1][ 1]] = 'E';
        int midingx =  rand()%(mazeheight-1)+1;
        int midingy = rand()%(mazewidth-1)+1;
        while (((startpoint[0][ 0] - midingx) * (startpoint[0][ 0] - midingx) + (startpoint[0][1] - midingy) * (startpoint[0][ 1] - midingy) < mazewidth*mazewidth/7 + mazeheight*mazeheight/7)
               || ((startpoint[1][ 0] - midingx) * (startpoint[1][ 0] - midingx) + (startpoint[1][ 1] - midingy) * (startpoint[1][ 1] - midingy) < mazewidth * mazewidth/7 + mazeheight * mazeheight/7))
        {
            midingx = rand()%(mazeheight-1) + 1;
            midingy = rand()%(mazewidth-1) + 1;
        }
        
        connect(maze, startpoint[0][ 0], startpoint[0][ 1], midingx, midingy,mazeheight,mazewidth,mazewidth*mazeheight/10);
        connect(maze, midingx, midingy, startpoint[1][ 0], startpoint[1][ 1],mazeheight, mazewidth, mazewidth * mazeheight / 10);
        for (int di = 2; di < mazeheight - 2; di++)
            for (int j = 2; j < mazewidth - 2; j++)
            {
                int adder = 0;
                for (int ei = di - 1; ei < di + 2; ei++)
                    for (int ej = j - 1; ej < j + 2; ej++)
                    {
                        if (maze[ei][ ej] == '.')
                            adder++;
                        
                    }
                if (adder > 7)
                {
                    maze[di][ j] = '#';
                    if (answer[di][ j] == '1')
                        answer[di][ j] = '0';
                }
                
            }
        //start ...
        int stx, sty;
        stx = startpoint[0][ 0];
        sty = startpoint[0][ 1];
        digdoor(maze, stx, sty, mazeheight, mazewidth);
        digdoor(maze, startpoint[1][ 0], startpoint[1][ 1], mazeheight, mazewidth);
        //......fill now
        
        int endx, endy;
        endx = startpoint[1][ 0];
        endy = startpoint[1][ 1];
        maze[endx][ endy] = '.';
        
        
        for (i = 1; i < mazeheight - 1; i++)
            for (k = 1; k < mazewidth - 1; k++)
            {
                if (maze[i][ k] == '.')
                {
                    answer[i][ k] = '1';
                }
            }
        long toyoo = mazeheight*mazewidth*100;
        while (toyoo > 0)
        {
            i = rand() % (mazeheight - 2) + 1;
            k = rand() % (mazewidth - 2) + 1;
            int symbolu = recursive_empty(maze, i, k, mazewidth, mazeheight);
            
            if(symbolu==0)
                if (rand()%150==1)
                {
                    maze[i][ k] = '.';
                }
            
            toyoo--;
        }
        for (int p = 0; p < mazeheight * mazewidth /10; p++)
        {
            int ox = rand() % (mazeheight - 2) + 1;
            int oy = rand() % (mazewidth - 2) + 1;
            if (maze[ox - 1][ oy] == '.' && maze[ox + 1][ oy] == '.')
                maze[ox][ oy] = '.';
            if (maze[ox][ oy - 1] == '.' && maze[ox][ oy + 1] == '.')
                maze[ox][ oy] = '.';
            if (maze[ox - 1][ oy-1] == '.' && maze[ox + 1][ oy+1] == '.')
                maze[ox][ oy] = '.';
            if (maze[ox+1][ oy - 1] == '.' && maze[ox-1][ oy + 1] == '.')
                maze[ox][ oy] = '.';
            
        }
        for (int di = 2; di < mazeheight - 2; di++)
            for (int j = 2; j < mazewidth - 2; j++)
            {
                int adder = 0;
                for (int ei = di - 1; ei < di + 2; ei++)
                    for (int ej = j - 1; ej < j + 2; ej++)
                    {
                        if (maze[ei][ ej] == '.')
                            adder++;
                        
                    }
                if (answer[di][ j] == '1')
                    continue;
                if (adder > 7)
                {
                    maze[di][ j] = '#';
                }
                if (adder == 7)
                {
                    int ox = di;
                    int oy = j;
                    if (maze[ox - 1][ oy] == '#' && maze[ox + 1][ oy] == '#')
                        continue;
                    if (maze[ox][ oy - 1] == '#' && maze[ox][ oy + 1] == '#')
                        continue;
                    if (maze[ox - 1][ oy - 1] == '#' && maze[ox + 1][ oy + 1] == '#')
                        continue;
                    if (maze[ox + 1][ oy - 1] == '#' && maze[ox - 1][ oy + 1] == '#')
                        continue;
                    
                    maze[di][ j] = '#';
                    
                    
                }
                
            }
        maze[startpoint[0][0] ][ startpoint[0][1]] = 'S';
        maze[startpoint[1][0] ][ startpoint[1][1]] = 'E';
    }
    
};

#endif /* mazegenerator_h */
