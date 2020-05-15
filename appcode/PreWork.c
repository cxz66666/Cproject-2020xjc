#pragma once

#include"MyData.h"
#include <direct.h>
#define  SHOWTIMEPRE 0 //�������ʱ��
#define  DISPLAY   1  //ÿ��400ms��������display  ��Ϊ������Щ�����߰��갴ť�󲻽�������ƶ��޷�����
#define  REFRESHTIME  400

void PreWork();
void FindCSV();
void DefineMycolor();
BOOL CheckName(char* name);
void Calculate(stu_Ptr HEAD);
void AssignTable();
BOOL CheckChangedNum(string str[],string ans);
void InitData();
void  FreeColumn(char *Ptr[]);
void PreWork()
{
    /*������ೣ��  ��ֹ�Ժ��ٻ�ȡ�˷���Դ*/
    FontHeight = GetFontHeight();
    FontAscent = GetFontAscent();
    FontDescent = GetFontDescent();
  	//printf("%lf %lf %lf \n", FontHeight, FontAscent, FontDescent);
    
    /*����direct.h���currentDirectory�ӿڻ�ȡ��ǰĿ¼ ���ŵ�FilePath��*/
    GetCurrentDirectory(100, FilePath); 
    //printf("%s\n", FilePath);
    FindCSV(); //�ҵ���ǰĿ¼�µ�csv�ļ����ŵ�FileName��
    MaxX = GetWindowWidth();
    MaxY = GetWindowHeight();
  
    DefineMycolor(); //����Ҫ����ɫȫ��ע��

    /*һ�¾�̬�����Ժ󲻻�䶯*/
   	StaticbeginTableX= beginTableX = GetWindowWidth() * 0.2,
    StaticbeginTableY= beginTableY = GetWindowHeight() * 0.2;
  	StaticendTableX=endTableX = GetWindowWidth() * 0.8, 
      StaticendTableY= endTableY = GetWindowHeight() * 0.9;
    /*for (int i = 0; i < FileNum; i++)
        printf("%s\n", FileName[i]);*/
   memset(ChangingPtrStringNum, 0, sizeof(ChangingPtrStringNum));
   
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
    DefineColor("ChoosedColor", 254.0 / 255, 95.0 / 255, 85.0 / 255); //ѡ�к����ɫ

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
    	int i;
        for (i = 0; i < FileNum; i++)
        {
            if (!strcmp(name, FileName[i]))
                return 1;
        }
    }
    return 0;
}
void AssignTable() {   //����������״ͼ��������ͼ
   //һ�������б�ѡ����
   int i;
    for (i=1; i <= ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            IsChooseColumn[column] = 1;   //������1����2 ������Ϊ1
    }

    if (ChooseColumnNum && ChooseColumnNum <4)      //2������״ͼ  1��������ͼ  ԭ��Ĭ����1  ����ֻҪ�ĳ�2 ����
    {
        int change1 = ChoosedColumn[1];    //�ѵ�һ��ѡ�е���Ϊ2
        IsChooseColumn[change1] = 2;
      
        DrawWithColumn = 1;
        DrawWithLine = TotalColumnNum - 1;
    }
    else if (ChooseColumnNum >= 4)
    {
        int change1 = ChoosedColumn[1],change2 = ChoosedColumn[2];
        IsChooseColumn[change1] = 2, IsChooseColumn[change2] = 2;
        DrawWithColumn = 2;
        DrawWithLine = TotalColumnNum - 2;

    }
        
        
}
/*��Ҫ�����������û�е���߲�������*/
BOOL CheckChangedNum(string str[], string ans) {
    int i,j;
    for (i = 1; i <= TotalColumnNum; i++) {
        for (j = 0; str[i][j]; j++) {     //����е����ASCII�벻�����ֵ�
            if (str[i][j] == '.'||(str[i][j]<48||str[i][j]>58)) {
                strcpy(ans, "��������");
                return FALSE;
            }
        }
        /*ע��atoi����0���ʾ������   ������ֵ��ʾû����*/
        if (!atoi(str[i]))   //�������0���������⣡����
        {
            strcpy(ans, "��������");
            return FALSE;
        }
    }
    //��״̬��Ϊ���³ɹ�
    strcpy(ans, "���³ɹ�");

    for (i = 1; i <= TotalColumnNum; i++) {
    
        ChangingPtr->Data[i] = atoi(str[i]);    //�ı�Ptr��ĸ�������
    }
   
    return TRUE;
}

