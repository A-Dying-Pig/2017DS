#include "html_analysis.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QColor>
#include "html_analysis.h"
#include <locale>
#include <windows.h>
#include "query_web_hash_table.h"
#include "qt_download_web.h"

#include "m_stack.h"
#define MAXSIZE 1024
using namespace std;

int html_analysis::extractInfo(string filename)
{
    ifstream in("./input/"+filename,ios::in);
    if(!in.is_open())
        return 0;
    char temp;
    string url;
    int order;
    in>>url;
    qt_download_web * web = new qt_download_web;
    connect(web,SIGNAL(start_analyse(int,QString)),this,SLOT(analyse(int,QString)));
    connect(this,SIGNAL(continue_analyse()),web->loop,SLOT(quit()));
    while(!in.eof())
    {
        in>>order>>temp>>temp>>url;
        url.pop_back();
        web->set(url,order);
    }
    delete web;
    return order;
}


void html_analysis::run(std::string filename)
{
    initDictionary();
    extractInfo(filename);
    //clear "result.txt"
    std::ofstream _clear("result.txt",std::ios::trunc);
    _clear.close();
    batch_query("query.txt");
    emit finished();
}


void html_analysis::analyse(int order,QString str)
{
    wchar_t t = 0;
    std::wstring Hl = str.toStdWString();
    int substancetimes = 0,record = 0,websitetimes = 0,locktimes = 0;
    bool trigger = false,head = true;
    bool start_write = false;
    m_charstring<wchar_t> content;
    m_stack<wchar_t *> _stack;
    m_charstring<wchar_t> website,substance;
    m_charstringlink<wchar_t *>seg;



        //Process
        long len = Hl.size();
        for (int i = 0; i < len; i++)
        {
            t = Hl[i];
                    if (record == 3 && !substancetimes)					//记录发帖内容
                {
                    if (start_write)
                            substance.concat(t);
                }

            if (t == L'<')							//用<>判断是否为标签，及头标签或尾标签
                {
                    trigger = true;
                    i++;
                    t = Hl[i];
                    if (t == L'/')	head = false;
                    else   head = true;
                }
            else if (t == L'>')
                {
                    trigger = false;
                    if (content.back() == L'/') head = false;

                    //头标签
                    if (head)
                    {
                        wchar_t *tem = (wchar_t*)malloc(sizeof(wchar_t)*wcslen(content._str())+2);
                        wcscpy(tem,content._str());

                        //<br />和<r />不进栈，其他标签进栈
                        if ((content.getSavednum() != 3 || content.indexOf("br ") == -1 )&&
                            (content.getSavednum() != 2 ||content.indexOf("r ")== -1)&&
                            (content.getSavednum() != 1 ||content.indexOf("r")== -1 )&&
                            (content.getSavednum() != 2 ||content.indexOf("br")== -1)&&
                             content.indexOf("img "))
                            _stack.push(tem);
                        else
                        {
                            if (record == 3 && start_write)
                                rid_back(substance);
                            free(tem);
                        }

                         //发帖内容模块
                        if (record == 3)
                        {
                            if (content.indexOf("ignore_js") != -1 ||
                                content.indexOf("div") != -1 ||
                                content.indexOf("a ") != -1)
                            {

                                if (start_write)
                                    rid_back(substance);
                                locktimes ++;
                                start_write = false;

                            }
                            else if (content.indexOf("font ")!=-1)
                            {
                                if (start_write)
                                    rid_back(substance);
                            }
                        }
                        //非发帖内容模块
                        else
                        {
                            if (content.indexOf("td class=\"t_f\"")!= -1 && !substancetimes)
                            {
                                 start_write = true;
                                 record = 3;
                            }
                        }
                        content.clear();
                    }
                    //尾标签
                    else
                    {
                        //非<br /> 和 <r />，则出栈
                        if ((content.getSavednum() != 4 || content.indexOf("br /") == -1 ) &&
                            (content.getSavednum() != 3 ||content.indexOf("r /")== -1 ) &&
                            (content.getSavednum() != 3 ||content.indexOf("br/")== -1)  &&
                            (content.getSavednum() != 2 ||content.indexOf("r/") == -1) &&
                             content.indexOf("img "))
                        {
                            wchar_t * popout = _stack.pop();
                            if (popout)
                            {
                                free(popout);

                                if (record == 3 && !substancetimes)	//当查找标签出栈时，停止记录
                                {

                                    if (content.indexOf("ignore_js") != -1 ||
                                        content.indexOf("div") != -1 ||
                                        content.indexOf("/a") != -1)
                                    {
                                        locktimes --;
                                        if (!locktimes)
                                            start_write = true;
                                    }
                                    else if (content.indexOf("/font")!=-1)
                                    {
                                        if (start_write)
                                            rid_back(substance);
                                    }
                                    else if (content.indexOf("/td") !=-1)
                                    {
                                         record = 0;
                                         substancetimes++;
                                         break;
                                    }
                                 }
                                else if (content.indexOf("link href=")!= -1 && websitetimes == 0)
                                 {
                                     websitetimes++;
                                     get_website(content,website);
                                 }
                            }
                        }
                        else
                        {
                            if (record == 3 && start_write)
                                rid_back(substance);
                        }
                            content.clear();
                    }
                }

            if (trigger) content.concat(t); //记录标签内容
        }


        //整理记录数据，去除由于上述处理方法，所导致的系统误差
        if (start_write)
            rid_back(substance);
        modify_substance(substance);

        //分词
        divideWords(substance,seg,order,website);
        //输出分词
        Node<wchar_t *> * p = seg.gethead()->next,*q = p;
        while (p)
        {
            q = p;
            p = p->next;
            free(q->value);
        }
        wchar_t * clearstack;
        //清空栈，避免内存泄漏
        while (!_stack.empty())
        {
            clearstack = _stack.pop();
            free(clearstack);
        }
        emit update_bar(order);
        emit continue_analyse();
}

