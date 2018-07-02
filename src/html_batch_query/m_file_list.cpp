#include "m_file_list.h"

m_file_list::m_file_list()
{
    head = new list_node;
    rear = head;
    head->next = NULL;
    head->pre = NULL;
    head->webID = -1;
    head->times = HEADTIMES;		//从头到尾按次数不递增排序，所以头结点次数应该最大
}

m_file_list::~m_file_list()
{
    list_node * p = head, *q = head;  //p,q用来释放链表节点所占内存
    while(p)
    {
        q = p;
        p = p->next;
        delete(q);
    }
}

void m_file_list::edit(int webID,list_node src)
{
    list_node *p = search(webID);
    p->keyword = src.keyword;
    p->times = src.times;
    p->webID = src.webID;
    p->website = src.website;
}



void m_file_list::sort(list_node *p)
{
    list_node* p_pre = p->pre;
    while (p->pre->times < p->times)
    {
        p_pre = p->pre;
        p_pre->pre->next = p;
        p->pre = p_pre->pre;
        p_pre->next = p->next;
        if (p->next)	//p不是尾节点
            p->next->pre = p_pre;
        else
            rear = p->pre;
        p->next = p_pre;
        p_pre->pre = p;
    }
}

list_node * m_file_list::search (int webID)
{
    list_node * p = head->next;
    while (p)
    {
        if (p->webID == webID)
            return p;
        p = p->next;
    }
    return NULL;
}


void m_file_list::add(int webID, m_charstring<wchar_t> website, m_charstring<wchar_t> keyword)
{
    list_node *p = search(webID);
    if (p)
    {
        p->times++;
        sort(p);
    }
    else
    {
        list_node* tmp = new list_node;
        rear->next = tmp;
        tmp->pre = rear;
        rear = tmp;
        tmp ->next = NULL;
        tmp->times = 1;
        tmp->webID = webID;
        tmp->keyword = keyword;
        tmp->website = website;
    }
}

bool m_file_list::remove (int webID)
{
    list_node* p = search(webID);
    if (!p) return false;
    else
    {
        if (p->next)		//p不是尾节点
        {
            p->pre->next = p->next;
            p->next->pre = p->pre;
        }
        else               //p是尾节点
            p->pre->next = p->next;
        delete p;
    }
}
