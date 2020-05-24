#pragma once
#include "MyCreat.c"
#include "MyData.h"
#include "MyDrawTable.c"
#include "MyPredict.c"
#include "Readcsv.c"
/*�����ĺ����������չ�������
���󲿷ֲ��ô��շ�������
Ӧ�ð��������� ����Ӳ��
*/
void display();                 //����Ҫ��չʾ����
void DrawPicture(CaseNode_Ptr Head); //������Ҫ��ͼ

void DrawMain();                      //Main����
void DrawOpenDir();                   //�򿪸����ļ���ť
void DrawMenu();                      //������
void DrawCreateNewFile();             //�������ļ�
void DrawStatus();                    //���½�״̬
void HandleFileButton(int selection); //���������������
void HandleToolButton(int selection);
void HandleHelpButton(int selection);
BOOL FileDialog(char* path);
void DrawLeftButton(CaseNode_Ptr Head); //����ѡ������ ѡ���е���ʾ
void drawMainPicture();
void DrawEachDate(int tmpnum, char *Date, CaseNode_Ptr ptr);      //��ÿһ�������
void DrawDate(CaseNode_Ptr HEAD);                                 //���·�������
void DrawTextZH(string str, double bx, double by);           //�������
void DrawTextChar(string str, double bx, double by);         //����ַ�
void DrawArrow();                                            //��xy��ͷ
void DrawLastTableNum();                                     //������
void Drawlegend();                                           //��ͼ��
void DrawHistogram(double TableData[][2], int ClassDataNum); //����״ͼ
void DrawXYLine();                                           //��xy��
void DrawBaseline();                                         //��6����׼��
void DrawMainLine();                                         //����Ҫ����
void Add(int num);
void Delete(int num);
void ResetFileName(string Name);
int SplitFileName(string szFile);
void HandleFileError(string ErrorAns);
BOOL CheckFileName(string szFile);  //����ļ�����
void WriteTitle();   //���⺯��
void DrawVirusAll(); //�������ĺ���
void DrawVirus();
void DrawMagnifier(); //���Ŵ󾵵ĺ���
void DrawPart(double x, double y, double degree);
void DrawWelcomeWindow(); //����ӭ����ĺ���
void  ShowOldPoint();   //Ԥ��ʱѡ�����߿��Կ�ԭ��������
void DrawHelpPage1();  //�����������һҳ�ĺ���
void DrawHelpPage2();  //����������ڶ�ҳ�ĺ���
#define MY_DRAW_K 20   //�ڻ�table��ʱ�� ����xֱ�ӻ����ٸ���
#define SHOWTIMEDRAW 0 //�������ʱ��
#define titleX 7       //����λ��
#define titleY 10
#define textX 9 //��ʼ����С��λ��
#define textY 7
#define PI 3.1415926

static double currentX = 0.0, currentY = 0.0; //��ǰ��������λ��

// ��ʾ����
/*ע��Ϊ���������Ŀ����߽�textbox����Щ����޸� ʹ���������GBK���������*/
void display()
{
    if (!IsSave && !IsNew)
        UpdateDisplay();
    DisplayClear(); //����

    DrawMain(); //���·���
    DrawMenu(); //���˵�
    //�Ȼ���Ҫ�Ĳ����ٻ��˵�  ��ֹ�ڵ�
}

void DrawMain()
{
    
   
    if (IsHelp == 1)
    {
        DrawHelpPage1(); //�������������һҳ
    }
    else if (IsHelp == 2)
    {
        DrawHelpPage2(); //������������ڶ�ҳ
    }
    else if (IsNew == 1)
    { //չʾͼ���м������   ��������½�  �����½������ Isopendirѡ��򿪵�

        DrawCreateNewFile();
    }
    else if (IsOpen == 0)
    {
        DrawWelcomeWindow(); //����ӭ����
    }
    else if (IsOpen == 1)
    {
        DrawOpenDir(); //��ѡ���ļ���
    }

    else if (IsOpen == 2) //�����ȡ���˸�csv�ļ���ô��isopenֵ��Ϊ2
    {

        DrawPicture(NowShowTable); //��Ԥ��ģʽ�Ͱ����ļ�������ݻ�ͼ Ԥ��ģʽ�Ͱ���Ԥ��������ͼ

        if (IsSave == 1) //������ڱ���״̬
        {
            SaveToCsv(NowShowTable); //���浱ǰ������
        }
    }
    DrawStatus(); //���½ǻ���ǰ״̬
}

void DrawPicture(CaseNode_Ptr Head)
{

    DrawLeftButton(Head); //����һ�Ѱ�ť

    drawMainPicture(); //��Ҫ�Ǹ���
    DrawPredict();     //��Ԥ��������

    if (IsRedisplay)   //�����Ҫ����ˢ�µĻ� ֱ������
    {
        IsRedisplay = 0;
        display();
    }
}

