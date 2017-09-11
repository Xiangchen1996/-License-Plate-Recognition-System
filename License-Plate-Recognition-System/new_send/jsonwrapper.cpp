#include "jsonwrapper.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

JsonWrapper::JsonWrapper()
{

}

//0
QString JsonWrapper::wrapLogin(QString id, QString pwd)
{
    QJsonObject login;
    login.insert("code", 100);
    login.insert("id", id);
    login.insert("pwd", pwd);
    QJsonDocument document;
    document.setObject(login);
    QByteArray login_array = document.toJson(QJsonDocument::Compact);
    QString str(login_array);
    qDebug() << "wrapLogin:" << str;
    return str;
}
//1
QString JsonWrapper::wrapSend(QString picName,int picSize,QString sendIP)
{
    QJsonObject info;
    info.insert("code",200);
    info.insert("size",picSize);
    info.insert("picName",picName);
    info.insert("sendIP",sendIP);

    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapSend:" << str;
    return str;
}
//2
QString JsonWrapper::wrapStop(QString picName)
{
    QJsonObject del;
    del.insert("code", 201);
    del.insert("picName", picName);
    QJsonDocument document;
    document.setObject(del);
    QByteArray del_array = document.toJson(QJsonDocument::Compact);
    QString str(del_array);
    qDebug() << "wrapStop:" << str;
    return str;
}
//3
QString JsonWrapper::wrapClose()
{
    QJsonObject info;
    info.insert("code",300);
    QJsonDocument document;
    document.setObject(info);
    QByteArray info_array = document.toJson(QJsonDocument::Compact);
    QString str(info_array);
    qDebug() << "wrapClose:" << str;
    return str;
}
