#ifndef DETECTTHREAD
#define DETECTTHREAD
#include <QThread>

class DetectThread : public QThread
{
    Q_OBJECT

public:
    explicit DetectThread(QObject *parent = 0): QThread(parent)
    {

    }

    ~DetectThread(){

    }


protected:
    virtual void run() Q_DECL_OVERRIDE {

        while(true){
            msleep(1000);

            emit detectConnection();
        }
    }



signals:
    void detectConnection();
};





#endif // DETECTTHREAD

