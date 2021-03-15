#include <iostream>

#include <vector>
#include <string.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        // 任意两个皇后都不能处于同一条横行、纵行或斜线上
        // 迭代，使用bisited矩阵记录元素、横行、纵行、斜线
        vector<vector<string>> ans;
        vector<string> temp(n,string(n,'.'));
        return ans;
    } 
};

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

