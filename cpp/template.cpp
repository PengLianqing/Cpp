#include <iostream>

using namespace std;

/**
  * @brief          普通函数
  * @retval         none
  */
void mySwap(int &a,int &b){
    cout<<"void mySwap(int &a,int &b)"<<endl;
    int c=a;
    a=b;
    b=c;
}

/**
  * @brief          函数模板
  * @retval         none
  */
template<typename T>
void mySwap(T& a,T&b){
    cout<<"void mySwap(T& a,T&b)"<<endl;
    T temp=a;
    a=b;
    b=temp;
}

/**
  * @brief          函数模板的重载
  * @retval         none
  */
template<typename T>
void mySwap(T& a,T&b,int flag){
    cout<<"void mySwap(T& a,T&b,int flag)"<<endl;
}

/**
  * @brief          函数模板的具体化
  * @retval         none
  */
class A{
    public:
        A(string str,int num){
            this->str=str;
            this->num=num;
        }
        string str;
        int num;
};

template<> void mySwap(A& a ,A& b){
    cout<<"template<> void mySwap(A& a ,A& b)"<<endl;
    A c(a.str,a.num);
    a.str=b.str; a.num=b.num;
    b.str=c.str; b.num=c.num;
}

/**
  * @brief          函数模板测试
  * @retval         none
  */
void funcTemplateTest(){
    int a=10,b=2;
    mySwap(a, b); //调用普通函数
    cout<<a<<";"<<b<<endl;
    mySwap<int>(a, b); //调用模板函数
    cout<<a<<";"<<b<<endl;
    mySwap(a, b ,0); //调用模板重载函数
    cout<<a<<";"<<b<<endl;
    A c("C",0);
    A d("D",1);
    mySwap<>(c,d); //调用模板函数的具体化
    cout<<"C:"<<c.str<<c.num<<";D:"<<d.str<<d.num<<endl;
}

/**
  * @brief          类模板
  * @retval         none
  */
template<class B,class C=int> //C默认参数指定为int
class D{
    public:
    D(B b,C c){
        this->b=b;
        this->c=c;
    }
    void showD(){
        cout<<this->b<<","<<this->c<<endl;
    }
    B b;
    C c;
};

/**
  * @brief          类模板对象做函数参数
  * @retval         none
  */
void var1(D<string,int> &d){ //指定传入参数类型
    d.showD();
}

template<class T1,class T2>
void var2(D<T1,T2> &d){ //参数模板化
    d.showD();
}

template<class T>
void var3(T &d){ //类模板化 
    cout<<"T的类型为:"<<typeid(T).name()<<endl;
    d.showD();
}

void classTemplateVar(){ //类模板对象做函数参数测试
    D<string ,int> d("d",1);
    var1(d);
    var2(d);
    var3(d);
}
/**
  * @brief          类模板成员函数的创建时机
  * @retval         none
  */
class E1{
    public:
        void showE1(){
            cout<<"E1::showE1"<<endl;
        }
};
class E2{
    public:
        void showE1(){
            cout<<"E1::showE1"<<endl;
        }
};
template<class T>
class E{
    public:
        T t;
        void func1(){
            t.showE1(); //类模板中的成员函数只有在被调用的时候才会创建
        }
        void func2(){
            t.showE2(); //类模板中的成员函数只有在被调用的时候才会创建
        }
};

/**
  * @brief          类模板继承
  * @retval         none
  */
template<class T>
class Base{
    T m;
};

class Son1:public Base<int>{ //继承类模板需要指定T类型

};

template<class T1 ,class T2> //类模板继承类模板
class Son2:public Base<T2>{
    public:
        Son2(){
            cout<<"T1:"<<typeid(T1).name()<<endl;
            cout<<"T2:"<<typeid(T2).name()<<endl;
        }
        T1 obj;
};

template<class T> //类模板继承类模板
class Son3:public Base<T>{
    public:
        Son3(){
            cout<<"T:"<<typeid(T).name()<<endl;
        }
};

void inheritanceClass(){ //类模板的继承测试
    Son1 s1;
    Son2<string ,int> s2;
    Son3<int> s3;
}


/**
  * @brief          类模板成员函数类外实现
  * @retval         none
  */
template<class T1,class T2>
class F{
    public:
        F(T1 t1,T2 t2){
            this->t1=t1;
            this->t2=t2;
        }
        void ffunc();
        T1 t1;
        T2 t2;
};

template<class T1,class T2>
void F<T1,T2>::ffunc(){
    cout<<"t1:"<<this->t1<<",t2:"<<this->t2<<endl;
}

/**
  * @brief          类与友元
  * @retval         none
  */
template<class T1,class T2> class G;
template<class T1,class T2> //全局函数配合友元 类外实现
void printG2(G<T1,T2>& g){
    cout<<"t1:"<<g.t1<<",t2:"<<g.t2<<endl;
}

template<class T1,class T2>
class G{
    friend void printG1(G<T1,T2>& g){ //全局函数配合友元 类内实现
            cout<<"t1:"<<g.t1<<",t2:"<<g.t2<<endl;
        }
    friend void printG2<>(G<T1,T2>& g); //全局函数配合友元 类外实现
    public:
        G(T1 t1,T2 t2){
            this->t1=t1;
            this->t2=t2;
        }
    private:
        T1 t1;
        T2 t2;
};

void friendTest(){ //全局函数配合友元测试
    G<string ,int> g("G",1);
    printG1(g);
    printG2(g);
}

/**
  * @brief          类模板测试
  * @retval         none
  */
void classTemplateTest(){
    D<string ,int> d("D",1); //指定B为string类型，C为int类型
    cout<<"d:"<<d.b<<","<<d.c<<endl;

    E<E1> e;
    e.func1();
    //e.func2(); //编译出错，说明类模板中的成员函数只有在被调用的时候才会创建

    classTemplateVar(); //类模板对象做函数参数测试
    inheritanceClass(); //类模板的继承测试

    F<string ,int> f("F",1); //类模板成员函数类外实现
    f.ffunc();
}

int main()
{
    funcTemplateTest();
    classTemplateTest();
    cout << "all done." << std::endl;
    return 0;
}

