#pragma once

#include"MyData.h"


void PreWork();
void FindCSV();
void DefineMycolor();
BOOL CheckName(char* name);
void Calculate();
void AssignTable();

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
    endTableX = GetWindowWidth() * 0.8, endTableY = GetWindowHeight() * 0.9;
    /*for (int i = 0; i < FileNum; i++)
        printf("%s\n", FileName[i]);*/
    

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

    DefineColor("TableColor1", 239.0/255, 106.0/255, 46.0/255);
    DefineColor("TableColor2", 64.0/255, 199.0/255, 120.0/255);
    DefineColor("TableColor3", 37.0/255, 74.0/255, 178.0/255);
    DefineColor("TableColor4", 255.0/255, 33.0/255, 127.0/255);
    DefineColor("TableColor5", 204.0/255, 0, 213.0/255);
    DefineColor("TableColor6", 102.0/255, 44.0/255, 145.0/255);
    DefineColor("TableColor7", 23.0/255, 163.0/255, 152.0/255);
    DefineColor("TableColor8", 255.0 / 255, 198.0 / 255, 255.0 / 255);
    DefineColor("TableColor9", 51.0/255, 49.0/255, 46.0/255);
    DefineColor("TableColor10", 253.0/255, 255.0/255, 182.0/255);
    DefineColor("TableColor11", 202.0/255, 255.0/255, 191.0/255);
    DefineColor("TableColor12", 155.0/255, 246.0/255, 255.0/255);

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
void AssignTable() {   //分配是用柱状图还是折线图
    ChooseColumnNum = 0;    //一共多少列被选中了
    for (int i = 1; i <= TotalColumnNum; i++) {
        if (IsChooseColumn[i])
            IsChooseColumn[i] = 1, ChooseColumnNum++;   //无论是1还是2 都先设为1
    }

    if (ChooseColumnNum && ChooseColumnNum <4)      //是二代表柱状图  一代表折线图  原来默认是1  那我只要改成2 就行
    {
        for (int i = 1; i <= TotalColumnNum; i++) {
            if (IsChooseColumn[i] == 1)
            {
                IsChooseColumn[i] = 2;
                break;
            }
        }
       
        DrawWithColumn = 1;
        DrawWithLine = TotalColumnNum - 1;
    }
    else if (ChooseColumnNum >= 4)
    {
        int i;
        for (i = 1; i <= TotalColumnNum; i++) {
            if (IsChooseColumn[i] == 1)
            {
                IsChooseColumn[i] = 2;
                break;
            }
        }
        for (i; i <= TotalColumnNum; i++) {
            if (IsChooseColumn[i] == 1)
            {
                IsChooseColumn[i] = 2;
                break;
            }
        }

        DrawWithColumn = 2;
        DrawWithLine = TotalColumnNum - 2;

    }
        
        
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
            tail = tmp;   //tail表示的是最后一个被选中的日期
            ShowNum++;
            for (int i = 1; i <= TotalColumnNum; i++)
            {
                if (IsChooseColumn[i])
                {
                    Maxnum = max(Maxnum, tmp->Data[i]);
                }
            }
        }

        tmp = tmp->next;
    }
    ShowDateNum = ShowNum;   //显示的日期数目
    //printf("Maxnum=%d   ShowNum=%d\n", Maxnum,ShowNum);
    if (Maxnum > 1000) {
 
        (Maxnum / 6) % 100 > 50 ? (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 100) + 100 ):( TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 100));
         
    }
    else {
        (Maxnum / 6) % 10 > 5 ? (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 10) + 10) : (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 10));

    }
    TableMark2 = TableMark1 * 2;
    TableMark3 = TableMark1 * 3;
    TableMark4 = TableMark1 * 4;
    TableMark5 = TableMark1 * 5;
    TableMark6 = TableMark1 * 6;
     PerY = (endTableY - beginTableY) / 7 / TableMark1;
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
            for (int i = 1; i <= TotalColumnNum; i++) {
                if (IsChooseColumn[i]) {
                    
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
    AssignTable();//把折线图的设为1   柱状图设为2     柱状图数目不超过两个 尽量平均分配
    ColumnWidth = min(0.2, 0.25 * PerX);
}