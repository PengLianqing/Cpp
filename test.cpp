#include <iostream>
#include <vector>
using namespace std;
int num = 0;
void dfs( int y,int x,int ysize,int xsize,int pos,int length,vector<int> &rodey,vector<int> &rodex){

    rodey[pos] = y;
    rodex[pos] = x;

    if(y<=0&&x>=xsize-1){
        for(int i=0;i<length;i++){
            cout<<"y:"<<rodey[i]<<"x:"<<rodex[i]<<";    ";
        }
        cout<<endl;
        ++num;
    }
    
    if(y-1>=0) dfs(y-1,x,ysize,xsize,pos+1,length,rodey,rodex);
    if(x+1<xsize) dfs(y,x+1,ysize,xsize,pos+1,length,rodey,rodex);
}
// 时间复杂度计算公式
// 优化解法
// linux命令，查看僵尸线程，查看端口，结果筛选，命令脚本；
// epoll、select底层原理与实现
// C++11新功能，auto
// 编译


// n*m 
// 左下角，往上和往右走，输出所有的可能的路径
void solution(){
    int n = 4 ,m = 5;
    int ysize = n;
    int xsize = m;
    int length = m+n-1;
    int pos = 0;
    vector<int> rodey(length,0) ,rodex(length,0);
    // 3,0 -> 0,4
    dfs(3,0,ysize,xsize,pos,length,rodey,rodex);
    cout<<num<<endl;
    cout << "all done" << endl;
}


int main()
{
    solution();
    std::cout << "Hello world" << std::endl;
    return 0;
}

