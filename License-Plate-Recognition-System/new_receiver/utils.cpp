#include "utils.h"

Utils::Utils()
{

}


QMutex *Utils::mutex=new QMutex();
Utils *Utils::utils=NULL;

Utils *Utils::getInstance()
{
    mutex->lock();
    if(NULL==utils)
    {
        utils=new Utils();
    }
    mutex->unlock();
    return utils;
}

QString Utils::MD5encrypt(QString encode)
{
    mutex->lock();
    QByteArray byte = encode.toLatin1();
    QByteArray byteMd5 = QCryptographicHash::hash(byte, QCryptographicHash::Md5);
    QString res = byteMd5.toHex();
    mutex->unlock();
    return res;
}

QString Utils::getSystemDate()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd"); //设置显示格式
    return str;
}

QString Utils::getPlace(QString code)
{
    QString result;
    if(code.mid(0,5).compare("410323")){
        result.append("Liao Ning,Shenyang");
    }
    if(code.mid(6,8).compare("222")){
        result.append("BaiTa Street");
    }

    return result;
}
