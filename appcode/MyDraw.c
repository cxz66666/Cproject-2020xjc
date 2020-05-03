#pragma once
#include"MyData.h"
#include "Readcsv.c"
#include "MyDrawTable.c"
void DrawOpenDir();
void DrawMenu();
void DrawButton();
void HandleFileButton(int selection);
void HandleToolButton(int selection);
void DrawButton();
void DrawLeftButton(stu_Ptr Head);
void drawMainPicture();
void drawDate(int tmpnum, char* Date);
void DrawTextZH(string str, double bx, double by);
void DrawTextChar(string str, double bx, double by);

#define   MY_DRAW_K  20  //�ڻ�table��ʱ�� ����xֱ�ӻ����ٸ���

void DrawMenu()
{
    static char *menuListFile[] = {"File",
                                   "Open | Ctrl-O",
                                   "Close | Ctrl-W",
                                   "Exit | Ctrl-E"

    };
    static char *menuListTool[] = {"Setting",
                                   "Advance Setting",
                                   "Music",
                                   "Other"};
    double fH = GetFontHeight();
    double x = 0;
    double y = GetWindowHeight();
    double height = fH * 1.5;
    double w = TextStringWidth(menuListFile[0]) * 2;
    setMenuColors("MenuBar", "White", "White", "White", 1);
    drawMenuBar(0, y - height, GetWindowWidth(), height);
    setMenuColors("MenuBar", "Black", "MenuFrameHot", "Black", 1);
    int selection;
    selection = menuList(GenUIID(0), x, y - height, w * 1.5, w * 3, height, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
    HandleFileButton(selection);
    selection = menuList(GenUIID(0), x + w * 1.5, y - height, w * 1.5, w * 3, height, menuListTool, sizeof(menuListFile) / sizeof(menuListFile[0]));
    HandleToolButton(selection);
}
void DrawOpenDir()
{
    double BoxHeight = GetFontHeight() * 2;
    double BeginY = MaxY - MaxY / 4;
    SetPenColor("TextBoxLabel");
    char InputWelcome[] = "��Ҳ���������ļ�ȫ��";
    SetPenSize(2);
    char NameDemo[] = "demo.csv";
    if (!FileNum)
    {

        char tmpLabel[] = "��ǰĿ¼����csv�ļ�";
        drawLabel(MaxX / 2 - TextStringWidth(tmpLabel) / 2, BeginY, tmpLabel);
    }
    else
    {
        char tmplabel[40] = "";
        sprintf(tmplabel, "��ǰĿ¼�¹���%d��csv�ļ�", FileNum);
        drawLabel(MaxX / 2 - TextStringWidth(tmplabel) / 2, BeginY, tmplabel);
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
        for (int i = 1; i <= FileNum; i++)
        {
            printf("1\n");
            if (button(GenUIID(i - 1), MaxX / 2 - TextStringWidth(NameDemo), BeginY - i * BoxHeight * 1.5 + 0.25 * BoxHeight, TextStringWidth(NameDemo) * 2, BoxHeight, FileName[i - 1]))
            {
                OpenFileName = (char *)malloc(sizeof(strlen(FileName[i - 1]) + 1));
                strcpy(OpenFileName, FileName[i - 1]);
                //printf("ok\n");
                if (ReadCSVFile(FileName[i - 1]))  //read��ȷ����1   ����ȷ����0
                {
                    if (!FileTotalNum)
                    {
                        SetPenColor("Red");
                        drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 3.5 * BoxHeight, "��������ȷ���ļ��Ѿ��ر��Ҳ�ΪNaN��");
                    }
                    else
                    {
                        IsOpen = 2;   //2��ʱ����ǿ��Խ��л�ͼ��
                        Calculate();
                        drawMainPicture();
                        return;
                    }
                }
            }
        }
    }

    static char dirName[30] = "";

    SetPenColor("TextBoxLabel");
    drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 0.5 * BoxHeight, InputWelcome); //�����y   ��˵һ�� һ��boxheight������������߶�  һ����ťռ1.5����boxheight  �������¸��ճ�0.25boxheight

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
    textbox(GenUIID(0), MaxX / 2 - 1, BeginY - FileNum * BoxHeight * 1.5 - 2 * BoxHeight, 2, BoxHeight, dirName, 30); //�����������Ϊ1 �����30�� ˭������ô�డ
    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    if (button(GenUIID(0), MaxX / 2 + 1.5, BeginY - FileNum * BoxHeight * 1.5 - 2 * BoxHeight, 1, BoxHeight, "ȷ��"))
    {
        if (CheckName(dirName))
        {

            // printf("okcheck\n");
            OpenFileName = (char *)malloc(sizeof(strlen(dirName) + 1));
            strcpy(OpenFileName, dirName);
            if (ReadCSVFile(dirName))
            {
                if (!FileTotalNum)
                {
                    SetPenColor("Red");
                    drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 3.5 * BoxHeight, "��������ȷ���ļ��Ѿ��ر��Ҳ�ΪNaN��");
                }
                else
                {
                    IsOpen = 2;
                    return;
                }
            }
        }
        else
        {
            SetPenColor("Red");
            drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 3.5 * BoxHeight, "��ȷ����������ȷ���ļ���Ŷ");
        }
    };
    
}



