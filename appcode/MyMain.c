#pragma once

#include "conio.h"
#include "extgraph.h"
#include "genlib.h"
#include "graphics.h"
#include "imgui.h"
#include "simpio.h"
#include "time.h"
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <math.h>
#include <mmsystem.h>
#include <ocidl.h>
#include <ole2.h>
#include <olectl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wingdi.h>
#include <winuser.h>
#include "PreWork.c"
#include "MyDraw.c"
#include "HandleMouse.c"

// 显示界面
void display();

// 鼠标事件回调函数
void MouseEventProcess(int x, int y, int button, int event);
// 字符事件回调函数
void CharEventProcess(char ch);
// 键盘事件回调函数
void KeyboardEventProcess(int key, int event);




void DrawMain();


// 入口，只调用一次
void DrawPicture(stu_Ptr Head);

void Main()
{
    // 初始化图形窗口
    SetWindowSize(24, 13.5);
    InitGraphics();
   	InitConsole();
    PreWork(); //把一堆定义的事干完
    // 注册回调函数
    // printf("%lf %lf", GetWindowWidth(), GetWindowHeight());
    registerMouseEvent(MouseEventProcess); 
    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
}

// 显示界面
void display()
{
    if(!IsSave)   //如果不在保存界面上  就update  因为保存界面可能输入中文  使用update无法输入中文
    UpdateDisplay();
    DisplayClear();

    DrawMenu();
    // 黑色选择按钮
    DrawMain();

}



void DrawMain()
{
    // printf("%d", IsOpen);
    if (IsOpen == 1)
    {
        DrawOpenDir();
    }
    else if (IsOpen == 2)
    {
        if (IsSave == 1)
        {
            SaveToCsv(NowShowTable);
        }
        if(!IsPredict)
        DrawPicture(head);  //如果不是预测模式就画文件里的图
        else {
            DrawPicture(PreHead);  //如果是预测就画预测的 图
        }
    }
}




void DrawPicture(stu_Ptr Head)
{
   
    DrawLeftButton(Head);   //左侧的一堆按钮
   
    drawMainPicture();   //画主图 
    DrawPredict();     //画预测的输入框
}


// 鼠标事件回调函数
void MouseEventProcess(int x, int y, int button, int event)
{
    // UI 获取鼠标事件
  
    uiGetMouse(x, y, button, event);
    //clock_t start_time, end_time;
    //start_time = clock();
    //static num = 0;
   
    if (HandleMouse(x, y, button, event) && IsOpen == 2) {
      // num++;
        Calculate(NowShowTable); //如果移动了  重新计算
       // UpdateDisplay();
    }
       
    display();
   // end_time = clock();
    //double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  //  printf("num为%d\n", num);
}





void CharEventProcess(char ch)
{
    uiGetChar(ch); // GUI字符输入
    display();
}
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI获取键盘
    display();
}
