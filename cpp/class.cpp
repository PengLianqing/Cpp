/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       class.cpp
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
  * @brief          构造函数测试
  */
class A{
    public:
        int x;
        int y;
        A()
        {
            x = 1;
            y = 2;
            cout << "无参构造函数调用。" << endl;
        }

        A(int a, int b)
        {
            x = a;
            y = b;
            cout << "有参构造函数调用。" << endl;
        }

        A(const A& a)
        {
            x = a.x;
            y = a.y;
            cout << "拷贝构造函数调用。" << endl;
        }

        ~A()
        {
            cout << "析构函数调用。" << endl;
        }
};

/**
  * @brief          构造函数测试
  */
void test01(A a)
{
    return;
}

/**
  * @brief          构造函数测试
  */
A test02(void)
{
    A a(10 ,20);
    cout << "a" << (int *)&a << endl;
    return a;
}

/**
  * @brief          构造函数测试
  */
void testconstructor()
{
    cout << "A a(10 ,20);" << endl;
    A a(10 ,20);
    cout << "A b(a);" << endl;
    A b(a);
    cout << "A c = a;" << endl;
    A c = a;

    cout << "d = a;" << endl;
    A d;
    d = a; //赋值操作

    cout << "test01(a);" << endl;
    test01(a);
    
    cout << "A e = test02();" << endl;
    A e = test02(); 
    cout << "e" << (int *)&e << endl;
    cout << e.x << ";" << e.y << endl;
}

/**
  * @brief          浅拷贝、深拷贝测试
  */
class B{
public:
    int x;
    int *y;
    B(){
        x = 10;
        y = new int(20);
        cout << "无参构造函数调用。" << endl;
    }

    B(int a ,int b){
        x = a;
        y = new int(b);
        cout << "有参构造函数调用。" << endl;
    }

    B(const B& b){
        x = 1;
        y = new int(*b.y);
        cout << "拷贝构造函数调用。" << endl;
    }

    ~B(){
        if(y!=NULL){
            delete y;
        }
        cout << "析构函数调用。" << endl;
    }
};

/**
  * @brief          浅拷贝、深拷贝测试
  */
B test03(void)
{
    B b(10 ,20);
    cout << "b" << (int *)&b << endl;
    return b;
}

/**
  * @brief          浅拷贝、深拷贝测试
  */
void testcopy()
{
    B b1(12, 34);   //有参构造
    B b2(b1);   //拷贝构造
    cout << "b1:" << *b1.y << endl;
    cout << "b2:" << *b2.y << endl;

    B b3 = test03(); //
    cout << "b3:" << (int *)&b3 << endl;
}

/**
  * @brief          静态成员变量、成员函数测试
  * 静态成员变量特点：
  * 1 在编译阶段分配内存
  * 2 类内声明，类外初始化
  * 3 所有对象共享同一份数据
  * 静态成员函数特点：
  * 所有对象共享一个函数
  * 静态成员函数只能访问静态成员变量
  */
class Person
{
public:
	static int m_A; //静态成员变量

    static void func(){
        m_A = 100;
        m_B = 100;
    }
private:
	static int m_B; //静态成员变量也是有访问权限的
    static void funcp(){} //无法通过p1.或Person::访问到
};

int Person::m_A = 10; //程序外初始化静态成员变量
int Person::m_B = 10; //程序内不可访问private Person::m_B
/**
  * @brief          静态成员变量、成员函数测试
  */
void testStatic()
{
    Person::m_A = 10086; //通过类名访问静态成员变量

    Person p1; //通过对象访问静态成员变量
    p1.m_A = 5;

    p1.func();  //通过对象访问静态成员变量
    Person::func(); //通过类名访问静态成员变量
}

/**
  * @brief          占用空间测试
  */
class C{
    int a; //4字节，总4
    int b; //4字节，总8
    int *c; //8字节，总16
    int d; //4字节,总24(8对齐)
    static int e;
    static int f; //不占用对象空间
    void func01(){}
    void func02(int a ,int b){}
    int func03(int a, int b) { return 0; }
    static int func04(int a, int b) { return 0; } //函数不占用对象空间
};

/**
  * @brief          占用空间测试:空对象
  */
class D{
};

/**
  * @brief          占用空间测试
  * cout << sizeof(C) << endl; //类大小
  * C c; cout << sizeof(c) << endl; //对象大小==类大小
  */
void testsize()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(Person) << endl;

    cout << sizeof(C) << endl;
    C c;
    cout << sizeof(c) << endl;

    cout << sizeof(D) << endl;
    D d;
    cout << sizeof(d) << endl;
}

