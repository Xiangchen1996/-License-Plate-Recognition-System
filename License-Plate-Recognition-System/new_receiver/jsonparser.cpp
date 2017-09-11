#include "jsonparser.h"

JsonParser::JsonParser()
{

}



int JsonParser::getCode()
{
//TODO
    QJsonParseError error;
    int code=-1;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("code"))
               {
                   QJsonValue code_value = obj.take("code");
                   if (code_value.isDouble())
                   {
                       code = code_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"code:"<<code;
    return code;
}

void JsonParser::setMessage(QString message)
{
    this->message=message;
}


QString JsonParser::getId()
{
    QJsonParseError error;
    QString id;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("id"))
               {
                   QJsonValue id_value = obj.take("id");
                   if (id_value.isString())
                   {
                       id = id_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"id:"<<id;
    return id;
}

QString JsonParser::getPassword()
{
    QJsonParseError error;
    QString pwd;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("pwd"))
               {
                   QJsonValue pwd_value = obj.take("pwd");
                   if (pwd_value.isString())
                   {
                       pwd = pwd_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"pwd:"<<pwd;
    return pwd;
}

int JsonParser::getSize()
{
    QJsonParseError error;
    int size=0;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("size"))
               {
                   QJsonValue size_value = obj.take("size");
                   if (size_value.isDouble())
                   {
                       size = size_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"size:"<<size;
    return size;
}

QByteArray JsonParser::getData()
{
    QJsonParseError error;
    QByteArray data;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("data"))
               {
                   QJsonValue data_value = obj.take("data");
                   if (data_value.isString())
                   {
                       data = data_value.toVariant().toString().toLatin1();
                   }
               }
           }
    }
    qDebug()<<"data:"<<data;
    return data;
}

QString JsonParser::getSender()
{
    QJsonParseError error;
    QString sender;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("sendIP"))
               {
                   QJsonValue sender_value = obj.take("sendIP");
                   if (sender_value.isString())
                   {
                       sender = sender_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"sendIP:"<<sender;
    return sender;
}

QString JsonParser::getPicName()
{
    QJsonParseError error;
    QString name;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("picName"))
               {
                   QJsonValue name_value = obj.take("picName");
                   if (name_value.isString())
                   {
                       name = name_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"picName:"<<name;
    return name;
}

QString JsonParser::getDate()
{
    QJsonParseError error;
    QString date;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("date"))
               {
                   QJsonValue date_value = obj.take("date");
                   if (date_value.isString())
                   {
                       date = date_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"date:"<<date;
    return date;
}

QString JsonParser::getPlace()
{
    QJsonParseError error;
    QString place;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("place"))
               {
                   QJsonValue place_value = obj.take("place");
                   if (place_value.isString())
                   {
                       place = place_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"place:"<<place;
    return place;
}

QString JsonParser::getPath()
{
    QJsonParseError error;
    QString path;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("path"))
               {
                   QJsonValue path_value = obj.take("path");
                   if (path_value.isString())
                   {
                       path = path_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"path:"<<path;
    return path;
}

QString JsonParser::getFinalCarNumber()
{
    QJsonParseError error;
    QString final;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("final_car_number"))
               {
                   QJsonValue final_value = obj.take("final_car_number");
                   if (final_value.isString())
                   {
                       final = final_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"FinalCarNumber:"<<final;
    return final;
}


QString JsonParser::getHostName()
{
    QJsonParseError error;
    QString name;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("hostName"))
               {
                   QJsonValue name_value = obj.take("hostName");
                   if (name_value.isString())
                   {
                       name = name_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"hostName:"<<name;
    return name;
}

QString JsonParser::getDataBaseName()
{
    QJsonParseError error;
    QString name;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("databaseName"))
               {
                   QJsonValue name_value = obj.take("databaseName");
                   if (name_value.isString())
                   {
                       name = name_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"dataBaseName:"<<name;
    return name;
}

QString JsonParser::getDataBaseType()
{
    QJsonParseError error;
    QString type;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("databaseType"))
               {
                   QJsonValue type_value = obj.take("databaseType");
                   if (type_value.isString())
                   {
                       type = type_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"dataBaseType:"<<type;
    return type;
}


bool JsonParser::getTestOnBorrow()
{
    QJsonParseError error;
    bool borrow=true;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("testOnBorrow"))
               {
                   QJsonValue borrow_value = obj.take("testOnBorrow");
                   if (borrow_value.isBool())
                   {
                       borrow = borrow_value.toVariant().toBool();
                   }
               }
           }
    }
    qDebug()<<"testOnBorrow:"<<borrow;
    return borrow;
}

QString JsonParser::getTestOnBorrowSql()
{
    QJsonParseError error;
    QString borrowSql;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("testOnBorrowSql"))
               {
                   QJsonValue borrowSql_value = obj.take("testOnBorrowSql");
                   if (borrowSql_value.isString())
                   {
                       borrowSql = borrowSql_value.toVariant().toString();
                   }
               }
           }
    }
    qDebug()<<"testOnBorrowSql:"<<borrowSql;
    return borrowSql;
}



int JsonParser::getMaxWaitTime()
{
    QJsonParseError error;
    int max=0;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("maxWaitTime"))
               {
                   QJsonValue max_value = obj.take("maxWaitTime");
                   if (max_value.isDouble())
                   {
                       max = max_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"maxWaitTime:"<<max;
    return max;
}

double JsonParser::getRate()
{
    QJsonParseError error;
    double rate=0;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("rate"))
               {
                   QJsonValue rate_value = obj.take("rate");
                   if (rate_value.isDouble())
                   {
                       rate = rate_value.toVariant().toDouble();
                   }
               }
           }
    }
    qDebug()<<"rate:"<<rate;
    return rate;
}


int JsonParser::getWaitInterval()
{
    QJsonParseError error;
    int wait=0;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("waitInterval"))
               {
                   QJsonValue wait_value = obj.take("waitInterval");
                   if (wait_value.isDouble())
                   {
                       wait = wait_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"waitInterval:"<<wait;
    return wait;
}

int JsonParser::getMaxConnectionCount()
{
    QJsonParseError error;
    int max=0;
    QJsonDocument doucment = QJsonDocument::fromJson(message.toUtf8(),&error);
    if (error.error == QJsonParseError::NoError)
    {
           if (doucment.isObject())
           {
               QJsonObject obj = doucment.object();
               if (obj.contains("maxConnectionCount"))
               {
                   QJsonValue max_value = obj.take("maxConnectionCount");
                   if (max_value.isDouble())
                   {
                       max = max_value.toVariant().toInt();
                   }
               }
           }
    }
    qDebug()<<"maxConnectionCount:"<<max;
    return max;
}
