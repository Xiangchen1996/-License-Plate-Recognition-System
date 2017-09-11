#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->le_pwd->setEchoMode(QLineEdit::Password);
}

Dialog::~Dialog()
{
    delete ui;
}

//最小化
void Dialog::on_btn_min_clicked()
{
    this->showMinimized();
}

//关闭
void Dialog::on_btn_close_clicked()
{

    this->close();
}

//暂且写成这样，需要根据业务逻辑修改
void Dialog::on_btn_login_clicked()
{
    DBHelper *db=DBHelper::getInstance();
    if(!ui->le_uname->text().isEmpty()&&!ui->le_pwd->text().isEmpty())
    {
        qDebug()<<"name:"<<ui->le_uname->text()<<"  pwd:"<<Utils::getInstance()->MD5encrypt(ui->le_pwd->text());
        if(db->sysuserLogin(ui->le_uname->text(),Utils::getInstance()->MD5encrypt(ui->le_pwd->text())))
        {
            this->accept();
        }

    }

}

void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void Dialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void Dialog::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}
