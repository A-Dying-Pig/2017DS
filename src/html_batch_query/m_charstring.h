#ifndef M_CHARSTRING_H_
#define M_CHARSTRING_H_

#include <stdlib.h>
#include <string>
#define STRINGMAXSIZE 64

template<typename T>
class m_charstring
{
    T* Str;
    int Maxsize,Savednum;
public:
    m_charstring (int size = STRINGMAXSIZE);
    m_charstring (T* src);
    m_charstring (std::string src);
    m_charstring (const m_charstring<T> &src);
    ~m_charstring (){
        free(Str);
    }
    int indexOf(m_charstring str);
    int indexOf(std::string);
    m_charstring substring (int start, int length);
    void concat (m_charstring str);
    void concat (T str);
    void operator = (m_charstring src);
    bool operator == (m_charstring src);
    bool operator < (m_charstring src);
    bool operator > (m_charstring src);
    int getSavednum ()
    {return Savednum;}
    void _itoa (int i);
    void clear();
    T* _str();
    T pop_back();
    T back();
};

template<typename T>
bool m_charstring<T>::operator==(m_charstring<T> src)
{
    if (wcscmp(Str,src._str()) == 0) return true;
    else return false;
}

template<typename T>
bool m_charstring<T>::operator < (m_charstring<T> src)
{
    if (wcscmp(Str,src._str()) < 0) return true;
    else return false;
}

template<typename T>
bool m_charstring<T>::operator > (m_charstring<T> src)
{
    if (wcscmp(Str,src._str()) > 0) return true;
    else return false;
}

template<typename T>
m_charstring<T>::m_charstring(const m_charstring<T> &src)
{
    Savednum = src.Savednum;
    Maxsize = Savednum + STRINGMAXSIZE;
    Str = (T *)malloc(sizeof(T)*Maxsize);
    for (int i = 0; i < Savednum; i++)
        Str[i] = src.Str[i];
    Str[Savednum] = '\0';
}

template<typename T>
void m_charstring<T>::clear()
{
    Savednum = 0;
    Str[0] = '\0';
}

template<typename T>
void m_charstring<T>::concat(T str)
{
    Savednum ++;
    if (Maxsize <= Savednum)
    {
        Maxsize = Savednum + STRINGMAXSIZE;
        Str = (T *)realloc(Str,sizeof(T)*Maxsize);
    }
    Str[Savednum-1] = str;
    Str[Savednum] = '\0';
}


template<typename T>
void m_charstring<T>::_itoa(int i)
{
    T *p = Str;
    Savednum = 0;
    itoa(i,Str,10);
    while(*p)
    {
        Savednum++;p++;
    }
    Str[Savednum] = '\0';
}

template<typename T>
m_charstring<T>::m_charstring(int size):Maxsize(size),Savednum(0)
{Str = (T*)malloc(sizeof(T)*Maxsize);}

template<typename T>
m_charstring<T>::m_charstring(std::string src)
{
    Savednum = src.length();
    Maxsize = Savednum + STRINGMAXSIZE;
    Str = (T*)malloc(sizeof(T)*Maxsize);
    for (int i = 0; i < Savednum; i ++)
        Str[i] = src[i];
    Str[Savednum]='\0';
}

template<typename T>
m_charstring<T>:: m_charstring(T *src)
{
    T *p =src;
    Savednum = 0;
    while(*p)
    {
        Savednum++;p++;
    }
    Maxsize = Savednum + STRINGMAXSIZE;
    Str = (T *)malloc(sizeof(T)*Maxsize);
    for (int i = 0; i < Savednum; i++)
        Str[i] = src[i];
    Str[Savednum] = '\0';
}

template<typename T>
int m_charstring<T>::indexOf(m_charstring<T> str)
{return indexOf(Str);}

template<typename T>
int m_charstring<T>::indexOf(std::string str)
{
    int i = 0,j = 0 ;
    int n = str.length();
    if (Savednum<n) return -1;
    for (i = 0; i <= Savednum - n; i++ )
    {
        for (j = 0; j < n; j++)
        {
            if (Str[i+j] != str[j])
                break;
        }
        if (j == n) break;
    }
    if (i == Savednum - n +1) return -1;
    else return i;
}


template<typename T>
void m_charstring<T>::concat(m_charstring<T> str)
{
    int temp = Savednum;
    Savednum += str.Savednum;
    if (Maxsize <= Savednum)
    {
        Maxsize = Savednum + STRINGMAXSIZE;
        Str = (T *)realloc(Str,sizeof(T)*Maxsize);
    }
    for (int i = temp; i < Savednum;i++)
        Str[i] = str.Str[i - temp];
    Str[Savednum] = '\0';
}



template<typename T>
m_charstring<T> m_charstring<T>::substring (int start, int length)
{
    m_charstring<T> result(length+STRINGMAXSIZE);
    for (int i = 0; i<length; i ++)
        result.Str[i] = Str[i+start];
    result.Savednum = length;
    result.Str[result.Savednum] = '\0';
    return result;
}


template<typename T>
void m_charstring<T>::operator = (m_charstring<T> src)
{
    T *p =src.Str;
    Savednum = 0;
    while(*p)
    {
        Savednum++;p++;
    }
    if (Maxsize <= Savednum)
    {
        Maxsize = Savednum + STRINGMAXSIZE;
        Str = (T *)realloc(Str,sizeof(T)*Maxsize);
    }

    for (int i = 0; i < Savednum; i++)
            Str[i] = src.Str[i];
    Str[Savednum] = '\0';
}

template<typename T>
T* m_charstring<T>::_str()
{
    return Str;
}

template<typename T>
T m_charstring<T>::pop_back()
{
    if (Savednum == 0) return NULL;
    Savednum--;
    T temp = Str[Savednum];
    Str[Savednum] = '\0';
    return temp;
}

template<typename T>
T m_charstring<T>::back()
{return Str[Savednum - 1];}

#endif
