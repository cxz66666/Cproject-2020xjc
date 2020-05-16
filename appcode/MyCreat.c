#pragma once

#include "MyData.h"

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, int* Data);

void DrawCreateNewFile();
stu_Ptr CreatNewPtr(int* Data);
BOOL CheckColumnName( int ColumnNum,string ErrorAns);

static char ColumnData[11][20];
void DrawCreateNewFile() {

    static char InputMonth[20] = "", InputDay[20] = "";
    static char DateLength[20] = "";
    static char ColumnNum[20] = "";
    static int Data[10];   //1���·� 2������ 3�����ڳ��� 4������
    static char ErrorAns[20] = "";
    static int ShowColumn = 0;
    
    double BeginY = MaxY * 0.8;  //������ʼ��Yֵ
    /*����˼· ÿ�λ�ͼ��Y���ȥ�̶��ĸ߶� X��ʼ�վ���  ȷ������ͼ�����������*/
    if (!ShowColumn) {
        SetPenColor("TextBoxLabel");
        SetPenSize(3);
        SetPointSize(22); 
        SetPenColor("Black");
        drawLabel(MaxX / 2 - TextStringWidth("��ʼ����") / 2, BeginY -= FontHeight * 3, "��ʼ����");
    
        SetPenColor("Black");   
        setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
        drawLabel(MaxX * 0.485, BeginY -= FontHeight * 2.5, "��");
        drawLabel(MaxX * 0.535, BeginY, "��");
        textbox(GenUIID(0), MaxX * 0.46, BeginY -= 1.5 * FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);
        textbox(GenUIID(0), MaxX * 0.51, BeginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

        SetPenColor("Black");
        drawLabel(MaxX * 0.5 - TextStringWidth("���ڳ���") / 2, BeginY -= FontHeight * 2.5, "���ڳ���");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 2.5, MaxX * 0.04, FontHeight * 1.3, DateLength, 4);

        SetPenColor("Black");
        drawLabel(MaxX * 0.5 - TextStringWidth("�еĸ���") / 2, BeginY -= FontHeight *2.5, "�еĸ���");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 2.5, MaxX * 0.04, FontHeight * 1.4, ColumnNum, 3);

        setButtonColors("DirSelectionFrame", "PreWordColor", "DirSelectionFrameHot", "Black", 1);
        if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 4, MaxX * 0.05, FontHeight * 1.4, "ȷ��")) {

            if (CheckCreateNewFile(InputMonth, InputDay, DateLength, ColumnNum, ErrorAns, Data)) {//���м򵥵ļ���Լ��  ���û����ͽ���������ģʽ
                
                ShowColumn = 1;  //չʾ����ÿһ�е������
            }
            
        }
        if (!strlen(ErrorAns)) {
        
            SetPenColor("Red"); 
            SetPenSize(3);
            drawLabel((MaxX - TextStringWidth(ErrorAns)) / 2, BeginY -= FontHeight * 3, ErrorAns);  //���������ʾ
        
        }
    }
   else {
        
        BeginY = MaxY * 0.8; //��ߴ���Ϊ��ʼ
        setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
        int i;
        drawLabel((MaxX - TextStringWidth("����������")) / 2, BeginY - FontHeight, "����������");  
        for (i = 1; i <= 4; i++) {
            printf("data %d is %d\n", i, Data[i]);
        }
        for (i = 1; i <= Data[4]; i++) {
            textbox(GenUIID(i), MaxX * 0.47, BeginY -= 3 * FontHeight, MaxX * 0.06, 1.5 * FontHeight, ColumnData[i], 10);
        }
        if (button(GenUIID(0), MaxX * 0.47, BeginY -= 3 * FontHeight, MaxX * 0.06, 1.5 * FontHeight, "ȷ��")) {
            if (CheckColumnName(Data[5],ErrorAns)) {
                
                stu_Ptr NewHead = CreatNewPtr(Data);   //�õ��µ�ͷ�ڵ�
                NowShowTable = NewHead; //��Ŀǰչʾ�ı�Ϊ�µı�
                Calculate(NowShowTable);   //���¼���÷��õ�λ��
                IsNew = 0;
                IsOpen = 2;
                ShowColumn = 0; //����չʾ�����
            }
           
        }
        if (!strlen(ErrorAns)) {
            SetPenColor("Red");
            drawLabel(MaxX * 0.5 - TextStringWidth(ErrorAns) / 2, BeginY -= 2 * FontHeight, ErrorAns);
        }
    }
    if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 2, MaxX * 0.05, FontHeight * 1.4, "ȡ��")) {

        IsNew = 0;
    }

}

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, int *Data) {
 
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(ColumnNum)) //���û���붫��
    {
        strcpy(ErrorAns, "��������������");
        return FALSE;
    }
    int MonthNum = atoi(InputMonth), DayNum = atoi(InputDay), DateNum = atoi(DateLength), Column = atoi(ColumnNum);


    if (!MonthNum || MonthNum > 12) {
        strcpy(ErrorAns, "���������·�");
        return FALSE;
    }

    if (!DayNum || DayNum > MonthDate[MonthNum]) {
        strcpy(ErrorAns, "������������");
        return FALSE;
    }
    if (!DateNum) {
        strcpy(ErrorAns, "�����������ڳ���");
        return FALSE;
    }
    if (DateNum > 30) {
        strcpy(ErrorAns, "���Ȳ��ܳ���30");
        return FALSE;
    }
    if (!Column) {
        strcpy(ErrorAns, "�������������");
        return FALSE;
    }
    if (Column > 10) {
        strcpy(ErrorAns, "�������ܳ���10");
        return FALSE;
    }

    Data[1] = MonthNum, Data[2] = DayNum, Data[3] = DateNum, Data[4] = Column;
    return TRUE;
}

stu_Ptr CreatNewPtr(int* Data) {
   
    int i;

    InitData();  //���ݳ�ʼ��
    
    for (i = 1; i <= Data[4]; i++) {
      
        TmpColumnName[i] = (char*)malloc(sizeof(sizeof(ColumnData[i]) +10 ));
        strcpy(TmpColumnName[i], ColumnData[i]);   //���临�ƽ�ȥ
        ColumnName[i] = TmpColumnName[i];
    }
    TotalColumnNum = Data[4];
    FileTotalNum = Data[3];


    stu_Ptr ans, tmp,tmp1;    //tmp�������� tmp1�����½� 
    ans = (stu_Ptr)malloc(sizeof(struct stu));
    tmp = ans;
    
    for (i = 1; i <= Data[3]; i++) {
        tmp1 = (stu_Ptr)malloc(sizeof(struct stu));
        tmp1->IsSelect = TRUE;
        tmp1->Date = GetDate(Data[1], Data[2] + i - 1);  //����malloc��������λ��
        memset(tmp1->Data, 0, sizeof(tmp1->Data));
        tmp->IsShowNum = FALSE;  //��չʾչʾ����
        /*�����Ĳ��ö���ΪCalculate�����¸�ֵ*/
        tmp->next = tmp1; 
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return ans;
}
BOOL CheckColumnName( int ColumnNum,string ErrorAns) {

    int i,j;
    for (i = 1; i <= ColumnNum; i++) {
        if (!strlen(ColumnData[i])) {
            strcpy(ErrorAns, "������ȱʧ");
            return FALSE;
            }

        for (j = 0; ColumnData[i][j]; j++) {
            if (ColumnData[i][j] >0) {
                strcpy(ErrorAns, "����������");
                return FALSE;
            }
        }
    }
    strcpy(ErrorAns, "�ɹ�");
    return TRUE;
}
