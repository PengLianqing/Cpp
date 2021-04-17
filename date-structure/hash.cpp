/*
实现哈希表

简化：可以使用list而不是自定义链表。
list<int> l;
l.push_back( 1 );
auto it = find(l.begin(),l.end(),1);
l.erase( it );
*/

#include <cstdint>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

#include <list>

using namespace std;

class mhash{
    // Node链表节点
    class Node{
        public:
        int val;
        Node *next;
        Node( int _val ):val(_val){
            next = nullptr;
        }
    };

public:
    vector<Node*> hashmap;
    int size;

    mhash(int _size=31):size(_size){ // 默认设置size为31，一般为质数
        hashmap.resize(size);
        for(int i=0;i<size;++i){
            hashmap[i] = nullptr;
        }
    }
    
    bool insert( int num ){
        int hashnum = num % size;
        Node *node = new Node(num);
        
        if(!hashmap[hashnum]){ // 链表为空
           hashmap[hashnum] = node; 
           return true;
        }

        Node *head = hashmap[hashnum];

        while( head && head->val!=num ){

            if(!head->next){ // 如果检索到了链表结尾，则加入元素
                head->next = node;
                return true;
            }

            head = head -> next;
        }
        return false;
    }
    
    bool remove( int num ){
        int hashnum = num % size;

        if( !hashmap[hashnum] ) return false;
        Node *head = hashmap[hashnum];
        
        if(head->val==num){ // 判断是不是链表的第一个元素
            hashmap[hashnum] = head->next;
            delete head;
            return true;
        }

        while( head->next ){
            
            if(head->next->val==num){
                Node *temp = head->next;
                head->next = head->next->next;
                delete temp;
                return true;
            }
            head = head -> next;
        }
        return false;
    }
    
    bool contains( int num ){

        int hashnum = num % size;

        Node *head = hashmap[hashnum];

        while( head ){

            if(head->val==num){
                return true;
            }

            head = head->next;

        }
        return false;
    }
};

mhash mh;
int main(){

/*
    // 测试
    for(int i=0;i<128;++i){
        cout << "insert" << i << "," << mh.insert( i ) << endl;
    }
    for(int i=0;i<128;++i){
        cout << "contains" << i << "," << mh.contains( i ) << endl;
    }
    for(int i=0;i<128;++i){
        cout << "remove" << i << "," << mh.remove( i ) << endl;
    }
*/
    // 随机数测试
    for(int i=0;i<64;++i){
        int num = rand()%128;
        cout << "insert" << num << "," << mh.insert( num ) << endl;
    }
    for(int i=0;i<128;++i){
        cout << "contains" << i << "," << mh.contains( i ) << endl;
    }
    for(int i=0;i<128;++i){
        cout << "remove" << i << "," << mh.remove( i ) << endl;
    }

    return 0;
}