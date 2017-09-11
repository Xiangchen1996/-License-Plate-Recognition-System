#include "dbhelper.h"

DBHelper::DBHelper()
{
    wrapper=new JsonWrapper();
}

DBHelper *DBHelper::m_dbhelper=NULL;
QMutex *DBHelper::mutex=new QMutex();
QSqlDatabase DBHelper::db;

DBHelper *DBHelper::getInstance()
{
    mutex->lock();
    if(NULL == m_dbhelper)
    {
        m_dbhelper = new DBHelper();
        db=ConnectionPool::openConnection();
    }
    mutex->unlock();
    return m_dbhelper;
}

void DBHelper::initial()
{
    mutex->lock();
    ConnectionPool::closeConnection(db);
    mutex->unlock();
}

list<QString> DBHelper::getRecordByID(QString id)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture,person where person.car_number = picture.final_car_number"
                  " and person.ID_number = ?");
    query.bindValue(0,id);
    query.exec();

    qDebug()<<"select * from picture,person where person.car_number = picture.final_car_number"
              " and person.ID_number = "<<id;
    qDebug()<<"queryError ------->"<<query.lastError();
    list<QString> result;
    while(query.next())
    {
        QString picName=query.value("name").toString();
        QString auto_num=query.value("auto_car_number").toString();
        QString human_num=query.value("human_car_number").toString();
        QString final_num=query.value("final_car_number").toString();
        QString date=query.value("date").toString();
        QString place=query.value("place").toString();
        QString path=query.value("path").toString();
        int size=query.value("size").toInt();
        QString sendIP=query.value("sendIP").toString();
        double rate=query.value("rate").toDouble();
        QString temp= wrapper->wrapRecordResult(picName,auto_num,human_num,final_num,date,place,path,size,sendIP,rate);
        result.push_back(temp);
    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return result;
}

list<QString> DBHelper::getRecordByCarNumber(QString car_num)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where final_car_number = ?");
    query.bindValue(0,car_num);
    query.exec();

    qDebug()<<"select * from picture where final_car_number = "<<car_num;
    qDebug()<<"queryError ------->"<<query.lastError();
    list<QString> result;
    while(query.next())
    {
        QString picName=query.value("name").toString();
        QString auto_num=query.value("auto_car_number").toString();
        QString human_num=query.value("human_car_number").toString();
        QString final_num=query.value("final_car_number").toString();
        QString date=query.value("date").toString();
        QString place=query.value("place").toString();
        QString path=query.value("path").toString();
        int size=query.value("size").toInt();
        QString sendIP=query.value("sendIP").toString();
        double rate=query.value("rate").toDouble();
        QString temp= wrapper->wrapRecordResult(picName,auto_num,human_num,final_num,date,place,path,size,sendIP,rate);
        result.push_back(temp);
    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return result;
}

list<QString> DBHelper::getRecordByName(QString name)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture,person where person.car_number = picture.final_car_number"
                  " and person.name = ?");
    query.bindValue(0,name);
    query.exec();

    qDebug()<<"select * from picture,person where person.car_number = picture.final_car_number"
              " and person.name = "<<name;
    qDebug()<<"queryError ------->"<<query.lastError();
    list<QString> result;
    while(query.next())
    {
        QString picName=query.value("name").toString();
        QString auto_num=query.value("auto_car_number").toString();
        QString human_num=query.value("human_car_number").toString();
        QString final_num=query.value("final_car_number").toString();
        QString date=query.value("date").toString();
        QString place=query.value("place").toString();
        QString path=query.value("path").toString();
        int size=query.value("size").toInt();
        QString sendIP=query.value("sendIP").toString();
        double rate=query.value("rate").toDouble();
        QString temp= wrapper->wrapRecordResult(picName,auto_num,human_num,final_num,date,place,path,size,sendIP,rate);
        result.push_back(temp);
    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return result;
}

list<QString> DBHelper::getRecordByPicName(QString name)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where name = ?");
    query.bindValue(0,name);
    query.exec();

    qDebug()<<"select * from picture where name = ?"<<name;
    qDebug()<<"queryError ------->"<<query.lastError();
    list<QString> result;
    while(query.next())
    {
        QString picName=query.value("name").toString();
        QString auto_num=query.value("auto_car_number").toString();
        QString human_num=query.value("human_car_number").toString();
        QString final_num=query.value("final_car_number").toString();
        QString date=query.value("date").toString();
        QString place=query.value("place").toString();
        QString path=query.value("path").toString();
        int size=query.value("size").toInt();
        QString sendIP=query.value("sendIP").toString();
        double rate=query.value("rate").toDouble();
        QString temp= wrapper->wrapRecordResult(picName,auto_num,human_num,final_num,date,place,path,size,sendIP,rate);
        result.push_back(temp);
    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return result;
}

void DBHelper::deleteRecord(QString name)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("delete from picture where name = ?");
    query.bindValue(0,name);
    query.exec();
    qDebug()<<"delete from picture where name = "<<name;
    qDebug()<<"queryError ------->"<<query.lastError();
    QFile file("./rec_pic"+name);
    if(file.exists()){
        QFile::remove("./rec_pic"+name);
    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
}

