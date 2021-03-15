/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       algorithm-sort.cpp
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
#include <vector>

using namespace std;

class algorithmSort{
    public:
    /**
      * @brief          快速排序
      * 左闭右闭的二分写法
      * 时间复杂度:O(nlogn),最坏情况O(n^2)
      * 空间复杂度:O(logn),递归使用的栈空间
      */
    void quickSort(vector<int> &nums,int l,int r){
        if(l+1>=r) return; //2个数及以下没有排序的必要了
        int first=l,last=r,key=nums[first];
        //目标是最终[first]前面的数均<=nums[first],后面的数都>nums[first]
        while(first<last){
            while(first<last&&nums[last]>=key){
                --last;
            }
            nums[first]=nums[last]; //将较小的数放在前面
            while(first<last&&nums[first]<key){
                ++first;
            }
            nums[last]=nums[first]; //将较大的数放在后面
        }
        nums[first]=key; //此时nums[first]前面的数<=nums[first],后面的数>nums[first]
        quickSort(nums,l,first); //递归
        quickSort(nums,first+1,r);
    }
    /**
      * @brief          归并排序
      * 时间复杂度:O(nlogn)
      * 空间复杂度:O(n),临时数组
      */
    void mergeSort(vector<int> &nums,int l,int r,vector<int> &temp){
        if(l+1>=r) return; //2个数及以下没有排序的必要了
        int m=l+(r-l)/2;
        mergeSort(nums,l,m,temp); //[l,m]
        mergeSort(nums,m+1,r,temp); //[m+1,r]
        //在[l,m]和[m+1,r]均为有序队列的情况下
        int l1=l,l2=m+1,i=l;
        while(i<=r){ //未全遍历完
            if( l2>r||(l1<=m&&nums[l1]<=nums[l2]) ){
                //l2遍历完 或 未遍历完且nums[l1]<=nums[l2]
                temp[i++]=nums[l1++];
            }
            else{
                //l1遍历完 或 未遍历完且nums[l1]>nums[l2]
                temp[i++]=nums[l2++];
            }
        }
        for(int j=l;j<=r;j++){
            nums[j]=temp[j];
        }
    }

    /**
      * @brief          插入排序
      * 时间复杂度:O(n^2)
      * 空间复杂度:O(1)
      */
    void insertionSort(vector<int> &nums,int n){
        // 1,3,5,2,4,6,9,7,1,1 原数据
        // 1,2,3,5,4,6,9,7,1,1 插入排序(将nums[j]插入到j前面满足的最小的位置上)
        // 1,2,3,4,5,6,9,7,1,1
        // 1,2,3,4,5,6,7,9,1,1
        // ......
        for(int i=0;i<n;i++){
            for(int j=i;j>0&&nums[j]<nums[j-1];j--){
                swap(nums[j],nums[j-1]);
            }
                            for(int num:nums) cout<<num<<",";
                cout<<endl;
        }
    }

    /**
      * @brief          冒泡排序
      * 时间复杂度:O(n^2)
      * 空间复杂度:O(1)
      */
    void bubbleSort(vector<int> &nums,int n){
        // 1,3,5,2,4,6,9,7,1,1 原数据
        // 1,3,2,4,5,6,7,1,1,9 冒泡排序(较小元素逐渐从后面冒泡到前面)
        // 1,2,3,4,5,6,1,1,7,9
        // 1,2,3,4,5,1,1,6,7,9
        // ......
        for(int i=1;i<n;++i){
            bool swapped=false; //如果没有进行交换，则说明后续元素保持升序
            for(int j=1;j<=n-i+1;++j){
                if(nums[j]<nums[j-1]){
                    swap(nums[j],nums[j-1]);
                    swapped=true;
                }
            }
            cout<<endl;
        }
    }

    /**
      * @brief          选择排序
      * 时间复杂度:O(n^2)
      * 空间复杂度:O(1)
      */
    void selectionSort(vector<int> &nums,int n){
        //选择出nums[i]后面的最小元素,与nums[i]交换
        for(int i=0;i<n;++i){
            int min=i;
            for(int j=i;j<n;++j){
                if(nums[j]<nums[min]) min=j;
            }
            swap(nums[i],nums[min]);
        }
    }
};

int main(){
    algorithmSort s;

    vector <int>nums{1,3,5,2,4,6,9,7,1,1};
    cout<<"原始数据:";
    for(int num:nums) cout<<num<<",";
    cout<<endl;

    //s.quickSort(nums,0,nums.size()-1); //快速排序

    //vector<int> temp(nums.size());
    //s.mergeSort(nums,0,nums.size()-1,temp); //归并排序

    //s.bubbleSort(nums,nums.size()); //冒泡排序

    //s.insertionSort(nums,nums.size()); //插入排序

    s.selectionSort(nums,nums.size()); //选择排序

    cout<<"排序数据:";
    for(int num:nums) cout<<num<<",";
    cout<<endl;

    cout<<"all done."<<endl;
    return 0;
}