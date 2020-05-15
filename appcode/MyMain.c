
#pragma once
/*写在前面   
********！！！！！*********
整个程序由于时间仓促没来的急好好优化，个人感觉有很多坑，各位高手轻喷，谢谢


整个注释我认为并不能按照what来写，应该按照why来写，因此没必要摁着30%的注释率来康


如果注释没到30% 不是因为不知道要多写  是因为不想恶心别人  也不想恶心自己
*******！！！！！**********
*/



/*
头文件全部在main里include
同时对每个文件pragma once 
防止重复include报错
*/
#include "conio.h"
#include "extgraph.h"
#include "genlib.h"
#include "graphics.h"
#include "imgui.h"
#include "simpio.h"
#include "time.h"
#include <Windows.h>
#include <direct.h> //整个是用来找当前目录下的文件
#include <io.h>   //跟上个同理
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
/*以下三个是自己的
PreWork是对整个绘画前的准备工作以及零散的计算工作，包括极为重要的Calculate
MyDraw里放着所有的绘图函数
HandleMouse.c放着对鼠标/键盘的输入处理
*/
#include "PreWork.c"
#include "MyDraw.c"
#include "HandleMouse.c"



// 鼠标事件回调函数
void MouseEventProcess(int x, int y, int button, int event);
// 字符事件回调函数
void CharEventProcess(char ch);
// 键盘事件回调函数
void KeyboardEventProcess(int key, int event);

//其实这个Timer注册是为了用来及时显示的，但是在显示报错信息是很蠢很鸡肋
void TimerEventProcess(int timerID);/*定时器消息回调函数*/



void Main()
{
    // 初始化图形窗口
    SetWindowSize(24, 13.5); //经过不断的调整  这个比例很舒服 满足16：9的舒适屏幕
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
        Calculate(NowShowTable); //如果打开了文件并且移动了鼠标  重新计算
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
  
    if (HandleKeyBoard(ch) && IsOpen == 2) {   //如果打开了文件并且有键盘消息
        Calculate(NowShowTable);
    }
    display();
   
}
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI获取键盘
    display();
}
