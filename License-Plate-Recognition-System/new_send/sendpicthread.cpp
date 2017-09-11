#include "sendpicthread.h"




/*
 * class sendPicThread : public QThread
{
    Q_OBJECT
public:
    sendPicThread(QString hostIP);
    void run();
    void setPicPath(QString);
private:
    QTcpSocket *tcpSocket;
    QString hostIP;
    QString picPath;
};
*/
sendPicThread::sendPicThread(QString hostIP)
{
    moveToThread(this);
//    this->hostIP->moveToThread(this);
//    this->picPath->moveToThread(this);

    this->hostIP = hostIP;

    tcpSocket = new QTcpSocket();
    tcpSocket->moveToThread(this);
    tcpSocket->connectToHost(hostIP,9999);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));

    parser = new JsonParser();

}
void sendPicThread::readMessage()
{
    quint16 blockSize=0;
    QString read;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (blockSize == 0)
    {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    in >> read;
    parser->setMessage(read);
    int result = parser->getResult();
    if(2001 == result)
    {

        emit sendNextPic();
        qDebug()<<"**************";

    }
    else if(2000 == result)
    {
        emit sendcurrentPic();
        qDebug()<<"**************";
    }
    else
    {
        qDebug()<<"error::"<<read;
    }


}

void sendPicThread::stopAndQuit()
{
    this->quit();
}


//哎  那我就有一点疑问了，run方法一直在运行，那当当前这张图片传完了，
//run方法岂不是还在运行发送啊啊，这儿时候不管picPath变没变，他发的是哪张图呢
void sendPicThread::run()
{
    QFile file(this->picPath);
    file.open(QIODevice::ReadOnly);

    QByteArray ba;
    ba = file.readAll();

    //下面开始发送图片
    for(int i=0;i<ba.size();i++)
    {
        emit sendNo(ba.size()/5000,i/5000);
        if(i%5000==0&&i!=0)
        {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out << QString(QFileInfo(this->picPath).fileName());
            out << ba.mid(i-5000,5000);
            out << ba.mid(i-5000,5000).size();
            out << i/5000;
            qDebug()<<"!"<<i/5000<<":"<<block.size()<<"-->"<<ba.mid(i-5000,5000).size();
            tcpSocket->write(block);
            tcpSocket->flush();

            msleep(100);

        }else if(i==ba.size()-1){

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            int count=i/5000;
            out << QString(QFileInfo(this->picPath).fileName());
            out << ba.mid(count*5000,ba.size()-count*5000);
            out << ba.mid(count*5000,ba.size()-count*5000).size();
            out << count+1;
            qDebug()<<"@"<<count+1<<":"<<block.size()<<"-->"<<ba.mid(count*5000,ba.size()-count*5000).size();
            tcpSocket->write(block);
            tcpSocket->flush();
            msleep(100);
        }

    }
    emit closeThisThread();
    tcpSocket->waitForReadyRead();
//    tcpSocket->
   // exec();
    //return;

}

/* ！！！此方法应在主线程中发送图片前调用
 * 将run方法所要使用的参数改成线程类的一个属性，
 * 添加相应的get、set方法，并在线程类对象的run方法
 * 被调用前set到对象中，这样run方法就可以直接
 * 使用对象的属性
 *
 */
void sendPicThread::setPicPath(QString picPath)
{
    this->picPath = picPath;
}

