/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       poly.cpp
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
  * @brief          多态测试
  */
class A{
    public:
        virtual void func() //父类函数前面加上virtual关键字，变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
        {
            cout << "A virtual func." << endl;
        }
};

class B:public A{
    public:
        void func()  //void func()/virtual void func()均可。
        {
            cout << "B func." << endl;
        }
};

//C++允许父类和子类之间的类型转换
//我们希望传入什么对象，那么就调用什么对象的函数
//如果函数地址在编译阶段就能确定，那么静态联编
//如果函数地址在运行阶段才能确定，就是动态联编
void functest(A &a){
    a.func();
}

int main(){
    A a;
    functest(a); //A virtual func.

    //如果不加virtual，会执行父类中的speak函数
    //加入virtual，会执行子类中的speak函数
    //当父类的指针或引用指向子类对象时，发生多态
    B b;
    functest(b); //B func.

    return 0;
}