#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QGridLayout>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT


public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:

    QGridLayout *layout;
    Ui::Widget *ui;

signals:
    void process (std::wstring tmp);
    void process_date (std::wstring tmp);

public slots:
    void btn_clicked();
    void btn_sort_by_date_clicked();
    void output(QString tmp);

};

#endif // WIDGET_H
