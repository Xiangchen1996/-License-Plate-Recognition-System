#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <tcpserver.h>
#include <dbhelper.h>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void startServer();

    void stopServer();

    void setCommandPort(const int port);

    bool getRunningState();

    int getCommandPort();

    TcpServer* getCommandSocket();
    TcpServer* getDataSocket();


private:
    int defaultCommandPort;
    int dataPort;
    TcpServer *commandSocket;
    TcpServer *dataSocket;
    void initSocket();
    bool runningState;


signals:

public slots:
};

#endif // SERVER_H
