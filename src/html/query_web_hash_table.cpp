#include "query_web_hash_table.h"
#include <iostream>
#include <QDebug>
#include <fstream>

query_web_hash_table::query_web_hash_table()
{
    list_head.next = NULL;
    list_head.webID = MAX_INPUT_WEBSITE+1;
    for (int i = 0; i < MAX_INPUT_WEBSITE; i++)
    {
            m_hash[i].totaltimes = 0;
            m_hash[i].variance = 0;
            m_hash[i].first = new query_web_node;
            m_hash[i].rear = m_hash[i].first;
            m_hash[i].first->value = NULL;
            m_hash[i].first->next = NULL;
    }
}

query_web_hash_table::~query_web_hash_table()
{
    sort_list *t1 = list_head.next,*t2 = t1;
    while(t1)
    {
        t2 = t1;
        t1 = t1->next;
        delete(t2);
    }
    for (int i = 0; i< MAX_INPUT_WEBSITE; i++)
    {
        query_web_node *p = m_hash[i].first,*q = p;
        while(p)
        {
            q = p;
            p = p->next;
            delete(q);
        }
    }
}

void query_web_hash_table::insert_hash(list_node *p)
{
    query_web_node *tmp = new query_web_node;
    tmp ->value = p;
    tmp ->next = NULL;
    m_hash[p->webID].totaltimes += p->times;
    m_hash[p->webID].rear->next = tmp;
    m_hash[p->webID].rear = tmp;
}

void query_web_hash_table::insert_list(int webID)
{
    sort_list *p = &list_head;
    while(p)
    {
        if (!p->next)
        {
            if (webID < p->webID)
            {
                sort_list *tmp = new sort_list;
                tmp->next = NULL;
                tmp->webID = webID;
                p->next = tmp;
                break;
            }
        }
        else
        {
            if (webID > p->next->webID)
            {
                sort_list *tmp = new sort_list;
                tmp->next = p->next;
                tmp->webID = webID;
                p->next = tmp;
                break;
            }
            else if (webID == p->next->webID)
                break;
        }
        p = p->next;
    }
}

void query_web_hash_table::insert(list_node * p)
{
    insert_hash(p);
    insert_list(p->webID);
}

double query_web_hash_table::abs(double x)
{
    if (x >= 0) return x;
    else return -x;
}

void query_web_hash_table::get_variance(int word_num)
{
    if (!word_num) return;
    sort_list *p = list_head.next;
    query_web_node * q = NULL;
    double avr = 0;
    int count = 0;
    while (p)
    {
        avr = m_hash[p->webID].totaltimes / word_num;
        q = m_hash[p->webID].first->next;
        while (q)
        {
            count++;
            m_hash[p->webID].variance += abs(q->value->times - avr);
            q = q->next;
        }
        m_hash[p->webID].variance += avr* (word_num - count);
        p = p -> next;
    }
}

void query_web_hash_table::sort()
{
    sort_list *p = list_head.next;
    if (!p)	return;
    sort_list *q = p->next;
    int temp = 0;
        while (q)	//冒泡排序
    {
        p = list_head.next;
        while (p && p->next)
        {
            if (m_hash[p->webID].totaltimes < m_hash[p->next->webID].totaltimes)
            {
                temp = p->next->webID;
                p->next->webID = p->webID;
                p->webID = temp;
            }
            else if (m_hash[p->webID].totaltimes == m_hash[p->next->webID].totaltimes)
            {
                if (m_hash[p->webID].variance > m_hash[p->next->webID].variance)
                {
                temp = p->next->webID;
                p->next->webID = p->webID;
                p->webID = temp;
                }
            }
            p = p->next;
        }
        q = q->next;
    }
}


void query_web_hash_table::sort_by_date()
{
    sort_list *p = list_head.next, *q = p->next;
    if (!p)	return;
    int temp = 0;
        while (q)	//冒泡排序
    {
        p = list_head.next;
        while (p && p->next)
        {
            if (m_hash[p->webID].first->next->value->date.compare_date
                    (m_hash[p->next->webID].first->next->value->date) == -1 )
            {
                temp = p->next->webID;
                p->next->webID = p->webID;
                p->webID = temp;
            }
            else if (m_hash[p->webID].first->next->value->date.compare_date
                     (m_hash[p->next->webID].first->next->value->date) == 0)
            {
                if (m_hash[p->webID].totaltimes < m_hash[p->next->webID].totaltimes)
                {
                    temp = p->next->webID;
                    p->next->webID = p->webID;
                    p->webID = temp;
                }
                else if (m_hash[p->webID].totaltimes == m_hash[p->next->webID].totaltimes)
                {
                    if (m_hash[p->webID].variance > m_hash[p->next->webID].variance)
                    {
                    temp = p->next->webID;
                    p->next->webID = p->webID;
                    p->webID = temp;
                    }
                }
            }
            p = p->next;
        }
        q = q->next;
    }
}


void query_web_hash_table::reset()
{
    sort_list *t1 = list_head.next,*t2 = t1;
    while(t1)
    {
        m_hash[t1->webID].totaltimes = 0;
        m_hash[t1->webID].variance = 0;
        query_web_node *p = m_hash[t1->webID].first->next,*q = p;
        while(p)
        {
            q = p;
            p = p->next;
            delete(q);
        }
        m_hash[t1->webID].first->next = NULL;
        m_hash[t1->webID].rear = m_hash[t1->webID].first;
        t2 = t1;
        t1 = t1->next;
        delete(t2);
    }
    list_head.next = NULL;

}