/**
  * @brief          this测试 / 常函数、常对象
  */
class E{
    public:
    E(int x){
        this->x = x; //当形参与成员变量同名时可以用this指针来区分
    }

    E& func(E& e){
        this->x += e.x; //当形参与成员变量同名时可以用this指针来区分
        return *this; //在类的非静态成员函数中返回对象本身，使用return *this
    }

    int x;

    void func01(){
        //可以被空的this指针调用
        cout << "func01" << endl;
        //空this指针时x会出问题
        cout << "this->x:" << x << endl;
    }

    void func02(){
        if(this==NULL){
            //判断this是否为空指针，增加代码健壮性
            cout << "error:this is NULL" << endl;
            return;
        }
        cout << "func02" << endl;
        //空this指针时x会出问题
        cout << "this->x:" << x << endl;
    }

    mutable int y; //可修改的，常函数/对象可修改
    void func03(){
        this->x = 10;
        this->y = 10;
        cout << "func03()" << endl;
    }
    void func04() const{
        //this->x = 10; //常成员函数不可访问this->x
        cout << "x:" << this->x << endl;
        this->y = 10; //常成员函数可访问mutable this->y
        cout << "func04()" << endl;
    }
};

/**
  * @brief          this测试
  */
void thistest(){
    E e1(3);
    E e2(2);
    e2.func(e1).func(e1).func(e1); //链式编程
    //e2.func(e1) //2+3
    //e2.func(e1).func(e1) //2+3+3
    //e2.func(e1).func(e1).func(e1) //2+3+3+3

    //若E& func(E& e){改为E func(E e){ 则返回5 
    //原因：以值方式返回局部对象会调用拷贝构造函数构造新的对象。
    cout << e2.x << endl;

    E *e = NULL;
    //e->func01(); //空指针访问成员x会出问题
    e->func02();

    const E e3(1); //常对象
    //e3.x = 10; //常对象不可修改x，但可修改mutable int y
    cout << "e3:" << e3.x << endl; //常对象可以读取x
    e3.y = 10; 
    //e3.func03(); //常对象只能调用常函数
    e3.func04();
}

/**
  * @brief          friend测试
  */
/**
  * @brief          成员函数做友元
  * 避免出现F未定义的情况，首先class F，然后class NFFriend
  * 然后定义class F中的成员，最后定义class NFFriend中的函数NFFriend:: 
  */
class F;
class NFFriend{
    public:
        NFFriend();
        ~NFFriend();
        void NFFriendfunc01();
        void NFFriendfunc02();
        F *f;
        //F f; //不可行原因F只声明但还未定义，所以只能F *f
};

/**
  * @brief          friend测试
  */
class F{
    friend void freindfunc(F *f);
    friend class FFriend;
    friend void NFFriend::NFFriendfunc02();

public:
    int x;
    F()
    { //默认构造函数
        x = 1;
        y = 2;
        }
    private:
        int y;
};

NFFriend::NFFriend(){
    f = new F;
}

NFFriend::~NFFriend(){
    if(f!=NULL)
    {
        delete f;
    }
}

void NFFriend::NFFriendfunc01(){
    f->x = 10;
    //f->y = 20; //非友元成员函数无法访问F private
    cout << "f->x:" << f->x << endl;
    //cout << "f->y:" << f->y << endl;
}

void NFFriend::NFFriendfunc02(){
    f->x = 10;
    f->y = 20; //友元成员函数可以访问F private
    cout << "f->x:" << f->x << endl;
    cout << "f->y:" << f->y << endl;
}

/**
  * @brief          全局函数做友元
  */
void freindfunc(F *f){
    cout << "f->x:" << f->x << endl;
    cout << "f->y:" << f->y << endl;
}

/**
  * @brief          类做友元
  */
class FFriend{
    public:
        void FFriendfunc(){
            f.x = 10;
            f.y = 20;
            cout << "f.x:" << f.x << endl;
            cout << "f.y:" << f.y << endl;
        }

        F f;
};

void friendtest()
{
    F f01;
    freindfunc(&f01); //全局函数做友元

    FFriend ffriend;
    ffriend.FFriendfunc(); //类做友元

    NFFriend nffriend;
    nffriend.NFFriendfunc01();
    nffriend.NFFriendfunc02(); //成员函数做友元
}

int main()
{
    // testconstructor();
    // testcopy();
    // testStatic();
    // testsize();
    thistest();
    // friendtest();
    return 0;
}