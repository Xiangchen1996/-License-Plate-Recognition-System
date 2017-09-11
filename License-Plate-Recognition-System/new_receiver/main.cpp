#include "dialog.h"
#include <QApplication>
#include <maindialog.h>
#include <server.h>
#include <detectthread.h>
#include <QDir>
#include <dbhelper.h>
#include <utils.h>
#include "workqueue.h"
#include "imageprocessthread.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    workQueue::getInstance();
    imageProcessThread *imageThread = new imageProcessThread();
    imageThread->start();


//    qDebug()<<DBHelper::getInstance()->getRecordByPicName("41032322220170802102534.JPG").back();
//    qDebug()<<DBHelper::getInstance()->userLogin("root",Utils::getInstance()->MD5encrypt("root"));
//    qDebug()<<DBHelper::getInstance()->sysuserLogin("root",Utils::getInstance()->MD5encrypt("root"));
    QDir dir(QDir::currentPath()+"/rev_pic");
    if(dir.exists())
    {
        qDebug()<<"PicReceiverFolder exist";

    }
    else
    {
       bool ok = dir.mkpath(QDir::currentPath()+"/rev_pic");//创建多级目录
       qDebug()<<"create picReceiverFolder : "<<ok;
    }

    DetectThread *detectThread=new DetectThread();
    detectThread->start();

    Server *server=new Server();


    Dialog w;
    if(w.exec()==QDialog::Accepted)
    {
        mainDialog *mDialog=new mainDialog(server,detectThread);
        mDialog->show();

        return a.exec();
    }else{
        return 0;
    }

}



