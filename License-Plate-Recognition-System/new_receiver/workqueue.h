#ifndef WORKQUEUE_H
#define WORKQUEUE_H

#include <QObject>
#include <QMutex>
#include <queue>

using namespace std;
class workQueue : public QObject
{
    Q_OBJECT
public:

    static workQueue *getInstance();

    void pop();
    void push(QString name);
    bool isEmpty();
    QString back();
    QString front();
    queue<QString> getWorkQueue();
private:
    explicit workQueue(QObject *parent = 0);
    static workQueue *wQueue;
    static QMutex *mutex;
    static queue<QString> names;


signals:
    void refreshQueue();
public slots:
};

#endif // WORKQUEUE_H
