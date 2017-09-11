#include "donequeue.h"

DoneQueue::DoneQueue(QObject *parent) : QObject(parent)
{

}

QMutex *DoneQueue::mutex=new QMutex();
DoneQueue *DoneQueue::wQueue=NULL;
queue<QString> DoneQueue::names;

DoneQueue *DoneQueue::getInstance()
{
    mutex->lock();
    if(NULL==wQueue)
    {
        wQueue=new DoneQueue();
    }
    mutex->unlock();
    return wQueue;
}


QString DoneQueue::back()
{
    return names.back();
}

QString DoneQueue::front()
{
    return names.front();
}

bool DoneQueue::isEmpty()
{
    return names.empty();
}

void DoneQueue::pop()
{
    mutex->lock();
    names.pop();

    mutex->unlock();
    emit refreshQueue();
}

void DoneQueue::push(QString name)
{
    mutex->lock();
    names.push(name);

    mutex->unlock();
    emit refreshQueue();
}

queue<QString> DoneQueue::getDoneQueue()
{
    return names;
}
