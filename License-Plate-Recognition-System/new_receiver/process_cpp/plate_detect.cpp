#include "./process_h/plate_detect.h"

CPlateDetect::CPlateDetect()
{
    //cout << "CPlateDetect" << endl;
    m_plateLocate = new CPlateLocate();
    m_plateJudge = new CPlateJudge();

    // 默认EasyPR在一幅图中定位最多3个车
    m_maxPlates = 3;
}

void CPlateDetect::LoadSVM(string s)
{
    m_plateJudge->LoadModel(s.c_str());
}

int CPlateDetect::plateDetect(Mat src, vector<Mat>& resultVec, int index)
{
    //可能是车牌的图块集合
    vector<Mat> matVec;

    int resultLo = m_plateLocate->plateLocate(src, matVec);

    if (0 != resultLo)
        return -1;

    int resultJu = m_plateJudge->plateJudge(matVec, resultVec);

    if(getPDDebug())
    {
        int size = resultVec.size();
        for (int i = 0; i < size; i++)
        {
            Mat img = resultVec[i];
            if(1)
            {
                stringstream ss(stringstream::in | stringstream::out);
                ss << "image/tmp/plate_judge_result_" << i << ".jpg";
                imwrite(ss.str(), img);
            }
        }
    }


    if (0 != resultJu)
        return -2;

    return 0;
}


int CPlateDetect::plateDetectDeep(Mat src, vector<CPlate>& resultVec,QString srcPath, bool showDetectArea, int index)
{
    printf("*****************************************");

    vector<CPlate> color_Plates;
    vector<CPlate> sobel_Plates;
    vector<CPlate> color_result_Plates;
    vector<CPlate> sobel_result_Plates;

    vector<CPlate> all_result_Plates;


//************************************************************
    m_plateLocate->plateColorLocate(src, color_Plates, index);

    m_plateJudge->plateJudge(color_Plates, color_result_Plates,srcPath);


    for (int i = 0; i< color_result_Plates.size(); i++)
    {
        CPlate plate = color_result_Plates[i];

        RotatedRect minRect = plate.getPlatePos();
        Point2f rect_points[4];
        minRect.points(rect_points);


        all_result_Plates.push_back(plate);
    }


    {
        m_plateLocate->plateSobelLocate(src, sobel_Plates, index);
        m_plateJudge->plateJudge(sobel_Plates, sobel_result_Plates,srcPath);

        for (int i = 0; i< sobel_result_Plates.size(); i++)
        {
            CPlate plate = sobel_result_Plates[i];

            plate.bColored = false;

            all_result_Plates.push_back(plate);
        }
    }

    for (int i = 0; i < all_result_Plates.size(); i++)
    {
        // 把截取的车牌图像依次放到左上角
        CPlate plate = all_result_Plates[i];
        resultVec.push_back(plate);
    }

    return 0;
}