void DrawStatus()
{
    SetPenSize(1);
    SetPenColor("Black");
    char NowStatus[100];
    memset(NowStatus, 0, sizeof(NowStatus));   //��ʼ��        
    SetPointSize(15);
    /*����ע�ͼ������Ǻ���*/
    if (IsSave)                          //��ÿ��״̬�����ж�
        strcpy(NowStatus, "�����ļ�����");
    else if (IsHelp == 1 || IsHelp == 2)
    {
        sprintf(NowStatus, "���ڲ鿴����");
    }
    else if (IsChooseXaxis)
        strcpy(NowStatus, "�����ƶ�X��");
    else if (IsChooseYaxis)
        strcpy(NowStatus, "�����ƶ�Y��");
    else if (IsChooseLine)
        strcpy(NowStatus, "�����ƶ�����");
    else if (IsChooseHistogram)
        strcpy(NowStatus, "ѡ������");
    else if (IsChangeNum)
        strcpy(NowStatus, "���ڸ�������");
    else if (IsPredict)
        strcpy(NowStatus, "���ڽ���Ԥ��");
    else if (IsOpen == 1)
        strcpy(NowStatus, "���ڴ��ļ�");
    else if (IsOpen == 2)
        sprintf(NowStatus, "���ڲ鿴%s�ļ�", OpenFileName);
    else if (IsNew == 1)
        strcpy(NowStatus, "�����½��ļ�");
    else if (IsOpen == 0)
        ;
    else
        strcpy(NowStatus, "��������");

    MovePen(0.1, 0.1);
    //���ע��
    DrawTextString(NowStatus);
}
void DrawMenu()
{
    /*menulistFile��MenulistTool���������������Ķ���*/
    SetPointSize(16);
    static char *menuListFile[] = {"File",
                                   "New | Ctrl-N",
                                   "Open | Ctrl-O",
                                   "Close | Ctrl-W",
                                   "Save | Ctrl-S",
                                   "Exit | Ctrl-E"

    };
    

    static char *menuListHelp[] = {"Help",
                                   "Help |Ctrl-H"};
    double fH = GetFontHeight();
    double x = 0;
    double y = GetWindowHeight();
    double height = fH * 1.5;
    double w = TextStringWidth(menuListFile[0]) * 2;
    setMenuColors("MenuBar", "White", "White", "White", 1);
    //����Bar����ɫ
    drawMenuBar(0, y - height, GetWindowWidth(), height);
    //������������ѡ��
    setMenuColors("MenuBar", "Black", "MenuFrameHot", "Black", 1);
    int selection;
    selection = menuList(GenUIID(0), x, y - height, w * 1.5, w * 3, height, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
    HandleFileButton(selection); //ÿ���˵���Ӧhandle����
  
    selection = menuList(GenUIID(0), x + w * 1.5, y - height, w * 1.5, w * 3, height, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
    HandleHelpButton(selection);
}
BOOL CheckFileName(string szFile) {
    int Length = strlen(szFile);
    if (szFile[Length - 4] == '.'
        && szFile[Length - 3] == 'c'
        && szFile[Length - 2] == 's'
        && szFile[Length - 1] == 'v')
        return TRUE;
    else return FALSE;
}
void DrawOpenDir()
{
    //ÿ�ΰ���ť����ErrorAns��������
    static char ErrorAns[40] = "";
    SetPointSize(18);
    double BoxHeight = GetFontHeight() * 2;   
    double BeginY = MaxY * 0.82;
    SetPenColor("TextBoxLabel");
    char InputWelcome[] = "��Ҳ���������ļ�ȫ��";
    SetPenSize(2);
    char NameDemo[] = "demo.csv";
    drawLabel(MaxX *0.81,MaxY*0.9,"��Ҳ���Ե���·���ť"); 
    drawLabel(MaxX *0.8,MaxY*0.9-BoxHeight/2,"��ϵͳ�ļ�������Ŀ¼");
    if (button(GenUIID(0), MaxX*0.83,MaxY*0.9-2*BoxHeight, 2,FontHeight * 2, "��"))   //ʹ���ֳɵĹ��� win����apiֱ�Ӵ�
    {
        char szFile[MAX_PATH] = {0};
        memset(ErrorAns, 0, sizeof(ErrorAns)); //ErrorAns

        MyError = 0;
        if (FileDialog(szFile))   //winapi
        {
            if (CheckFileName(szFile))   //����Ƿ���csv�ļ�
            {
                string str = szFile + SplitFileName(szFile);
                if (ReadCSVFile(szFile))  //�����ȡ�ɹ�
                {
                    ResetFileName(str);  //�л����ڵ�filename
                    NowShowTable = FileHead;   //�л�
                    IsOpen = 2;  //���Խ��д�
                    ChangeIsSelect(NowShowTable);
                    Calculate(NowShowTable);
                    return;
                }
            }
            else
            {
                strcpy(ErrorAns, "�ļ���ʧ�ܣ������ļ�����"); //�ļ����Ͳ���
            }
        }
        else
        {
            strcpy(ErrorAns, "�ļ���ʧ��");  //û��
        }
    }

    SetPenColor("Red");
    char tmpLabel[40] = "��ǰĿ¼����csv�ļ�";
    
    
    
    if (!FileNum) //���û���ļ�
    {
        drawLabel(MaxX / 2 - TextStringWidth(tmpLabel) / 2, BeginY-0.1*MaxY, tmpLabel);
    }
    else
    {
        //ʹ��sprintf���丳ֵ

        sprintf(tmpLabel, "��ǰĿ¼�¹���%d��csv�ļ�", FileNum);

        drawLabel(MaxX / 2 - TextStringWidth(tmpLabel) / 2, BeginY, tmpLabel);
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
        int i;
        for (i = 1; i <= FileNum; i++)
        {
            // printf("1\n");
            if (button(GenUIID(i - 1), MaxX / 2 - TextStringWidth(NameDemo), BeginY - i * BoxHeight * 1.5 + 0.25 * BoxHeight, TextStringWidth(NameDemo) * 2, BoxHeight, FileName[i - 1]))
            {
                memset(ErrorAns, 0, sizeof(ErrorAns));
                MyError = 0;
                ResetFileName(FileName[i - 1]);
                //printf("ok\n");
                if (ReadCSVFile(FileName[i - 1])) //��ȡ�ļ���
                {
                    if (!FileTotalNum) //�������û�ж�ȡ��
                    {
                        strcpy(ErrorAns, "�ļ���ʧ��");
                    }
                    else
                    {
                        NowShowTable = FileHead;
                        IsOpen = 2;                   //�л�����ģʽ
                        ChangeIsSelect(NowShowTable); //
                        Calculate(NowShowTable);

                        return;
                    }
                }
                else
                {
                    MyFree(FileHead);  //���û�����ļ�  ����Ҫfree���Ѿ�����
                }
            }
        }
    }

    static char dirName[30] = "";

    SetPenColor("TextBoxLabel");
    drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 0.5 * BoxHeight-0.1*MaxY, InputWelcome); //�����y   ��˵һ�� һ��boxheight������������߶�  һ����ťռ1.5����boxheight  �������¸��ճ�0.25boxheight

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
    textbox(GenUIID(0), MaxX / 2 - 1, BeginY - FileNum * BoxHeight * 1.5 - 2 * BoxHeight-0.1*MaxY, 2, BoxHeight, dirName, 30); //�����������Ϊ1 �����30�� ˭������ô�డ
    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    if (button(GenUIID(0), MaxX / 2 + 1.5, BeginY - FileNum * BoxHeight * 1.5 - 2 * BoxHeight-0.1*MaxY, 1, BoxHeight, "ȷ��"))
    {
        memset(ErrorAns, 0, sizeof(ErrorAns));
        MyError = 0;   //error�ı�����ʾ
        if (CheckName(dirName))   //���ȼ���ļ�����
        { 
            ResetFileName(dirName);  //���ɹ�������

            if (ReadCSVFile(dirName))   //�����ļ���ȡ
            {
                if (!FileTotalNum)   //û�����ļ�
                { 
                    SetPenColor("Red");
                    strcpy(ErrorAns, "��������ȷ���ļ��Ѿ��ر��Ҳ�ΪNaN��");
                }
                else
                {
                    NowShowTable = FileHead;
                    IsOpen = 2;   //���ļ�
                    ChangeIsSelect(NowShowTable);  //�ı��������ѡ20��
                    Calculate(NowShowTable);
                    return;
                }
            }
            else
            {
                MyFree(FileHead);  //ͬ��free��
            }
        }
        else
        {
            SetPenColor("Red");
            strcpy(ErrorAns, "�����ļ����Ƿ���ȷ");
        }
    }
    SetPenColor("Red"); //���ErrorAns�ж��� �������� û��������м���
    if (strlen(ErrorAns))
    {
    //    printf("%s\n", ErrorAns);
        drawLabel(0.5 * MaxX - TextStringWidth(ErrorAns) / 2, 0.01 * MaxY, ErrorAns);
    }
    else
    {
        HandleFileError(ErrorAns);
    }
}

void DrawLeftButton(CaseNode_Ptr Head)
{
    SetPenSize(1);
    SetPointSize(15);
    double fH = FontHeight;
   static  char ErrorAns[20]; //���ü�����뷵�ص�ֵ
    
   static IsShowChooseDate = FALSE;
    int nowNum = 0;
    Head = Head->next; //���е�������������ͷ�ڵ��

    if (!IsShowChooseDate) {
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1); //ע���Ƿ���Ϳ
        if (button(GenUIID(0), 0.2, MaxY * 0.9, TextStringWidth("��ʾ����") * 1.5, 1.5 * FontHeight, "��ʾ����"))
            IsShowChooseDate = TRUE;
    }
    if (IsShowChooseDate)
    {
        SetPenSize(1);
        while (Head != NULL)
        {
            int IsSelect = Head->IsSelect;                             //��Ҫ�����ж��Ƿ���Ϳ
            setButtonColors("Color14", "Color14", "Red", "Red", IsSelect); //ע���Ƿ���Ϳ
            nowNum++;
            /*�����趨10������ʾ��ҳ   ֻ��ʾ��ǰʮ��*/
            if (nowNum > 10 * NowDateNum && nowNum <= 10 * (NowDateNum + 1))
            {
                if (button(GenUIID(nowNum), 0.1, MaxY -1- (1.2 * ((nowNum - 1) % 10 + 1) + 1.5) * FontHeight, 0.15, 0.15, ""))
                {
                    Head->IsSelect = !(Head->IsSelect);
                    Calculate(NowShowTable);
                }
                /*������Щλ�û�������΢��һ��  ע���ˣ���*/
                SetPenColor("Black");
                drawLabel(0.3, MaxY -1- (1.2 * ((nowNum - 1) % 10 + 1) + 1.5) * FontHeight, Head->Date);
            }
            if (nowNum + 1 > 10 * (NowDateNum + 1))
                break; //ֻ��ʾ10�����˾ͷ�ҳ
            Head = Head->next;
        }
        SetPenSize(2);
      

        if (NowDateNum)
        { //������ǵ�0ҳ����ʾ��һҳ��ť
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, MaxY-1 - 15 * FontHeight, 1, FontHeight, "��һҳ"))
            {
                IsRedisplay = 1;
                NowDateNum--; //���ڵĻ�ҳ
                DisplayClear();
            }
        }
        if (nowNum != FileTotalNum)
        {
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, MaxY - 17 * FontHeight-1, 1, FontHeight, "��һҳ"))
            {
                IsRedisplay = 1;
                NowDateNum++; //���ڵĻ�ҳ
                DisplayClear();
                              //  display();
            }
        }
        
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1); 
        if (button(GenUIID(0), 0.2, MaxY * 0.9, TextStringWidth("��������")*1.5, FontHeight*1.5, "��������"))
        {
            IsShowChooseDate = FALSE;
        }
    }
    int i;
    for (i = NowDateColumn * 4 + 1; i <= TotalColumnNum && i <= (NowDateColumn + 1) * 4; i++)
    {
        setButtonColors("Orange", "Red", "Black", "Red", IsChooseColumn[i]);
        if (button(GenUIID(i), 0.1, 4 - (1.4 * ((i - 1) % 4 + 1) + 1.5) * GetFontHeight(), 0.15, 0.15, ""))
        {
            IsChooseColumn[i] = !IsChooseColumn[i];
            if (IsChooseColumn[i])
            {
                Add(i);
                //     int j;
                //    for (j = 1; j <= ChooseColumnNum; j++)
                //      printf("%d ", ChoosedColumn[j]);
                // printf("\n");
            }
            //��i�ӵ��Ѿ�ѡ�������
            else
            {
                Delete(i); //��iɾȥ
                           /* int j;
                for (j = 1; j <= ChooseColumnNum; j++)
                    printf("%d ", ChoosedColumn[j]);
                printf("\n");*/
            }

            Calculate(NowShowTable);
        }
        drawLabel(0.4, 4 - (1.4 * ((i - 1) % 4 + 1) + 1.5) * GetFontHeight(), ColumnName[i]);

        //���Ƿ��ڸ���/��ʾ����  ��һ����ɫ���ÿ��������
        if (IsChangeNum && ChangingPtr != NULL)
        {
            setTextBoxColors("TextBoxFrame", COLOR[i], "TextBoxFrameHot", COLOR[i], 0);

            textbox(GenUIID(i), 0.5 + TextStringWidth(ColumnName[i]), 4.0 - (1.4 * ((i - 1) % 4 + 1) + 1.5) * GetFontHeight(), 1.5, FontHeight * 1.2, ChangingPtrStringNum[i], 10);
        }

        if (NowDateColumn)
        { //������ڵ�һҳ
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, 4 - 9 * FontHeight, 1, FontHeight, "��һҳ"))
            {
                IsRedisplay = 1;
                NowDateColumn--; //�еĻ�ҳ
                DisplayClear();
            }
        }

        if ((NowDateColumn + 1) * 4 < TotalColumnNum)
        { //����������һҳ
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, 4 - 11 * FontHeight, 1, FontHeight, "��һҳ"))
            {
                IsRedisplay = 1;
                NowDateColumn++; //�еĻ�ҳ
                DisplayClear();
            }
        }
    }
   

    //��ȷ�ϰ�ť  ȷ��֮������ʹ�ø���
    if (IsChangeNum && ChangingPtr != NULL)
    {
        CheckChangedNum(ChangingPtrStringNum, ErrorAns);     //�����ݺͷ��ص���ʾ������
        setButtonColors("Orange", "Red", "Black", "Red", 0);
        if (button(GenUIID(0), 1.5, 0.9, 0.8, 0.4, "ȷ��"))
        {

            for (i = 1; i <= TotalColumnNum; i++) {

                ChangingPtr->Data[i] = atoi(ChangingPtrStringNum[i]);    //�ı�Ptr��ĸ�������
            }
            strcpy(ErrorAns, "���³ɹ�");
                Calculate(NowShowTable); //ע����Ҫ���¼���


           
        }

        //����ԭ��ť   ��������ƶ���xy�����ĳ������   �����ʾ�����ť
        if (IsChooseXaxis || IsChooseYaxis || IsChooseLine)
        {
            setButtonColors("Orange", "Red", "Black", "Black", IsChooseColumn[i]);
            if (button(GenUIID(0), 0.95 * MaxX, 0.9 * MaxY, 1, 0.5, "��ԭ"))
            {

                /*�����иı仹ԭ
              �ı�����Ƿ�ѡ�� ѡ�е�����   �ƶ��ĳ���   ͼ�����λ��*/
                IsChooseXaxis = IsChooseYaxis = IsChooseLine = 0;
                ChooseLineNum = 0;
                ChooseLineMoveX = ChooseLineMoveY = 0;
                endTableX = StaticendTableX;
                endTableY = StaticendTableY;
                Calculate(NowShowTable); //��ؼ�ס���¼���
            }
        }
        if (IsChangeNum && strlen(ErrorAns)) {
            drawLabel(2.5, 0.9, ErrorAns);
        }
    }
}
void HandleFileButton(int selection)
{
    switch (selection)
    {

    case 1:
        IsHelp = 0;
        IsNew = 1; //����ÿ�������ı�data����趨ֵ
        break;
    case 2:
        IsHelp = 0;
        IsOpen = 1; //����ѡ��csv�ļ�����
        IsNew = 0;
        InitData(); //��ǰ�����ݳ�ʼ����

        break;
    case 3:
        IsHelp = 0;
        IsNew = 0;
        IsOpen = 0;
        MyFree(NowShowTable);      //closeʱ��Ҫ������Ľڵ�free��
        FreeColumn(TmpColumnName); //�ٰ�����Ĵ洢�еĿռ�free��
        break;
    case 4:
        IsSave = 1;
        break;
    case 5:
        exit(-1);
    }
}