void Calculate(stu_Ptr HEAD)
{
#if  SHOWTIMEPRE
    clock_t start_time, end_time;
    start_time = clock();   //��ȡ��ʼִ��ʱ��
#endif //  SHOWTIME

    if (HEAD == NULL) {
        printf("�ڴ�����޷�����\n");
        return;
    }

    memset(CubicEquation, 0, sizeof(CubicEquation));   //ÿ�μ�����ķ��̶���һ��  �����������˵
    int ShowNum = 0;
    int Maxnum = 0;
    stu_Ptr tmp = HEAD->next;   //���еĶ���ͷ�ڵ��  ע����
    while (tmp != NULL)  
    {
     
        if (tmp->IsSelect)
        {
            tail = tmp;   //tail��ʾ�������һ����ѡ�е�����
            ShowNum++;
            int i; 
            for (i=1; i <= ChooseColumnNum; i++)
            {
                int column = ChoosedColumn[i];
                
                    Maxnum = max(Maxnum, tmp->Data[column]);
                
            }
        }

        tmp = tmp->next;
    }
    ShowDateNum = ShowNum;   //��ʾ��������Ŀ
    //printf("Maxnum=%d   ShowNum=%d\n", Maxnum,ShowNum);
    if (Maxnum > 1000) {

        (Maxnum / 6) % 100 > 50 ? (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 100) + 100) : (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 100));

    }
    else if (Maxnum > 100) {
        (Maxnum / 6) % 10 > 5 ? (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 10) + 10) : (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 10));

    }
    else TableMark1 = 10;
    TableMark2 = TableMark1 * 2;
    TableMark3 = TableMark1 * 3;
    TableMark4 = TableMark1 * 4;
    TableMark5 = TableMark1 * 5;
    TableMark6 = TableMark1 * 6;
     PerY = (endTableY - beginTableY) / 7 / TableMark1;
    PerX = (endTableX - beginTableX) / (ShowNum + 1.0);
    //printf("%lf %lf \n", endTableX, endTableY);
    
    
    tmp = HEAD->next;
    
  
    int tmpX = 0;
    //TableData   ��һ����ѡ�������   �ڶ����Ǹ�������   ��������x y
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
   // printf("px py�ֱ�Ϊ%.3lf %.3lf\n", PerX, PerY);

    while (tmp != NULL) {
        if (tmp->IsSelect) {
           
            tmpX++;
            int  i; 
            for (i=1; i <= ChooseColumnNum; i++) {
                 {
                    int column = ChoosedColumn[i];
                    
                    tmp->XPosition[column] = tmpX * PerX + beginTableX;                 //�����TableData�ͽṹ�����X��Yposition��ͬ����ֵ
                    TableData[column][++ClassDataNum[column]][0] = tmpX * PerX + beginTableX;
                

                    tmp->YPosition[column] = beginTableY + tmp->Data[column] * PerY;
                    TableData[column][ClassDataNum[column]][1] = beginTableY + tmp->Data[column] * PerY;   //��y��ֵ
                 //   printf("%d\n", tmp->Data[column]);
                  
                  //  printf("���ǵ�%d��Ԫ�� ��%d������ ��xy�ֱ�Ϊ%.3lf %.3lf\n", tmpX, i, tmp->XPosition[column], tmp->YPosition[column]);
                }
            }
         
        }
        tmp = tmp->next;
    }
    AssignTable();//������ͼ����Ϊ1   ��״ͼ��Ϊ2     ��״ͼ��Ŀ���������� ����ƽ������
    ColumnWidth = min(0.2, 0.25 * PerX);
    
#if  SHOWTIMEPRE
    end_time = clock();     //��ȡ����ʱ��
    double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("������ʱΪ%lf seconds\n", Times);

#endif //  SHOWTIME

}
void InitData() {
    
    memset(IsChooseColumn, 0, sizeof(IsChooseColumn));
    memset(ChoosedColumn, 0, sizeof(ChoosedColumn));
    ChooseColumnNum = 0;
    TotalColumnNum = 0;
    NowDateColumn = 0;
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
    ChooseLineMoveX = ChooseLineMoveY = 0;
    ChooseLineNum = ChooseHistogramNum = 0;
    memset(ChangingPtrStringNum, 0, sizeof(ChangingPtrStringNum));
    ChangingPtr = NULL;
    IsPredict = IsChangeNum = IsSave=FALSE;
    IsRedisplay = 0;
    IsChooseXaxis = FALSE, IsChooseYaxis = FALSE, IsChooseLine = FALSE, IsChooseHistogram = FALSE;
    DrawWithLine = DrawWithColumn = DrawWithColumnNow = 0;
    FileTotalNum = 0;
    NowDateNum = NowDateColumn = 0;
}

void  FreeColumn(char* Ptr[]) {
    for (int i = 1; i <= TotalColumnNum; i++) {
        if (Ptr[i] != NULL)
            if(Ptr[i][0] != 0)
            free(Ptr[i]);
    }
}