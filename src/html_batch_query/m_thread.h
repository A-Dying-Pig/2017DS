#ifndef M_THREAD_H
#define M_THREAD_H

#include <QThread>
#include "html_analysis.h"
class m_thread:public QThread
{
    Q_OBJECT

public:
   html_analysis *html;
   explicit m_thread(QObject *parent = 0);
protected:
    virtual void run();
signals:
    void update_bar(int i);
    void show_progress_bar();
};

#endif // M_THREAD_H