/*����
��β����������ʾ
���ĳ���ݱ�ѡ��  ��ô��ʾ�������ڵ�����

*/
void DrawLastTableNum()
{
    CaseNode_Ptr tmp = FileTail; //ע��FileTail�ŵ�������ѡ�����ڵ����һ���ڵ�
    int i;
    for (i = 1; i <= ChooseColumnNum; i++)
    {
        int column = ChoosedColumn[i];
        string ShowNum = tostring(tmp->Data[column]); //������������������Ҫfree��
        SetPenColor(COLOR[column]);                   //����ɫ��Ϊ�趨����ɫ
        if (column != ChooseLineNum && column != ChooseHistogramNum)
        {
            MovePen(tmp->XPosition[column] + 0.05, tmp->YPosition[column]);
            DrawTextString(ShowNum);
        }

        else if (column == ChooseLineNum || column == ChooseHistogramNum)
        { //���������ѡ�е�ֱ�߻�����״ͼ

            CaseNode_Ptr tmp1 = NowShowTable->next; //��ʼ��ÿ��ѡ�е����ڶ�������

            while (tmp1 != NULL)
            {
                if (tmp1->IsSelect)
                {
                    string ShowNum1 = tostring(tmp1->Data[column]);
                    if (column == ChooseLineNum) //�����ѡ��ֱ��
                        MovePen(tmp1->XPosition[column] + ChooseLineMoveX + 0.05, tmp1->YPosition[column] + ChooseLineMoveY + 0.2);
                    else //�������ѡ���У�
                        MovePen(tmp1->XPosition[column] - TextStringWidth(ShowNum1) / 2, tmp1->YPosition[column] + FontHeight);

                    DrawTextString(ShowNum1);
                    free(ShowNum1);
                }
                tmp1 = tmp1->next;
            }
        }

        free(ShowNum);
    }
}

