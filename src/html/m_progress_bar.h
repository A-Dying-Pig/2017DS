#ifndef M_PROGRESS_BAR_H
#define M_PROGRESS_BAR_H

#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include <QProgressBar>
#define MAXWEB 2000

class m_progress_bar: public QThread
{
    Q_OBJECT

public:

    QProgressBar *bar;
    QEventLoop *lop;
    explicit m_progress_bar(QObject *parent = 0);
protected:
     virtual void run()
    {
        bar->show();
        lop->exec();
    }

public slots:
    void finish();
    void update_bar(int i);


};

#endif // M_PROGRESS_BAR_H
