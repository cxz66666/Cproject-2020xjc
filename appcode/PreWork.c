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
    FindCSV(); //找到当前目录下的csv文件并放到FileName中
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
        if (data.attrib == _A_SUBDIR) // 如果是目录
            ;
        else
        {

            FileName[FileNum] = (char *)malloc(sizeof(data.name) + 1);
            strcpy(FileName[FileNum++], data.name);
        }

        nRet = _findnext(handle, &data);
    }
    _findclose(handle); // 关闭当前句柄
}
void DefineMycolor()
{

    DefineColor("MenuFrame", 232.0 / 255, 237.0 / 255, 239.0 / 255); //菜单框
    DefineColor("MenuFrameHot", 236.0 / 255, 232.0 / 255, 223.0 / 255);

    DefineColor("MenuBar", 227.0 / 255, 235.0 / 255, 255.0 / 255); //bar框
    DefineColor("TextBoxFrame", 155.0 / 255, 156.0 / 255, 155.0 / 255);

    DefineColor("TextBoxFrameHot", 124.0 / 255, 205.0 / 255, 244.0 / 255);
    DefineColor("TextBoxLabel", 11.0 / 255, 19.0 / 255, 43.0 / 255); //输入框

    DefineColor("DirSelectionFrameHot", 91.0 / 255, 192.0 / 255, 235.0 / 255); //文件选择框
    DefineColor("DirSelectionFrame", 112.0 / 255, 214.0 / 255, 1.0);

    DefineColor("DataButton", 218.0 / 255, 215.0 / 255, 205.0 / 255); //日期选择框的颜色
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
    //TableData   第一层是选择的种类   第二层是各个日期   第三层是x y
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
   // printf("px py分别为%.3lf %.3lf\n", PerX, PerY);

    while (tmp != NULL) {
        if (tmp->IsSelect) {
            tmpX++;
            for (int i = 1; i <= ChooseDataNum; i++) {
                if (IsChooseData[i]) {
                    
                    tmp->XPosition[i] = tmpX * PerX + beginTableX;                 //对这个TableData和结构体里的X，Yposition赋同样的值
                    TableData[i][++ClassDataNum[i]][0] = tmpX * PerX + beginTableX;
                

                    tmp->YPosition[i] = beginTableY + tmp->Data[i] * PerY;
                    TableData[i][ClassDataNum[i]][1] = beginTableY + tmp->Data[i] * PerY;   //对y赋值
                 //   printf("%d\n", tmp->Data[i]);
                    //if(i==2)
                  //  printf("这是第%d个元素 第%d种数据 其xy分别为%.3lf %.3lf\n", tmpX, i, tmp->XPosition[i], tmp->YPosition[i]);
                }
            }
         
        }
        tmp = tmp->next;
    }
   

}