void Drawlegend() //��ͼ��
{
    double NowX = beginTableX + PerX, NowY = beginTableY / 4;
    int presize = GetPenSize(); //�õ���ǰ�ʵ����ݣ�֮���ָ�
    string precolor = GetPenColor();
    int i;
    for (i = 1; i <= ChooseColumnNum; i++)
    {
        int column = ChoosedColumn[i];
        NowX += 0.8; //0.8�������Ǽ��

        MovePen(NowX, NowY);

        IsChooseColumn[column] == 1 ? SetPenSize(2) : SetPenSize(6); //���������߻�����   1��������  2����
        SetPenColor(COLOR[column]);
        DrawLine(0.6, 0); //��ͼ������
        MovePen(GetCurrentX() + 0.25, GetCurrentY());
        DrawTextString(ColumnName[column]); //д����Ϣ

        NowX = GetCurrentX(), NowY = GetCurrentY();
        if (NowX > StaticendTableX - PerX) //����
        {
            NowX = beginTableX + PerX; //ע���������
            NowY -= FontHeight * 1.5;
        }
    }
    SetPenColor(precolor); //����ԭ����ɫ
    SetPenSize(presize);   //����ԭ���ߴ�
}
void DrawDate(CaseNode_Ptr HEAD)
{
    SetPenColor("Black");
    CaseNode_Ptr tmp = HEAD->next;
    int tmpnum = 0;
    while (tmp != NULL)
    {
        if (tmp->IsSelect)
        {
            ++tmpnum;
            DrawEachDate(tmpnum, tmp->Date, tmp); //��ÿһ�������  ������Ϊ��ǰ���˶����죬��Ҫ����������ʾ�ĺ�����λ��  ������
        }
        tmp = tmp->next;
    } //�����ں�������
}
void DrawMainLine()
{

    DrawWithColumnNow = 0; //�Ѿ����˼�����״ͼ�� ��Ϊ cxz�趨��໭���� ���Ժ�����
    int i, j;
    for (i = 1; i <= ChooseColumnNum; i++)
    {

        /*������׼������
        size  �ʵ�λ��
        */
        SetPenSize(2);
        MovePen(beginTableX, beginTableY);
        int column = ChoosedColumn[i];
        SetPenColor(COLOR[column]); //������׼������

        if (IsChooseLine && column == ChooseLineNum)
        { //�������߱�ѡ��
            SetPenColor("ChoosedColor");
            SetPenSize(4);
            //������������ȫ������ƫ����  ֮���ټ�ȥ
            for (j = 1; j <= ClassDataNum[column]; j++)
            {
                TableData[column][j][0] += ChooseLineMoveX;
                TableData[column][j][1] += ChooseLineMoveY;
            } //������xy�������
        }
        if (IsChooseHistogram && column == ChooseHistogramNum)
        {
            SetPenColor("ChoosedColor");
            SetPenSize(2);
        }
        if (IsChooseColumn[column] == 1) //1�ǻ�����   2����״ͼ
            //1������������ֵ��
            Cubic_Spline(TableData[column], ClassDataNum[column], MY_DRAW_K, column);
        else
        {
            //2�û���״ͼ�����㷨
            DrawHistogram(TableData[column], ClassDataNum[column]);
        }
        if (IsChooseLine && column == ChooseLineNum)
        {
            for (j = 1; j <= ClassDataNum[column]; j++)
            {
                TableData[column][j][0] -= ChooseLineMoveX;
                TableData[column][j][1] -= ChooseLineMoveY;
            } //����֮ǰ������ƫ����  ����Ҫ��ȥ
        }

    } //!!!!   ���߲���   ���� !!!!  �����õ�����������ֵ��  ��״ͼ��ûɶ  �о����� ����һ���죨
}
void DrawArrow()
{
    SetPenColor("Black");
    SetPenSize(1);
    /*X��  ���Ƿ�ѡ������*/
    if (IsChooseXaxis)
        SetPenColor("ChoosedColor"), SetPenSize(3);
    MovePen(endTableX, beginTableY);
    DrawLine(-0.2, 0.2);
    MovePen(endTableX, beginTableY);
    DrawLine(-0.2, -0.2);
    /*Y��  ���Ƿ�ѡ������*/
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseYaxis)
        SetPenColor("ChoosedColor"), SetPenSize(3);
    MovePen(beginTableX, endTableY);
    DrawLine(-0.2, -0.2);
    MovePen(beginTableX, endTableY);
    DrawLine(0.2, -0.2);
}

