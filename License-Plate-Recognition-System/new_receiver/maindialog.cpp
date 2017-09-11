#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(Server *server,DetectThread *detectThread,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{

    this->detectThread=detectThread;
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->server=server;
    changeButtonState();
    currentIndex=0;

    parser=new JsonParser();
    ui->le_port->setValidator(new QIntValidator(0, 9999, this)); //0, 1000为输入的数字值范围
    ui->le_port->setEnabled(false);
    ui->le_port->setText(QString::number(server->getCommandPort()));

    model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,tr("车牌"));
    model->setHeaderData(1,Qt::Horizontal,tr("时间"));
    model->setHeaderData(2,Qt::Horizontal,tr("地点"));

    model_1 = new QStandardItemModel();
    model_1->setColumnCount(2);
    model_1->setHeaderData(0,Qt::Horizontal,tr("文件名"));
    model_1->setHeaderData(1,Qt::Horizontal,tr("匹配率"));

    model_2 = new QStandardItemModel();
    model_2->setColumnCount(2);
    model_2->setHeaderData(0,Qt::Horizontal,tr("文件名"));
    model_2->setHeaderData(1,Qt::Horizontal,tr("匹配率"));




    ui->tv_infoList->setModel(model);
    ui->tv_infoList->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->lv_needRecognize->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->lv_recognized->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lv_needRecognize->setModel(model_2);
    ui->lv_needRecognize->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lv_recognized->setModel(model_1);
    ui->lv_recognized->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(this->server->getCommandSocket(),SIGNAL(refreshConnection()),this,SLOT(getConnectedIP()));
    connect(this->detectThread,SIGNAL(detectConnection()),this,SLOT(getConnectedIP()));
    connect(RecQueue::getInstance(),SIGNAL(refreshQueue()),this,SLOT(refreshRecQueue()));
    connect(DoneQueue::getInstance(),SIGNAL(refreshQueue()),this,SLOT(refreshDoneQueue()));




    getConnectedIP();
    refreshRecQueue();
    refreshDoneQueue();
}

void mainDialog::refreshRecQueue()
{
    queue<QString> rec=RecQueue::getInstance()->getRecQueue();
    qDebug()<<"rec queue size:"<<rec.size();
    model_1->clear();
    model_1->setColumnCount(2);
    model_1->setHeaderData(0,Qt::Horizontal,tr("文件名"));
    model_1->setHeaderData(1,Qt::Horizontal,tr("匹配率"));

    int count=0;
    while(!rec.empty())
    {
        QString elment=rec.front();
        qDebug()<<count<<"*********"<<elment;
        QString info=DBHelper::getInstance()->getRecordByPicName(rec.front()).front();
        JsonParser *p=new JsonParser();
        p->setMessage(info);
        model_1->setItem(count,0,new QStandardItem(p->getPicName()));
        model_1->setItem(count,1,new QStandardItem(QString::number(p->getRate())));
        count++;
        rec.pop();
    }

    ui->lv_needRecognize->setModel(model_1);




}

void mainDialog::refreshDoneQueue()
{
    queue<QString> done=DoneQueue::getInstance()->getDoneQueue();
    model_2->clear();
    model_2->setColumnCount(2);
    model_2->setHeaderData(0,Qt::Horizontal,tr("文件名"));
    model_2->setHeaderData(1,Qt::Horizontal,tr("匹配率"));

    int count=0;
    while(!done.empty())
    {
        QString info=DBHelper::getInstance()->getRecordByPicName(done.front()).front();
//        qDebug()<<count<<"----->"<<info;
        JsonParser *p=new JsonParser();
        p->setMessage(info);
        model_2->setItem(count,0,new QStandardItem(p->getPicName()));
        model_2->setItem(count,1,new QStandardItem(QString::number(p->getRate())));
        count++;
        done.pop();
    }
    ui->lv_recognized->setModel(model_2);
}

void mainDialog::modelReset()
{
    model->clear();
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,tr("车牌"));
    model->setHeaderData(1,Qt::Horizontal,tr("时间"));
    model->setHeaderData(2,Qt::Horizontal,tr("地点"));
}

void mainDialog::getConnectedIP()
{
    names=this->server->getCommandSocket()->getIPList();
    QStringList ips;
    list<QString>::iterator itor;
    for(itor = names.begin(); itor != names.end(); ++itor)
    {
        ips<<*itor;
    }
    QStringListModel *model = new QStringListModel(ips);
    ui->lv_connectList->setModel(model);
}

void mainDialog::changeButtonState()
{
    if(server->getRunningState()){
        ui->btn_startServe->setEnabled(false);
        ui->btn_modify->setEnabled(false);
        ui->btn_stopServe->setEnabled(true);
        ui->le_port->setEnabled(false);
    }else{
        ui->btn_startServe->setEnabled(true);
        ui->btn_modify->setEnabled(true);
        ui->btn_stopServe->setEnabled(false);
        ui->le_port->setEnabled(true);
    }
    ui->le_port->setText(QString::number(server->getCommandPort()));

}

void mainDialog::startSocket()
{
    server->startServer();
}

void mainDialog::stopSocket()
{
    server->stopServer();
}


mainDialog::~mainDialog()
{
    delete ui;
}


//最小化
void mainDialog::on_btn_min_clicked()
{
    this->showMinimized();
}

//关闭
void mainDialog::on_btn_close_clicked()
{
    this->close();
}

void mainDialog::on_btn_startServe_clicked()
{
    //TODO
    server->startServer();
    changeButtonState();

}

