#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>
#include <QMutex>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>
class JsonParser
{
private:
    QString message;
public:
    JsonParser();
    int getCode();
    void setMessage(QString message);
    QString getId();
    QString getPassword();
    int getSize();
    QString getPicName();
    QString getDate();
    QString getPlace();
    QString getPath();
    QByteArray getData();
    QString getSender();
    double getRate();
    QString getFinalCarNumber();


    QString getHostName();
    QString getDataBaseName();
    QString getDataBaseType();
    bool getTestOnBorrow();
    QString getTestOnBorrowSql();
    int getMaxWaitTime();
    int getWaitInterval();
    int getMaxConnectionCount();

};

#endif // JSONPARSER_H