void Add(int num)
{
    int i;
    for (i = ChooseColumnNum; ChoosedColumn[i] >= num && i > 0; i--)
    {
        ChoosedColumn[i + 1] = ChoosedColumn[i];
    }

    ChoosedColumn[i + 1] = num;
    ++ChooseColumnNum;
}
void Delete(int num)
{
    int i;
    for (i = 1; i <= ChooseColumnNum; i++)
    {
        if (ChoosedColumn[i] == num) //�ҵ���num
            break;
    }
    for (i; i < ChooseColumnNum; i++) //ÿһλ��ǰ�ƶ�
        ChoosedColumn[i] = ChoosedColumn[i + 1];
    ChooseColumnNum--;
}
void DrawBaseline()
{
    //������׼�ߵ���������
    SetPenSize(1);
    SetPenColor("Gray");
    int i;
    for (i = 1; i <= 6; i++)
    {
        MovePen(beginTableX, beginTableY + (endTableY - beginTableY) / 7 * i);
        DrawLine(endTableX - beginTableX, 0);
    } //����

    SetPenColor("Black");

    for (i = 1; i <= 6; i++)
    {
        string c = tostring(TableMark1 * i);
        MovePen(beginTableX - 0.1 - TextStringWidth(c), beginTableY + (endTableY - beginTableY) / 7 * i);
        DrawTextString(c);
        if (c != NULL)
            free(c);
    }
}
void DrawXYLine()
{
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseXaxis)
    {
        SetPenColor("ChoosedColor");
        SetPenSize(3); //�������x
    }
    MovePen(beginTableX, beginTableY); //������x��y��
    DrawLine(endTableX - beginTableX, 0);
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseYaxis)
    {
        SetPenColor("ChoosedColor"); //�������y
        SetPenSize(3);
    }
    MovePen(beginTableX, beginTableY);
    DrawLine(0, endTableY - beginTableY);
}
int SplitFileName(string szFile)   //�ֳ��ļ��� ���ںϲ�״̬
{
    int ans = 0, i;
    for (i = 0; szFile[i]; i++)
    {
        if (szFile[i] == '/' || szFile[i] == '\\')
            ans = i;
    }

    return ans + 1;
}
void HandleFileError(string ErrorAns)  //��Error���д���
{

    if (!MyError)  
        return;
    else if (MyError == -1)
    {
        strcpy(ErrorAns, "�ļ���ʧ��");
        drawLabel(0.5 * MaxX - TextStringWidth(ErrorAns) / 2, 0.01 * MaxY, ErrorAns);
    }
    else if (MyError == -2)
    {
        strcpy(ErrorAns, "�ļ�����Ϊ��");

        drawLabel(0.5 * MaxX - TextStringWidth(ErrorAns) / 2, 0.01 * MaxY, ErrorAns);
    }
}
void ResetFileName(string Name)
{

    if (OpenFileName != NULL || Name[0] != '\0')
    {
        free(OpenFileName);
        OpenFileName = NULL;
    }
    OpenFileName = (char*)malloc(sizeof(Name) + 30);
    strcpy(OpenFileName, Name);
}
void drawMainPicture()
{
#if SHOWTIMEDRAW

    clock_t start_time, end_time;
    start_time = clock(); //��ȡ��ʼִ��ʱ��
#endif                    // SHOWTIME

    DrawDate(NowShowTable);
    DrawXYLine(); //����xy��   ���ѡ�о͸���

    DrawMainLine(); //����Ҫ������ ����������״ͼ

    // printf("DrawWithColumn is  %d\n", DrawWithColumn);

    DrawBaseline();     //��y���ϵ�������׼��
    DrawArrow();        //xy��ļ�ͷ
    DrawLastTableNum(); //����������ʾ
    Drawlegend();       //��ͼ��
    DrawSelectedInf();
    ShowOldPoint();
#if SHOWTIMEDRAW
    end_time = clock();
    printf("%lf seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
#endif // DEBUG
}
void DrawTextChar(string str, double bx, double by)
{ //д�ַ������֣�
    string c;

    if (str[1] > 0 && str[1] <= 255) //�������λ��
    {
        c = (string)malloc(10);
        c[0] = str[0];
        c[1] = str[1];
        c[2] = 0;
    }
    else
    {
        c = (string)malloc(10);
        c[0] = str[0];
        c[1] = 0;
    }

    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    if (c != NULL)
        free(c); //���c��NULL freeʱ��������
}
BOOL FileDialog(char* path)
{
    OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn); // �ṹ��С
    ofn.lpstrFile = path; // ·��
    ofn.nMaxFile = MAX_PATH; // ·����С
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0"; // �ļ�����
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	return GetOpenFileName(&ofn);
}
void DrawTextZH(string str, double bx, double by)
{                                                //д����
    string c = (string)malloc(sizeof(char) * 5); //��3freeʱ�򱨴�
    string tmp = c;
    memset(c, 0, sizeof(c));
    c[0] = str[0], c[1] = str[1];
    c[2] = 0;
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    if (tmp != NULL)
        free(tmp); //���c��NULL freeʱ��������
}
void DrawEachDate(int tmpnum, char *Date, CaseNode_Ptr ptr)
{
    SetPointSize(15);
    double midx = tmpnum * PerX + beginTableX;

    double bx = midx, by = beginTableY - 0.2;
    //��ÿ�����ڶ������ж�  ��ɫ���Ƿ�ѡ�С�λ��

    MovePen(bx, by);
    SetPenColor(ptr->Changedcolor);
    if (ptr->IsShowNum)
    {
        SetPenColor("Red");
    }
    int i;
    for (i = 0; Date[i]; i++)
    {
        if (Date[i] > 0 && Date[i] < 255)
        { //������
            by -= FontHeight;
            DrawTextChar(Date + i, bx, by);

            if (Date[i + 1] > 0 && Date[i + 1] <= 255)
                i++; //�����������λ ��Ҫ��i++ ��Ϊ�Ѿ�����drawtextchar�����
        }
        else
        { //������
            by -= FontHeight;
            DrawTextZH(Date + i, bx, by);
            i++;
        }
    }
    if (IsChangeNum)
    { //������ڸ�������ģʽ  ÿ�����������һ��Сѡ���
        SetPenSize(2);
        int i;
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", ptr->IsShowNum);
        CaseNode_Ptr tmp = NowShowTable;
        if (button(GenUIID(tmpnum), bx - FontHeight / 2.5, by - FontHeight, FontHeight * 0.8, FontHeight * 0.8, ""))
        {
            if (!(ptr->IsShowNum))
            {
                while (tmp != NULL)
                { //������������ѡ��  ��ô�������Ķ���ΪFALSE��Ϊһ��ֻ�ܸ���һ��
                    if (tmp != ptr)
                        tmp->IsShowNum = FALSE;
                    tmp = tmp->next;
                }
                for (i = 1; i <= TotalColumnNum; i++)
                {
                    if (ChangingPtrStringNum[i] != NULL)
                        free(ChangingPtrStringNum[i]);
                }

                ChangingPtr = ptr; //���ı��ptrָ�����
                for (i = 1; i <= TotalColumnNum; i++)
                {
                    ChangingPtrStringNum[i] = tostring(ptr->Data[i]);
                //    printf("%s\n", ChangingPtrStringNum[i]);
                }
            }
            else
            {
                ChangingPtr = NULL; //����ָ��NULL
            }

            ptr->IsShowNum = !(ptr->IsShowNum); //��һ�¾��л��Ƿ�ѡ��
        }
    }
}