void mainDialog::on_btn_stopServe_clicked()
{
    //TODO
    server->stopServer();
    changeButtonState();

}

void mainDialog::on_btn_modify_clicked()
{
    if(!ui->le_port->text().isEmpty())
    {
        server->setCommandPort(ui->le_port->text().toInt());
    }else{
        QMessageBox::information(this, "Server","input the right port");
    }
}

void mainDialog::on_cb_queryWay_currentIndexChanged(int index)
{
    currentIndex=index;
}

void mainDialog::on_btn_query_clicked()
{
    modelReset();
    switch(currentIndex){
    //IDCard
    case 0:
        if(!ui->le_query->text().isEmpty())
        {
            list<QString> lists=DBHelper::getInstance()->getRecordByID(ui->le_query->text());
            list<QString>::iterator itor;
            int count=0;
            for(itor=lists.begin();itor!=lists.end();itor++){
                parser->setMessage(*itor);
                model->setItem(count,0,new QStandardItem(parser->getFinalCarNumber()));
                model->setItem(count,1,new QStandardItem(parser->getDate()));
                model->setItem(count,2,new QStandardItem(parser->getPlace()));
                count++;
            }
        }
        //test
//        model->setItem(0,0,new QStandardItem(QString("123")));
//        model->setItem(0,1,new QStandardItem(QString("456")));
//        model->setItem(0,2,new QStandardItem(QString("789")));
//        model->setItem(1,0,new QStandardItem(QString("aaa")));
//        model->setItem(1,1,new QStandardItem(QString("bbb")));
//        model->setItem(1,2,new QStandardItem(QString("ccc")));
        break;
    //car_Number
    case 1:
        if(!ui->le_query->text().isEmpty())
        {
            list<QString> lists=DBHelper::getInstance()->getRecordByCarNumber(ui->le_query->text());
            list<QString>::iterator itor;
            int count=0;
            for(itor=lists.begin();itor!=lists.end();itor++){
                parser->setMessage(*itor);
                model->setItem(count,0,new QStandardItem(parser->getFinalCarNumber()));
                model->setItem(count,1,new QStandardItem(parser->getDate()));
                model->setItem(count,2,new QStandardItem(parser->getPlace()));
                count++;
            }
        }
        break;
    //person_name
    case 2:
        if(!ui->le_query->text().isEmpty())
        {
            list<QString> lists=DBHelper::getInstance()->getRecordByName(ui->le_query->text());
            list<QString>::iterator itor;
            int count=0;
            for(itor=lists.begin();itor!=lists.end();itor++){
                parser->setMessage(*itor);
                model->setItem(count,0,new QStandardItem(parser->getFinalCarNumber()));
                model->setItem(count,1,new QStandardItem(parser->getDate()));
                model->setItem(count,2,new QStandardItem(parser->getPlace()));
                count++;
            }
        }
        break;
    }
}


void mainDialog::on_tv_infoList_doubleClicked(const QModelIndex &index)
{
    //model->data(index);

    QModelIndex in=model->index(index.row(),0);
    QString car_num = model->data(in, Qt::DisplayRole).toString();

//    recognitionDialog *rec=new recognitionDialog();
//    rec->show();
    QString picName=DBHelper::getInstance()->getPicName(car_num);
    if(!picName.isEmpty())
    {
        recognitionDialog *rec=new recognitionDialog(picName);
        rec->exec();
    }else{
        QMessageBox::information(this, "Server","do not have the car");
    }
    //TODO
}

void mainDialog::on_lv_recognized_doubleClicked(const QModelIndex &index)
{
    QModelIndex in=model_2->index(index.row(),0);
    QString picName = model_2->data(in, Qt::DisplayRole).toString();
    recognitionDialog *rec=new recognitionDialog(picName);
    rec->exec();

}

void mainDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousepressd && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos()- mousePoint);
        e->accept();
    }

}


void mainDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        mousepressd = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void mainDialog::mouseReleaseEvent(QMouseEvent *){
    mousepressd = false;
}

//QString mainDialog::getPlateNumber()
//{

//}



void mainDialog::on_lv_needRecognize_clicked(const QModelIndex &index)
{
    QModelIndex in=model_1->index(index.row(),0);
    QString picName = model_1->data(in, Qt::DisplayRole).toString();

    recognitionDialog *rec=new recognitionDialog(picName);
    rec->exec();

    //查询数据库该名字对应的数据记录在人工修改位是否有标记，没有有的话，说明该图像未经人工操作，则不做操作
    //否则将其从RecQueue中pop掉并加入DoneQueue
    QString human_rec = DBHelper::getInstance()->getHumanRecNumber(picName);

    if(human_rec == "")
    {
//        return;
    }
    else//否则说明人工操作过，取出该图像文件并加入到DoneQueue
    {
        queue<QString> tempNames;//用作临时队列来方便取出操作过的图像文件
        qDebug()<<tempNames.empty();
        while(! RecQueue::getInstance()->isEmpty())
        {
            QString tempname = RecQueue::getInstance()->front();
            if(tempname.compare(picName) != 0)
            {
                tempNames.push(tempname);

            }
            else
            {
                DoneQueue::getInstance()->push(picName);

            }
            RecQueue::getInstance()->pop();

        }


        //取出该图像文件后，恢复原有的RecQueue：
        while(!tempNames.empty())
        {
            QString tempname = tempNames.front();
            RecQueue::getInstance()->push(tempname);
            tempNames.pop();
            qDebug()<<"///////////////////////////";
        }
    }
    //最后刷新队列
    //RecQueue::getInstance()->refreshQueue();

}
