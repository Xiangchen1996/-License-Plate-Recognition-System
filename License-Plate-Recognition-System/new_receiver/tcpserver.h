#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QStringList>
#include <QTcpServer>
#include <QMutex>
#include <tcpthread.h>
#include <queue>
#include <list>
#include <QDebug>

using namespace std;
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(bool data);
    bool stopAllThread();
    TcpThread *obtainThread();

    list<QString> getIPList();
    void refreshNames();

protected:
    void incomingConnection(int socketDescriptor);

private:
    QStringList fortunes;
    QMutex *mutex;
    list<TcpThread*> workThread;
    queue<TcpThread*> allThread;
    list<int> waiting;
    list<QString> names;
    bool isData;

    void startWork(int socketDescriptor);

private slots:
    void notifyServer(int i);

signals:
    void refreshConnection();
};

#endif // TCPSERVER_H
