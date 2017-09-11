#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <tcpserver.h>
#include <QMessageBox>
#include <QDebug>
#include <server.h>
#include <list>
#include <QStringListModel>
#include <detectthread.h>
#include <QStandardItemModel>
#include <jsonparser.h>
#include <recognitiondialog.h>
#include <recqueue.h>
#include <donequeue.h>
#include <QPainter>
#include <QMouseEvent>

using namespace std;
namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(Server *server,DetectThread *detectThread,QWidget *parent = 0);
    ~mainDialog();
    QString getPlateNumber();

private slots:
    void on_btn_min_clicked();

    void on_btn_close_clicked();

    void on_btn_startServe_clicked();

    void on_btn_stopServe_clicked();

    void on_btn_modify_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::mainDialog *ui;
    void changeButtonState();

    void startSocket();
    void stopSocket();
    void modelReset();
    list<QString> names;
    Server *server;
    DetectThread *detectThread;
    int currentIndex;
    QStandardItemModel  *model;//右侧查询列表
    QStandardItemModel  *model_1;//中间下部列表
    QStandardItemModel  *model_2;//中间上部列表
    JsonParser *parser;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下





private slots:
    void getConnectedIP();

    void refreshRecQueue();
    void refreshDoneQueue();

    void on_cb_queryWay_currentIndexChanged(int index);
    void on_btn_query_clicked();
    void on_tv_infoList_doubleClicked(const QModelIndex &index);
    void on_lv_recognized_doubleClicked(const QModelIndex &index);
    void on_lv_needRecognize_clicked(const QModelIndex &index);
};

#endif // MAINDIALOG_H
