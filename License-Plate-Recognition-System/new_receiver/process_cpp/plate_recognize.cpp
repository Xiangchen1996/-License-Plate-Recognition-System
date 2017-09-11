#include "./process_h/plate_recognize.h"


CPlateRecognize::CPlateRecognize()
{
    m_plateDetect= new CPlateDetect();
    m_charsRecognise = new CCharsRecognise();
}

////! 装载SVM模型
void CPlateRecognize::LoadSVM(string strSVM)
{
    m_plateDetect->LoadSVM(strSVM.c_str());
}

////! 装载ANN模型
void CPlateRecognize::LoadANN(string strANN)
{
    m_charsRecognise->LoadANN(strANN.c_str());
}



int CPlateRecognize::plateRecognize(Mat src, vector<string>& licenseVec, QString srcPath, double& rate, int index)
{
    // 车牌方块集合
    vector<CPlate> plateVec;


    // 如果设置了Debug模式，就依次显示所有的图片
    bool showDetectArea = getPDDebug();
    showDetectArea=0;
    // 进行深度定位，使用颜色信息与二次Sobel
    int resultPD = plateDetectDeep(src, plateVec, srcPath, showDetectArea,0);

    Mat result;
    src.copyTo(result);

    if (resultPD == 0)
    {
        int num = plateVec.size();


        for (int j = 0; j < num; j++)
        {
            CPlate item = plateVec[j];

            Mat plate = item.getPlateMat();

            //获取车牌颜色
            string plateType = getPlateColor(plate);

            //获取车牌号
            string plateIdentify = "";
            int resultCR = charsRecognise(plate, plateIdentify,rate);
            if (resultCR == 0)
            {
                string license = plateType + ":" + plateIdentify;
                licenseVec.push_back(license);


                RotatedRect minRect = item.getPlatePos();
                Point2f rect_points[4];
                minRect.points( rect_points );

                if(item.bColored)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        line(result, rect_points[j], rect_points[(j + 1) % 4], Scalar(255, 255, 0), 2, 8);
                        //颜色定位车牌，黄色方框
                    }
                }
                else
                {
                    for( int j = 0; j < 4; j++ )
                    {
                        line(result, rect_points[j], rect_points[(j+1)%4], Scalar(0,0,255), 2, 8 );//sobel定位车牌，红色方框
                    }

                }


            }
        }
    }


    //showResult(result);


    return resultPD;
}


