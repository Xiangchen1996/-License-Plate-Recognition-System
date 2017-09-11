#ifndef UTILS_H
#define UTILS_H
#include <QMutex>
#include <QString>
#include <QCryptographicHash>
#include <QDateTime>

class Utils
{
private:
    Utils();
    static Utils *utils;
    static QMutex *mutex;
public:
    static Utils *getInstance();
    QString MD5encrypt(QString encode);
    QString getSystemDate();
    QString getPlace(QString code);
};

#endif // UTILS_H
