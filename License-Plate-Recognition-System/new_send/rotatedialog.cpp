#include "rotatedialog.h"
#include <QPropertyAnimation>
#include "logindialog.h"
#include "addPortDialog.h"

RotateWidget::RotateWidget(QWidget *parent)
    : QStackedWidget(parent)
    , m_isRoratingWindow(false)
    , m_nextPageIndex(0)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    // 给窗口设置rotateValue属性;
    this->setProperty("rotateValue", 0);
    initRotateWindow();

//    if(m_loginWindow->isConnected())
//    {
//        QMessageBox::information(this,tr("连接成功"),tr("您已连接成功，请登录"),
//                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }
//    else
//    {
//        QMessageBox::information(this,tr("连接失败"),tr("您连接失败，请检查远端IP和端口号"),
//                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }


}

RotateWidget::~RotateWidget()
{

}

// 初始化旋转的窗口;
void RotateWidget::initRotateWindow()
{
    m_loginWindow = new loginDialog(this);
    // 这里定义了两个信号，需要自己去发送信号;
    connect(m_loginWindow, SIGNAL(rotateWindow()), this, SLOT(onRotateWindow()));
    m_loginNetSetWindow = new addPortDialog(this);
    connect(m_loginNetSetWindow, SIGNAL(rotateWindow()), this, SLOT(onRotateWindow()));

    //下面再定义两个信号，用于修复addportdialog和logindialog界面点击X无法完全关掉程序的bug
    //定义信号发送方：addportdialog和logindialog    接收方：this
    connect(m_loginWindow,SIGNAL(closeProgram()),this,SLOT(close()));
    connect(m_loginNetSetWindow,SIGNAL(closeProgram()),this,SLOT(close()));
    connect(m_loginWindow,SIGNAL(hideProgram()),this,SLOT(hide()));

    //下面再定义两个信号，用于修复addportdialog和logindialog界面点击-无法最小化
    connect(m_loginWindow,SIGNAL(minimizeWindow()),this,SLOT(onHideWindow()));
    connect(m_loginNetSetWindow,SIGNAL(minimizeWindow()),this,SLOT(onHideWindow()));


    //查询子控件addportdialog的le_server和le_port是否有内容显示
    //有内容----->首先显示登录界面
    //无内容----->首先显示连接设置界面
    //通过以上方式实现默认serverIP和port为上次的内容
    if(m_loginNetSetWindow->getServer()=="")
    {
        this->addWidget(m_loginNetSetWindow);
        this->addWidget(m_loginWindow);

    }
    else
    {
        this->addWidget(m_loginWindow);
        this->addWidget(m_loginNetSetWindow);
    }
    // 这里宽和高都增加，是因为在旋转过程中窗口宽和高都会变化;
    this->setFixedSize(QSize(m_loginWindow->width()+20, m_loginWindow->height() + 100));
    //设置背景透明色
    this->setStyleSheet("background-color:rgba(0,0,0,0)");

}

// 开始旋转窗口;
void RotateWidget::onRotateWindow()
{
    // 如果窗口正在旋转，直接返回;
    if (m_isRoratingWindow)
    {
        return;
    }
    m_isRoratingWindow = true;
    m_nextPageIndex = (currentIndex() + 1) >= count() ? 0 : (currentIndex() + 1);
    QPropertyAnimation *rotateAnimation = new QPropertyAnimation(this, "rotateValue");
    // 设置旋转持续时间;
    rotateAnimation->setDuration(1500);
    // 设置旋转角度变化趋势;
    rotateAnimation->setEasingCurve(QEasingCurve::InCubic);
    // 设置旋转角度范围;
    rotateAnimation->setStartValue(0);
    rotateAnimation->setEndValue(180);
    connect(rotateAnimation, SIGNAL(valueChanged(QVariant)), this, SLOT(repaint()));
    connect(rotateAnimation, SIGNAL(finished()), this, SLOT(onRotateFinished()));
    // 隐藏当前窗口，通过不同角度的绘制来达到旋转的效果;
    currentWidget()->hide();
    rotateAnimation->start();
}

// 旋转结束;
void RotateWidget::onRotateFinished()
{
    m_isRoratingWindow = false;
    setCurrentWidget(widget(m_nextPageIndex));
    repaint();
}

// 绘制旋转效果;
void RotateWidget::paintEvent(QPaintEvent* event)
{
    if (m_isRoratingWindow)
    {
        // 小于90度时;
        int rotateValue = this->property("rotateValue").toInt();
        if (rotateValue <= 90)
        {
            QPixmap rotatePixmap(currentWidget()->size());
            currentWidget()->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateValue, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, rotatePixmap);
        }
        // 大于90度时
        else
        {
            QPixmap rotatePixmap(widget(m_nextPageIndex)->size());
            widget(m_nextPageIndex)->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(rotateValue + 180, Qt::YAxis);
            painter.setTransform(transform);
            painter.drawPixmap(-1 * width() / 2, 0, rotatePixmap);
        }
    }
    else
    {
        return QStackedWidget::paintEvent(event);
    }
}

void RotateWidget::onHideWindow()
{
    this->showMinimized();
}

void RotateWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void RotateWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void RotateWidget::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}

int RotateWidget::exec()
{
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
}