void DrawWelcomeWindow()
{

    //��ô��ڳߴ�
    currentX = GetWindowWidth();
    currentY = GetWindowHeight();

    WriteTitle();
    DrawVirusAll();

    DrawMagnifier();
}

void WriteTitle()
{ //������ʼҳ�����
    SetPointSize(70);
    SetPenColor("TitleColor");
    SetPenSize(8);
    SetFont("����"); //����������
    drawLabel(titleX, titleY, "ս�ߣ�������һ��");
    SetPointSize(25);
    SetPenColor("TextColor");
    drawLabel(textX, textY, "��ӭʹ���������ݷ�������");
}

void DrawVirusAll()
{
    MovePen(9.9, 3); //һ���򵥻���������ʻ��ĺ��� ���趨λ�û�������
    DrawVirus();
    MovePen(11.5, 3);
    DrawVirus();
    MovePen(10.7, 4.3);
    DrawVirus();
}

void DrawVirus()
{ //���廭�������ĺ���
    double cx = 0.0, cy = 0.0;
    int i = 0;
    cx = 2;
    cy = 2;
    SetPenSize(3);
    SetPenColor("VirusColor"); //�趨��ɫ
    for (i = 0; i < 8; i++)
    {
        DrawArc(0.24, 45 * i, 45);
        cx = GetCurrentX();
        cy = GetCurrentY();
        DrawPart(cx, cy, 45 * i + 45);
    }
}

