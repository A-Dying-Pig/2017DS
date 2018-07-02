#include "widget.h"
#include <QPixmap>
#include <QPushButton>
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //布局
    ui->setupUi(this);
    layout = new QGridLayout;
    layout->addWidget(ui->btn,2,6,1,1);
    layout->addWidget(ui->input,2,1,1,5);
    layout->addWidget(ui->output,6,1,10,6);
    layout->addWidget(ui->lbl_input,1,1,1,3);
    layout->addWidget(ui->lbl_sort,5,1,1,3);
    layout->addWidget(ui->by_times,5,3,1,1);
    layout->addWidget(ui->by_date,5,5,1,1);
    setLayout(layout);

    //设置显示文字
    ui->btn->setText(tr("搜索"));
    ui->lbl_input->setText(tr("请输入搜索关键词"));
    ui->lbl_input->setFont(QFont("Timers",10,60));
    ui->lbl_sort->setText(tr("优先按关键词出现次数排序(默认)"));
    ui->by_date->setText(tr("按发帖日期排序"));
    ui->by_times->setText(tr("按搜索词次数排序"));

    //window
    resize(QSize(1200,800));
    setWindowIcon(QIcon(":icon/digger.ico"));
    setWindowTitle(tr("铁甲网信息搜索"));

    //links
    ui->output->setOpenExternalLinks(true);

    //signal-slot
    connect(ui->btn,SIGNAL(clicked()),this,SLOT(btn_clicked()));
    connect(ui->by_times,SIGNAL(clicked()),this,SLOT(btn_clicked()));
    connect(ui->by_date,SIGNAL(clicked()),this,SLOT(btn_sort_by_date_clicked()));
}

Widget::~Widget()
{
    delete ui;
    delete layout;
}

void Widget::btn_clicked()
{
    QString t = ui->input->text();
    ui->lbl_sort->setText(tr("优先按关键词出现次数排序"));
    emit process(t.toStdWString());
}

void Widget::btn_sort_by_date_clicked()
{
    QString t = ui->input->text();
    ui->lbl_sort->setText(tr("优先按发帖日期排序"));
    emit process_date(t.toStdWString());
}

void Widget::output(QString tmp)
{
    ui->output->setText(tmp);
}
