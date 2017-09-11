#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T21:22:46
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT+=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_receiver
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    recognitiondialog.cpp \
    maindialog.cpp \
    utils.cpp \
    tcpserver.cpp \
    tcpthread.cpp \
    server.cpp \
    jsonparser.cpp \
    jsonwrapper.cpp \
    connectionpool.cpp \
    dbhelper.cpp \
    workqueue.cpp \
    donequeue.cpp \
    process_cpp/ann_train.cpp \
    process_cpp/chars_identify.cpp \
    process_cpp/chars_recognise.cpp \
    process_cpp/chars_segment.cpp \
    process_cpp/core_func.cpp \
    process_cpp/imageprocess.cpp \
    process_cpp/plate_detect.cpp \
    process_cpp/plate_judge.cpp \
    process_cpp/plate_locate.cpp \
    process_cpp/plate_recognize.cpp \
    process_cpp/svm_train.cpp \
    process_cpp/util.cpp \
    imageprocessthread.cpp \
    recqueue.cpp

HEADERS  += dialog.h \
    recognitiondialog.h \
    maindialog.h \
    utils.h \
    tcpserver.h \
    detectthread.h \
    tcpthread.h \
    server.h \
    jsonparser.h \
    jsonwrapper.h \
    connectionpool.h \
    dbhelper.h \
    workqueue.h \
    donequeue.h \
    process_h/chars_identify.h \
    process_h/chars_recognise.h \
    process_h/chars_segment.h \
    process_h/core_func.h \
    process_h/imageprocess.h \
    process_h/plate.h \
    process_h/plate_detect.h \
    process_h/plate_judge.h \
    process_h/plate_locate.h \
    process_h/plate_recognize.h \
    process_h/uheader.h \
    process_h/util.h \
    imageprocessthread.h \
    recqueue.h

FORMS    += dialog.ui \
    recognitiondialog.ui \
    maindialog.ui

RESOURCES += \
    res.qrc \
    image.qrc

INCLUDEPATH +=D:\opencv\opencv\include\opencv \
              D:\opencv\opencv\include\opencv2 \
              D:\opencv\opencv\include


LIBS += D:/opencv/opencv/lib/libopencv_calib3d249.dll.a \
        D:/opencv/opencv/lib/libopencv_contrib249.dll.a \
        D:/opencv/opencv/lib/libopencv_nonfree249.dll.a \
        D:/opencv/opencv/lib/libopencv_ocl249.dll.a 	\
        D:/opencv/opencv/lib/libopencv_gpu249.dll.a	\
        D:/opencv/opencv/lib/libopencv_photo249.dll.a	\
        D:/opencv/opencv/lib/libopencv_objdetect249.dll.a \
        D:/opencv/opencv/lib/libopencv_legacy249.dll.a	\
        D:/opencv/opencv/lib/libopencv_ml249.dll.a	\
        D:/opencv/opencv/lib/libopencv_video249.dll.a	\
        D:/opencv/opencv/lib/libopencv_features2d249.dll.a \
        D:/opencv/opencv/lib/libopencv_highgui249.dll.a	\
        D:/opencv/opencv/lib/libopencv_imgproc249.dll.a \
        D:/opencv/opencv/lib/libopencv_flann249.dll.a	\
        D:/opencv/opencv/lib/libopencv_core249.dll.a

DISTFILES += \
    model/ann - bak.xml \
    model/ann.xml \
    model/haarcascade_frontalface_alt_tree.xml \
    model/haarcascade_frontalface_default.xml \
    model/svm.xml
