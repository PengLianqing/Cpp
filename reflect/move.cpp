/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       move.cpp
  * @brief      移动构造
  *             g++ move.cpp -fno-elide-constructors 关闭返回值优化
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
#include <cstring>
#include <vector>
using namespace std;

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

/*
    移动构造是直接将自己的指针指向了拷贝对象的资源。
    std::move()方法来将左值转换为右值，使编译器对左值使用移动构造。
*/

// 传入右值 , 调用移动构造函数
void test1(){
    vector<MyString> vecStr;
    MyString::CCtor = 0;
    MyString::MCtor = 0;
    MyString::CAsgn = 0;
    MyString::MAsgn = 0;
    vecStr.reserve(1000); //先分配好1000个空间
    for(int i=0;i<1000;i++){
        vecStr.push_back(MyString("hello"));
    }
    cout << "传入右值:" << endl;
    cout << "CCtor = " << MyString::CCtor << endl;
    cout << "MCtor = " << MyString::MCtor << endl;
    cout << "CAsgn = " << MyString::CAsgn << endl;
    cout << "MAsgn = " << MyString::MAsgn << endl;
}

// 传入左值 , 调用拷贝构造函数
void test2(){
    vector<MyString> vecStr;
    MyString::CCtor = 0;
    MyString::MCtor = 0;
    MyString::CAsgn = 0;
    MyString::MAsgn = 0;
    vecStr.reserve(1000); //先分配好1000个空间
    for(int i=0;i<1000;i++){
        MyString temp( "hello" );
        vecStr.push_back( temp );
    }
    cout << "传入左值:" << endl;
    cout << "CCtor = " << MyString::CCtor << endl;
    cout << "MCtor = " << MyString::MCtor << endl;
    cout << "CAsgn = " << MyString::CAsgn << endl;
    cout << "MAsgn = " << MyString::MAsgn << endl;
}

// std::move , 强制调用移动构造函数
void test3(){
    vector<MyString> vecStr;
    MyString::CCtor = 0;
    MyString::MCtor = 0;
    MyString::CAsgn = 0;
    MyString::MAsgn = 0;
    vecStr.reserve(1000); //先分配好1000个空间
    for(int i=0;i<1000;i++){
        MyString temp( "hello" );
        vecStr.push_back( std::move(temp) );
    }
    cout << "传入std::move:" << endl;
    cout << "CCtor = " << MyString::CCtor << endl;
    cout << "MCtor = " << MyString::MCtor << endl;
    cout << "CAsgn = " << MyString::CAsgn << endl;
    cout << "MAsgn = " << MyString::MAsgn << endl;
}

/*
    完美转发：
    通过一个函数将参数继续转交给另一个函数进行处理，如果还能继续保持参数的原有特征，就是完美转发。
    使用通用引用类型和std::forward()模板函数共同实现完美转发。
*/
void RunCode(int &&m) {
    cout << "rvalue ref" << endl;
}
void RunCode(int &m) {
    cout << "lvalue ref" << endl;
}
void RunCode(const int &&m) {
    cout << "const rvalue ref" << endl;
}
void RunCode(const int &m) {
    cout << "const lvalue ref" << endl;
}

// 这里用了通用引用，如果写T&,就不支持传入右值，而写T&&，既能支持左值，又能支持右值
template<typename T>
void perfectForward(T && t) {
    RunCode(forward<T> (t));
}

template<typename T>
void notPerfectForward(T && t) {
    RunCode(t);
}

void test4()
{
    int a = 0;
    int b = 0;
    const int c = 0;
    const int d = 0;

    notPerfectForward(a); // lvalue ref
    notPerfectForward(move(b)); // lvalue ref
    notPerfectForward(c); // const lvalue ref
    notPerfectForward(move(d)); // const lvalue ref

    cout << endl;
    perfectForward(a); // lvalue ref
    perfectForward(move(b)); // rvalue ref
    perfectForward(c); // const lvalue ref
    perfectForward(move(d)); // const rvalue ref
}

int main()
{
   test1();
   test2();
   test3();
   test4();
}
