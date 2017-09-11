#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <dbhelper.h>
#include <utils.h>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btn_min_clicked();

    void on_btn_close_clicked();

    void on_btn_login_clicked();
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::Dialog *ui;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下
};

#endif // DIALOG_H
