#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QStringListModel>
#include <QTimer>
#include "sendpicthread.h"
#include "umethod.h"
#include "jsonparser.h"
#include "jsonwrapper.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QFileInfo>
#include <QHostInfo>
#include "messagebox.h"

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();


private slots:
    void on_btn_min_clicked();

    void on_btn_close_clicked();

    void on_btn_choosePic_clicked();

    void on_btn_sendPic_clicked();

    void on_btn_exit_clicked();


    void on_btn_stopSend_clicked();
    void sendNextPicture();
    void sendCurrentPicture();
    void updateProgress(int total,int current);

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    QString getIP();

signals:
    void stopAndQuit();

private:
    Ui::mainDialog *ui;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下

    UMethod *tool;
    QString currentPicPath;
    int totalNumber;
    int currentNumber;
    JsonParser *parser;
    JsonWrapper *wrapper;
};

#endif // MAINDIALOG_H
