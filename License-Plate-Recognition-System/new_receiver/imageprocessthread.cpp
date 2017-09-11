#include "imageprocessthread.h"

imageProcessThread::imageProcessThread(QObject *parent) :QThread(parent)
{

}

void imageProcessThread::run()
{
    plateRecognize=new CPlateRecognize();//plateRecognize专门用于图像处理与识别
    //开始处理图像
    plateRecognize->LoadSVM("./model/svm.xml");
    plateRecognize->LoadANN("./model/ann.xml");
    plateRecognize->setDebug(true);
    plateRecognize->setLifemode(true);

    qDebug()<<"entering the run()";
    connect(workQueue::getInstance(),SIGNAL(refreshQueue()),this,SLOT(getPlateNumber()));
    qDebug()<<"end binding";
    exec();
}




QString imageProcessThread::getPlateNumber()
{



    if(!workQueue::getInstance()->isEmpty())
    {
        QString picName = workQueue::getInstance()->front();
        QString picPath = QDir::currentPath()+"/rev_pic/"+picName;
        Mat img = imread(picPath.toStdString());
        vector<string> licenseVec;
        double rate=0;
        int result = plateRecognize->plateRecognize(img,licenseVec,"",rate);
        if(0 == result)
        {
            if(licenseVec.at(0) != "")
            {
                qDebug()<<"end executing image processing";
                QString plateNumber = QString::fromStdString(licenseVec.at(0));
                qDebug()<<plateNumber;



                //6 province 3 code 14 date

                DBHelper::getInstance()->updatePicInfo(picName,plateNumber.mid(plateNumber.indexOf(":")+1),
                                                       picName.mid(9,14),
                                                       Utils::getInstance()->getPlace(picName.mid(0,8)),rate);
                //TODO
                if(rate<0.85)
                {
                    RecQueue::getInstance()->push(picName);
                }
                workQueue::getInstance()->pop();
                return "";
            }
            else
                qDebug()<<"No Plate Number";
        }
        else
            qDebug()<<"No execute plateRecognize successfully";
    }
    else
    {
        return NULL;
    }

}
