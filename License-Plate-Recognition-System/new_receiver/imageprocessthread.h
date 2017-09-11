#ifndef IMAGEPROCESSTHREAD_H
#define IMAGEPROCESSTHREAD_H

#include <QObject>
#include "workqueue.h"
#include <donequeue.h>
#include <recqueue.h>
#include <dbhelper.h>
#include "./process_h/plate_recognize.h"
#include <QString>
#include <QDir>
#include <QThread>
#include <QDebug>

class imageProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit imageProcessThread(QObject *parent = 0);
    void run();

signals:

public slots:
    QString getPlateNumber();
private:
    CPlateRecognize *plateRecognize;
};

#endif // IMAGEPROCESSTHREAD_H
