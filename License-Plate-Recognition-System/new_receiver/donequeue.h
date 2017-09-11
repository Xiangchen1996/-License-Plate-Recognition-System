#ifndef DONEQUEUE_H
#define DONEQUEUE_H

#include <QObject>
#include <queue>
#include <QMutex>

using namespace std;
class DoneQueue : public QObject
{
    Q_OBJECT
public:
    static DoneQueue *getInstance();
    void pop();
    void push(QString name);
    bool isEmpty();
    QString back();
    QString front();
    queue<QString> getDoneQueue();
private:
    explicit DoneQueue(QObject *parent = 0);
    static DoneQueue *wQueue;
    static QMutex *mutex;
    static queue<QString> names;

signals:
    void refreshQueue();
public slots:
};

#endif // DONEQUEUE_H
