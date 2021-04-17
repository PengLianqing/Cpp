/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       bst.cpp
  * @brief      binary-search-tree
  *             插入和清空树节点时TreeNode* &node使用引用,否则出现赋值错误;
  *             节点所有左子树都小于节点，所有右子树都大于节点;
  *             中序遍历得到从小到大排序的结果.
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
#include <unordered_map>

using namespace std;

class BST{

    class TreeNode{
        public:
            int val;
            TreeNode* left;
            TreeNode* right;
            TreeNode(int _val):val(_val),left(nullptr),right(nullptr){}
    };

    TreeNode* root = nullptr; // 根节点

    // 删除节点与所有子节点对应的内存,并指针值为nullptr
    void makeEmpty( TreeNode* &node ){
        if( !node ) return;
        makeEmpty( node->left );
        makeEmpty( node->right );
        delete node;
        node = nullptr;
    }

    // 插入节点
    // TreeNode* &node使用引用,否则出现赋值错误
    TreeNode* insertVal( TreeNode* &node , int x ){
        if( !node ){
            node = new TreeNode(x);
        }else if( x < node->val ){
            node->left = insertVal( node->left , x );
        }else if(  x > node->val ){
            node->right = insertVal( node->right , x );
        }
        return node;
    }

    // 查找节点
    TreeNode* findVal( TreeNode* node , int val ){
        if( !node ) return nullptr;
        if( val < node->val ) return findVal( node->left , val ); // 小于节点,向左子节点递归
        if( val > node->val ) return findVal( node->right, val ); // 大于节点,向右子节点递归
        return node;
    }

    // 查找最小节点,向下遍历左子节点
    TreeNode* findMin( TreeNode* node ){
        if( !node) return node; // nullptr
        if( !node->left ) return node; // 没有左子节点,该节点为最小值
        return findMax( node->left );
    }

    // 查找最大节点,向下遍历右子节点
    TreeNode* findMax( TreeNode* node){
        if( !node) return node;
        if( !node->right ) return node; // 没有右子节点,该节点为最大值
        return findMax( node->right );
    }

    // 移除节点
    TreeNode* removeVal( TreeNode* node , int val ){
        TreeNode* temp;
        if( !node ) return nullptr;
        // 未找到节点,继续寻找
        if( val < node->val ){
            node->left = removeVal( node->left , val );
        }else if( val > node->val ){
            node->right = removeVal( node->right , val );
        }
        // 找到节点,删除节点并调整树
        else{ 
            // 节点有左右子节点,将右子树的最小值调整到当前节点
            if( node->left && node->right ){ 
                temp = findMin( node->right );
                node->val = temp->val;
                node->right = removeVal( node->right , node->val );
            }
            // 节点有空子节点,将非空的节点调整到当前节点
            else{ 
                temp = node;
                if( !node->left ){
                    node = node->right;
                }else if( !node->right ){
                    node = node->left;
                }
                delete temp;
            }
        }
        return node;
    }

    // preorder遍历
    void preOrder( TreeNode* node ){
        if( !node ) return;
        cout << node->val << ",";
        preOrder( node->left );
        preOrder( node->right );
    }

    // inorder遍历
    void inorder( TreeNode* node ){
        if( !node ) return;
        inorder( node->left );
        cout << node->val << ",";
        inorder( node->right );
    }

    public:
        BST(){
            root = nullptr;
        }

        ~BST(){
            makeEmpty( root ); 
        }

        void insert( int val ){
            insertVal( root , val );
        }

        void remove( int val ){
            removeVal( root , val );
        }

        bool find( int val ){
            return findVal( root , val )?true:false;
        }

        void order(){
            inorder( root );
            // preOrder( root );
        }

        void erase(){
            makeEmpty( root ); 
        }
};

BST bst;
int main(){
    // 建立索引，对比find结果
    unordered_map<int,int> mp; 
    for(int i=0;i<100;++i) mp[ rand()%256 ]=1;

    // insert
    for(auto elem:mp){ 
        cout << elem.first << ",";
        bst.insert( elem.first );
    } cout << endl;

    // inorder
    cout << "insert order:"; 
    bst.order();
    cout << endl;

    // find
    for(int i=0;i<256;++i){ 
        cout << i << ",";
        cout << mp[i] << ",";
        cout << bst.find( i ) << endl;;
    }

    // remove
    bst.remove( 70 );
    // inorder
    cout << "remove order:"; 
    bst.order();
    cout << endl;

    // erase
    bst.erase();
    // inorder
    cout << "erase order:"; 
    bst.order();
    cout << endl;
}