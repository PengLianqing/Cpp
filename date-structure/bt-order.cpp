/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       bt-order.cpp
  * @brief      先序遍历、中序遍历、后序遍历、层序遍历的递归实现、迭代实现、morris算法
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
#include <queue>
#include <stack>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BT{
    public:

        BT( vector<string> &nodes ){
            buildTree(nodes);
        }

        void preorder(){
            cout << "preorder ";
            preorder(root);
            cout << endl;
        }

        void inorder(){
            cout << "inorder ";
            inorder(root);
            cout << endl;
        }

        void postorder(){
            cout << "postorder ";
            postorder(root);
            cout << endl;
        }

        void morris_preorder(){
            cout << "morris_preorder ";
            morris_preorder(root);
            cout << endl;
        }

        void morris_inorder(){
            cout << "morris_inorder ";
            morris_inorder(root);
            cout << endl;
        }

        void morris_postorder(){
            cout << "morris_postorder ";
            morris_postorder(root);
            cout << endl;
        }

        void layerorder(){
            cout << "layerorder ";
            for(auto elem:tree){
                if(elem) cout << elem->val << " ";
            }cout << endl;
        }

        void queue_layerorder(){
            // 如果需要获取层信息，则在循环开始获取q的大小，并每次循环弹出一层数据
            cout << "queue_layerorder ";
            queue<TreeNode*> q;
            TreeNode* node = root;
            if(!node) return;
            q.push(node);
            while( !q.empty() ){
                node = q.front();
                q.pop();
                cout << node->val << " ";
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            cout << endl;
        }

        // 根节点-左子节点-弹出-右子节点 ， 前序遍历是插入顺序
        void stack_preorder(){
            cout << "stack_preorder ";
            stack<TreeNode*> st;
            TreeNode* node = root;
            if(!node) return;
            while( node || !st.empty() ){
                while(node){
                    st.push(node);
                    cout << node->val << " ";
                    node = node->left;
                }
                node = st.top();
                st.pop();
                node = node->right;
            }
            cout << endl;
        }

        // 根节点-左子节点-弹出-右子节点 ， 中序遍历是弹出顺序
        void stack_inorder(){
            cout << "stack_inorder ";
            stack<TreeNode*> st;
            TreeNode* node = root;
            if(!node) return;
            while( node || !st.empty() ){
                while(node){
                    st.push(node);
                    node = node->left;
                }
                node = st.top();
                st.pop();
                cout << node->val << " ";
                node = node->right;
            }
            cout << endl;
        }

        // 根节点-左子节点-弹出-弹出节点的右子节点 ， 后序遍历是弹出顺序（没有右子节点或右子节点遍历过的节点）
        void stack_postorder(){
            cout << "stack_inorder ";
            stack<TreeNode*> st;
            TreeNode *node = root , *prev = nullptr;
            if(!node) return;
            while( node || !st.empty() ){
                while(node){
                    st.push(node);
                    node = node->left;
                }
                node = st.top();
                st.pop();

                // 中序遍历，node = node->right;继续迭代；
                // 后序遍历，将有右子节点的节点重新入栈，并迭代其右子树，从而得到左-右-根。

                if( !node->right || node->right==prev ){ // 没有右子节点或右子节点遍历过，下一次迭代只弹出节点
                    cout << node->val << " ";
                    prev = node;
                    node = nullptr;
                }else{ // 有右子节点，节点入栈
                    st.push(node);
                    node = node->right;
                }
            }
            cout << endl;
        }

        // // 辅助栈st和val:节点的入栈顺序为节点、右节点、左节点
        // // 使用辅助栈val记录节点的入栈顺序
        // // 辅助栈val出栈顺序即为入栈顺序的反序
        // void stack_postorder(){
        //     cout << "stack_postorder ";
        //     stack<TreeNode*> st;
        //     stack<int> val;
        //     TreeNode* node = root;
        //     st.push(node);
        //     while( !st.empty() ){
        //         if(node){
        //             st.push(node);
        //             val.push(node->val);
        //             node = node->right;
        //         }else{
        //             node = st.top();
        //             st.pop();
        //             node = node->left;
        //         }
        //     }
        //     while( !val.empty() ){
        //         cout << val.top() << ",";
        //         val.pop();
        //     }
        //     cout << endl;
        // }

    private:
        TreeNode* root; // root
        vector<TreeNode*> tree; // 层序，用于创建树

        // 构建树
        void buildTree( vector<string> &nodes){

            // 创建节点
            int n = nodes.size();
            // vector<TreeNode*> tree(n,nullptr);
            tree.resize(n);
            for( int i=0;i<n;++i){
                if( nodes[i]=="NULL" ){
                    tree[i] = nullptr;
                }else{
                    int num = stoi( nodes[i] );
                    tree[i] = new TreeNode(num);
                }
            }

            // root
            root = tree[0]?tree[0]:nullptr;

            // 构建树
            queue<TreeNode*>q;
            int j=0;
            q.push( tree[j++] );
            while( !q.empty() ){
                TreeNode* node = q.front();
                q.pop();
                if(j<tree.size()){
                    node->left = tree[j++];
                    q.push( node->left );
                }
                if(j<tree.size()){
                    node->right = tree[j++];
                    q.push( node->right );
                }
            }
        }

        // 前序遍历-O(h)空间普通方法
        void preorder(TreeNode* node){
            if(!node) return;
            cout << node->val << " " ;
            preorder(node->left);
            preorder(node->right);
        }

        // 中序遍历-O(h)空间普通方法
        void inorder(TreeNode* node){
            if(!node) return;
            inorder(node->left);
            cout << node->val << " " ;
            inorder(node->right);
        }

        // 后序遍历-O(h)空间普通方法
        void postorder(TreeNode* node){
            if(!node) return;
            postorder(node->left);
            postorder(node->right);
            cout << node->val << " " ;
        }

         /*
            Morris 遍历算法整体步骤如下（假设当前遍历到的节点为 x）：
            如果 x 无左孩子，则访问 x 的右孩子，即 x = x.right。
            如果 x 有左孩子，则找到 x 左子树上最右的节点（即左子树中序遍历的最后一个节点，x 在中序遍历中的前驱节点），我们记为predecessor。根据predecessor 的右孩子是否为空，进行如下操作。
            如果 predecessor 的右孩子为空，则将其右孩子指向 x，然后访问 x 的左孩子，即 x = x.left。
            如果 predecessor 的右孩子不为空，则此时其右孩子指向 x，说明我们已经遍历完 x 的左子树，我们将 predecessor 的右孩子置空，然后访问 x 的右孩子，即 x = x.right。
            重复上述操作，直至访问完整棵树。

            特点:
            每个节点会被访问两次,时间复杂度为O(n),
            但是只用到常数辅助空间,空间复杂度为O(1).

            即：
            每走到一个有左子节点的节点都会有两个循环，第一次是建立连接，第二次是删除连接。
            如果节点有左子节点，那么第一次走到最下面并建立对应左子树上最右的节点predecessor与对应根节点的连接,第二次则是走右节点。
            如果节点没有左节点，那么向右子节点或通过建立的连接回到对应根节点。

            ** 前中后序遍历修改的是node->val的打印时机. **
        */
        void morris(TreeNode* node){
            TreeNode *predecessor = nullptr;
            while (node != nullptr) {

                // 0 此处node其实遍历了两遍,有些节点是x序遍历不需要的

                // 如果有左孩子，则分情况讨论
                if (node->left != nullptr) {
                    
                    // predecessor 节点就是当前node节点向左子树，然后一直向右走至无法走为止（这个位置是建立连接的节点）
                    predecessor = node->left;
                    while (predecessor->right != nullptr && predecessor->right != node) {
                        // predecessor找到对应根节点左子树上最右的节点,判断!=node是为了不走环路
                        predecessor = predecessor->right;
                    }
                    
                    // 判断predecessor是否被建立连接,如果没有建立,说明是第一次遍历
                    // predecessor的右指针指向node，建立连接
                    // node向左遍历
                    if (predecessor->right == nullptr) {
                        predecessor->right = node;
                        node = node->left;
                    }
                    
                    // 判断predecessor是否被建立连接,如果已经建立，说明是第二次遍历
                    // 断开predecessor 的右指针与node的连接
                    // node向右遍历
                    else {
                        predecessor->right = nullptr; // 断开连接
                        node = node->right; // 遍历右子树
                    }
                }

                // 如果没有左孩子，则直接访问右孩子
                // 即本来只有右孩子的访问右孩子
                // 建立了返回路径的，通过连接返回到对应的根节点
                else {
                    node = node->right;
                }
            }
        }

        // 前序遍历-O(1)空间morris方法
        // 在某个根结点创建连线的时候打印。
        // 打印自身无法创建连线的节点，也就是叶子节点。
        void morris_preorder(TreeNode* node){
            TreeNode *predecessor = nullptr;
            while (node != nullptr) {
                if (node->left != nullptr) {
                    predecessor = node->left;
                    while (predecessor->right != nullptr && predecessor->right != node) { 
                        predecessor = predecessor->right;
                    }
                    if (predecessor->right == nullptr) {
                        // preorder 路径
                        cout << node->val << " ";
                        predecessor->right = node;
                        node = node->left;
                    }
                    else {
                        predecessor->right = nullptr;
                        node = node->right;
                    }
                }
                else {
                    // preorder 路径
                    cout << node->val << " ";
                    node = node->right;
                }
            }
        }

        // 中序遍历-O(1)空间morris方法
        // 从最左侧开始顺着右节点打印，也就是在将cu1切换到上层节点的时候。
        void morris_inorder(TreeNode* node){
            TreeNode *predecessor = nullptr;
            while (node != nullptr) {
                if (node->left != nullptr) {
                    predecessor = node->left;
                    while (predecessor->right != nullptr && predecessor->right != node) { 
                        predecessor = predecessor->right;
                    }
                    if (predecessor->right == nullptr) {
                        predecessor->right = node;
                        node = node->left;
                    }
                    else {
                        // inorder 路径
                        cout << node->val << " ";
                        predecessor->right = nullptr;
                        node = node->right;
                    }
                }
                else {
                    // inorder 路径
                    cout << node->val << " ";
                    node = node->right;
                }
            }
        }
        
        // 后序遍历-O(1)空间morris方法
        // 当返回上层之后，也就是将连线断开的时候，逆序打印下层的单链表。
        // 不应该打印当前层，而是下一层，否则根结点会先与右边打印。
        // 最后需要额外打印根节点层。
        void morris_postorder(TreeNode* node){
            TreeNode *predecessor = nullptr;
            while (node != nullptr) {
                if (node->left != nullptr) {
                    predecessor = node->left;
                    while (predecessor->right != nullptr && predecessor->right != node) {
                        predecessor = predecessor->right;
                    }
                    if (predecessor->right == nullptr) {
                        predecessor->right = node;
                        node = node->left;
                    }
                    else {
                        predecessor->right = nullptr;
                        // 打印节点的左子节点处的链表
                        postMorrisPrint(node->left);
                        node = node->right; // 遍历右子树
                    }
                }
                else {
                    node = node->right;
                }
            }
            // 打印根节点root的链表
            postMorrisPrint(root);
        }

        // 打印
        void postMorrisPrint( TreeNode* node ){
            TreeNode* reverseList = postMorrisReverseList( node );
            TreeNode* cur = reverseList;
            while( cur ){
                cout << cur->val << " ";
                cur = cur->right;
            }
            postMorrisReverseList( reverseList );
        }

        // 翻转单链表
        TreeNode* postMorrisReverseList(TreeNode *head) {
            TreeNode* cur = head;
            TreeNode* pre = nullptr;
            while ( cur ) {
                TreeNode* next = cur->right;
                cur->right = pre;
                pre = cur;
                cur = next;
            }
            return pre;
        }

};

int main(){
    
    vector<string> nodes={"0","1","2","3","4","5","6","NULL","NULL","NULL","7"};
    BT bt(nodes);
    bt.layerorder();
    bt.queue_layerorder();

    bt.preorder();
    bt.morris_preorder();
    bt.stack_preorder();

    bt.inorder();
    bt.morris_inorder();
    bt.stack_inorder();

    bt.postorder();
    bt.morris_postorder();
    bt.stack_postorder();
}