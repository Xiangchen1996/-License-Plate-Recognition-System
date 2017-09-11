#include "workqueue.h"

workQueue::workQueue(QObject *parent) : QObject(parent)
{

}

QMutex *workQueue::mutex=new QMutex();
workQueue *workQueue::wQueue=NULL;
queue<QString> workQueue::names;

workQueue *workQueue::getInstance()
{
    mutex->lock();
    if(NULL==wQueue)
    {
        wQueue=new workQueue();
    }
    mutex->unlock();
    return wQueue;
}

QString workQueue::back()
{
    return names.back();
}

QString workQueue::front()
{
    return names.front();
}

bool workQueue::isEmpty()
{
    return names.empty();
}

void workQueue::pop()
{
    mutex->lock();
    names.pop();

    mutex->unlock();
    emit refreshQueue();
}

void workQueue::push(QString name)
{
    mutex->lock();
    names.push(name);

    mutex->unlock();
    emit refreshQueue();
}

queue<QString> workQueue::getWorkQueue()
{
    return names;
}
