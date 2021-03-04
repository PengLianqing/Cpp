#include <iostream>

using namespace std;

/**
  * @brief          函数对象
  * @retval         none
  */
class A{
    public:
        A(){
            count=0; //函数对象可以有自己的状态
        }
        int operator()(int a,int b){ //函数对象可以有自己的参数、返回值
            count++;   
            return a+b;
        }
        int count;
};

/**
  * @brief          函数对象作为参数传递
  * @retval         none
  */
int func(A &a,int b,int c){
    return a(b,c);
}

void functionObject(){
    A a;
    cout<<a(2,3)<<endl; //函数对象
    cout<<"调用次数:"<<a.count<<endl; //函数对象的状态
    cout<<func(a,1,2)<<endl; //函数对象作为参数传递
    cout << "all done." << endl;
}

#include <vector>
#include <algorithm>
/**
  * @brief          一元谓词与find_if
  * @retval         none
  */
struct greaterFive{
    bool operator()(int a){
        return a>5;
    }
};

void findTest(){
    vector<int> nums(10);
    for(int i=0;i<10;i++) nums[i]=i;
    vector<int>::iterator it=find_if(nums.begin(),nums.end(),greaterFive()); //find_if
    if(it!=nums.end()) cout<<*it<<endl;
    else cout<<"none."<<endl;
}

/**
  * @brief          一元谓词与sort
  * @retval         none
  */
struct myCompare{
    bool operator()(int a,int b){
        return a>b;
    }
};

void sortTest(){
    vector<int> nums(10);
    for(int i=0;i<10;i++) nums[i]=rand()%32;
    sort(nums.begin(),nums.end()); //默认从小到大
    for(int num:nums) cout<<num<<";";
    cout<<endl;
    sort(nums.begin(),nums.end(),myCompare()); //sort 自定义从大到小
    for(int num:nums) cout<<num<<";";
    cout<<endl;
}

int main()
{
    functionObject(); //函数对象测试
    findTest(); //一元谓词测试
    sortTest(); //二元谓词测试
    return 0;
}