void DrawLeftButton(stu_Ptr Head)
{
    double fH = GetFontHeight();
    int nowNum = 0;
    Head = Head->next;   //����ͷ�ڵ㰡������������ŶŶŶŶŶŶ

    while (Head != NULL)  
    {
        int IsSelect = Head->IsSelect;
        setButtonColors("Orange", "Red", "Black", "Red", IsSelect);
        nowNum++;
        if (button(GenUIID(nowNum), 0.1, MaxY - (1.2 * nowNum + 1.5) * GetFontHeight(), 0.08, 0.08, ""))
        {
            Head->IsSelect = 1 - (Head->IsSelect);
            Calculate();

        }
        drawLabel(0.3, MaxY - (1.2 * nowNum + 1.5) * GetFontHeight(), Head->Date);
        Head = Head->next;
    }

    for (int i = 1; i <= ChooseDataNum; i++)
    {
        setButtonColors("Orange", "Red", "Black", "Red", IsChooseData[i]);
        if (button(GenUIID(i), 0.1, 4 - (1.4 * i + 1.5) * GetFontHeight(), 0.15, 0.15, ""))
        {
            IsChooseData[i] = 1 - IsChooseData[i];
            Calculate();
        
        }
        drawLabel(0.4, 4 - (1.4 * i + 1.5) * GetFontHeight(), ChooseData[i]);
    }
}

void HandleFileButton(int selection)
{
    if (selection == 1)
    {
        IsOpen = 1;
    }
    else if (selection == 2)
    {
        IsOpen = 0;
    }
    else if (selection == 3)
    {
        exit(-1);
    }
}
void HandleToolButton(int selection)
{
    if (selection == 1)
    {
        IsOpenAdvance = 1;
    }
    else if (selection == 2)
    {
        IsMusic = 1;
    }
    else if (selection == 3)
    {
        IsOpenOther = 1;
    }
}

void drawMainPicture()
{


    SetPenSize(2);
    for (int i = 1; i <= ChooseDataNum; i++) {
     
        MovePen(beginTableX, beginTableY);
        if (IsChooseData[i]) {
            SetPenColor(COLOR[i]);
            Cubic_Spline(TableData[i], ClassDataNum[i], MY_DRAW_K);
        }

    }   //!!!!   ���߲���   ���� !!!!  �õ�����������ֵ��   �о����� ����һ���죨


    SetPenColor("Black");
    SetPenSize(1);
    MovePen(beginTableX, beginTableY);   //������x��y��
    DrawLine(endTableX - beginTableX,0);
    MovePen(beginTableX, beginTableY);
    DrawLine(0, endTableY - beginTableY);
    stu_Ptr tmp = head->next;
    int tmpnum = 0;
    while (tmp != NULL) {
        if (tmp->IsSelect) {
            ++tmpnum;
            drawDate(tmpnum, tmp->Date);   
          }
        tmp = tmp->next;
    }      //�����ں�������

    SetPenColor("Gray");
    for (int i = 1; i <= 4; i++) {
        MovePen(beginTableX, beginTableY + (endTableY - beginTableY) / 5 * i);
        DrawLine(endTableX - beginTableX, 0);
    }   //����  

    SetPenColor("Black");
    for (int i = 1; i <= 4; i++) {
        string c = tostring(TableMark1 * i);
        MovePen(beginTableX - 0.1 - TextStringWidth(c), beginTableY + (endTableY - beginTableY) / 5 * i);
        DrawTextString(c);
        free(c);
    }

     
}
void DrawTextChar(string str,double bx,double by) {   //д�ַ������֣�
    string c;
    if (str[1] > 0 && str[1] <= 255)   //�������λ��
    {
        c= (string)malloc(3);
        c[0] = str[0];
        c[1] = str[1];
        c[2] = 0;
    }
    else {
        c = (string)malloc(2);
        c[0] = str[0];
        c[1] = 0;
    }
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
   // free(c);  ��������е��쳣����  ��console��ʱ��ᱨ��  ����ô�Ű�
}

void DrawTextZH(string str,double bx,double by) {   //д����
    string c = (string )malloc(3);
    c[0] = str[0], c[1] = str[1], c[2] = '\0';
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    //free(c);
}
void drawDate(int tmpnum, char* Date)
{
    SetPointSize(15);
    double midx = tmpnum * PerX+beginTableX;


    double bx= midx , by = beginTableY ;

    MovePen(bx, by);
    for (int i = 0; Date[i]; i++) {
        if (Date[i] > 0 && Date[i] < 255) {  //������
            by -= FontHeight;
            DrawTextChar(Date + i,bx,by);
           
            if (Date[i + 1] > 0 && Date[i + 1] <= 255)
                i++; //�����������λ ��Ҫ��i++��

        }
        else {   //������
            by -= FontHeight;
            DrawTextZH(Date+i,bx,by);
            i++;
        }
     
    }
}
