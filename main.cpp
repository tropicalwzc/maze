//
//  main.cpp
//  mazesearch
//
//  Created by 王子诚 on 2019/11/16.
//  Copyright © 2019 王子诚. All rights reserved.
//
#include "mazegenerator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

const string filepath = "/Users/tropical_fish/Desktop/Xcode_workplace/mazesearch/mazesearch/MazeData.txt";

vector<string>mapper;
long st_x,st_y,ed_x,ed_y,W,H;
int next_maxdp;
int mymazeH,mymazeW;
char mazerecev[400][400]={};
char answer[400][400]={};
int realmap[400][400]={};
long long clk = 0;
int maxdep = 0;
vector<pair<int, int> >storage[10000];
vector<pair<int, int> >path;
bool vist[400][400]={};
vector<long long>fooluse;
vector<long long>smartuse;

void read_from_mymaze_mapper()
{
    long len=mapper.size();
    long lc = mapper[0].size();
    H=len;
    W=lc;
    cout<<"h "<<len<<" w "<<lc<<endl;
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<lc;j++)
        {
            if(mapper[i][j]=='#')
            {
                realmap[i][j]=1;
            }
            else if(mapper[i][j]=='.')
            {
                realmap[i][j]=0;
            }
            else{
                if(mapper[i][j]=='S')
                {
                    realmap[i][j]=10;
                    st_x=i;
                    st_y=j;
                }
                if(mapper[i][j]=='E')
                {
                    realmap[i][j]=-10;
                    ed_x=i;
                    ed_y=j;
                }
            }
        }
    }
}

void save_mymaze_to_mapper()
{
    mapper.clear();
    for(int i=0;i<mymazeH;i++)
    {
        string mc="";
        for(int j=0;j<mymazeW;j++)
        {
            mc+=mazerecev[i][j];
        }
        mapper.push_back(mc);
    }
}

void read_from_mapper()
{
    long len=mapper.size();
    long lc = mapper[0].size();
    H=len;
    W=lc;
    cout<<"h "<<len<<" w "<<lc<<endl;
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<lc;j++)
        {
            if(mapper[i][j]=='1')
            {
                realmap[i][j]=1;
            }
            else if(mapper[i][j]=='0')
            {
                realmap[i][j]=0;
            }
            else{
                if(mapper[i][j]=='S')
                {
                    realmap[i][j]=10;
                    st_x=i;
                    st_y=j;
                }
                if(mapper[i][j]=='E')
                {
                    realmap[i][j]=-10;
                    ed_x=i;
                    ed_y=j;
                }
            }
        }
    }
}
void read_from_file()
{
    ifstream reader(filepath,ios::in);
    if(!reader)
    {
        cout<<"open error"<<endl;
        return;
    }
    mapper.clear();
    string s = "";
    while (getline(reader,s))
    {
        mapper.push_back(s);
    }
}




void init()
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            vist[i][j]=false;
        }
    }
    path.clear();
}
struct direction{
    int x;
    int y;
    int gxval;
    operator int()const{
        return gxval;
    }
    direction(int xx,int yy){
        x=xx;
        y=yy;
        gxval = abs(x-ed_x)+abs(y-ed_y);
    }
};
int gx(int x,int y)
{
    return abs(x-ed_x)+abs(y-ed_y);
}
int smartdp(int nx,int ny,int step)
{
    clk++;
    vist[nx][ny]=true;
    if(realmap[nx][ny]==-10)
    {
        vist[nx][ny]=false;
        return 1;
    }
    int estimateval = step+gx(nx, ny);
    if(estimateval>maxdep) // fx = hx + gx
    {
        if(next_maxdp==maxdep)
        {
            next_maxdp =estimateval;
        }
        else{
            next_maxdp = min(next_maxdp,estimateval);
        }
        vist[nx][ny]=false;
        return 0;
    }
    int nxa1 = nx+1;
    int nxm1 = nx-1;
    int nya1 = ny+1;
    int nym1 = ny-1;
    vector<direction>visit_order;
    int res;
    
    if(ny>0){
        if(!vist[nx][nym1]&&realmap[nx][nym1]!=1)
        {
            visit_order.push_back(direction(nx,nym1));
        }
    }
    if(ny<W){
        if(!vist[nx][nya1]&&realmap[nx][nya1]!=1)
        {
            visit_order.push_back(direction(nx,nya1));
        }
    }
    
    if(nx>0){
        if(!vist[nxm1][ny]&&realmap[nxm1][ny]!=1)
        {
            visit_order.push_back(direction(nxm1,ny));
        }
    }
    if(nx<H){
        if(!vist[nxa1][ny]&&realmap[nxa1][ny]!=1)
        {
            visit_order.push_back(direction(nxa1,ny));
        }
    }
    sort(visit_order.begin(), visit_order.end());
    for(vector<direction>::iterator it = visit_order.begin();it!=visit_order.end();it++){
        res = smartdp(it->x, it->y, step+1);
        if(res == 1)
        {
            vist[nx][ny]=false;
            path.push_back(pair<int, int>(nx,ny));
            return 1;
        }
    }
    
    vist[nx][ny]=false;
    return 0;
}


