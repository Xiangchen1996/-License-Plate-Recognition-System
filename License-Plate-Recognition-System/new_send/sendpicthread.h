#ifndef SENDPICTHREAD_H
#define SENDPICTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QString>
#include <QDataStream>
#include <QFileInfo>
#include "jsonparser.h"



class sendPicThread : public QThread
{
    Q_OBJECT
public:
    sendPicThread(QString hostIP);
    void run();
    void setPicPath(QString);
private:
    QTcpSocket *tcpSocket;
    QString hostIP;
    QString picPath;
    JsonParser *parser;

signals:
    void sendNextPic();
    void sendcurrentPic();
    void sendNo(int total,int current);//发送共发送数量与当前数量
    void closeThisThread();
    void stopSend();

private slots:
    void readMessage();
    void stopAndQuit();
};

#endif // SENDPICTHREAD_H
