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
    static int Data[10];   //1放月份 2放日子 3放日期长度 4放列数
    static char ErrorAns[20] = "";
    static int ShowColumn = 0;
    
    double BeginY = MaxY * 0.8;  //定死开始的Y值
    /*总体思路 每次画图是Y轴减去固定的高度 X轴始终剧中  确保画的图是让人舒服的*/
    if (!ShowColumn) {
        SetPenColor("TextBoxLabel");
        SetPenSize(3);
        SetPointSize(22); 
        SetPenColor("Black");
        drawLabel(MaxX / 2 - TextStringWidth("起始日期") / 2, BeginY -= FontHeight * 3, "起始日期");
    
        SetPenColor("Black");   
        setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
        drawLabel(MaxX * 0.485, BeginY -= FontHeight * 2.5, "月");
        drawLabel(MaxX * 0.535, BeginY, "日");
        textbox(GenUIID(0), MaxX * 0.46, BeginY -= 1.5 * FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);
        textbox(GenUIID(0), MaxX * 0.51, BeginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

        SetPenColor("Black");
        drawLabel(MaxX * 0.5 - TextStringWidth("日期长度") / 2, BeginY -= FontHeight * 2.5, "日期长度");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 2.5, MaxX * 0.04, FontHeight * 1.3, DateLength, 4);

        SetPenColor("Black");
        drawLabel(MaxX * 0.5 - TextStringWidth("列的个数") / 2, BeginY -= FontHeight *2.5, "列的个数");
        textbox(GenUIID(0), MaxX * 0.48, BeginY -= FontHeight * 2.5, MaxX * 0.04, FontHeight * 1.4, ColumnNum, 3);

        setButtonColors("DirSelectionFrame", "PreWordColor", "DirSelectionFrameHot", "Black", 1);
        if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 4, MaxX * 0.05, FontHeight * 1.4, "确定")) {

            if (CheckCreateNewFile(InputMonth, InputDay, DateLength, ColumnNum, ErrorAns, Data)) {//进行简单的检查和约束  如果没问题就进入输入列模式
                
                ShowColumn = 1;  //展示输入每一列的输入框
            }
            
        }
        if (!strlen(ErrorAns)) {
        
            SetPenColor("Red"); 
            SetPenSize(3);
            drawLabel((MaxX - TextStringWidth(ErrorAns)) / 2, BeginY -= FontHeight * 3, ErrorAns);  //输入错误提示
        
        }
    }
   else {
        
        BeginY = MaxY * 0.8; //最高处置为初始
        setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
        int i;
        drawLabel((MaxX - TextStringWidth("请输入列名")) / 2, BeginY - FontHeight, "请输入列名");  
        for (i = 1; i <= 4; i++) {
            printf("data %d is %d\n", i, Data[i]);
        }
        for (i = 1; i <= Data[4]; i++) {
            textbox(GenUIID(i), MaxX * 0.47, BeginY -= 3 * FontHeight, MaxX * 0.06, 1.5 * FontHeight, ColumnData[i], 10);
        }
        if (button(GenUIID(0), MaxX * 0.47, BeginY -= 3 * FontHeight, MaxX * 0.06, 1.5 * FontHeight, "确认")) {
            if (CheckColumnName(Data[5],ErrorAns)) {
                
                stu_Ptr NewHead = CreatNewPtr(Data);   //拿到新的头节点
                NowShowTable = NewHead; //将目前展示的变为新的表
                Calculate(NowShowTable);   //重新计算该放置的位置
                IsNew = 0;
                IsOpen = 2;
                ShowColumn = 0; //重新展示输入框
            }
           
        }
        if (!strlen(ErrorAns)) {
            SetPenColor("Red");
            drawLabel(MaxX * 0.5 - TextStringWidth(ErrorAns) / 2, BeginY -= 2 * FontHeight, ErrorAns);
        }
    }
    if (button(GenUIID(0), MaxX * 0.475, BeginY -= FontHeight * 2, MaxX * 0.05, FontHeight * 1.4, "取消")) {

        IsNew = 0;
    }

}

BOOL CheckCreateNewFile(string InputMonth, string InputDay, string  DateLength, string  ColumnNum, string  ErrorAns, int *Data) {
 
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(ColumnNum)) //如果没输入东西
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

stu_Ptr CreatNewPtr(int* Data) {
   
    int i;

    InitData();  //数据初始化
    
    for (i = 1; i <= Data[4]; i++) {
      
        TmpColumnName[i] = (char*)malloc(sizeof(sizeof(ColumnData[i]) +10 ));
        strcpy(TmpColumnName[i], ColumnData[i]);   //将其复制进去
        ColumnName[i] = TmpColumnName[i];
    }
    TotalColumnNum = Data[4];
    FileTotalNum = Data[3];


    stu_Ptr ans, tmp,tmp1;    //tmp用来遍历 tmp1用来新建 
    ans = (stu_Ptr)malloc(sizeof(struct stu));
    tmp = ans;
    
    for (i = 1; i <= Data[3]; i++) {
        tmp1 = (stu_Ptr)malloc(sizeof(struct stu));
        tmp1->IsSelect = TRUE;
        tmp1->Date = GetDate(Data[1], Data[2] + i - 1);  //日期malloc出来储存位置
        memset(tmp1->Data, 0, sizeof(tmp1->Data));
        tmp->IsShowNum = FALSE;  //不展示展示数据
        /*其他的不用动因为Calculate会重新赋值*/
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
            strcpy(ErrorAns, "有数据缺失");
            return FALSE;
            }

        for (j = 0; ColumnData[i][j]; j++) {
            if (ColumnData[i][j] >0) {
                strcpy(ErrorAns, "请输入中文");
                return FALSE;
            }
        }
    }
    strcpy(ErrorAns, "成功");
    return TRUE;
}
