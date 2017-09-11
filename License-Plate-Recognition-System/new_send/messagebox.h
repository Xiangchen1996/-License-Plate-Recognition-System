/**
 *  Author: lwei
 *  Since: 2016.8.26
 *  Version: 1.0.0
 */
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QPoint>
#include <QMessageBox>

class QLabel;
class QVBoxLayout;
class QDialogButtonBox;
class QMouseEvent;

class MessageBox : public QDialog
{
    Q_OBJECT
public:
    enum Icon {
        Messsage,
        Question,
        Warning,
        Error,
    };

    explicit MessageBox(QWidget *parent = 0,
                        Icon icon = Messsage,
                        const QString &title = "Tip",
                        const QString &text = "",
                        QMessageBox::StandardButtons  = QMessageBox::Ok,
                        QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton defaultButton );

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int execReturnCode(QAbstractButton *button);

signals:

public slots:
private slots:
    void onButtonClicked(QAbstractButton *button);
private:
    QLabel *m_lIconTitle;
    QLabel *m_lTitle;
    QLabel *m_lIconMain;
    QLabel *m_lText;
    QVBoxLayout *m_layout;
    QDialogButtonBox *m_pButtonBox;
    bool m_mouserPressed;
    QPoint m_point;
};

#endif // MESSAGEBOX_H
