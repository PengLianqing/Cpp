/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       pointer.cpp
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
  * @brief          指针测试函数
  */
int *addition(int x,int y){ //指针函数
    int *sum=new int(x+y);
    return sum;
}

int subtraction(int x,int y){
    return x-y;
}

int operation(int x,int y,int (*func)(int,int)){ //调用函数指针
    return (*func)(x,y);
}

void pointerTest(){
    //指针
    int x=128;
    int *p1=&x; //指针和值都可以修改
    const int *p2=&x; //指针可以修改，值不可以修改
    int *const p3=&x; //指针不可以修改，但是值可以修改
    const int *const p4=&x; //指针和数据都不可以修改
    cout<<*p1<<","<<*p2<<","<<*p3<<","<<*p4<<endl;

    int *s=addition(2, 3); //指针函数 返回值为指针的函数
    cout<<*s<<endl;

    int (*minus)(int,int) = subtraction; //函数指针 指向函数的指针
    int n=operation(3,*s,minus); 
    cout<<n<<endl;
}

int main()
{
    pointerTest();
    cout<<"all done."<<endl;
    return 0;
}

