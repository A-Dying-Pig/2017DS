#include "m_program.h"
#include <QApplication>
#include <qdebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    m_program m_p;
    return a.exec();
}
