/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       quoto.cpp
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
#include <list>

using namespace std;

/**
  * @brief          quoto_t test class
  */
class quoto_t{
public:
    
};
quoto_t recursion;

void test1(void)
{
    int a = 0;
    int b = 1;
    //初始化c为a的引用，c与a名字不同，地址相同
    //不可以 int &c;引用必须初始化
    int &c = a;
    cout << "a=" << a << ",b=" << b << ",c=" << c << endl;
    cout << "int &c = a:" << c << endl;

    //将c引用的a赋值为b
    c = b;
    cout << "a=" << a << ",b=" << b << ",c=" << c << endl;
    cout << "c = b:" << c << endl;
}

/**
  * @brief          mswap1(a, b); 值传递（无效）
  */
void mswap1(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

/**
  * @brief          mswap2(&a, &b); 地址传递
  */
void mswap2(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
  * @brief          mswap3(a, b); 引用传递
  */
void mswap3(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void test2(void)
{
    //值传递
    int a=10,b=20;
    mswap1(a, b);
    cout << "值传递:"
         << "a=" << a << ",b=" << b << endl;

    //地址传递
    a=10,b=20;
    mswap2(&a, &b);
    cout << "地址传递:"
         << "a=" << a << ",b=" << b << endl;

    //引用传递
    a=10,b=20;
    mswap3(a, b);
    cout << "引用传递:"
         << "a=" << a << ",b=" << b << endl;
}

/**
  * @brief         int& test3(void) 不可以返回局部变量的引用
  */
// int& test3(void)
// {
//     int aa=10;
//     return aa;
// }

/**
  * @brief         int& test4(void) 可以返回静态变量的引用
  */
int& test4(void)
{
    static int aa=10;
    return aa;
}

/**
  * @brief         const int &做形参
  */
void test5(const int & a)
{
    //a = -1;  //increment of read-only reference 'ref'
    cout<<"const int & a:"<<a<<endl;
    return;
}
int main()
{
    test1();
    test2();

    //int &ref1 = test3();
    int &ref2 = test4();
    //cout<<"ref1:"<<ref1<<endl;
    cout<<"ref2:"<<ref2<<endl;
    test4() = 1000;
    cout<<"ref2:"<<ref2<<endl;

    //const int &
    const int &ref = 10;
    cout<<ref<<endl;
    //cout<<ref++<<","<<ref<<endl; //increment of read-only reference 'ref'

    //const int &做形参
    int res = 10;
    test5(res);
}