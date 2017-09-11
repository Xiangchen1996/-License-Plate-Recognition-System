#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);
    tool = UMethod::getTool();

    //读取本地文件，导入默认serverIP和port
    QFile f("./port.txt");
    QTextStream txtInput(&f);
    if(f.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString lineStr,strServer,strPort;
        lineStr = txtInput.readLine();
        strServer = lineStr;
        lineStr = txtInput.readLine();
        strPort = lineStr;
        ui->le_server->setText(strServer);
        ui->le_server->setEnabled(false);
        ui->le_port->setText(strPort);
        ui->le_port->setEnabled(false);
    }


    //进度条初始化
    ui->progressBar->setValue(0);

    //连接到服务器
    //tool=new UMethod(ui->le_server->text(),ui->le_port->text().toInt());

    connect(tool->getClient(), SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));


    //检测是否处于连接状态
    qDebug()<<"Connected?  :"<<(this->tool->getClient()->state()==3);





    parser=new JsonParser();
    wrapper = new JsonWrapper();
}

mainDialog::~mainDialog()
{
    delete ui;
}

//最小化
void mainDialog::on_btn_min_clicked()
{
    this->showMinimized();
}

//关闭
void mainDialog::on_btn_close_clicked()
{
    this->close();
}

void mainDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void mainDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void mainDialog::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}

void mainDialog::on_btn_choosePic_clicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle("请选择图像文件");
    fileDialog.setNameFilter("图像文件(*.png *.bmp *.jpg *.jpeg)");
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    //fileDialog.setFileMode(QFileDialog::Directory);
    QStringList strPathList;
    if(fileDialog.exec()==QDialog::Accepted)
    {
        strPathList = fileDialog.selectedFiles();
    }
    else
    {
        return;
    }
    qDebug()<<strPathList;
//    QString dirPath = strPathList.at(0);
//    QDir dir(dirPath);

//    int picNumber = dir.count();
//    QStringList picList;
//    QString tempPicName;

//    //这里因为Dir的前两个元素分别是"."和".."，故从第三个开始
//    for(int i=2;i<picNumber;i++)
//    {
//        tempPicName = dirPath+ "/" +dir[i];
//        picList.append(tempPicName);
//    }

    ui->lw_picList->addItems(strPathList);
    //给totalNumber和currentNumber设定初值
    this->totalNumber=strPathList.size();
    this->currentNumber=1;
}





//******下面方法再斟酌修改**************************
void mainDialog::on_btn_sendPic_clicked()
{
//    QString sendNumber;
    //进度条初始化
    ui->progressBar->setRange(0,1000);
    this->ui->l_number->setText(QString::number(currentNumber)+"/"+QString::number(totalNumber));
    //封装该图片的信息发送过去
    QString picPath = ui->lw_picList->item(0)->text();
    QString picName = QFileInfo(picPath).fileName();
    int picSize = QFileInfo(picPath).size();
    QString sendIP = getIP();
    QString sendString = wrapper->wrapSend(picName,picSize,sendIP);
    tool->sendMessage(sendString);

    //下面调用线程start方法开始运行，在此之前要先给send设置picPath
    //QString picPath = ui->lw_picList->item(0)->text();
    //开启线程
    sendPicThread *send;//用来发送图片的线程
    send = new sendPicThread(ui->le_server->text());
    send->setPicPath(picPath);
    connect(send,SIGNAL(sendNextPic()),this,SLOT(sendNextPicture()));
    connect(send,SIGNAL(sendcurrentPic()),this,SLOT(sendCurrentPicture()));
    connect(send,SIGNAL(sendNo(int,int)),this,SLOT(updateProgress(int,int)));
    connect(send,SIGNAL(closeThisThread()),send,SLOT(quit()));
//    connect(send,SIGNAL(stopSend()),send,SLOT(quit());
    send->start();
}


void mainDialog::on_btn_exit_clicked()
{
    QString sendString = wrapper->wrapClose();
    tool->sendMessage(sendString);
    this->close();
}

//void mainDialog::readMessage()
//{
//    qDebug()<<"beigin begin begin";
//    QString readString=tool->readMessage();
//    if(NULL==readString){
//            return;
//        }
//    parser->setMessage(readString);
//    int flag = parser->getResult();

//    if(2001 == flag)
//    {

//    }
//    else if(2000 == flag)
//    {
//        //******下面方法再斟酌修改**************************

