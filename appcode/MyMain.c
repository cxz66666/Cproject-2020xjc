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

// ��ʾ����


// ����¼��ص�����
void MouseEventProcess(int x, int y, int button, int event);
// �ַ��¼��ص�����
void CharEventProcess(char ch);
// �����¼��ص�����
void KeyboardEventProcess(int key, int event);






// ��ڣ�ֻ����һ��


void Main()
{
    // ��ʼ��ͼ�δ���
    SetWindowSize(24, 13.5);
    InitGraphics();
   	InitConsole();
    PreWork(); //��һ�Ѷ�����¸���
    // ע��ص�����
    // printf("%lf %lf", GetWindowWidth(), GetWindowHeight());
    registerMouseEvent(MouseEventProcess); 
    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
}









void DrawPicture(stu_Ptr Head)
{
   
    DrawLeftButton(Head);   //����һ�Ѱ�ť
   
    drawMainPicture();   //����ͼ 
    DrawPredict();     //��Ԥ��������
}


// ����¼��ص�����
void MouseEventProcess(int x, int y, int button, int event)
{
    // UI ��ȡ����¼�
  
    uiGetMouse(x, y, button, event);
    //clock_t start_time, end_time;
    //start_time = clock();
    //static num = 0;
   
    if (HandleMouse(x, y, button, event) && IsOpen == 2) {
      // num++;
        Calculate(NowShowTable); //����ƶ���  ���¼���
       // UpdateDisplay();
    }
       
    display();
   // end_time = clock();
    //double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  //  printf("numΪ%d\n", num);
}





void CharEventProcess(char ch)
{
    uiGetChar(ch); // GUI�ַ�����
    display();
}
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI��ȡ����
    display();
}
