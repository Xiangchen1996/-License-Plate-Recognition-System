#ifndef JSONWRAPPER_H
#define JSONWRAPPER_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>

class JsonWrapper
{
public:
    JsonWrapper();

    QString wrapLogin(QString id,QString pwd);

    QString wrapSend(QString picName,int picSize,QString sendIP);

    QString wrapStop(QString picName);

    QString wrapClose();

};

#endif // JSONWRAPPER_H
