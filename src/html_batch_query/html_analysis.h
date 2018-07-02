#ifndef HTML_ANALYSIS_H_
#define HTML_ANALYSIS_H_

#include <QObject>
#include <string>

#include "m_charstring.h"
#include <iostream>
#include "m_charstringlink.h"
#include "m_balanced_binary_tree.h"
#include "m_file_list.h"

#define WORDMAXSIZE 2

class html_analysis: public QObject
{
     Q_OBJECT

    m_balanced_binary_tree tree;
    int website_count;
public:
    explicit html_analysis(QObject *parent = 0);
    ~html_analysis();
    void divideWords( m_charstring<wchar_t> &str,m_charstringlink<wchar_t *>&seg,int webID,m_charstring<wchar_t> website);
    void initDictionary();
    bool getcontent(std::string url,int i);
    int extractInfo (std::string filename);
    wchar_t * UTF8toWC (char *utf8);
    void run (std::string filename);
    void rid_back(m_charstring<wchar_t> &str);
    void modify_substance(m_charstring<wchar_t> &substance);
    void get_website(m_charstring<wchar_t>&str,m_charstring<wchar_t>&website);
    void batch_query(std::string file);

signals:
    void show_result(QString tmp);
    void continue_analyse();
    void update_bar(int i);
    void finished();
public slots:
     void analyse (int order, QString str);
};


#endif
