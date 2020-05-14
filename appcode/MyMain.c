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



// 鼠标事件回调函数
void MouseEventProcess(int x, int y, int button, int event);
// 字符事件回调函数
void CharEventProcess(char ch);
// 键盘事件回调函数
void KeyboardEventProcess(int key, int event);


void TimerEventProcess(int timerID);/*定时器消息回调函数*/




void Main()
{
    // 初始化图形窗口
    SetWindowSize(24, 13.5);
    InitGraphics();
  //	InitConsole();
    PreWork(); //把一堆定义的事干完
    // 注册回调函数
    // printf("%lf %lf", GetWindowWidth(), GetWindowHeight());
    registerMouseEvent(MouseEventProcess); 
    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
    registerTimerEvent(TimerEventProcess);
}




void TimerEventProcess(int timerID)/*定时器消息回调函数*/
{
    if (timerID == 1)
        display();
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
  
    if (HandleKeyBoard(ch) && IsOpen == 2) {
        Calculate(NowShowTable);
    }
    display();
   
}
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI获取键盘
    display();
}
