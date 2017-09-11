#ifndef RECOGNITIONDIALOG_H
#define RECOGNITIONDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include "./process_h/plate_detect.h"
#include "dbhelper.h"
#include "utils.h"

namespace Ui {
class recognitionDialog;
}

class recognitionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit recognitionDialog(QString picName,QWidget *parent = 0);
    ~recognitionDialog();

private slots:
    void on_btn_min_clicked();

    void on_btn_close_clicked();
    void on_btn_delete_clicked();

    void on_btn_modify_clicked();

    void on_btn_exit_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::recognitionDialog *ui;
    QString picName;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下
    CPlateDetect *plateDetect;
};

#endif // RECOGNITIONDIALOG_H
