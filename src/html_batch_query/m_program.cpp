#include "m_program.h"

m_program::m_program(QObject *parent):QObject(parent)
{
    thread = new m_thread;
    one = new progress_bar;

    //connect
    connect(thread->html,SIGNAL(update_bar(int)),one,SLOT(update_bar(int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(show_progress_bar()),one,SLOT(show()));
    connect(thread->html,SIGNAL(finished()),one,SLOT(finish_program()));

    //thread_start
    thread->start();
}

m_program::~m_program()
{
    thread->quit();
}
