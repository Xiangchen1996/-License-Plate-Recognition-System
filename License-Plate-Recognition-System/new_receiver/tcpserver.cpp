#include "tcpserver.h"

TcpServer::TcpServer(bool data) :QTcpServer()
{
    this->isData=data;
    for(int i=0;i<10;i++){
        TcpThread *thread = new TcpThread(this->isData);
        allThread.push(thread);
        thread->setSerial(i);
        connect(thread,SIGNAL(recycleThread(int)),this,SLOT(notifyServer(int)));
    }
}



TcpThread* TcpServer::obtainThread()
{
    if(!allThread.empty())
    {
        TcpThread* t=allThread.front();
        allThread.pop();
        return t;
    }
    return NULL;
}

void TcpServer::notifyServer(int i)
{
    list<TcpThread*>::iterator itor;
    for (itor = workThread.begin(); itor != workThread.end(); ++itor)
    {
        if(((TcpThread*)*itor)->getSerial()==i){
            TcpThread *thread=((TcpThread*)*itor);
            thread->reset();
            allThread.push(thread);
            workThread.remove(thread);
            if(waiting.size()>0){
                int code=waiting.front();
                waiting.pop_front();
                startWork(code);
            }
            refreshNames();
            break;
        }

    }


}

void TcpServer::refreshNames()
{
    names.clear();
    list<TcpThread*>::iterator itor;
    for (itor = workThread.begin(); itor != workThread.end(); ++itor)
    {
        if(!((TcpThread*)*itor)->getIP().isEmpty())
        names.push_back(((TcpThread*)*itor)->getIP());
    }
    emit refreshConnection();
}

void TcpServer::startWork(int socketDescriptor)
{
    TcpThread *thread = obtainThread();
    if(NULL!=thread)
    {
        thread->setArgs(socketDescriptor,mutex);
        workThread.push_back(thread);
        thread->start();

        refreshNames();
    }
}


list<QString> TcpServer::getIPList()
{
    return names;
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    TcpThread *thread = obtainThread();
    if(NULL!=thread)
    {
        thread->setArgs(socketDescriptor,mutex);
        workThread.push_back(thread);
        thread->start();
        refreshNames();
    }else{
        waiting.push_back(socketDescriptor);
    }


}




bool TcpServer::stopAllThread()
{
    //TODO
    while(!workThread.empty())
    {
        ((TcpThread*)workThread.front())->reset();
//        ((TcpThread*)workThread.front())->quit();
//        ((TcpThread*)workThread.front())->wait();
//        delete ((TcpThread*)(workThread.front()));
        workThread.pop_front();
    }
    return true;
}