int dp(int nx,int ny,int step)
{
    clk++;
    vist[nx][ny]=true;
    if(realmap[nx][ny]==-10)
    {
        vist[nx][ny]=false;
        return 1;
    }
    if(step>=maxdep)
    {
        vist[nx][ny]=false;
        return 0;
    }
    int nxa1 = nx+1;
    int nxm1 = nx-1;
    int nya1 = ny+1;
    int nym1 = ny-1;
    set<direction>visit_order;
    int res;

    if(nx>0){
        if(!vist[nxm1][ny]&&realmap[nxm1][ny]!=1)
        {
            res= dp(nxm1, ny,step+1);
            if(res==1)
            {
                path.push_back(pair<int, int>(nx,ny));
                return 1;
            }
        }
    }
    if(nx<H){
        if(!vist[nxa1][ny]&&realmap[nxa1][ny]!=1)
        {
            res= dp(nxa1,ny,step+1);
            if(res==1)
            {
                path.push_back(pair<int, int>(nx,ny));
                return 1;
            }
        }
    }
    if(ny>0){
        if(!vist[nx][nym1]&&realmap[nx][nym1]!=1)
        {
            res= dp(nx,nym1,step+1);
            if(res==1)
            {
                path.push_back(pair<int, int>(nx,ny));
                return 1;
            }
        }
    }
    if(ny<W){
        if(!vist[nx][nya1]&&realmap[nx][nya1]!=1)
        {
            res= dp(nx,nya1,step+1);
            if(res==1)
            {
                path.push_back(pair<int, int>(nx,ny));
                return 1;
            }
        }
    }

    vist[nx][ny]=false;
    return 0;
}

