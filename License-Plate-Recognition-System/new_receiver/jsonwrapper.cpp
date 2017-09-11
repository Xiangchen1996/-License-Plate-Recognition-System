#include "jsonwrapper.h"

JsonWrapper::JsonWrapper()
{

}

QString JsonWrapper::wrapLoginResult(int code)
{
    QJsonObject login;
    login.insert("code", 1000+code);
    QJsonDocument document;
    document.setObject(login);
    QByteArray login_array = document.toJson(QJsonDocument::Compact);
    QString str(login_array);
    qDebug() << "wrapLoginResult:" << str;
    return str;
}

QString JsonWrapper::wrapReceivePicResult(int code)
{
    QJsonObject pic;
    pic.insert("code", 2000+code);
    QJsonDocument document;
    document.setObject(pic);
    QByteArray pic_array = document.toJson(QJsonDocument::Compact);
    QString str(pic_array);
    qDebug() << "wrapReceivePicResult:" << str;
    return str;
}

QString JsonWrapper::wrapRecordResult(QString name, QString auto_car_num, QString human_car_num, QString final_car_num,
                                      QString date,QString place, QString path, int size, QString sendIP, double rate)
{
    QJsonObject record;
    record.insert("picName", name);
    record.insert("auto_car_number",auto_car_num);
    record.insert("human_car_number",human_car_num);
    record.insert("final_car_number",final_car_num);
    record.insert("date",date);
    record.insert("place",place);
    record.insert("path",path);
    record.insert("size",size);
    record.insert("sendIP",sendIP);
    record.insert("rate",rate);

    QJsonDocument document;
    document.setObject(record);
    QByteArray record_array = document.toJson(QJsonDocument::Compact);
    QString str(record_array);
    //qDebug() << "wrapRecordResult:" << str;//------------------------------------自行屏蔽
    return str;
}
