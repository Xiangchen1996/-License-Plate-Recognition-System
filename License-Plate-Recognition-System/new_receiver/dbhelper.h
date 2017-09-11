#ifndef DBHELPER_H
#define DBHELPER_H
#include <QMutex>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <utils.h>
#include <connectionpool.h>
#include <list>
#include <jsonwrapper.h>

using namespace std;
class DBHelper
{
private:
    DBHelper();
    static DBHelper *m_dbhelper;
    static QMutex *mutex;
    static QSqlDatabase db;
    JsonWrapper *wrapper;

public:
    static DBHelper* getInstance();
    bool userLogin(QString name,QString pwd);
    bool sysuserLogin(QString name,QString pwd);
    list<QString> getRecordByID(QString id);
    list<QString> getRecordByCarNumber(QString car_num);
    list<QString> getRecordByName(QString name);
    list<QString> getRecordByPicName(QString name);
    void deleteRecord(QString name);
    void addRecord(QString name,int size,QString sendIP);
    int getPicSize(QString name);
    QString getPicName(QString car_num);
    QString getPicPlace(QString picName);
    QString getPicDate(QString picName);
    QString getAutoRecNumber(QString picName);
    QString getHumanRecNumber(QString picName);

    void humanRec(QString picName,QString humanRec);
    void updatePicInfo(QString picName,QString auto_rec,QString date,QString place,double rate);
    void modifyPicInfo(QString picName,QString final_num);


    void initial();

};

#endif // DBHELPER_H
