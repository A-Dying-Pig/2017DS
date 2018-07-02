#include <fstream>
#include <QTextCodec>
#include <QFile>
#include "qt_download_web.h"


qt_download_web::qt_download_web( QObject *parent):QObject(parent)
{
    timer = new QTimer;
    loop = new QEventLoop;
    m_NetManger = new QNetworkAccessManager;
    timer->setInterval(8000);

    //connect
    connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));
    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
    connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),timer, SLOT(stop()));
}

void qt_download_web::set(std::string url, int ID)
{
     webID = ID;
     QUrl web(url.c_str());
     m_Reply = m_NetManger->get(QNetworkRequest(web));
     timer->start();
     loop->exec();
}


qt_download_web::~qt_download_web()
{
    delete m_NetManger;
}

void qt_download_web::finishedSlot(QNetworkReply *)
{

    m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (m_Reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_Reply->readAll();
        QTextCodec* pCodec = QTextCodec::codecForName("gbk");
        QString string = pCodec->toUnicode(bytes);
        emit start_analyse(webID,string);
     }
     else
      {
            qDebug()<< m_Reply->errorString();
      }

      m_Reply->deleteLater();
}

