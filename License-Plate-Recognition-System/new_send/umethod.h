#ifndef UMETHOD_H
#define UMETHOD_H
#include <QString>
#include <QTcpSocket>
#include <QFile>

class UMethod
{
private:
    UMethod();
    static QTcpSocket *client;
    static UMethod * tool;
public:
    void sendMessage(QString string);
    QString readMessage();
    static QString MD5encrypt(QString encode);
    static UMethod* getTool();
    static QTcpSocket* getClient();

};

#endif // UMETHOD_H
