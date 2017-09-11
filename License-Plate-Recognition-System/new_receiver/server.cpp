#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    defaultCommandPort=4444;
    dataPort=9999;
    runningState=true;
    DBHelper::getInstance()->initial();
    initSocket();
}




void Server::initSocket()
{
    commandSocket=new TcpServer(false);
    dataSocket=new TcpServer(true);
    if(!commandSocket->listen(QHostAddress::Any, defaultCommandPort))
    {
        qDebug()<<"server cannot open socket";
        return;
    }
    if(!dataSocket->listen(QHostAddress::Any,dataPort))
    {
        qDebug()<<"server cannot open socket";
        return;
    }
    runningState=true;
    qDebug()<<"Server -------> init success on port "<<defaultCommandPort;

}

void Server::startServer()
{
    if(!runningState)
    {
        if(!commandSocket->listen(QHostAddress::Any, defaultCommandPort))
        {
            qDebug()<<"server cannot open socket";
            return;
        }
        if(!dataSocket->listen(QHostAddress::Any,dataPort))
        {
            qDebug()<<"server cannot open socket";
            return;
        }
        runningState=true;
        qDebug()<<"Server -------> start success on port "<<defaultCommandPort;
    }
}

void Server::stopServer()
{
    if(runningState)
    {
        commandSocket->stopAllThread();
        dataSocket->stopAllThread();
        commandSocket->close();
        dataSocket->close();
        runningState=false;
        qDebug()<<"Server -------> stop success";
    }
}

int Server::getCommandPort()
{
    return defaultCommandPort;
}

bool Server::getRunningState()
{
    return runningState;
}

void Server::setCommandPort(const int port)
{
    defaultCommandPort=port;
}

TcpServer* Server::getCommandSocket()
{
    return commandSocket;
}

TcpServer* Server::getDataSocket()
{
    return dataSocket;
}
