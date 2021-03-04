/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       inherit.cpp
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
  * @brief          继承测试
  */
class A{
    public:
        int x;

        void func(){
            cout << "A func()." << endl;
        }

        void func(int x){
            cout << "A func(int x)." << endl;
        }

    protected:
        int y;
    private:
        int z;
};

/**
  * @brief          public继承
  */
//继承中:先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反
class B:public A{
    public:
        int b;
        void func()
        {
            x = 10; //public x;
            y = 5; //protected y;
            //z = 3;  //z不可访问
            cout << "x=" << x << "; y=" << y << ";" << endl;
        }
};

/**
  * @brief          protected继承
  */
class C:protected A{
    public:
        int c;
        void func()
        {
            x = 10; //protected x;
            y = 5; //protected y;
            //z = 3;  //z不可访问
            cout << "x=" << x << "; y=" << y << ";" << endl;
        }
};

/**
  * @brief          private继承
  */
class D:private A{
    public:
        int d;
        void func()
        {
            x = 10; //private x;
            y = 5; //private y;
            //z = 3;  //z不可访问
            cout << "x=" << x << "; y=" << y << ";" << endl;
        }
};

/**
  * @brief          继承多个基类
  */
class E{
    public:
        int m;
        int n;
};
class F:public A,public E{
    public:
        void func(){
            x = 1;
            y = 2;
            m = 1;
            n = 2;
            cout << "A:x=" << x << "; y=" << y << ";" << endl;
            cout << "F:m=" << m << "; n=" << n << ";" << endl;
        }
};

/**
  * @brief          菱形继承
  */
class G:virtual public A{
};
class H:virtual public A{
};
class I:public G,public H{
    public:
        void func(){
            x = 10;
            cout << "x " << x << " G::x " << G::x << " H::x " << H::x << endl;
            G::x = 11;
            cout << "x " << x << " G::x " << G::x << " H::x " << H::x << endl;
            H::x = 12;
            cout << "x " << x << " G::x " << G::x << " H::x " << H::x << endl;
        }
};

/**
  * @brief          继承测试
  * 两个派生类继承同一个基类，又有某个类同时继承两个派生类
  * 通过虚继承解决子类继承两份相同的数据导致的资源浪费问题。
  */
int main(){

    B b; 
    b.x = 6; //public x
    b.func();

    C c;
    //c.x = 2; //protected x
    c.func();

    D d;
    //d.x = 4; //private x
    d.func();

    //父类中非静态成员变量会被子类继承
    //父类中私有属性被编译器屏蔽，无法访问，但占有空间
    cout << "sizeof(A):" << sizeof(A) << endl; //12=3*int
    cout << "sizeof(B):" << sizeof(B) << endl; //16=3*int+int
    cout << "sizeof(C):" << sizeof(C) << endl; //16=3*int+int
    cout << "sizeof(D):" << sizeof(D) << endl; //16=3*int+int

    //同名函数处理
    b.func();
    //b.func(10); //子类会隐藏父类中所有版本的同名成员函数
    b.A::func();

    //继承多个类
    F f;
    f.func();

    //菱形继承
    I i;
    i.func();

    return 0;
}