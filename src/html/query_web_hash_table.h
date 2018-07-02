#ifndef QUERY_WEB_HASH_TABLE_H_
#define QUERY_WEB_HASH_TABLE_H_

#include "m_file_list.h"
#define MAX_INPUT_WEBSITE 4000		//最多输入网址


struct query_web_node
{
    list_node *value;
    query_web_node *next;
};

struct query_web_head
{
    int totaltimes;     //各个查询词出现的总次数
    double variance;       //表示各查询词出现次数的分散程度
    query_web_node * first,*rear;
};

struct sort_list		//排序链表，用来记录包含查询词的文档ID,按降序排列，初始最大值
{
    int webID;
    sort_list *next;
};
class query_web_hash_table
{ 
    sort_list list_head;
public:
    query_web_head m_hash[MAX_INPUT_WEBSITE];
    query_web_hash_table();
    ~query_web_hash_table();
    void get_variance (int word_num);		//输入查询词数
    void insert (list_node *p);
    void insert_hash(list_node* p);
    void reset();
    void insert_list(int webID);
    sort_list * first_of_list()
    {return list_head.next;}
    void sort ();
    void sort_by_date();
    double abs(double x);
};



#endif
