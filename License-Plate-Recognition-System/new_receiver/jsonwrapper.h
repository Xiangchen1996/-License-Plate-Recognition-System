#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H


#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
class JsonWrapper
{
public:
    JsonWrapper();
    QString wrapLoginResult(int code);
    QString wrapRecordResult(QString name,QString auto_car_num,QString human_car_num,QString final_car_num,
                             QString date,QString place,QString path,int size,QString sendIP,double rate);
    QString wrapReceivePicResult(int code);
};

#endif // JSONWRAPPER_H
