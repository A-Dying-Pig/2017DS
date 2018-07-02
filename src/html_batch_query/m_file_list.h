#ifndef M_FILE_LIST_H_
#define M_FILE_LIST_H_
#include "m_charstring.h"

#define HEADTIMES 9999999
struct list_node
{
    int webID;						//网页ID
    m_charstring<wchar_t> website;	//网页网址
    m_charstring<wchar_t> keyword;  //关键词
    int times;						//单词在该文件出现次数
    list_node *next,*pre;
};


class m_file_list
{
    list_node *head, *rear;
public:
    m_file_list();
    ~m_file_list();
    void add (int webID,m_charstring<wchar_t> website,m_charstring<wchar_t> keyword);
    void sort (list_node * p);
    void edit(int webID,list_node src);
    list_node *search (int webID);
    bool remove (int webID);
    list_node* gethead(){return head;}
};


#endif
