/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       operator.cpp
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

class A{
    public:
        int x;
        int y;
        
        // /**
        //   * @brief          通过成员函数重载,与A operator+(A &a, A &b)作用相同
        //   */
        // A operator+(A &a)
        // {
        //     A temp;
        //     temp.x = this->x + a.x;
        //     temp.y = this->y + a.y;
        //     return temp;
        // }
        friend ostream &operator<<(ostream &out, A a);
        A &operator++();
        A operator++(int);
        A &operator=(int num);
};

/**
  * @brief          通过全局函数重载
  */
A operator+(A &a, A &b)
{
    A temp;
    temp.x = a.x + b.x;
    temp.y = a.y + b.y;
    return temp;
}

/**
  * @brief          重载运算符时的函数重载
  */
A operator+(A &a, int m)
{
    A temp;
    temp.x = a.x + m;
    temp.y = a.y + m;
    return temp;
}

/**
  * @brief          重载左移运算符
  * friend ostream &operator<<(ostream &out, A a); 在A中声明友元以访问private变量。
  */    
ostream &operator<<(ostream &out, A a) //此处使用A &a会报错，即cout<<c++<<会出问题.不可引用返回的局部变量
{
    out << "a.x:" << a.x << "; a.y:" << a.y << ";"; //支持链式编程
    return out;
}

/**
  * @brief          重载递增运算符 ++a;
  */
A& A::operator++(){
    x++;
    y++;
    return *this;
}

/**
  * @brief          重载递增运算符 a++;
  */
A A::operator++(int){
    A temp = *this;
    x++;
    y++;
    return temp;
}

/**
  * @brief          重载赋值运算符
  */
class B{
    public:
        int *x;

        B(int m)
        {
            x = new int(m);
        }

        ~B(){
            if(x!=NULL){
                delete x;
                x = NULL;
            }
        }

        B &operator=(B &b){ //重载赋值运算符
            //cout << "=运算符调用" << endl;
            if(x!=NULL){
                delete x;
                x = NULL;
            }
            x = new int(*b.x);
            return *this;
        }

        bool operator==(B &b);
        bool operator!=(B &b);
        void operator()(string text);
};

/**
  * @brief          重载关系运算符== !=
  */
bool B::operator==(B &b){
    if(*this->x == *b.x){
        return true;
    }
    else{
        return false;
    }
}

bool B::operator!=(B &b){
    if(*this->x == *b.x){
        return false;
    }
    else{
        return true;
    }
}

/**
  * @brief          重载函数调用运算符()
  */
void B::operator()(string text){
    cout << "operator():" << text << endl;
}

int main()
{
    A a;
    a.x = 1;
    a.y = 2;

    A b;
    b.x = 3;
    b.y = 4;

    A c = a + b; //通过全局函数重载
    cout << "c.x:" << c.x << endl;
    cout << "c.y:" << c.y << endl;

    A d = a + 4; //重载运算符时的函数重载
    cout << "d.x:" << d.x << endl;
    cout << "d.y:" << d.y << endl;

    cout << "重载<<运算符:" << c << endl; //重载左移运算符 a.x:4; a.y:6;

    cout << "重载++c运算符：" << ++c << "," << c << endl; //重载左移运算符 a.x:5; a.y:7;,a.x:5; a.y:7;
    cout << "重载c++运算符：" << c++ << "," << c << endl; //重载左移运算符 a.x:5; a.y:7;,a.x:6; a.y:8;

    B e(1);
    B f(2);
    f = e; //重载运算符=
    cout << "*f.x:" << *f.x << endl;
    cout << (f == e) << endl; //重载关系运算符==
    cout << (f != e) << endl; //重载关系运算符!=
 
    e("helloworld"); //重载函数调用运算符()

    return 0;
}