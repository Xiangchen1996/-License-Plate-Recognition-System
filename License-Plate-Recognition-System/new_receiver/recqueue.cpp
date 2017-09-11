#include "recqueue.h"

RecQueue::RecQueue(QObject *parent) : QObject(parent)
{

}

QMutex *RecQueue::mutex=new QMutex();
RecQueue *RecQueue::rQueue=NULL;
queue<QString> RecQueue::names;

RecQueue *RecQueue::getInstance()
{
    mutex->lock();
    if(NULL==rQueue)
    {
        rQueue=new RecQueue();
    }
    mutex->unlock();
    return rQueue;
}

QString RecQueue::back()
{
    return names.back();
}

QString RecQueue::front()
{
    return names.front();
}

bool RecQueue::isEmpty()
{
    return names.empty();
}

void RecQueue::pop()
{
    mutex->lock();
    names.pop();

    mutex->unlock();
    emit refreshQueue();
}

void RecQueue::push(QString name)
{
    mutex->lock();
    names.push(name);

    mutex->unlock();
    emit refreshQueue();
}

queue<QString> RecQueue::getRecQueue()
{
    return names;
}
