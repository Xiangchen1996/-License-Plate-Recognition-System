#include "./process_h/chars_recognise.h"



CCharsRecognise::CCharsRecognise()
{
    //cout << "CCharsRecognise" << endl;
    m_charsSegment = new CCharsSegment();
    m_charsIdentify = new CCharsIdentify();
}

void CCharsRecognise::LoadANN(string s)
{
    m_charsIdentify->LoadModel(s.c_str());
}

string CCharsRecognise::charsRecognise(Mat plate)
{
    return m_charsIdentify->charsIdentify(plate);
}
int CCharsRecognise::charsRecognise(Mat plate, string& plateLicense,double &rate, int index)
{
    //车牌字符方块集合
    vector<Mat> matVec;

    string plateIdentify = "";


    int result = m_charsSegment->charsSegment(plate, matVec);
    if (result == 0)
    {
        int num = matVec.size();
        double totalRate=0,singleRate=0;
        for (int j = 0; j < num; j++)
        {
            Mat charMat = matVec[j];
            bool isChinses = false;
            bool isSpeci=false;
            //默认首个字符块是中文字符
            if (j == 0)
                isChinses = true;
            if(j==1)
                isSpeci=true;
            string charcater = m_charsIdentify->charsIdentify(charMat, isChinses,isSpeci,singleRate);
            totalRate += singleRate;
            cout<<"singleRate:"<<singleRate<<endl;
             cout<<"totalRate:"<<totalRate<<endl;

            plateIdentify = plateIdentify + charcater;
        }
        rate = totalRate/7;
        cout<<"average rate:"<<rate;
    }

    plateLicense = plateIdentify;

    if (plateLicense.size() < 7)
    {
        return -1;
    }

    return result;
}

