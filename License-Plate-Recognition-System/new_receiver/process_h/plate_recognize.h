//////////////////////////////////////////////////////////////////////////
// Name:	    plate_recognize Header
// Version:		1.0
// Date:	    2014-09-28
// Author:	    liuruoze
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:
// Defines CPlateRecognize
//////////////////////////////////////////////////////////////////////////
#ifndef __PLATE_RECOGNIZE_H__
#define __PLATE_RECOGNIZE_H__

#include <QString>
#include "plate_detect.h"
#include "chars_recognise.h"


class CPlateRecognize : public CPlateDetect, public CCharsRecognise
{
public:
    CPlateRecognize();

    //! 车牌检测与字符识别
    int plateRecognize(Mat, vector<string>&, QString,double &,int index = 0);

    //! 生活模式与工业模式切换
    inline void setLifemode(bool param)
    {
        CPlateDetect::setPDLifemode(param);
    }

    //! 是否开启调试模式
    inline void setDebug(int param)
    {
        CPlateDetect::setPDDebug(param);
        CCharsRecognise::setCRDebug(param);
    }

    ////! 装载SVM
    void LoadSVM(string s);

    ////! 装载ANN模型
    void LoadANN(string s);

private:
    ////！车牌检测
    CPlateDetect* m_plateDetect;

    ////! 字符识别
    CCharsRecognise* m_charsRecognise;
};

#endif /* endif __PLATE_RECOGNITION_H__ */
