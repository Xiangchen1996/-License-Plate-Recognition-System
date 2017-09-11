#ifndef RECQUEUE_H
#define RECQUEUE_H

#include <QObject>
#include <QMutex>
#include <queue>

using namespace std;
class RecQueue : public QObject
{
    Q_OBJECT
public:

    static RecQueue *getInstance();

    void pop();
    void push(QString name);
    bool isEmpty();
    QString back();
    QString front();
    queue<QString> getRecQueue();
private:
    explicit RecQueue(QObject *parent = 0);
    static RecQueue *rQueue;
    static QMutex *mutex;
    static queue<QString> names;


signals:
    void refreshQueue();
public slots:
};

#endif // RECQUEUE_H
