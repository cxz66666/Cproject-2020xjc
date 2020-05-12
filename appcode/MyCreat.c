#pragma once

#include "MyData.h"

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, string Data);

void DrawCreateNewFile();
BOOL CreatNewPtr(int* Data);

void DrawCreateNewFile() {

    static char InputMonth[20] = "", InputDay[20] = "";
    static char DateLength[20] = "";
    static char ColumnNum[20] = "";
    static int Data[5];   //1���·� 2������ 3�����ڳ��� 4������
    static char ErrorAns[20] = "";
    static int ShowColumn = 0;
    double BeginY = MaxY * 0.8;  //������ʼ��Yֵ
    if (!ShowColumn) {
        SetPenColor("TextBoxLabel");
        SetPenSize(3);

     
        drawLabel(MaxX / 2 - TextStringWidth("��ʼ����") / 2, BeginY, "��ʼ����");

        setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
        drawLabel(MaxX * 0.46, BeginY -= FontHeight * 3, "��");
        drawLabel(MaxX * 0.51, BeginY, "��");
        textbox(GenUIID(0), MaxX * 0.475, BeginY -= 1.5 * FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);
        textbox(GenUIID(0), MaxX * 0.525, BeginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

        SetPenColor("Red");
        drawLabel(MaxX * 0.5 - TextStringWidth("���ڳ���") / 2, BeginY -= FontHeight * 2, "���ڳ���");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, DateLength, 4);

        SetPenColor("Green");
        drawLabel(MaxX * 0.5 - TextStringWidth("�еĸ���") / 2, BeginY -= FontHeight * 2, "�еĸ���");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.4, ColumnNum, 3);

        setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 1);
        if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 1.4, "ȷ��")) {

            if (CheckCreateNewFile(InputMonth, InputDay, DateLength, ColumnNum, ErrorAns, Data)) {
                ShowColumn = 1;  //չʾ����ÿһ�е������
            }
            else
            {
                SetPenColor("Red");
                SetPenSize(3);
                drawLabel((MaxX - TextStringWidth(ErrorAns)) / 2, BeginY -= FontHeight * 3, ErrorAns);
            }
        }
    }
    else {
        ;
    }
    if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 1.4, "ȡ��")) {

        IsNew = 0;
    }

}

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, string Data) {
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(ColumnNum))
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

BOOL CreatNewPtr(int* Data) {

}