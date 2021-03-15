/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       right_quoto.cpp
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
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>


using namespace std;

/**
  * @brief          right_quoto test 
  */
class Copyable{
    public:
        Copyable(int n):n(n) {};

        Copyable(const Copyable &c){ // 常量左值引用的拷贝构造函数
            cout << "copy" << endl;
        }

        int n;
};

Copyable ReturnRval(){
    return Copyable(1); // 返回一个对象
}

void AcceptRval(Copyable c){
    cout << c.n << endl;
}

void AcceptRef(const Copyable& c) { // 常量左值引用
    cout << c.n << endl;
}

void right_quoto(){
    // 右值引用 &&
    int&& a = 1;
    int b = 1;
    int&& c = std::move(b); // std::move 将左值转化为右值
    cout<<"a:"<<a<<endl;
    cout<<"b:"<<b<<endl;
    cout<<"c:"<<c<<endl;

    // 常量左值引用
    AcceptRval( ReturnRval() );// 一次拷贝构造函数都没有用到
    AcceptRef( ReturnRval() ); // 一次拷贝构造函数都没有用到,编译器默认开启了返回值优化
}

/**
  * @brief          移动构造、移动赋值
  */
class MyString
{
public:
    static size_t CCtor; //统计调用拷贝构造函数的次数
    static size_t MCtor; //统计调用移动构造函数的次数
    static size_t CAsgn; //统计调用拷贝赋值函数的次数
    static size_t MAsgn; //统计调用移动赋值函数的次数

public:
    // 构造函数
   MyString(const char* cstr=0){
       if (cstr) {
          m_data = new char[strlen(cstr)+1];
          strcpy(m_data, cstr);
       }
       else {
          m_data = new char[1];
          *m_data = '\0';
       }
   }

   // 拷贝构造函数
   MyString(const MyString& str) {
       CCtor ++;
       m_data = new char[ strlen(str.m_data) + 1 ];
       strcpy(m_data, str.m_data);
   }

   // 移动构造函数
   MyString(MyString&& str) noexcept
       :m_data(str.m_data) {
       MCtor ++;
       str.m_data = nullptr; //不再指向之前的资源了
   }

   // 拷贝赋值函数 =号重载
   MyString& operator=(const MyString& str){
       CAsgn ++;
       if (this == &str) // 避免自我赋值!!
          return *this;

       delete[] m_data;
       m_data = new char[ strlen(str.m_data) + 1 ];
       strcpy(m_data, str.m_data);
       return *this;
   }

   // 移动赋值函数 =号重载
   MyString& operator=(MyString&& str) noexcept{
       MAsgn ++;
       if (this == &str) // 避免自我赋值!!
          return *this;

       delete[] m_data;
       m_data = str.m_data;
       str.m_data = nullptr; //不再指向之前的资源了
       return *this;
   }

   ~MyString() {
       delete[] m_data;
   }

   char* get_c_str() const { return m_data; }
private:
   char* m_data;
};

size_t MyString::CCtor = 0;
size_t MyString::MCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MAsgn = 0;

void move_test(){ // 移动构造、移动赋值测试
    vector<MyString> vecStr;
    vecStr.reserve(1000); //先分配好1000个空间
    for(int i=0;i<1000;i++){
        vecStr.push_back(MyString("hello"));
    }
    cout << "CCtor = " << MyString::CCtor << endl;
    cout << "MCtor = " << MyString::MCtor << endl;
    cout << "CAsgn = " << MyString::CAsgn << endl;
    cout << "MAsgn = " << MyString::MAsgn << endl;
}

int main()
{
    right_quoto();
    move_test();
    cout << "all done." << endl;
    return 0;
}

