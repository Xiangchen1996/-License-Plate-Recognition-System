#ifndef TCPTHREAD_H
#define TCPTHREAD_H


#include <QThread>
#include <QMutex>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <jsonparser.h>
#include <dbhelper.h>
#include <jsonwrapper.h>
#include <workqueue.h>
#include <QTimer>

class TcpThread : public QThread
{
    Q_OBJECT
private:
    int socketDescriptor;
    QMutex *mutex;
    bool running;
    QTcpSocket *tcpSocket;
    QString ip;
    int serial;
    JsonParser *parser;
    JsonWrapper *wrapper;
    QString rev_path;
    bool isData;
    bool detect;
    QTimer *testTimer;
    QString fileName;
public:
    explicit TcpThread(bool data,QObject *parent=0);
    void run();
    void setSerial(int num);
    int getSerial();
    void setArgs(int socketDescriptor,QMutex *mutex);
    void reset();
    bool getRunningState();
    int getSocketDescriptor();
    void dispatcher(int code);
    QString getIP();

    void userLogin(QString id,QString pwd);
    void addPicRecord(QString name,int size,QString sendIP);
    void stopReceivePic(QString name);
    void sendMessage(QString message);

private slots:
    void readMessage();
    void revDone();
signals:
    void recycleThread(int num);

};

#endif // TCPTHREAD_H