void html_analysis::get_website(m_charstring<wchar_t>&str,m_charstring<wchar_t>&website)
{
    //抽取网址
    int n =str.getSavednum();
    wchar_t *temp = str._str();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (temp[i] == L'"')
        {
            count++;
            continue;
        }
        if (count == 1) website.concat(temp[i]);
        else if (count > 1 ) return;
    }
}

void html_analysis::modify_substance(m_charstring<wchar_t>&substance)
{
    int n =substance.getSavednum();
    bool  trigger = false;
    wchar_t *temp = substance._str(), tempconvert = 0;
    unsigned int code = 0;
    m_charstring<wchar_t> chartemp;
    wstringstream convert;
    for (int i = 0; i < n; i++)
    {
        if (temp[i] == L'\n' || temp[i]== L' ' || temp[i] == L'\r')	continue;

        if (temp[i] != L'#' && temp[i] != L'&' && temp[i] != L';' && trigger)
            convert <<temp[i];
        //将&#23453;类符号转为汉字
        else if (temp[i] == L'&' && temp[i+1] == L'#')
            {
                trigger = true;
                i = i + 1;
            }
        else if (temp[i] == L';' && trigger)
        {
            trigger = false;
            convert>>code;
            tempconvert = code;
            convert.str(L"");
            if (convert.eof())
                convert.clear();
            chartemp.concat(tempconvert);
        }
        else if (!trigger)
        {
            //去除&nbsp,<br />,<r >,<r />
            if (temp[i] == L'&'&& i+5 <= n-1 && temp[i+1]== L'n' &&temp[i+2]==L'b'&& temp[i+3] == L's' &&temp[i+4] == L'p'&&temp[i+5] ==L';')
                i += 5;
            else if (temp[i] == L'<' && i +5 <= n -1 && temp[i+1]== L'b' &&temp[i+2]==L'r'&& temp[i+3] == L' ' &&temp[i+4] == L'/'&&temp[i+5] ==L'>' )
                i += 5;
            else if (temp[i] == L'<' && i + 4 <= n -1 && temp[i+1]== L'r' &&temp[i+2]==L' ' && temp[i+3] ==L'/'&& temp[i+4] ==L'>')
                i += 4;
            else if (temp[i] == L'<' && i + 3 <= n -1 && temp[i+1]== L'r' &&temp[i+2]==L' ' && temp[i+3] ==L'>')
                i += 3;
            else
                chartemp.concat(temp[i]);
        }
    }
    substance = chartemp;
}


void html_analysis::initDictionary()
{
    char ctemp[100];
    wchar_t* temp;
    int count = 1;
    //初始化不同的词库
    ifstream in ("./dictionary/dic.dic",ios::in);
    while(!in.eof())
    {
        in>>ctemp;
        temp = UTF8toWC((char*)ctemp);
        tree.insert(temp,count);
        count++;
        free(temp);
    }

    wchar_t term[6];
    wifstream interm("./dictionary/term.txt",ios::in);
    setlocale(LC_ALL,"chs");
    while(!interm.eof())
    {
        interm>>term;
        tree.insert(term,count);
        count++;
    }
}


