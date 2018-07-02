#ifndef M_FILE_LIST_H_
#define M_FILE_LIST_H_
#include "m_charstring.h"

#define HEADTIMES 999999
struct list_node
{
    int webID;						//网页ID
    m_charstring<wchar_t> website;	//网页网址
    m_charstring<wchar_t> content;  //内容
    m_charstring<wchar_t> keyword;  //关键词
    m_charstring<wchar_t> title;    //标题
    m_charstring<wchar_t> author;   //作者
    m_charstring<wchar_t> date;     //发帖日期
    int times;						//单词在该文件出现次数
    list_node *next,*pre;
};


class m_file_list
{
    list_node *head, *rear;
public:
    m_file_list();
    ~m_file_list();
    void add (int webID,m_charstring<wchar_t> website,m_charstring<wchar_t> keyword,m_charstring<wchar_t> content,
              m_charstring<wchar_t> author,m_charstring<wchar_t> title,m_charstring<wchar_t> date);
    void sort (list_node * p);
    void edit (int webID, list_node src);
    list_node *search (int webID);
    bool remove (int webID);
    list_node* gethead(){return head;}
};


#endif