void DBHelper::addRecord(QString name, int size, QString sendIP)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("insert into picture values(NULL,?,NULL,NULL,NULL,NULL,NULL,?,?,?,?,NULL)");
    query.bindValue(0,name);
    query.bindValue(1,"./rev_pic/"+name);
    query.bindValue(2,size);
    query.bindValue(3,sendIP);
    query.bindValue(4,0);
    query.exec();
    qDebug()<<"insert into picture";
    qDebug()<<"queryError ------->"<<query.lastError();
    ConnectionPool::closeConnection(db);
    mutex->unlock();
}

int DBHelper::getPicSize(QString name)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where name = ?");
    query.bindValue(0,name);
    query.exec();
    int size;
    qDebug()<<"select * from picture where name = "<<name;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        size=query.value("size").toInt();

        qDebug()<<"picSize:"<<size;

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return size;
}

QString DBHelper::getPicName(QString car_num)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where final_car_number = ?");
    query.bindValue(0,car_num);
    query.exec();
    QString name;
    qDebug()<<"select * from picture where final_car_number ="<<car_num;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        name=query.value("name").toString();

        qDebug()<<"picName:"<<name;

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return name;
}

QString DBHelper::getPicPlace(QString picName)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where name = ?");
    query.bindValue(0,picName);
    query.exec();
    QString place;
    qDebug()<<"select * from picture where name ="<<picName;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        place=query.value("place").toString();

        qDebug()<<"picPlace:"<<place;

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return place;
}

QString DBHelper::getPicDate(QString picName)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where name = ?");
    query.bindValue(0,picName);
    query.exec();
    QString date;
    qDebug()<<"select * from picture where name ="<<picName;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        date=query.value("date").toString();

        qDebug()<<"picDate:"<<date;

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return date;
}

QString DBHelper::getAutoRecNumber(QString picName)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where name = ?");
    query.bindValue(0,picName);
    query.exec();
    QString autoRec;
    qDebug()<<"select * from picture where name ="<<picName;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        autoRec=query.value("auto_car_number").toString();

        qDebug()<<"picAutoCarNumber:"<<autoRec;

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return autoRec;
}

void DBHelper::humanRec(QString picName, QString humanRec)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("update picture set human_car_number = ? ,final_car_number = ? , modify = ? where name = ?");
    query.bindValue(0,humanRec);
    query.bindValue(1,humanRec);
    query.bindValue(2,1);
    query.bindValue(3,picName);
    query.exec();

    qDebug()<<"update picture set human_car_number = "<<humanRec<<" where name = "<<picName;
    qDebug()<<"queryError ------->"<<query.lastError();
    ConnectionPool::closeConnection(db);
    mutex->unlock();
}

void DBHelper::updatePicInfo(QString picName, QString auto_rec, QString date, QString place, double rate)
{
    mutex->lock();
    QSqlQuery query(db);

    query.prepare("update picture set auto_car_number = ? ,final_car_number = ?,date = ? , place = ? , rate = ? where name = ?");
    query.bindValue(0,auto_rec);
    query.bindValue(1,auto_rec);
    query.bindValue(2,date);
    query.bindValue(3,place);
    query.bindValue(4,rate);
    query.bindValue(5,picName);
    query.exec();

    qDebug()<<"update picture set auto_car_number = "<<auto_rec<<",date = "<<date<< ",place = "<<place
           <<",rate = "<<rate<<"where name = "<<picName;
    qDebug()<<"queryError ------->"<<query.lastError();
    ConnectionPool::closeConnection(db);
    mutex->unlock();
}

bool DBHelper::userLogin(QString name, QString pwd)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from user where name = ?");//刚改的
    query.bindValue(0,name);
    query.exec();
//    query.exec("select * from sysuser");
//    qDebug()<<query.size();
//    qDebug()<<"select * from user where name = "<<name;
//    qDebug()<<"queryError ------->"<<query.lastError();
//    qDebug()<<"name"<<name;
//    qDebug()<<"pwd"<<pwd;

    if(query.next())
//    while(query.next())
    {
        QString beforePwd=query.value(2).toString();

        QString afterPwd=Utils::getInstance()->MD5encrypt(beforePwd);

//        qDebug()<<"sqlPWD:"<<afterPwd;
//        qDebug()<<"userPwd:"<<pwd;

        if(0==afterPwd.compare(pwd))
        {
            mutex->unlock();
            ConnectionPool::closeConnection(db);
            return true;
        }

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return false;

}



bool DBHelper::sysuserLogin(QString name, QString pwd)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from sysuser where name = ?");
    query.bindValue(0,name);
    query.exec();

    qDebug()<<"select * from sysuser where name = "<<name;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        QString beforePwd=query.value(2).toString();
        QString afterPwd=Utils::getInstance()->MD5encrypt(beforePwd);
        qDebug()<<"sqlPWD:"<<afterPwd;
        if(0==afterPwd.compare(pwd))
        {
            mutex->unlock();
            ConnectionPool::closeConnection(db);
            return true;
        }

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return false;
}


QString DBHelper::getHumanRecNumber(QString picName)
{
    mutex->lock();
    QSqlQuery query(db);
    query.prepare("select * from picture where name = ?");
    query.bindValue(0,picName);
    query.exec();
    QString humanRec;
    qDebug()<<"select * from picture where name ="<<picName;
    qDebug()<<"queryError ------->"<<query.lastError();
    while(query.next())
    {

        humanRec=query.value("human_car_number").toString();

        qDebug()<<"picHumanCarNumber:"<<humanRec;

    }
    ConnectionPool::closeConnection(db);
    mutex->unlock();
    return humanRec;
}
