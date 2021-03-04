/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       recursion.cpp
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
#include <list>

using namespace std;

/**
  * @brief          binary tree
  */
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(int x) :val(x) ,left(NULL) ,right(NULL) ,parent(NULL) {}
    TreeNode() :val(0) ,left(NULL) ,right(NULL) ,parent(NULL) {}
};

/**
  * @brief          List_t
  */
struct List_t{
    int val;
    List_t *next;
    List_t(int x) :val(x) ,next(NULL) {}
    List_t() :val(0) ,next(NULL) {}
};

/**
  * @brief          recursion_t test class
  */
class recursion_t{
public:
    //递归方式实现阶乘
    int factorial(int n);
    int factorial_test(void);

    //递归方式实现树的遍历
    void preOrder(TreeNode *node);
    void inOrder(TreeNode *node);
    void postOrder(TreeNode *node);
    int binary_tree_test(void);

    //递归方式实现链表逆序打印
    void List_t_reverse_print(List_t *node);
    int List_t_reverse_print_test(void);
};
recursion_t recursion;

/**
  * @brief          recursion_t::factorial_test
  */
int recursion_t::factorial_test(void)
{
    cout<<"##factorial_test##"<<endl;
    cout<<factorial(5)<<endl;
    return 0;
}

/**
  * @brief          recursion_t::factorial
  * 实现递归方式求阶乘
  */
int recursion_t::factorial(int n)
{
    if(n==1)
    {
        return n;
    }
    return n*factorial(n-1);
}

/**
  * @brief          recursion_t::binary_tree_test
  */
int recursion_t::binary_tree_test(void)
{
    cout<<"##binary_tree_test##"<<endl;
//              1               
//           /     \
//          2       3   
//         /       / \
//        4       5   6
//         \         /
//          7       8
    struct TreeNode *Node[10];
    for(int i=0 ;i<10 ;i++)
    {
        Node[i] = new TreeNode; //为Node元素申请内存
    }
    Node[0]->val = 1;   Node[0]->left = Node[1];    Node[0]->right = Node[2];   Node[0]->parent = nullptr;

    Node[1]->val = 2;   Node[1]->left = Node[3];    Node[1]->right = nullptr;   Node[1]->parent = Node[0];
    Node[2]->val = 3;   Node[2]->left = Node[4];    Node[2]->right = Node[5];   Node[2]->parent = Node[0];

    Node[3]->val = 4;   Node[3]->left = nullptr;    Node[3]->right = Node[6];   Node[3]->parent = Node[1];
    Node[4]->val = 5;   Node[4]->left = nullptr;    Node[4]->right = nullptr;   Node[4]->parent = Node[2];
    Node[5]->val = 6;   Node[5]->left = Node[7];    Node[5]->right = nullptr;   Node[5]->parent = Node[2];

    Node[6]->val = 7;   Node[6]->left = nullptr;    Node[6]->right = nullptr;   Node[6]->parent = Node[3];
    Node[7]->val = 8;   Node[7]->left = nullptr;    Node[7]->right = nullptr;   Node[7]->parent = Node[5];

    cout<<"preorder:"<<endl;
    recursion.preOrder(Node[0]);
    cout<<"inorder:"<<endl;
    recursion.inOrder(Node[0]);
    cout<<"postorder:"<<endl;
    recursion.postOrder(Node[0]);

    return 0;
}

/**
  * @brief          recursion_t::preOrder
  * 实现递归方式遍历二叉树-前序遍历
  * @param[in]      TreeNode *
  * @param[out]     none
  * @retval         none
  */
void recursion_t::preOrder(TreeNode *node)
{
    if(node==nullptr)
    {
        return;
    }
    cout<<node->val<<endl;
    preOrder(node->left);
    preOrder(node->right);
}

/**
  * @brief          recursion_t::inOrder
  * 实现递归方式遍历二叉树-中序遍历
  * @param[in]      TreeNode *
  * @param[out]     none
  * @retval         none
  */
void recursion_t::inOrder(TreeNode *node)
{
    if(node==nullptr)
    {
        return;
    }
    inOrder(node->left);
    cout<<node->val<<endl;
    inOrder(node->right);
}

/**
  * @brief          recursion_t::postOrder
  * 实现递归方式遍历二叉树-后序遍历
  * @param[in]      TreeNode *
  * @param[out]     none
  * @retval         none
  */
void recursion_t::postOrder(TreeNode *node)
{
    if(node==nullptr)
    {
        return;
    }
    preOrder(node->left);
    preOrder(node->right);
    cout<<node->val<<endl;
}

/**
  * @brief          recursion_t::List_t_print_test
  */
int recursion_t::List_t_reverse_print_test(void)
{
    cout<<"##List_t_print_test##"<<endl;

// 1->4->7->2->5->8->3->6->9->0

    struct List_t *Node[10];
    for(int i=0 ;i<10 ;i++)
    {
        Node[i] = new List_t; //为Node元素申请内存
    }
    Node[0]->val = 1;   Node[0]->next = Node[1]; 
    Node[1]->val = 4;   Node[1]->next = Node[2];
    Node[2]->val = 7;   Node[2]->next = Node[3];
    Node[3]->val = 2;   Node[3]->next = Node[4];
    Node[4]->val = 5;   Node[4]->next = Node[5];   
    Node[5]->val = 8;   Node[5]->next = Node[6];
    Node[6]->val = 3;   Node[6]->next = Node[7];
    Node[7]->val = 6;   Node[7]->next = Node[8];
    Node[8]->val = 9;   Node[8]->next = Node[9];
    Node[9]->val = 0;   Node[9]->next = nullptr;

    cout<<"reverse order:"<<endl;
    recursion.List_t_reverse_print(Node[0]);

    return 0;
}

/**
  * @brief          recursion_t::List_t_print
  * 实现递归方式逆序打印链表
  * @param[in]      TreeNode *
  * @param[out]     none
  * @retval         none
  */
void recursion_t::List_t_reverse_print(List_t *node)
{
    if(node==nullptr)
    {
        return;
    }
    //cout<<node->val<<endl; //正序打印就放在递归之前
    List_t_reverse_print(node->next);
    cout<<node->val<<endl; //逆序打印就放在递归之后
    
}
/**
  * @brief          main
  * @param[in]      none
  * @param[out]     none
  * @retval         none
  */
int main()
{
    recursion.factorial_test();
    recursion.binary_tree_test();
    recursion.List_t_reverse_print_test();
    return 0;
}