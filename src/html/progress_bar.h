#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QProgressBar>
#include <QWidget>
#include <QLabel>

class progress_bar : public QWidget
{
    Q_OBJECT

public:
    QProgressBar *bar;
    QLabel *lbl;
    explicit progress_bar(QWidget *parent = 0);
public slots:
    void update_bar(int i);
};

#endif // PROGRESS_BAR_H
