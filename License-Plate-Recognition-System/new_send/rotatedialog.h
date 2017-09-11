#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QStackedWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QTextStream>


class loginDialog;
class addPortDialog;
class RotateWidget : public QStackedWidget
{
    Q_OBJECT

public:
    RotateWidget(QWidget *parent = NULL);
    ~RotateWidget();
    int exec();
private:
    // 初始化旋转的窗口;
    void initRotateWindow();
    // 绘制旋转效果;
    void paintEvent(QPaintEvent* event);

private slots:
    // 开始旋转窗口;
    void onRotateWindow();
    // 窗口旋转结束;
    void onRotateFinished();
    // 最小化窗口;
    void onHideWindow();


protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


private:
    // 当前窗口是否正在旋转;
    bool m_isRoratingWindow;
    loginDialog* m_loginWindow;
    addPortDialog* m_loginNetSetWindow;
    int m_nextPageIndex;
    QPoint mousePoint;//鼠标拖动时的坐标
    bool mousepressd;//用于判断是否按下
};

#endif // ROTATEWIDGET_H