int bfs(int current_depth)
{
    vector<pair<int, int> >lastnodes = storage[current_depth-1];
    long totalnodes = lastnodes.size();
    for(int i=0;i<totalnodes;i++)
    {
        int nx = lastnodes[i].first;
        int ny = lastnodes[i].second;

        int nxa1 = nx+1;
        int nxm1 = nx-1;
        int nya1 = ny+1;
        int nym1 = ny-1;
        if(nx>0){
            if(!vist[nxm1][ny]&&realmap[nxm1][ny]!=1)
            {
                storage[current_depth].push_back(pair<int, int>(nxm1,ny));
                vist[nxm1][ny]=true;
                if(realmap[nxm1][ny]==-10)
                {
                    return 1;
                }
            }
        }
        if(nx<H){
            if(!vist[nxa1][ny]&&realmap[nxa1][ny]!=1)
            {
                storage[current_depth].push_back(pair<int, int>(nxa1,ny));
                vist[nxa1][ny]=true;
                if(realmap[nxa1][ny]==-10)
                {
                    return 1;
                }
            }
        }
        if(ny>0){
            if(!vist[nx][nym1]&&realmap[nx][nym1]!=1)
            {
                storage[current_depth].push_back(pair<int, int>(nx,nym1));
                vist[nx][nym1]=true;
                if(realmap[nx][nym1]==-10)
                {
                    return 1;
                }
            }
        }
        if(ny<W){
            if(!vist[nx][nya1]&&realmap[nx][nya1]!=1)
            {
                storage[current_depth].push_back(pair<int, int>(nx,nya1));
                vist[nx][nya1]=true;
                if(realmap[nx][nya1]==-10)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
void display_map()
{
    int len=mapper.size();
    int lc = mapper[0].size();

    for(int i=0;i<len;i++)
    {
        for(int j=0;j<lc;j++)
        {
            if(mapper[i][j]=='1')
            {
                cout<<"#";
            }
            else if(mapper[i][j]=='0')
            {
                cout<<".";
            }
            else if(mapper[i][j]=='p'){
                cout<<"-";
            }
            else if(mapper[i][j]=='q'){
                cout<<"|";
            }
            else{
                cout<<mapper[i][j];
            }
        }
        cout<<endl;
    }
}
void output_path()
{
    for(int i=0;i<path.size()-1;i++)
    {
        cout<<"("<<path[i].first<<","<<path[i].second<<")";
        mapper[path[i].first][path[i].second]='p';
        if(i>1)
        {
            if(path[i-1].second==path[i+1].second)
            {
                mapper[path[i].first][path[i].second]='q';
            }
            if(abs(path[i-1].first-path[i+1].first)==1&&abs(path[i-1].second-path[i+1].second))
            {
                mapper[path[i].first][path[i].second]='o';
            }
        }
    }
    cout<<endl;
    display_map();
}
void bfs_test()
{
    read_from_file();
    init();
    for(int i=0;i<100;i++)
        storage[i].clear();
    
    int dpl = 1;
    for(dpl=1;dpl<200;dpl++)
    {
        int res = bfs(dpl);
        if(res == 1)
        {
            cout<<"bfs found result in "<<dpl<<" steps "<<endl;
            break;
        }
    }
    for(int j=0;j<dpl;j++)
    {
        long lc = storage[j].size();
        for(int p=0;p<lc;p++)
        {
            cout<<storage[j][p].first<<","<<storage[j][p].second<<" | ";
        }
        cout<<endl;
    }
}
void init_the_map(int option)
{
    if(option==0)
    {
        read_from_file();
        read_from_mapper();
    }
    else{
        save_mymaze_to_mapper();
        read_from_mymaze_mapper();
    }
    path.clear();
}
void generate_my_maze(int hh,int ww)
{
    mymazeH = hh;
    mymazeW = ww;
    mazegenerate gener;
    gener.generatemaze(mazerecev, answer, mymazeH, mymazeW);
}
void fast_test_fool()
{
    clk=0;
    for(maxdep=0;maxdep<200;maxdep++)
    {
        init();
        int res = dp(st_x, st_y, 0);
        if(res == 1)
            break;
    }
    fooluse.push_back(clk);
    output_path();
}
void foolidea()
{
    clk=0;
    cout<<endl;
    for(maxdep=0;maxdep<200;maxdep++)
    {
        cout<<" "<<maxdep;
        init();
        int res = dp(st_x, st_y, 0);
        if(res == 1)
            break;
    }
    cout<<endl;
    cout<<"迭代加深 total searched "<<clk<<" nodes "<<endl;
    cout<<"need steps "<<maxdep<<endl;
    output_path();
    cout<<endl;
}
void fast_test_smart()
{
    clk = 0; //重新计数
    next_maxdp=0;
    for(maxdep = 0;maxdep<1000;maxdep=next_maxdp)
    {
        cout<<maxdep<<" ";
        init();
        int res = smartdp(st_x, st_y, 0);
        if(res == 1)
            break;
        if(next_maxdp == maxdep)
        {
            cout<<"no answer"<<endl;
            break;
        }
    }
    smartuse.push_back(clk);
    output_path();
}
void smartidea()
{
    cout<<endl;
    clk = 0; //重新计数
    next_maxdp=0;
    for(maxdep = 0;maxdep < 1000;maxdep=next_maxdp)
    {
        cout<<maxdep<<" ";
        init();
        int res = smartdp(st_x, st_y, 0);
        if(res == 1)
            break;
        if(next_maxdp == maxdep)
        {
            cout<<"no answer"<<endl;
            break;
        }
    }
    cout<<endl;
    cout<<"IDA* total searched "<<clk<<" nodes "<<endl;
    cout<<"need steps "<<maxdep<<endl;
    output_path();
}
void org_test()
{
    init_the_map(0);
    foolidea();
    init_the_map(0);
    smartidea();
}
int main(int argc, const char * argv[]) {
    // insert code here...
    org_test();
    
    srand(unsigned(time(NULL)));
    for(int i=0;i<1;i++)
    {
        cout<<endl<<"test "<<i<<endl;
        generate_my_maze(40, 60);
       // init_the_map(1);
       // fast_test_fool();
        init_the_map(1);
        display_map();
        fast_test_smart();
    }
    cout<<endl;
    for(int j=0;j<1;j++)
    {
        cout<<smartuse[j]<<endl;
    }

    return 0;
}
