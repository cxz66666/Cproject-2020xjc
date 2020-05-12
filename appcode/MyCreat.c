#pragma once

#include "MyData.h"

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, string Data);

void DrawCreateNewFile();
BOOL CreatNewPtr(int* Data);

void DrawCreateNewFile() {

    static char InputMonth[20] = "", InputDay[20] = "";
    static char DateLength[20] = "";
    static char ColumnNum[20] = "";
    static int Data[5];   //1放月份 2放日子 3放日期长度 4放列数
    static char ErrorAns[20] = "";
    static int ShowColumn = 0;
    double BeginY = MaxY * 0.8;  //定死开始的Y值
    if (!ShowColumn) {
        SetPenColor("TextBoxLabel");
        SetPenSize(3);

     
        drawLabel(MaxX / 2 - TextStringWidth("起始日期") / 2, BeginY, "起始日期");

        setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
        drawLabel(MaxX * 0.46, BeginY -= FontHeight * 3, "月");
        drawLabel(MaxX * 0.51, BeginY, "日");
        textbox(GenUIID(0), MaxX * 0.475, BeginY -= 1.5 * FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);
        textbox(GenUIID(0), MaxX * 0.525, BeginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

        SetPenColor("Red");
        drawLabel(MaxX * 0.5 - TextStringWidth("日期长度") / 2, BeginY -= FontHeight * 2, "日期长度");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, DateLength, 4);

        SetPenColor("Green");
        drawLabel(MaxX * 0.5 - TextStringWidth("列的个数") / 2, BeginY -= FontHeight * 2, "列的个数");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.4, ColumnNum, 3);

        setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 1);
        if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 1.4, "确定")) {

            if (CheckCreateNewFile(InputMonth, InputDay, DateLength, ColumnNum, ErrorAns, Data)) {
                ShowColumn = 1;  //展示输入每一列的输入框
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
    if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 1.4, "取消")) {

        IsNew = 0;
    }

}

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, string Data) {
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(ColumnNum))
    {
        strcpy(ErrorAns, "请输入完整数据");
        return FALSE;
    }
    int MonthNum = atoi(InputMonth), DayNum = atoi(InputDay), DateNum = atoi(DateLength), Column = atoi(ColumnNum);


    if (!MonthNum || MonthNum > 12) {
        strcpy(ErrorAns, "请检查输入月份");
        return FALSE;
    }

    if (!DayNum || DayNum > MonthDate[MonthNum]) {
        strcpy(ErrorAns, "请检查输入日期");
        return FALSE;
    }
    if (!DateNum) {
        strcpy(ErrorAns, "请检查输入日期长度");
        return FALSE;
    }
    if (DateNum > 30) {
        strcpy(ErrorAns, "长度不能超过30");
        return FALSE;
    }
    if (!Column) {
        strcpy(ErrorAns, "请检查输入的列数");
        return FALSE;
    }
    if (Column > 10) {
        strcpy(ErrorAns, "列数不能超过10");
        return FALSE;
    }
    Data[1] = MonthNum, Data[2] = DayNum, Data[3] = DateNum, Data[4] = Column;
    return TRUE;
}

BOOL CreatNewPtr(int* Data) {

}