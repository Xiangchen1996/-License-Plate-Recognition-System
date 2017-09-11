#include "rotatedialog.h"
#include <QApplication>
#include <QTcpSocket>
#include "messagebox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RotateWidget w;
    w.show();


    return a.exec();
}
