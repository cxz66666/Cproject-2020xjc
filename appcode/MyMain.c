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
// �����й�����  MaxX��MaxY


// ��ʾ����
void display();

// ����¼��ص�����
void MouseEventProcess(int x, int y, int button, int event);
void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void TimeEventProcess(int timerID);



void DrawMain();


// ��ڣ�ֻ����һ��
void DrawPicture(stu_Ptr Head);

void Main()
{
    // ��ʼ��ͼ�δ���
    SetWindowSize(24, 13.5);
    InitGraphics();
   InitConsole();
    PreWork(); //��һ�Ѷ�����¸���
    // ע��ص�����
    // printf("%lf %lf", GetWindowWidth(), GetWindowHeight());
    registerMouseEvent(MouseEventProcess); //���
    registerKeyboardEvent(KeyboardEventProcess);
    registerTimerEvent(TimeEventProcess);
    registerCharEvent(CharEventProcess);
}

// ��ʾ����
void display()
{
    
    DisplayClear();
    DrawMenu();
    // ��ɫѡ��ť
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
   
    DrawLeftButton(Head);   //���������ͼ��
    drawMainPicture();
}


// ����¼��ص�����
void MouseEventProcess(int x, int y, int button, int event)
{
    // UI ��ȡ����¼�
  
    uiGetMouse(x, y, button, event);
    if (HandleMouse(x, y, button, event) && IsOpen == 2)
        Calculate(); //����ƶ���  ���¼���
    
   
    display();
}



void TimeEventProcess(int timerID)
{
    display();
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