#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "jsonparser.h"
#include "jsonwrapper.h"
#include <QDataStream>
#include <QCryptographicHash>
#include <QString>
#include "logindialog.h"
#include "umethod.h"
#include <QAbstractSocket>
#include <QPixmap>
#include <QIcon>
#include "maindialog.h"
#include "messagebox.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

private slots:
    void on_btn_min_clicked();

    void on_btn_close_clicked();

    void on_btn_addPort_clicked();

    void on_btn_login_clicked();

    void on_btn_login_2_clicked();

signals:
    void rotateWindow();
    void closeProgram();
    void minimizeWindow();
    void hideProgram();

public slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void login();
    void readMessage();
    void sendMessage();
    bool isConnected();

private:
    Ui::loginDialog *ui;

    QLineEdit *id_edit;
    QLineEdit *pwd_edit;

    JsonParser *parser;
    JsonWrapper *wrapper;

    UMethod *tool;

};

#endif // LOGINDIALOG_H
