/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       para.cpp
  * @brief      
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Jan-1-2021      Peng            1. 完成
  *
  @verbatim
  ==============================================================================
  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2021 Peng****************************
  */
#include <iostream>

using namespace std;

/**
  * @brief          test1(int a ,int b=10 ,int c=100)
  * 默认参数
  */
void test1(int a ,int b=10 ,int c=100)
{
    cout<<"a:"<<a<<endl;
    cout<<"b:"<<b<<endl;
    cout<<"c:"<<c<<endl;
}

/**
  * @brief          test2(int a ,int ,int)
  *                 test2(int a ,int ,int=10)
  * 占位参数：为了以后程序扩展留下线索，同时兼容c的不规范写法
  */
void test2(int a ,int ,int)
{
    cout<<"a:"<<a<<endl;
}
int main(void)
{
    test1(1);
    test1(1, 1, 1);

    test2(1);
    test2(1, 1, 1);
    return 0;
}