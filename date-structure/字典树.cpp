/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       字典树.cpp
  * @brief      插入、查找、匹配、删除
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
#include <string>

using namespace std;

class Trie {
public:

    class TreeNode{
        public:
            TreeNode* ch[26];
            bool isWord;
            TreeNode():isWord(false){
                for(int i=0;i<26;++i){
                    ch[i] = nullptr;
                }
            }
    };

    TreeNode* root;
    
    /** Initialize your data structure here. */
    Trie() {
        root = new TreeNode();
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TreeNode* node = root;
        for( char c:word ){
            int num = c-'a';
            if( !node->ch[ num ] ){ // nullptr
                node->ch[ num ] = new TreeNode();
            }
            node = node->ch[ num ];
        }
        node->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TreeNode* node = root;
        for( char c:word ){ // 如果没有其中的字符，返回false
            int num = c-'a';
            if( !node->ch[ num ] ){ // nullptr
                return false;
            }
            node = node->ch[ num ];
        }
        if( node->isWord ) return true; // 是一个单词，返回true
        else return false; // 不是一个单词，可能只是其他单词的前缀
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TreeNode* node = root;
        for( char c:prefix ){ // 如果没有其中的字符，返回false
            int num = c-'a';
            if( !node->ch[ num ] ){ // nullptr
                return false;
            }
            node = node->ch[ num ];
        }
        return true;
    }

    // 删除单词
    void remove(string word) {
        TreeNode *node = root , *hasword = root;
        int pos = 0;
        for( int i=0;i<word.size();++i ){ // 如果没有其中的字符，返回false
            int num = word[i]-'a';
            if( !node->ch[ num ] ){ // nullptr
                return;
            }
            if( node->isWord ){ // 如果碰到有字符串，则储存该节点
                hasword = node;
                pos = i;
            }
            node = node->ch[ num ];
        }
        if( node->isWord ){ // 如果存在该word
            // 1.如果此word是字典中某word的子串，只设置node->isWord为false
            for( int j=0;j<26;++j ){
                if( node->ch[j] ){
                    node->isWord = false;
                    return;
                }
            }
            // 2.如果此word不是字典中某word的子串，删除hasword到此处的路径
            node->isWord = false;
            TreeNode* delnode = hasword->ch[ word[pos]-'a' ];
            hasword->ch[ word[pos]-'a' ] = nullptr;
            for( int j=pos+1;j<word.size();++j ){
                int num = word[j]-'a';
                TreeNode *temp = delnode;
                delnode = delnode->ch[ num ];
                delete temp;
            }
        }
    }
};

int main(){

    Trie trie;
    
    trie.insert("apple");
    cout << " insert apple " <<endl;
    cout << " search apple " << trie.search("apple") << endl;   // 返回 True
    cout << " search app " << trie.search("app") << endl;     // 返回 False
    cout << " startsWith app " << trie.startsWith("app") << endl; // 返回 True
    cout << endl;

    trie.insert("app");
    cout << " insert app " <<endl;
    cout << " search app " << trie.search("app") << endl;     // 返回 True
    cout << endl;
    
    trie.remove("a");
    cout << " remove a " <<endl;
    cout << " search apple " << trie.search("apple") << endl;   // 返回 True
    cout << " search app " << trie.search("app") << endl;     // 返回 True
    cout << " startsWith app " << trie.startsWith("app") << endl; // 返回 True
    cout << endl;
    
    trie.remove("apple");
    cout << " remove apple " <<endl;
    cout << " search apple " << trie.search("apple") << endl;   // 返回 false
    cout << " search app " << trie.search("app") << endl;     // 返回 True
    cout << " startsWith app " << trie.startsWith("app") << endl; // 返回 True
    cout << endl;

    trie.remove("app");
    cout << " remove app " <<endl;
    cout << " search apple " << trie.search("apple") << endl;   // 返回 False
    cout << " search app " << trie.search("app") << endl;     // 返回 False
    cout << " startsWith app " << trie.startsWith("app") << endl; // 返回 False
    cout << endl;
    
}