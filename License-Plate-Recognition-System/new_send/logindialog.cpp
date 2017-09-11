#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMouseEvent>
#include <QMessageBox>


loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    id_edit = ui->le_uname;
    pwd_edit = ui->le_pwd;
    ui->le_pwd->setEchoMode(QLineEdit::Password);
    parser = new JsonParser();
    wrapper = new JsonWrapper();

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
//            MessageBox *msgBox = new MessageBox(this, MessageBox::Messsage, "连接失败", "未连接到服务器，请输入ip和端口号",
//                                             QMessageBox::Ok | QMessageBox::No , QMessageBox::Ok);

            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->information(this, tr("未连接到服务器"),
                                tr("请输入ip和端口号"));
            msgBox->setStyleSheet("background-image:/resource/warning.jpg");
            QPushButton *okButton = (msgBox->addButton(tr("确定"),QMessageBox::AcceptRole));
            msgBox->exec();
       }
        else
        {
            tool = UMethod::getTool();

        }
    }
    f.close();
    qDebug()<<"tool"<<tool;
    connect(tool->getClient(), SIGNAL(readyRead()), this, SLOT(readMessage()));

    connect(tool->getClient(), SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));


}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_btn_min_clicked()
{
    emit minimizeWindow();
}

void loginDialog::on_btn_close_clicked()
{
    emit closeProgram();
}

void loginDialog::on_btn_addPort_clicked()
{
    emit rotateWindow();
}

//暂时写成下面这样，需要根据逻辑修改
void loginDialog::on_btn_login_clicked()
{
    login();
}

/*槽函数
 * void displayError(QAbstractSocket::SocketError socketError);
    void login();
    void readMessage();
    void sendMessage();
*/


void loginDialog::sendMessage()
{
    QString sendString;
    QString uid = id_edit->text();
    QString pwd = pwd_edit->text();
    if(NULL==uid||NULL==pwd){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("登录失败,请输入正确的用户名及密码");
        msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        msgBox->setStyleSheet("background-color:white");
        msgBox->exec();
            return;
        }
    QString md5_pwd;
    md5_pwd = UMethod::MD5encrypt(pwd);

    sendString = wrapper->wrapLogin(uid,md5_pwd);
    tool->sendMessage(sendString);
}

void loginDialog::readMessage()
{
    QString readString=tool->readMessage();
    qDebug()<<readString;
    if(NULL==readString){
            return;
        }
    parser->setMessage(readString);
    int flag = parser->getResult();
    qDebug()<<"flag:"<<flag;
    if(1001 == flag)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("您已登录成功");
        msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        msgBox->setStyleSheet("background-color:white");
        msgBox->exec();
       emit hideProgram();
        mainDialog *mdialog = new mainDialog();
        mdialog->exec();
    }
    else if(1000 == flag)
    {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("登录失败,请输入正确的用户名及密码");
        msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        msgBox->setStyleSheet("background-color:white");
        msgBox->exec();
    }
    else
    {

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("登录失败,可能是您未连接到接收端");
        msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        msgBox->setStyleSheet("background-color:white");
        msgBox->exec();

    }
}

void loginDialog::login()
{
    sendMessage();
}

void loginDialog::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Fortune Client"),
                tr("The host was not found. Please check the "
                "host name and port settings."));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Fortune Client"),
                tr("The connection was refused by the peer. "
                "Make sure the fortune server is running, "
                "and check that the host name and port "
                "settings are correct."));
            break;
        default:
            QMessageBox::information(this, tr("Fortune Client"),
                tr("The following error occurred: %1.")
                .arg(tool->getClient()->errorString()));
        }
}

bool loginDialog::isConnected()
{
    return (this->tool->getClient()->state()==3);
}

void loginDialog::on_btn_login_2_clicked()
{
    if(isConnected())
    {

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("您已连接成功，请登录");
        msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        msgBox->setStyleSheet("background-color:white");
        msgBox->exec();
    }
    else
    {

        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("连接失败，请检查远端IP和端口号");
        msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        msgBox->setStyleSheet("background-color:white");
        msgBox->exec();
    }
}
