#ifndef QT_DOWNLOAD_WEB_H
#define QT_DOWNLOAD_WEB_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QTimer>
#include <QEventLoop>

class qt_download_web:public QObject
{
    Q_OBJECT

    QTimer *timer;
    QNetworkAccessManager *m_NetManger;
    QNetworkReply* m_Reply;
    int webID;
public:
    QEventLoop *loop;
    explicit qt_download_web( QObject *parent = 0);
    void set(std::string url, int ID);
    ~qt_download_web();
signals:
    void start_analyse(int ID,QString str);
public slots:
   void finishedSlot( QNetworkReply*);
};

#endif // QT_DOWNLOAD_WEB_H
