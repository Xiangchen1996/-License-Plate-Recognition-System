#include "recognitiondialog.h"
#include "ui_recognitiondialog.h"

recognitionDialog::recognitionDialog(QString picName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recognitionDialog)
{
    ui->setupUi(this);
    this->picName=picName;

    ui->l_picName->setText(picName);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);


    //显示汽车图像
  //  ui->l_carPic->setPixmap(QPixmap::fromImage("./rev_pic/"+picName));
    QPixmap carPic("./rev_pic/"+picName);
    carPic = carPic.scaled(ui->l_carPic->width(),ui->l_carPic->height(),
                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->l_carPic->setPixmap(carPic);

    //解析违章时间和违章地点：
    ui->l_time->setText(picName.mid(9,4)+"年"+picName.mid(13,2)+"月"+picName.mid(15,2)+"日  "+
                        picName.mid(17,2)+":"+picName.mid(19,2)+":"+picName.mid(21,2));
    ui->l_location->setText(Utils::getInstance()->getPlace("410323"));



    //显示分割后的车牌图像
    vector<CPlate> plateVec;
    Mat carMat = imread("./rev_pic/"+picName.toStdString());
    qDebug()<<"*****"<<this->picName;
    plateDetect = new CPlateDetect();

//    plateDetect->plateDetectDeep(carMat, plateVec,"./tempPlate");
    if(0==plateDetect->plateDetectDeep(carMat, plateVec,"",false))
    {

        //返回0代表成功运行
        CPlate plate = plateVec[0];
        Mat plateMat = plate.getPlateMat();
        imwrite("./tempPlate/temp.jpg",plateMat);
        qDebug()<<"*****"<<this->picName;
        QPixmap plaPic("./tempPlate/temp.jpg");
        plaPic = plaPic.scaled(ui->l_platePic->width(),ui->l_platePic->height(),
                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->l_platePic->setPixmap(plaPic);

        //查询自动识别的结果
        QString autoResult = DBHelper::getInstance()->getAutoRecNumber(picName);
        ui->l_plateNumber->setText(autoResult);
        //并将结果放入可编辑lineedit中
        QString human_rec_number = DBHelper::getInstance()->getHumanRecNumber(picName);
        if(human_rec_number != "")
        {
            ui->le_plateNumber->setText(human_rec_number);
        }
        else
        {
            ui->le_plateNumber->setText(autoResult);
        }

    }
    else
    {
        ui->l_plateNumber->setText("无法识别，请人工识别");
    }

}

recognitionDialog::~recognitionDialog()
{
    delete ui;
}

//最小化
void recognitionDialog::on_btn_min_clicked()
{
    this->showMinimized();
}

//关闭
void recognitionDialog::on_btn_close_clicked()
{
    this->close();
}
void recognitionDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void recognitionDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void recognitionDialog::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}

void recognitionDialog::on_btn_delete_clicked()
{
    DBHelper::getInstance()->deleteRecord(picName);
}

void recognitionDialog::on_btn_modify_clicked()
{
    if(ui->le_plateNumber->text() != "")
    {
        DBHelper::getInstance()->humanRec(picName,ui->le_plateNumber->text());
    }
}

void recognitionDialog::on_btn_exit_clicked()
{
    this->close();
}
