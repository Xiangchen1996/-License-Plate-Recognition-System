#include "tcpthread.h"


TcpThread::TcpThread(bool data,QObject *parent)
    :QThread(parent)
{
    this->isData=data;
    parser=new JsonParser();
    wrapper=new JsonWrapper();
    rev_path="./rev_pic/";
    detect=true;
    fileName="";
}

void TcpThread::run()
{
    running=true;
    exec();
}


QString TcpThread::getIP()
{
    return ip;
}

void TcpThread::setSerial(int num)
{
    this->serial=num;
}

int TcpThread::getSerial()
{
    return serial;
}


bool TcpThread::getRunningState()
{
    return running;
}

void TcpThread::setArgs(int socketDescriptor, QMutex *mutex)
{
    this->socketDescriptor=socketDescriptor;
    this->mutex=mutex;
    tcpSocket = new QTcpSocket();
    detect=true;
    fileName="";
    if (!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        return;
    }
    ip=tcpSocket->peerAddress().toString();
    qDebug()<<"ServerThread ------> "<<this->thread()<< "IP --------->" <<ip<<" isDataSocket------>"<<isData;
    //Qt::AutoConnection表示系统自动选择相应的连接方式，
    //如果信号与槽在同一线程，就采用Qt::DirectConnection,一旦信号产生，立即执行槽函数。
    connect(tcpSocket, SIGNAL(readyRead()), this,
        SLOT(readMessage()), Qt::DirectConnection);
}

void TcpThread::readMessage()
{
    if(isData){
        qDebug()<<"data content : ";

        QString name;
        QByteArray data;
        int size;
        int count;
        QDataStream in(tcpSocket);
        in.setVersion(QDataStream::Qt_5_5);


        in >> name >> data >> size >> count;
        qDebug()<<name<<size<<count;
        //create pic file
        fileName=name;
        QFile file(rev_path+name);
        QString result;


        if(!file.isOpen())
        {
            if(!file.open(QIODevice::Append))
            {
                qDebug() << "Open failed.";
                result=wrapper->wrapReceivePicResult(0);
            }else{
                file.write(data,size);
                file.flush();

            }
            qDebug()<<"***************here here";

        }else{
            file.write(data,size);
            file.flush();
        }



        if(detect)
        {
            //创建定时器
            testTimer = new QTimer(this);
            //将定时器超时信号与槽(功能函数)联系起来
            connect(testTimer,SIGNAL(timeout()), this, SLOT(revDone()));
            //开始运行定时器，定时时间间隔为1000ms
            testTimer->start(10000); //！！！这里我给改成了5000-------------------------此处为我第1处自行改动

            detect=false;
        }



        //4.put the pic into queue
        //TODO



    }else{
        qDebug()<<"command content : ";
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

        in >> read ;
        qDebug()<<read;
        parser->setMessage(read);

        dispatcher(parser->getCode());
    }

}

void TcpThread::revDone()
{
    qDebug()<<"-------------file detect -------------";
    QFile file(rev_path+fileName);
    QString result;
    qDebug()<<file.size();
    qDebug()<<DBHelper::getInstance()->getPicSize(fileName);
//    qDebug()<<(DBHelper::getInstance()->getPicSize(fileName)==file.size());
    if(file.size()==DBHelper::getInstance()->getPicSize(fileName))
    {
        qDebug()<<"**********************************************";
        result=wrapper->wrapReceivePicResult(1);
        file.close();
        workQueue::getInstance()->push(fileName);

    }
    else{
        result=wrapper->wrapReceivePicResult(0);
        DBHelper::getInstance()->deleteRecord(fileName);
        file.close();
        QFile::remove("./rev_pic/"+fileName);
    }
    qDebug()<<result;
    sendMessage(result);


    tcpSocket->flush();

    this->tcpSocket->close();
    disconnect(testTimer,SIGNAL(timeout()), this, SLOT(revDone()));
    emit recycleThread(this->getSerial());
}

void TcpThread::dispatcher(int code)
{
    switch (code) {
    case 100:
        userLogin(parser->getId(),parser->getPassword());
        break;

    case 200:addPicRecord(parser->getPicName(),parser->getSize(),parser->getSender());
        break;

    case 201:
        stopReceivePic(parser->getPicName());
        break;
    case 300:
        qDebug()<<"receive message -------> close socket";
        this->tcpSocket->close();
        emit recycleThread(this->getSerial());
        break;
    default:
        break;
    }
}

void TcpThread::sendMessage(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << (quint16)0;
    out << message;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));


    tcpSocket->write(block);
    tcpSocket->flush();
}

void TcpThread::userLogin(QString id, QString pwd)
{
    QString result;
    if(DBHelper::getInstance()->userLogin(id,pwd)){
        result = wrapper->wrapLoginResult(1);
    }else{
        result = wrapper->wrapLoginResult(0);
    }
    sendMessage(result);
}

void TcpThread::addPicRecord(QString name, int size, QString sendIP)
{
    //1.add record in db
    DBHelper::getInstance()->addRecord(name,size,sendIP);


}

void TcpThread::stopReceivePic(QString name)
{
    list<QString> pics=DBHelper::getInstance()->getRecordByPicName(name);
    list<QString>::iterator itor;
    for(itor=pics.begin();itor!=pics.end();itor++){
        parser->setMessage(*itor);
        QString path=parser->getPath();
        int size=parser->getSize();

        QFile file(path);
        //TODO
        if(file.size()<size)
        {
            QFile::remove(path);
            DBHelper::getInstance()->deleteRecord(name);
        }
    }

}

void TcpThread::reset()
{
    disconnect(tcpSocket, SIGNAL(readyRead()), this,SLOT(readMessage()));
    this->socketDescriptor=-1;
    this->mutex=NULL;
    this->ip="";
    this->tcpSocket=NULL;
    detect=false;
    fileName="";
    running=false;
}

int TcpThread::getSocketDescriptor()
{
    return socketDescriptor;
}
