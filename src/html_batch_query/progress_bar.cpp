#include "progress_bar.h"
#include <QIcon>

progress_bar::progress_bar(QWidget *parent) : QWidget(parent)
{
    //label
    lbl = new QLabel(this);
    lbl->setFont(QFont("Timers",10,65));
    lbl->setText(tr("处理进度"));
    lbl->move(80,55);
    lbl->show();

    //bar
    bar = new QProgressBar(this);
    bar->setFixedHeight(30);
    bar->setFixedWidth(500);
    bar->setRange(0,2000);
    bar->move(75,100);
    bar->show();

    //window
    setFixedSize(600,200);
    setWindowIcon(QIcon(":icon/digger.ico"));
    setWindowTitle(tr("铁甲网贴子信息批量处理"));
}


void progress_bar::update_bar(int i)
{
    bar->setValue(i);
}


void progress_bar::finish_program()
{
    lbl->setText(tr("处理完成！"));
}
