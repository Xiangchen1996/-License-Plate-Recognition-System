#ifndef ADDPORTDIALOG_H
#define ADDPORTDIALOG_H

#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QTextStream>

namespace Ui {
class addPortDialog;
}

class addPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addPortDialog(QWidget *parent = 0);
    ~addPortDialog();
    QString getServer();
    QString getPort();

private slots:
    void on_btn_rotate_clicked();


    void on_btn_min_clicked();

    void on_btn_close_clicked();

    void on_btn_requestConnect_clicked();

signals:
    void rotateWindow();
    void closeProgram();
    void minimizeWindow();


private:
    Ui::addPortDialog *ui;

};

#endif // ADDPORTDIALOG_H
