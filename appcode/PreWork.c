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
    FindCSV(); //�ҵ���ǰĿ¼�µ�csv�ļ����ŵ�FileName��
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
void AssignTable() {   //����������״ͼ��������ͼ
    ChooseColumnNum = 0;    //һ�������б�ѡ����
    for (int i = 1; i <= TotalColumnNum; i++) {
        if (IsChooseColumn[i])
            IsChooseColumn[i] = 1, ChooseColumnNum++;   //������1����2 ������Ϊ1
    }

    if (ChooseColumnNum && ChooseColumnNum <4)      //�Ƕ�������״ͼ  һ��������ͼ  ԭ��Ĭ����1  ����ֻҪ�ĳ�2 ����
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
            tail = tmp;   //tail��ʾ�������һ����ѡ�е�����
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
    ShowDateNum = ShowNum;   //��ʾ��������Ŀ
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
    //TableData   ��һ����ѡ�������   �ڶ����Ǹ�������   ��������x y
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
   // printf("px py�ֱ�Ϊ%.3lf %.3lf\n", PerX, PerY);

    while (tmp != NULL) {
        if (tmp->IsSelect) {
           
            tmpX++;
            for (int i = 1; i <= TotalColumnNum; i++) {
                if (IsChooseColumn[i]) {
                    
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
    AssignTable();//������ͼ����Ϊ1   ��״ͼ��Ϊ2     ��״ͼ��Ŀ���������� ����ƽ������
    ColumnWidth = min(0.2, 0.25 * PerX);
}