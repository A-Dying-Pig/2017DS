#include "m_progress_bar.h"

m_progress_bar::m_progress_bar(QObject *parent):QThread(parent)
{
    bar = new QProgressBar;
    lop = new QEventLoop;
    bar->setFixedHeight(25);
    bar->setRange(0, MAXWEB);

}

void m_progress_bar::finish()
{
    lop->quit();
}

void m_progress_bar::update_bar(int i)
{
    bar->setValue(i);
}
