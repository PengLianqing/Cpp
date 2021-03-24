#include <iostream>
#include <vector>
using namespace std;

// int main(){
//     int a=0,b=0;
//     int num=0;
//     while(cin>>a){
//         while(a-->0){
//             cin>>num;
//             b=0;
//             while(num!=0){
//                 if(num%3==0){
//                     num/=3;
//                     ++b;
//                 }
//                 else if(num%2==0){
//                     num/=2;
//                     ++b;
//                 }
//                 else {
//                     --num;
//                     ++b;
//                 }
//             }
//             cout<<b<<endl;
//         }
//         // 100 99 33 11 10 9 3 1 0
//         // 10 9 3 1 0
//     }
//     return 0;
// }


int main(){
    int num=0,total=0;
    while(cin>>num>>total){
        vector<int> money(num*2,0);
        int i=0;
        while(i<num*2){
            cin>>money[i++];
        }
        for(auto elem : money) cout<<elem<<",";
    }
    return 0;
}

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 你需要返回m个指针，第i个指针指向一条链，表示第i个问题的答案
     * @param root TreeNode类 指向链表树的根
     * @param b int整型vector 表示每个问题是什么
     * @return ListNode类vector
     */
    vector<ListNode*> solve(TreeNode* root, vector<int>& b) {
        // write code here
        vector<ListNode*> ans;
       
        ListNode* list=new ListNode(root->val);
        ListNode* head=list;
        dfs(root,list,head,ans);
        
        return ans;
    }
    void dfs(TreeNode* &root , ListNode* list , ListNode* head , vector<ListNode*> &ans){
        if(!root) return ;
        ListNode* temp = new(ListNode)(root->val);
        list->next = temp;
        
        ans.push_back(head);
        
        ListNode* temp2 = new(ListNode)(root->val);
        list->next = temp2;
        
        //cout<<root->val<<endl;
        dfs(root->left,temp2,head,ans);
        dfs(root->right,temp2,head,ans);
    }

};

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 你需要返回m个指针，第i个指针指向一条链，表示第i个问题的答案
     * @param root TreeNode类 指向链表树的根
     * @param b int整型vector 表示每个问题是什么
     * @return ListNode类vector
     */
    vector<ListNode*> solve(TreeNode* root, vector<int>& b) {
        // write code here
        vector<ListNode*> ans;
       
        ListNode* list=new ListNode(root->val);
        ListNode* head=list;
        dfs(root,list,head,ans);
        
        return ans;
    }
    void dfs(TreeNode* &root , ListNode* list , ListNode* head , vector<ListNode*> &ans){
        if(!root) return ;
        ListNode* temp = new(ListNode)(root->val);
        list->next = temp;
        
        ans.push_back(head);
        
        ListNode* temp2 = new(ListNode)(root->val);
        list->next = temp2;
        
        //cout<<root->val<<endl;
        dfs(root->left,temp2,head,ans);
        dfs(root->right,temp2,head,ans);
    }

};