#pragma once

#include "conio.h"
#include "extgraph.h"
#include "genlib.h"
#include "graphics.h"
#include "imgui.h"
#include "simpio.h"
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

// 窗口有关坐标  MaxX和MaxY


// 显示界面
void display();

// 鼠标事件回调函数
void MouseEventProcess(int x, int y, int button, int event);
void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void TimeEventProcess(int timerID);



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
    registerMouseEvent(MouseEventProcess); //鼠标
    registerKeyboardEvent(KeyboardEventProcess);
    registerTimerEvent(TimeEventProcess);
    registerCharEvent(CharEventProcess);
}

// 显示界面
void display()
{
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
        DrawPicture(head);
    }
}




void DrawPicture(stu_Ptr Head)
{
   
    DrawLeftButton(Head);   //里面包含画图像
    drawMainPicture();
}


// 鼠标事件回调函数
void MouseEventProcess(int x, int y, int button, int event)
{
    // UI 获取鼠标事件
    uiGetMouse(x, y, button, event);
    
   
    display();
}



void TimeEventProcess(int timerID)
{
    display();
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