void DrawPart(double x, double y, double degree)
{
    MovePen(x, y);
    double px = 0.0, py = 0.0; // ���廭�������ĺ���
    px = cos(degree / 180 * PI);
    py = sin(degree / 180 * PI);
    DrawLine(0.15 * px, 0.15 * py);
    DrawLine(0.06 * py, -0.06 * px);
    DrawLine(0.06 * px, 0.06 * py);
    DrawLine(-0.18 * py, 0.18 * px);
    DrawLine(-0.06 * px, -0.06 * py);
    DrawLine(0.06 * py, -0.06 * px);
    DrawLine(-0.15 * px, -0.15 * py);
}

void DrawMagnifier()
{ //���Ŵ󾵵ĺ���
    MovePen(14.7, 4.5);
    SetPenSize(1);
    SetPenColor("CircleColor"); //�����ɫ
    StartFilledRegion(0.2);     //�������
    DrawArc(1, 0, 360);
    EndFilledRegion();        //�ر��������
    SetPenColor("WoodColor"); //Բ����ɫ
    SetPenSize(6);
    DrawArc(1, 0, 360);
    MovePen(14.45, 4.8); //����Բ���ϵķ��⻡
    SetPenColor("White");
    SetPenSize(7);
    DrawArc(1, 30, 60);
    MovePen(14.5, 3.85);
    SetPenSize(6);
    SetPenColor("WoodColor"); //�����ֱ��������ɫ
    StartFilledRegion(0.5);
    DrawLine(1.1, -1.1);
    DrawLine(-0.2, -0.2);
    DrawLine(-1.1, 1.1);
    DrawLine(0.2, 0.2);
    EndFilledRegion();
}

