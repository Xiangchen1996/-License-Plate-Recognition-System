#include "umethod.h"
#include <QDataStream>
#include <QCryptographicHash>
#include <QDateTime>
#include <QTcpSocket>


UMethod* UMethod::tool = NULL;
QTcpSocket* UMethod::client = NULL;

UMethod* UMethod::getTool()
{
    if(NULL == tool)
    {
        tool = new UMethod();
    }
    return tool;
}

QTcpSocket* UMethod::getClient()
{
    qDebug()<<"++++++++++++++++++";
    qDebug()<<"client:"<<client;
    if(NULL == client)
    {
        QFile f("./port.txt");
        if(!f.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            qDebug()<<"open port.txt failed, created port.txt";
        }
        else
        {

            QTextStream txtInput(&f);
            QString lineStr,strServer;
            int strPort;
            lineStr = txtInput.readLine();
            strServer = lineStr;
            lineStr = txtInput.readLine();
            strPort = lineStr.toInt();
            client=new QTcpSocket();
            client->abort();
            client->connectToHost(strServer, strPort);
            qDebug()<<"connected?   :"<<(client->state()==3);
            qDebug()<<strServer<<" "<<strPort;
        }
        f.close();
    }
    return client;
}

UMethod::UMethod()
{
}

//void UMethod::reset(QString ip,int port)
//{
//    if(NULL!=client){
//        client->abort();
//    }
//    client=new QTcpSocket();
//    client->connectToHost(ip, port);
//}


void UMethod::sendMessage(QString string)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);


    out << (quint16)0;
    out << string;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    client->write(block);
    client->flush();
}

QString UMethod::readMessage()
{
    quint16 blockSize=0;
    QString read;
    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_5);

    if (blockSize == 0)
    {
        if (client->bytesAvailable() < (int)sizeof(quint16))
            return NULL;
        in >> blockSize;
    }
    if (client->bytesAvailable() < blockSize)
        return NULL;

    in >> read;
    return read;
}

QString UMethod::MD5encrypt(QString encode)
{
    QByteArray byte = encode.toLatin1();
    QByteArray byteMd5 = QCryptographicHash::hash(byte, QCryptographicHash::Md5);
    QString res = byteMd5.toHex();
    return res;
}

//bool UMethod::isConnected()
//{
//    return client->isValid();
//}
