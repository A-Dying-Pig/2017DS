#ifndef M_STACK_H_
#define M_STACK_H_

#include <stdlib.h>
#include "m_charstring.h"
#define STACKMAXSIZE	100

template<typename T>
class m_stack
{

    int Maxsize,Savednum;
public:
    T *Base,*Top;
    m_stack(int size = STACKMAXSIZE):Maxsize (size),Savednum(0)
    {
        Base = (T *)malloc(sizeof(T)*size);
        Top = Base;
    }
    ~m_stack(){free(Base);}
    bool push (T element);
    T pop ();
    T top ();
    bool empty();
};


template<typename T>
bool m_stack<T>::push(T element)
{
    if(Savednum == Maxsize)
    {
        Base = (T *)realloc(Base,sizeof (T)*(Maxsize+STACKMAXSIZE));
        Maxsize += STACKMAXSIZE;
        Top = &Base[Savednum-1];
    }
    if (Base == NULL) return false;
    *Top = element;
    Top++;
    Savednum++;
    return true;
}

template<typename T>
T m_stack<T>::top ()
{
    if (Top != Base)
        return *(Top - 1);
    else
        return NULL;
}

template<typename T>
T m_stack<T>::pop ()
{
    if (Top != Base)
    {
        Top--;
        Savednum--;
        return *Top;
    }
    else
        return NULL;
}

template<typename T>
bool m_stack<T> ::empty()
{
    if (Top == Base) return true;
    else return false;
}



#endif
