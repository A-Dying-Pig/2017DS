#ifndef M_CHARSTRINGLINK_H_
#define M_CHARSTRINGLINK_H_
#include <iostream>

template<typename T>
struct Node
{
    T value;
    Node<T>* next;
};

template<typename T>
class m_charstringlink
{
    Node<T> *head,*rear;
    int savednum;
public:
    m_charstringlink ();
    ~m_charstringlink ();
    void add (T element);
    void remove (T element);
    Node<T>* search (T element);
    Node<T>* gethead()
    {return head;}
};


template<typename T>
m_charstringlink<T>::m_charstringlink()
{
    savednum = 0;
    head = new Node<T>;
    head->next = NULL;
    head->value = 0;
    rear = head;
}

template<typename T>
m_charstringlink<T>::~m_charstringlink()
{
    Node<T> *p = head,*q = head;
    rear = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
}

template<typename T>
void m_charstringlink<T>::add(T element)
{
    Node<T> * temp = new Node<T>;
    temp->next = NULL;
    temp->value = element;
    rear->next = temp;
    rear = temp;
    savednum++;
}

template<typename T>
void m_charstringlink<T>::remove (T element)
{
    Node<T>* p = head, *q = head;
    while(p->next)
    {
        if (p->next->value == element)
        {
            q = p->next;
            p->next = p->next->next;
            if (!p->next) rear = p;
            savednum--;
            delete q;
        }
        else
            p = p->next;
    }
}

template<typename T>
Node<T>* m_charstringlink<T>::search (T element)
{
    Node<T>*p = head;
    while (p)
    {
        if (p->value == element)
            return p;
        else
            p = p->next;
    }
    return NULL;
}

#endif