void HandleHelpButton(int selection)
{ //�˵���HELP���Ŀ��ƺ���
    if (selection == 1)
    {
        IsHelp = 1;
        IsNew = 0;
        IsOpen = 0;
    }
}

void DrawHelpPage1()
{ //����ҳ���һҳ
    double interval = 0.0;
    interval = GetFontHeight();
    drawLabel(MaxX - interval * 45, MaxY - interval * 4, "Hello�������Ǳ����ӻ����ߵ�ʹ��ָ��");
    drawLabel(MaxX - interval * 68, MaxY - interval * 8, "�������½�����");
    drawLabel(MaxX - interval * 68, MaxY - interval * 10, "����������Ͻ�File�˵��е�New����ʹ�ÿ�ݼ�Ctrl-N���½�ҳ�棬������ʾ�����½����ݵ�������ݣ����ȷ�Ϻ�����һҳ���������������ȷ�Ϻ������ӻ�ҳ�档");
    drawLabel(MaxX - interval * 68, MaxY - interval * 12, "�����ڴ��ļ�");
    drawLabel(MaxX - interval * 68, MaxY - interval * 14, "ʹ��File�˵��µ�Open����ʹ�ÿ�ݼ�Ctrl-N�򿪲鿴ҳ�棬����ֱ�ӵ�����Ϸ��򿪼�������windows��Դ���������ڣ����ݴ���Ŀ¼ѡ��csv�ļ��򿪼��ɡ������ڴ�");
    drawLabel(MaxX - interval * 68, MaxY - interval * 16, "�ļ�ǰ����Ҫ�鿴��csv�����ļ�����demoprj-devc->output�ļ����£��ļ�����ֱ����ʾ�ڵ�ǰĿ¼�¡�");
    drawLabel(MaxX - interval * 68, MaxY - interval * 18, "�����ڿ��ӻ�ҳ��");
    drawLabel(MaxX - interval * 68, MaxY - interval * 20, "���ҳ�����Ͻ���ʾ���ڣ���ѡ�����������������ﵽ��ʾ�����ص�ǰ���ڵ����ݵ�Ŀ�ģ���ʹ�����·�ҳ�����������������Ŷ����ѡ���½����������������ͼ������");
    drawLabel(MaxX - interval * 68, MaxY - interval * 22, "ʾ������ݵĿ��ӻ����ܡ�����ҳ���ҷ������ʾ�ɽ���Ԥ�⹦�ܵ�ʵ��Ŷ������϶�X��Y��ʵ��ͼ������Ź��ܣ�����������ʾ��ǰ�������ݣ���ʹ�����Ͻǻָ�����");
    drawLabel(MaxX - interval * 68, MaxY - interval * 24, "�����ָ���ʼͼ��״̬��");
    drawLabel(MaxX - interval * 68, MaxY - interval * 26, "���������ݸ��ģ��������½����ܺͲ鿴���ܣ�");
    drawLabel(MaxX - interval * 68, MaxY - interval * 28, "�ڿ��ӻ�ҳ�浥�����½Ǹ������ݹ��ܼ��������ѡX��������ݼ��ɽ����޸����ݣ�������漴�ɱ����޸����ݡ�");
    drawLabel(MaxX - interval * 68, MaxY - interval * 30, "������Ԥ�⹦��");
    drawLabel(MaxX - interval * 68, MaxY - interval * 32, "�ڿ��ӻ�ҳ���Ҳ����������ʾ����Ԥ�⡣��ʵ��5�׼����µ�ģ��Ԥ�⡣");
    //�����ť�������ҳ��ڶ�ҳ
    setButtonColors("Black", "Black", "DarkBlue", "DarkBlue", 0);
    if (button(GenUIID(0), MaxX - interval * 40, MaxY - interval * 36, 1.5, 0.8, "��һҳ"))
    {
        IsHelp = 2;
    }
}

void DrawHelpPage2()
{ //����ҳ��ڶ�ҳ
    double interval = 0.0;
    interval = GetFontHeight();

    drawLabel(MaxX - interval * 68, MaxY - interval * 8, "�����ڹرչ���");
    drawLabel(MaxX - interval * 68, MaxY - interval * 10, "������ҳ����File�˵��µ�Close����ʹ�ÿ�ݼ�Ctrl-W���ɻص���ʼҳ��");
    drawLabel(MaxX - interval * 68, MaxY - interval * 12, "�����ڱ��湦��");
    drawLabel(MaxX - interval * 68, MaxY - interval * 14, "�½����ݺ󵥻�File�˵��µ�Save����ʹ�ÿ�ݼ�Ctrl-S�������ݣ�ע��������ȷ���ļ���չ��.csv�����ɱ����ļ���OutPut�ļ����¡�");
    drawLabel(MaxX - interval * 68, MaxY - interval * 16, "�������˳�����");
    drawLabel(MaxX - interval * 68, MaxY - interval * 18, "���file�˵��µ�Exit����ʹ�ÿ�ݼ�Ctrl-E�˳������ߡ�");
    //�����ť�ص�����ҳ���һҳ
    setButtonColors("Black", "Black", "DarkBlue", "DarkBlue", 0);
    if (button(GenUIID(0), MaxX - interval * 40, MaxY - interval * 36, 1.5, 0.8, "��һҳ"))
    {
        IsHelp = 1;
    }
}
