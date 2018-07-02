#include "m_program.h"

m_program::m_program(QObject *parent):QObject(parent)
{
    thread = new m_thread;
    one = new progress_bar;
    two = new Widget;

    //connect
    connect(two,SIGNAL(process(std::wstring)),thread->html,SLOT(batch_query(std::wstring)));
    connect(two,SIGNAL(process_date(std::wstring)),thread->html,SLOT(batch_query_date(std::wstring)));
    connect(thread->html,SIGNAL(show_result(QString)),two,SLOT(output(QString)));
    connect(thread->html,SIGNAL(update_bar(int)),one,SLOT(update_bar(int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(show_progress_bar()),one,SLOT(show()));
    connect(thread,SIGNAL(show_search_page()),two,SLOT(show()));
    connect(thread,SIGNAL(show_search_page()),one,SLOT(hide()));

    //thread_start
    thread->start();
}

m_program::~m_program()
{
    thread->quit();
}