wchar_t * html_analysis::UTF8toWC (char *utf8)
{
     int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
     wchar_t* wstr = new wchar_t[len+1];
     memset(wstr, 0, len+1);
     MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
     return wstr;
}

html_analysis::html_analysis(QObject *parent) : QObject(parent)
{
    website_count = 1;
}

html_analysis::~html_analysis()
{
}

void html_analysis::divideWords(m_charstring<wchar_t> &str,m_charstringlink<wchar_t *>&seg,int webID,m_charstring<wchar_t> website)
{

    int n = str.getSavednum();
    if (!n) return;
    wchar_t temp[WORDMAXSIZE+1],*target = str._str();
    int j = n - WORDMAXSIZE,len = WORDMAXSIZE;
    node* search_result = NULL; //二叉树搜索结果
    while(len)
    {
        wcscpy(temp,&target[j]);
        //找到词库中的词
        search_result = tree.search(temp);
        if (search_result)
        {
            //建立文档链表
            search_result->file.add(webID,website,temp);
            search_result->Occur++;
            target[j] = '\0';
            if (j >= WORDMAXSIZE)
            {
                wchar_t * word = new wchar_t[len + 1];
                wcscpy(word,temp);
                seg.add(word);
                j -= WORDMAXSIZE;
                len = WORDMAXSIZE;
            }
            else
            {
                wchar_t * word = new wchar_t[len + 1];
                wcscpy(word,temp);
                seg.add(word);
                len = j;
                j = 0;
            }
        }
        else
        {
            if (len == 1)
            {
                target[j] = '\0';
                if (j >= WORDMAXSIZE)
                {
                    j -= WORDMAXSIZE;
                    len = WORDMAXSIZE;
                }
                else
                {
                    len = j;
                    j = 0;
                }
            }
            else
            {
                j++;
                len--;
            }
        }
    }
}


void html_analysis::rid_back(m_charstring<wchar_t> &str)
{
    while(str.getSavednum() && str.pop_back() != L'<')
    {}
}


void html_analysis::batch_query(std::string file)
{
        std::wstring tmp;
        wifstream in (file,ios::in);
        setlocale( LC_ALL, "chs" );
        int querytimes = 0, wordnum = 0,len = 0,wordlen = 0;	//查询次数,每次查询词数,字符串长度,查询词长度
        bool ok = true;						//用来控制计数
        wchar_t *T = NULL;
        query_web_hash_table hash;

        while(getline(in,tmp))				//获取一行查询
        {
            m_charstringlink<wchar_t*> first;
            ok = true;
            querytimes++;
            wordnum = 0;
            len = tmp.size();
            for (int j = 0; j < len;j ++)
            {
                if (!ok && (tmp[j] == L' '|| tmp[j] == ' '))
                    {
                        ok = true;
                        T[wordlen] = '\0';
                        first.add(T);
                    }
                else if (ok && (tmp[j] != L' '&& tmp[j] != ' '))
                {
                    T = new wchar_t[WORDMAXSIZE + 3];
                    wordlen = 0;
                    ok = false;
                    wordnum ++;
                    T[wordlen] = tmp[j];
                    wordlen++;
                }
                else if (!ok && (tmp[j] != L' '&& tmp[j] != ' '))
                {
                    T[wordlen] = tmp[j];
                    wordlen++;
                }
            }
            if (T[0]!='\0')
            {
                T[wordlen] = '\0';
                first.add(T);
            }

            //根据输入进行查询
            node* wordtmp = NULL;
            Node<wchar_t *> * p = first.gethead()->next;
            while (p)			//构建搜索结果哈希表
            {
                wordtmp = tree.search(p->value);
                if (wordtmp)
                {
                    list_node * file_ptr = wordtmp->file.gethead()->next;
                    while(file_ptr)
                    {
                        hash.insert(file_ptr);
                        file_ptr = file_ptr->next;
                    }
                }
                free(p->value);
                p = p->next;
            }
            //由哈希表和存储符合搜索结果的webID的排序链表输出结果
            hash.get_variance(wordnum);		//计算查询词出现次数分散程度
            hash.sort();					//根据查询词出现总次数和分散程度排序
            hash.output();
            //reset hash table
            hash.reset();
        }
}
