#ifndef M_BALANCED_BINARY_TREE_H_
#define M_BALANCED_BINARY_TREE_H_

#include "m_charstring.h"
#include "m_file_list.h"
#include <iostream>
#define WORD_MAX_SIZE 2

#define LH -1
#define EH 0
#define RH 1

struct node
{
    m_charstring<wchar_t> value;	//单词内容
    int wordID;						//单词ID
    int Occur;						//单词总出现次数
    int index;						//平衡因子
    m_file_list file;				//文档链表
    node *LChild, *RChild;
};

struct tree_root
{
    node* ptr[WORD_MAX_SIZE+1];
};


class m_balanced_binary_tree
{
    tree_root *root;
public:
    m_balanced_binary_tree();
    ~m_balanced_binary_tree();
    int insert_into_tree (node * &p,wchar_t *v, bool& taller,int wordID);	//1表示插入成功,0表示树中已存在要插入元素;insert_tree 是 insert的一个子程序
    bool insert (wchar_t * v,int wordID);									//true表示插入成功,在insert中按单词长度使单词加入不同的二叉平衡子树，每个子树的单词长度都一样，提高分词算法效率
    void adjust (node*& p, int type);
    node* search_subtree (m_charstring<wchar_t> str,node *tmp);
    node* search (m_charstring<wchar_t> str);
    void r_rotate (node *&p);
    void l_rotate (node *&p);
    void deletenode(node *p);
};




#endif
