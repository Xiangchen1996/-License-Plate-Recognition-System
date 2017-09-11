/**
 *  Author: lwei
 *  Since: 2016.8.26
 *  Version: 1.0.0
 */
#include "messagebox.h"
#include "iconhelper.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMouseEvent>

MessageBox::MessageBox(QWidget *parent,
                       Icon icon,
                       const QString &title,
                       const QString &text,
                       QMessageBox::StandardButtons standButtons,
                       QMessageBox::StandardButton defaultButton)
    :QDialog(parent)
    ,m_lIconTitle(new QLabel(this))
    ,m_lTitle(new QLabel(this))
    ,m_lIconMain(new QLabel(this))
    ,m_lText(new QLabel(this))
    ,m_layout(new QVBoxLayout())
    ,m_pButtonBox(new QDialogButtonBox(this))
    ,m_mouserPressed(false)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setFixedSize(QSize(606, 286));

    m_layout->setContentsMargins(20, 20, 20, 20);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(8, 0, 0, 0);
    titleLayout->setSpacing(20);
    titleLayout->addWidget(m_lIconTitle);
    titleLayout->addWidget(m_lTitle);
    titleLayout->addStretch(1);
    m_lIconTitle->setFixedHeight(20);
    m_lTitle->setFixedHeight(20);
    m_layout->addLayout(titleLayout);

    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setFixedHeight(200);
    m_layout->addWidget(groupBox);
    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    groupBox->setLayout(vBoxLayout);
    vBoxLayout->setContentsMargins(20, 20, 20, 20);
    vBoxLayout->setSpacing(20);

    QHBoxLayout *hLayout  = new QHBoxLayout();
    m_lIconMain->setFixedSize(QSize(90, 90));
    m_lText->setFixedHeight(90);
    hLayout->addWidget(m_lIconMain);
    hLayout->addWidget(m_lText);
    hLayout->addStretch(1);
    hLayout->setSpacing(10);
    vBoxLayout->addLayout(hLayout);

    QHBoxLayout *hLayoutButtons  = new QHBoxLayout();
    hLayoutButtons->addStretch(1);
    hLayoutButtons->addWidget(m_pButtonBox);
    vBoxLayout->addLayout(hLayoutButtons);
    m_pButtonBox->setFixedHeight(55);
    m_layout->addWidget(groupBox);
    setLayout(m_layout);

    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons((int)standButtons));
    setDefaultButton(defaultButton);

    QList<QAbstractButton *> buttons =  m_pButtonBox->buttons();
    for(int i = 0; i < buttons.size(); i++) {
        QDialogButtonBox::StandardButton button = m_pButtonBox->standardButton(buttons.at(i));
        QPushButton *pushButton = m_pButtonBox->button(button);
        pushButton->setFixedSize(QSize(135, 55));
        if(button == QDialogButtonBox::Ok || button == QDialogButtonBox::Yes) {
            pushButton->setText("确定");
        } else {
            pushButton->setText("取消");
        }
        pushButton->setStyleSheet("QPushButton{border:3px solid rgb(176,181,185);"
                                  "border-radius:5px;"
                                  "font-family:微软雅黑;font-size:18px;}");
    }

    IconHelper::Instance()->SetIcon(m_lIconTitle, QChar(0xf05a), 20);
    m_lTitle->setText(title);
    m_lTitle->setStyleSheet("font-family:微软雅黑;font-size:20px;");
    m_lText->setText(text);
    m_lText->setStyleSheet("font-family:微软雅黑;font-size:18px;");

    if(icon == Messsage) {
        m_lIconMain->setStyleSheet("border-image:url(:/icon/icon/info.png)");
    } else if(icon == Question) {
        m_lIconMain->setStyleSheet("border-image:url(:/icon/icon/question.png)");
    } else if(icon == Warning) {
        m_lIconMain->setStyleSheet("border-image:url(:/icon/icon/error.png)");
    } else if(icon == Error) {
        m_lIconMain->setStyleSheet("border-image:url(:/icon/icon/close.png)");
    }

    this->setStyleSheet("QDialog{border:1px solid black;background-color:rgb(212,217,221);}");

    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this,
            SLOT(onButtonClicked(QAbstractButton*)));
}

void MessageBox::setDefaultButton(QPushButton *button)
{
    if(!m_pButtonBox->buttons().contains(button)) {
        return ;
    }

    button->setDefault(true);
    button->setFocus();
}

void MessageBox::setDefaultButton(QMessageBox::StandardButton defaultButton)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(defaultButton)));
}

void MessageBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_mouserPressed = true;
        m_point = event->globalPos() - this->pos();
        event->accept();
    }
}

void MessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mouserPressed && (event->buttons() & Qt::LeftButton)) {
        this->move(event->globalPos() - m_point);
        event->accept();
    }
}

void MessageBox::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    m_mouserPressed = false;
}

int MessageBox::execReturnCode(QAbstractButton *button)
{
    return m_pButtonBox->standardButton(button);
}

void MessageBox::onButtonClicked(QAbstractButton *button)
{
    done(execReturnCode(button));
}
