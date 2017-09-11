#include "jsonparser.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QDebug>

JsonParser::JsonParser()
{}

void JsonParser::setMessage(QString str)
{
    this->message = str;
}

int JsonParser::getResult()
{
    QJsonParseError error;
    int result;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    qDebug()<<"message in getResult:"<<message;
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("code"))
               {
                   QJsonValue result_value = obj.take("code");
                   if (result_value.isDouble())
                   {
                       result = result_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"result:"<<result;
    return result;
}
