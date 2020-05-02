#pragma once

#include"MyData.h"


void PreWork();
void FindCSV();
void DefineMycolor();
BOOL CheckName(char* name);
void Calculate();

void PreWork()
{


    SetFont("KaiTi_GB2312");
    FontHeight = GetFontHeight();
    FontAscent = GetFontAscent();
    FontDescent = GetFontDescent();
  printf("%lf %lf %lf \n", FontHeight, FontAscent, FontDescent);
    
    GetCurrentDirectory(100, FilePath); 
    //printf("%s\n", FilePath);
    FindCSV(); //�ҵ���ǰĿ¼�µ�csv�ļ����ŵ�FileName��
    MaxX = GetWindowWidth();
    MaxY = GetWindowHeight();
    DefineMycolor();
    beginTableX = GetWindowWidth() * 0.2, beginTableY = GetWindowHeight() * 0.2;
    endTableX = GetWindowWidth() * 0.9, endTableY = GetWindowHeight() * 0.9;
    /*for (int i = 0; i < FileNum; i++)
        printf("%s\n", FileName[i]);*/
    IsChooseData[1] = 1;

}
void FindCSV()
{
    //"E:\\linux\\Compressed\\LibGraphics2019Hanoi\\demoprj-vs2017\\*.c";
    strcat(FilePath, "\\*.csv");
    //printf("%s", FilePath);
    struct _finddata_t data;
    long handle = _findfirst(FilePath, &data);

    if (handle < 0)
    {
        return;
    }

    int nRet = (handle < 0) ? -1 : 1;
    while (nRet >= 0)
    {
        if (data.attrib == _A_SUBDIR) // �����Ŀ¼
            ;
        else
        {

            FileName[FileNum] = (char *)malloc(sizeof(data.name) + 1);
            strcpy(FileName[FileNum++], data.name);
        }

        nRet = _findnext(handle, &data);
    }
    _findclose(handle); // �رյ�ǰ���
}
void DefineMycolor()
{

    DefineColor("MenuFrame", 232.0 / 255, 237.0 / 255, 239.0 / 255); //�˵���
    DefineColor("MenuFrameHot", 236.0 / 255, 232.0 / 255, 223.0 / 255);

    DefineColor("MenuBar", 227.0 / 255, 235.0 / 255, 255.0 / 255); //bar��
    DefineColor("TextBoxFrame", 155.0 / 255, 156.0 / 255, 155.0 / 255);

    DefineColor("TextBoxFrameHot", 124.0 / 255, 205.0 / 255, 244.0 / 255);
    DefineColor("TextBoxLabel", 11.0 / 255, 19.0 / 255, 43.0 / 255); //�����

    DefineColor("DirSelectionFrameHot", 91.0 / 255, 192.0 / 255, 235.0 / 255); //�ļ�ѡ���
    DefineColor("DirSelectionFrame", 112.0 / 255, 214.0 / 255, 1.0);

    DefineColor("DataButton", 218.0 / 255, 215.0 / 255, 205.0 / 255); //����ѡ������ɫ
}

BOOL CheckName(char* name)
{
    if (!strlen(name))
        return 0;
    else
    {
        for (int i = 0; i < FileNum; i++)
        {
            if (!strcmp(name, FileName[i]))
                return 1;
        }
    }
    return 0;
}

void Calculate()
{
  
    int ShowNum = 0;
    int Maxnum = 0;
    stu_Ptr tmp = head->next;
    while (tmp != NULL)
    {
     
        if (tmp->IsSelect)
        {
            ShowNum++;
            for (int i = 1; i <= ChooseDataNum; i++)
            {
                if (IsChooseData[i])
                {
                    Maxnum = max(Maxnum, tmp->Data[i]);
                }
            }
        }
        tmp = tmp->next;
    }
    //printf("Maxnum=%d   ShowNum=%d\n", Maxnum,ShowNum);
    if (Maxnum > 1000) {
 
        (Maxnum / 4) % 100 > 50 ? (TableMark1 = ((Maxnum / 4) - (Maxnum / 4) % 100) + 100 ):( TableMark1 = ((Maxnum / 4) - (Maxnum / 4) % 100));
         
    }
    else {
        (Maxnum / 4) % 10 > 5 ? (TableMark1 = ((Maxnum / 4) - (Maxnum / 4) % 10) + 10) : (TableMark1 = ((Maxnum / 4) - (Maxnum / 4) % 10));

    }
    TableMark2 = TableMark1 * 2;
    TableMark3 = TableMark1 * 3;
    TableMark4 = TableMark1 * 4;
     PerY = (endTableY - beginTableY) / 5 / TableMark1;
    PerX = (endTableX - beginTableX) / (ShowNum + 1);
    //printf("%lf %lf \n", endTableX, endTableY);
    
    
    tmp = head->next;
    
  
    int tmpX = 0;
    //TableData   ��һ����ѡ�������   �ڶ����Ǹ�������   ��������x y
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
   // printf("px py�ֱ�Ϊ%.3lf %.3lf\n", PerX, PerY);

    while (tmp != NULL) {
        if (tmp->IsSelect) {
            tmpX++;
            for (int i = 1; i <= ChooseDataNum; i++) {
                if (IsChooseData[i]) {
                    
                    tmp->XPosition[i] = tmpX * PerX + beginTableX;                 //�����TableData�ͽṹ�����X��Yposition��ͬ����ֵ
                    TableData[i][++ClassDataNum[i]][0] = tmpX * PerX + beginTableX;
                

                    tmp->YPosition[i] = beginTableY + tmp->Data[i] * PerY;
                    TableData[i][ClassDataNum[i]][1] = beginTableY + tmp->Data[i] * PerY;   //��y��ֵ
                 //   printf("%d\n", tmp->Data[i]);
                    //if(i==2)
                  //  printf("���ǵ�%d��Ԫ�� ��%d������ ��xy�ֱ�Ϊ%.3lf %.3lf\n", tmpX, i, tmp->XPosition[i], tmp->YPosition[i]);
                }
            }
         
        }
        tmp = tmp->next;
    }
   

}