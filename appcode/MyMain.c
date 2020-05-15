
#pragma once
/*д��ǰ��   
********����������*********
������������ʱ��ִ�û���ļ��ú��Ż������˸о��кܶ�ӣ���λ�������磬лл


����ע������Ϊ�����ܰ���what��д��Ӧ�ð���why��д�����û��Ҫ����30%��ע��������


���ע��û��30% ������Ϊ��֪��Ҫ��д  ����Ϊ������ı���  Ҳ��������Լ�
*******����������**********
*/



/*
ͷ�ļ�ȫ����main��include
ͬʱ��ÿ���ļ�pragma once 
��ֹ�ظ�include����
*/
#include "conio.h"
#include "extgraph.h"
#include "genlib.h"
#include "graphics.h"
#include "imgui.h"
#include "simpio.h"
#include "time.h"
#include <Windows.h>
#include <direct.h> //�����������ҵ�ǰĿ¼�µ��ļ�
#include <io.h>   //���ϸ�ͬ��
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
/*�����������Լ���
PreWork�Ƕ������滭ǰ��׼�������Լ���ɢ�ļ��㹤����������Ϊ��Ҫ��Calculate
MyDraw��������еĻ�ͼ����
HandleMouse.c���Ŷ����/���̵����봦��
*/
#include "PreWork.c"
#include "MyDraw.c"
#include "HandleMouse.c"



// ����¼��ص�����
void MouseEventProcess(int x, int y, int button, int event);
// �ַ��¼��ص�����
void CharEventProcess(char ch);
// �����¼��ص�����
void KeyboardEventProcess(int key, int event);

//��ʵ���Timerע����Ϊ��������ʱ��ʾ�ģ���������ʾ������Ϣ�Ǻܴ��ܼ���
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/



void Main()
{
    // ��ʼ��ͼ�δ���
    SetWindowSize(24, 13.5); //�������ϵĵ���  ������������ ����16��9��������Ļ
    InitGraphics();
  //	InitConsole();
    PreWork(); //��һ�Ѷ�����¸���
    // ע��ص�����
    // printf("%lf %lf", GetWindowWidth(), GetWindowHeight());
    registerMouseEvent(MouseEventProcess); 
    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
    registerTimerEvent(TimerEventProcess);
}




void TimerEventProcess(int timerID)/*��ʱ����Ϣ�ص�����*/
{
    if (timerID == 1)
        display();
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
        Calculate(NowShowTable); //��������ļ������ƶ������  ���¼���
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
  
    if (HandleKeyBoard(ch) && IsOpen == 2) {   //��������ļ������м�����Ϣ
        Calculate(NowShowTable);
    }
    display();
   
}
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI��ȡ����
    display();
}
