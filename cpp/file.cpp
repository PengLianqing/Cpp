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
#include <fstream>
#include <string>

using namespace std;

/*
ios::in 读文件
ios::out 写文件
ios::ate 初始位置为文件尾
ios::app 追加方式写文件
ios::trunc 如果文件存在先删除，再创建
ios::binary 二进制方式
*/

/**
  * @brief          文本方式
  */
void texttest(){
    //读文件
    ifstream ifs; //创建流对象
    ifs.open("a.txt", ios::in);
    if (!ifs.is_open())
    {
        cout << "open error" << endl;
        return;
    }
    
    char buf[4096];
    //#1 while(ifs>>buf){
    while(ifs>>buf){ 
        cout << buf << endl;
    }
    //#2 while (ifs.getline(buf,sizeof(buf))){
    while (ifs.getline(buf,sizeof(buf))){
        cout << buf << endl;
    }
    //#3 while (getline(ifs,buf)){
    string buffer;
    while (getline(ifs,buffer)){
        cout << buffer << endl;
    }
    //#4 while ((c = ifs.get()) != EOF) 
    char c;
	while ((c = ifs.get()) != EOF)
	{
		cout << c;
	}
    ifs.close();

    //追加方式写文件
    ofstream ofs;
    ofs.open("a.txt", ios::app);
    ofs << "Hello-world" << endl;
    ofs.close();
}

/**
  * @brief          二进制方式
  */
class A{
    public:
        int x;
        int y;
        double z;
        A(){

        }
        A(int x ,int y ,double z){
            this->x = x;
            this->y = y;
            this->z = z;
        }
};

void binarytest(){

    A a(1 ,6 ,3.14);
    //追加方式写文件
    ofstream ofs;
    ofs.open("b.txt", ios::out | ios::binary);
    ofs.write((char *)&a, sizeof(a));
    ofs.close();

    //读文件
    ifstream ifs; //创建流对象
    ifs.open("b.txt", ios::in|ios::binary);
    if (!ifs.is_open())
    {
        cout << "open error" << endl;
        return;
    }
    A b;
    ifs.read((char *)&b, sizeof(b));
    cout << b.x << endl;
    cout << b.y << endl;
    cout << b.z << endl;
    ifs.close();
}

int main(){
    //texttest();
    binarytest();
}