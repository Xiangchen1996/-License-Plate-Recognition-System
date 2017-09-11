#include "addportdialog.h"
#include "ui_addportdialog.h"
#include <QMouseEvent>

addPortDialog::addPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPortDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    //读取本地port.txt(先查询该文件是否存在，若不存在，先创建该文件)
    //内容为空--->le_server,le_pwd不显示内容
    //内容不为空--->将第一行内容放置le_server  第二行内容放置le_pwd

    QFile f("./port.txt");
    if(!f.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        qDebug()<<"open port.txt failed, created port.txt";
    }
    else
    {
        QTextStream txtInput(&f);
        QString lineStr,strServer,strPort;
        lineStr = txtInput.readLine();
        strServer = lineStr;
        lineStr = txtInput.readLine();
        strPort = lineStr;
        if(lineStr=="")
        {
            ui->le_server->setText("");
            ui->le_port->setText("");
        }
        else
        {
            ui->le_server->setText(strServer);
            ui->le_port->setText(strPort);
        }
    }
    f.close();

}

addPortDialog::~addPortDialog()
{
    delete ui;
}

void addPortDialog::on_btn_rotate_clicked()
{
    emit rotateWindow();
}


void addPortDialog::on_btn_min_clicked()
{
    emit minimizeWindow();
}

void addPortDialog::on_btn_close_clicked()
{
    emit closeProgram();
}

void addPortDialog::on_btn_requestConnect_clicked()
{
    //这里请求连接的时候，需要清空本地port.txt文件，将le_server和le_pwd中的内容重新写入txt中
    QString strServer,strPort;
    strServer = ui->le_server->text();
    strPort = ui->le_port->text();
    QFile f("./port.txt");
    QTextStream txtOutput(&f);
    if(f.open(QIODevice::ReadWrite|QIODevice::Text))
    {
        txtOutput <<strServer<<"\n";
        txtOutput <<strPort<<"\n";
    }
    f.close();


}

QString addPortDialog::getServer()
{
    return ui->le_server->text();
}

QString addPortDialog::getPort()
{
    return ui->le_port->text();
}
