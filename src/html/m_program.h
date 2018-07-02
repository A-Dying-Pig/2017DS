#ifndef M_PROGRAM_H
#define M_PROGRAM_H

#include <QObject>
#include "m_thread.h"
#include "widget.h"
#include "progress_bar.h"
#include "html_analysis.h"

class m_program:public QObject
{
    Q_OBJECT

public:
    m_thread * thread;
    progress_bar *one;
    Widget *two;
    explicit m_program(QObject *parent = 0);
    ~m_program();

};

#endif // M_PROGRAM_H