//    }
//}



void mainDialog::on_btn_stopSend_clicked()
{
    //向接收端发送正在停止的picName
    QString picPath = ui->lw_picList->item(0)->text();
    QString picName = QFileInfo(picPath).fileName();
    QString sendString = wrapper->wrapStop(picName);
    tool->sendMessage(sendString);
    //接收端需要清除list_view所有内容
    int rowCount =ui->lw_picList->count();
    for(int i=0;i<rowCount;i++)
    {
        ui->lw_picList->takeItem(i);
    }
    //对话框显示已停止
//    MessageBox *msgBox = new MessageBox(this, MessageBox::Messsage, "停止", tr("已停止发送，本次已发送%1张图片").
//                                        arg(currentNumber),
//                                     QMessageBox::Ok | QMessageBox::No , QMessageBox::Ok);
//    msgBox->exec();

    QMessageBox::information(this,tr("停止"),tr("已停止发送，本次已发送%1张图片").
                             arg(currentNumber-1));
//    msgBox->exec();
    //进度条归零
    ui->progressBar->setValue(0);
}

QString mainDialog::getIP()
{
    QString localHostName = QHostInfo::localHostName();

    qDebug() <<"localHostName:"<<localHostName;
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
}

void mainDialog::sendNextPicture()
{
    qDebug()<<"1111111111111111";
    //如果返回值表明发送当前图片成功，则从界面中将其删去
    this->currentNumber++;
    ui->lw_picList->takeItem(0);
    this->ui->l_number->setText(QString::number(currentNumber)+"/"+QString::number(totalNumber));

//    ui->progressBar->setValue(1000*currentNumber/totalNumber);
    //判断listView是否还有图片，若无-->显示发送完毕；若有--->继续发送
    if(0 == ui->lw_picList->count())
    {
//        MessageBox *msgBox = new MessageBox(this, MessageBox::Messsage, "发送", "已全部发送完毕！恭喜啊！",
//                                         QMessageBox::Ok | QMessageBox::No , QMessageBox::Ok);

        ui->l_end->setText("全部发送成功!");

        QMessageBox::information(this,tr("发送"),tr("已全部发送完毕！恭喜啊！"));
        //msgBox->exec();
    }
    else if(0 < ui->lw_picList->count())
    {
        //封装该图片的信息发送过去
        QString picPath = ui->lw_picList->item(0)->text();
        QString picName = QFileInfo(picPath).fileName();
        int picSize = QFileInfo(picPath).size();
        QString sendIP = getIP();
        QString sendString = wrapper->wrapSend(picName,picSize,sendIP);
        tool->sendMessage(sendString);


        sendPicThread *send;//用来发送图片的线程
        send = new sendPicThread(ui->le_server->text());
        send->setPicPath(picPath);
        connect(send,SIGNAL(sendNextPic()),this,SLOT(sendNextPicture()));
        connect(send,SIGNAL(sendcurrentPic()),this,SLOT(sendCurrentPicture()));
        connect(send,SIGNAL(sendNo(int,int)),this,SLOT(updateProgress(int,int)));
        connect(send,SIGNAL(closeThisThread()),send,SLOT(quit()));
        send->start();
    }
}

void mainDialog::sendCurrentPicture()
{
    qDebug()<<"0000000000000000";

    //封装该图片的信息发送过去
    QString picPath = ui->lw_picList->item(0)->text();
    QString picName = QFileInfo(picPath).fileName();
    int picSize = QFileInfo(picPath).size();
    QString sendIP = getIP();
    QString sendString = wrapper->wrapSend(picName,picSize,sendIP);
    tool->sendMessage(sendString);


    sendPicThread *send;//用来发送图片的线程
    send = new sendPicThread(ui->le_server->text());
    send->setPicPath(picPath);
    connect(send,SIGNAL(sendNextPic()),this,SLOT(sendNextPicture()));
    connect(send,SIGNAL(sendcurrentPic()),this,SLOT(sendCurrentPicture()));
    connect(send,SIGNAL(sendNo(int,int)),this,SLOT(updateProgress(int,int)));
    connect(send,SIGNAL(closeThisThread()),send,SLOT(quit()));
    send->start();
}

void mainDialog::updateProgress(int total, int current)
{
    this->ui->progressBar->setValue(1000*current/total);
}

