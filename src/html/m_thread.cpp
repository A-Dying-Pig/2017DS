#include "m_thread.h"

m_thread::m_thread(QObject *parent):QThread(parent)
{
    html = new html_analysis;
}

void m_thread::run()
{
    emit show_progress_bar();
    html->run("url.csv");
    emit show_search_page();
    exec();
}
