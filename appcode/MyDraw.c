#pragma once
#include"MyData.h"
#include "Readcsv.c"
#include "MyDrawTable.c"
#include "MyPredict.c"


void display();
void DrawPicture(stu_Ptr Head);

void DrawMain();
void DrawOpenDir();
void DrawMenu();
void DrawStatus();
void HandleFileButton(int selection);
void HandleToolButton(int selection);

void DrawLeftButton(stu_Ptr Head);
void drawMainPicture();
void DrawEachDate(int tmpnum, char* Date,stu_Ptr ptr);
void DrawDate(stu_Ptr HEAD);
void DrawTextZH(string str, double bx, double by);
void DrawTextChar(string str, double bx, double by);
void DrawArrow();
void DrawLastTableNum();
void Drawlegend();
void DrawHistogram(double TableData[][2],int ClassDataNum);
void DrawXYLine();
void DrawBaseline();
void DrawMainLine();
void Add(int num);
void Delete(int num);

#define   MY_DRAW_K  20  //�ڻ�table��ʱ�� ����xֱ�ӻ����ٸ���
#define  SHOWTIMEDRAW 0 //�������ʱ��



// ��ʾ����
void display()
{
    if (!IsSave)   //������ڱ��������  ��update  ��Ϊ������������������  ʹ��update�޷���������
        UpdateDisplay();
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
        if (IsSave == 1)
        {
            SaveToCsv(NowShowTable);
        }
        if (!IsPredict)
            DrawPicture(head);  //�������Ԥ��ģʽ�ͻ��ļ����ͼ
        else {
            DrawPicture(PreHead);  //�����Ԥ��ͻ�Ԥ��� ͼ
        }
    }
    DrawStatus();   //���½ǻ���ǰ״̬
}


void DrawPicture(stu_Ptr Head)
{

    DrawLeftButton(Head);   //����һ�Ѱ�ť

    drawMainPicture();   //��Ҫ�Ǹ���
    DrawPredict();     //��Ԥ��������
   
  
    if (IsRedisplay)
    {
        IsRedisplay = 0;
        display();
    }
}



void DrawStatus() {
    SetPenSize(1);
    SetPenColor("Black");
    char NowStatus[30];
    memset(NowStatus, 0, sizeof(NowStatus));
    if (IsSave)
        strcpy(NowStatus, "�����ļ�����");
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
    else
        strcpy(NowStatus, "��������");
    
    MovePen(0.1, 0.1);

    DrawTextString(NowStatus);
}
void DrawMenu()
{
    static char *menuListFile[] = {"File",
                                   "Open | Ctrl-O",
                                   "Close | Ctrl-W",
                                    "Save | Ctrl-S",
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
        int i;
		for ( i= 1; i <= FileNum; i++)
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
                        NowShowTable = head;
                        IsOpen = 2;   //2��ʱ����ǿ��Խ��л�ͼ��
                        Calculate(NowShowTable);
                       
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
                    NowShowTable = head;
                    IsOpen = 2;
                    Calculate(NowShowTable);
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
   

  


    SetPenSize(1);
    while (Head != NULL)  
    {
        int IsSelect = Head->IsSelect;
        setButtonColors("Orange", "Red", "Black", "Red", IsSelect);
        nowNum++;
       
        if (nowNum > 10 * NowDateNum&&nowNum<=10*(NowDateNum+1)) {
            if (button(GenUIID(nowNum), 0.1, MaxY - (1.2 * ((nowNum-1)%10+1) + 1.5) * FontHeight, 0.08, 0.08, ""))
            {
                Head->IsSelect = !(Head->IsSelect);
                Calculate(NowShowTable);

            }
            drawLabel(0.3, MaxY - (1.2 * ((nowNum - 1) % 10 + 1) + 1.5) * FontHeight, Head->Date);
        
        }
        if (nowNum+1 > 10 * (NowDateNum + 1))
            break;
        Head = Head->next;
     
    }
    SetPenSize(1);



    if (NowDateNum) {
        setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
        if (button(GenUIID(0), 0.2, MaxY - 15 * FontHeight, 1, FontHeight, "��һҳ"))
        { 
            IsRedisplay = 1;
            NowDateNum--;//���ڵĻ�ҳ
        //display();
        }

    }
    if (nowNum != FileTotalNum) {
        setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
        if (button(GenUIID(0), 0.2, MaxY - 17 * FontHeight, 1, FontHeight, "��һҳ"))
        {
            IsRedisplay = 1;
            NowDateNum++;//���ڵĻ�ҳ
          //  display();
        }
            

    }

	int i;
    for (i=NowDateColumn*4+1; i <= TotalColumnNum&&i<=(NowDateColumn+1)*4; i++)
    {
        setButtonColors("Orange", "Red", "Black", "Red", IsChooseColumn[i]);
        if (button(GenUIID(i), 0.1, 4 - (1.4 * ((i-1)%4+1) + 1.5) * GetFontHeight(), 0.15, 0.15, ""))
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
        drawLabel(0.4, 4 - (1.4 * ((i - 1) % 4 + 1)  + 1.5) * GetFontHeight(), ColumnName[i]);

        //���Ƿ��ڸ���/��ʾ����  ��һ����ɫ���ÿ��������
        if (IsChangeNum&&ChangingPtr!=NULL) {
            setTextBoxColors("TextBoxFrame", COLOR[i], "TextBoxFrameHot", COLOR[i], 0);

            textbox(GenUIID(i), 0.5 + TextStringWidth(ColumnName[i]), 4 - (1.4 * ((i - 1) % 4 + 1) + 1.5) * GetFontHeight(), 1.5, FontHeight*1.2, ChangingPtrStringNum[i], 10);
        }

        if (NowDateColumn) {
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, 4 - 9 * FontHeight, 1, FontHeight, "��һҳ"))
            {
                IsRedisplay = 1;
                NowDateColumn--;   //�еĻ�ҳ
                //display();
            }
        }

        if ((NowDateColumn + 1) * 4 < TotalColumnNum) {
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, 4 - 11 * FontHeight, 1, FontHeight, "��һҳ"))
            {
                IsRedisplay = 1;
                NowDateColumn++;//�еĻ�ҳ
                //display();
            }

        }

    }
    static char ErrorAns[20];  //���ü�����뷵�ص�ֵ
    //��ȷ�ϰ�ť  ȷ��֮������ʹ�ø���
    if (IsChangeNum&&ChangingPtr!=NULL) {
        setButtonColors("Orange", "Red", "Black", "Red", 0);
        if (button(GenUIID(0), 1.5, 0.9 , 0.8, 0.4, "ȷ��"))
        {
            if (CheckChangedNum(ChangingPtrStringNum, ErrorAns)) {
                Calculate(NowShowTable);
               
            }
            drawLabel(2.5, 0.9, ErrorAns);
        }
    }

    //����ԭ��ť   ��������ƶ���xy�����ĳ������   �����ʾ�����ť
    if (IsChooseXaxis || IsChooseYaxis || IsChooseLine) {
        setButtonColors("Orange", "Red", "Black", "Red", IsChooseColumn[i]);
        if (button(GenUIID(0), 0.95 * MaxX, 0.9 * MaxY, 1, 0.5, "��ԭ"))
        {
            IsChooseXaxis = IsChooseYaxis = IsChooseLine = 0;
            ChooseLineNum = 0;
            ChooseLineMoveX = ChooseLineMoveY = 0;
            endTableX = StaticendTableX;
            endTableY = StaticendTableY;
            Calculate(NowShowTable);
        }
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
    else if (selection == 3) {
        IsSave = 1;

    }
    else if (selection == 4)
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
void DrawLastTableNum() {
    stu_Ptr tmp = tail;
    int i;
    for (i=1; i <= ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            string ShowNum = tostring(tmp->Data[column]);
            SetPenColor(COLOR[column]);
            if (column != ChooseLineNum&&column!=ChooseHistogramNum) {
                MovePen(tmp->XPosition[column] + 0.05, tmp->YPosition[column]);
                DrawTextString(ShowNum);
            }
         
            else  if (column == ChooseLineNum||column==ChooseHistogramNum) {
               
                stu_Ptr tmp1 = NowShowTable->next;
                
                while (tmp1 != NULL) {
                    if (tmp1->IsSelect) {
                        string ShowNum1 = tostring(tmp1->Data[column]);
                        if (column == ChooseLineNum)
                            MovePen(tmp1->XPosition[column] + ChooseLineMoveX + 0.05, tmp1->YPosition[column] + ChooseLineMoveY + 0.2);
                        else
                            MovePen(tmp1->XPosition[column] - TextStringWidth(ShowNum1)/2, tmp1->YPosition[column] + FontHeight);
                       
                        DrawTextString(ShowNum1);
                        free(ShowNum1);
                    }
                    tmp1 = tmp1->next;

                }

            }
          


                free(ShowNum);
    }
}
void Drawlegend()  //��ͼ�� 
{  
    double  NowX = beginTableX + PerX,NowY=beginTableY/4;
    int presize = GetPenSize();
    string precolor = GetPenColor();
    int i;
    for (i = 1; i <=ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            NowX += 0.8;  //0.8�������Ǽ��

            MovePen(NowX, NowY);
         
           IsChooseColumn[column]==1? SetPenSize(2):SetPenSize(5);     //���������߻�����
            SetPenColor(COLOR[column]);
            DrawLine(0.6, 0);
            MovePen(GetCurrentX() + 0.25, GetCurrentY());         
            DrawTextString(ColumnName[column]);

            NowX = GetCurrentX(), NowY = GetCurrentY();
            if (NowX > endTableX - PerX)   //����
            {
                NowX = beginTableX + PerX;
                NowY -= FontHeight * 1.5;
            
            }
     
    }
    SetPenColor(precolor); //����ԭ����ɫ
    SetPenSize(presize);   //����ԭ���ߴ�
}
void DrawDate(stu_Ptr HEAD) {
    SetPenColor("Black");
    stu_Ptr tmp = HEAD->next;
    int tmpnum = 0;
    while (tmp != NULL) {
        if (tmp->IsSelect) {
            ++tmpnum;
            DrawEachDate(tmpnum, tmp->Date,tmp);
        }
        tmp = tmp->next;
    }      //�����ں�������
}
void DrawMainLine() {
    
    DrawWithColumnNow = 0;   //�Ѿ����˼�����״ͼ�� ��Ϊ cxz�趨��໭���� ���Ժ�����
    int i,j;
    for (i=1; i <= ChooseColumnNum; i++) {


        SetPenSize(2);
        MovePen(beginTableX, beginTableY);
        int column = ChoosedColumn[i];
        SetPenColor(COLOR[column]);   //������׼������


        if (IsChooseLine&& column == ChooseLineNum) {   //�������߱�ѡ��
            SetPenColor("ChoosedColor");
            SetPenSize(4); 
            
            for (j = 1; j <= ClassDataNum[column]; j++) {
                TableData[column][j][0] += ChooseLineMoveX;
                TableData[column][j][1] += ChooseLineMoveY;
            }    //������xy�������
           
        }
        if (IsChooseHistogram && column == ChooseHistogramNum)
        {
            SetPenColor("ChoosedColor");
            SetPenSize(2);
        }
            if (IsChooseColumn[column] == 1)   //1�ǻ�����   2����״ͼ
                Cubic_Spline(TableData[column], ClassDataNum[column], MY_DRAW_K, column);
            else {
                DrawHistogram(TableData[column], ClassDataNum[column]);
            }
            if (IsChooseLine && column == ChooseLineNum) {
                for (j = 1; j <= ClassDataNum[column]; j++) {
                    TableData[column][j][0] -= ChooseLineMoveX;
                    TableData[column][j][1] -= ChooseLineMoveY;
                }    //������xy����  
            }

    }   //!!!!   ���߲���   ���� !!!!  �����õ�����������ֵ��  ��״ͼ��ûɶ  �о����� ����һ���죨
}
void DrawArrow() {
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseXaxis)
        SetPenColor("ChoosedColor"), SetPenSize(3);
    MovePen(endTableX, beginTableY);
    DrawLine(-0.2, 0.2 );
    MovePen(endTableX, beginTableY);
    DrawLine(-0.2 , -0.2 );

    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseYaxis)
        SetPenColor("ChoosedColor"), SetPenSize(3);
    MovePen(beginTableX, endTableY);
    DrawLine(-0.2 , -0.2 );
    MovePen(beginTableX, endTableY);
    DrawLine(0.2 , -0.2 );
}

void Add(int num) {
    int i;
    for (i = ChooseColumnNum; ChoosedColumn[i]>=num&&i>0; i--) {
        ChoosedColumn[i + 1] = ChoosedColumn[i];
    }

    ChoosedColumn[i+1] = num;
    ++ChooseColumnNum;
}
void Delete(int num) {
    int i;
    for (i = 1; i <= ChooseColumnNum; i++) {
        if (ChoosedColumn[i] == num)
            break;
    }
    for (i; i < ChooseColumnNum; i++)
        ChoosedColumn[i] = ChoosedColumn[i + 1];
    ChooseColumnNum--;
}
void DrawBaseline() {
    SetPenSize(1);
    SetPenColor("Gray");
    int i;
    for (i = 1; i <= 6; i++) {
        MovePen(beginTableX, beginTableY + (endTableY - beginTableY) / 7 * i);
        DrawLine(endTableX - beginTableX, 0);
    }   //����  

    SetPenColor("Black");
    
    for ( i = 1; i <= 6; i++) {
        string c = tostring(TableMark1 * i);
        MovePen(beginTableX - 0.1 - TextStringWidth(c), beginTableY + (endTableY - beginTableY) / 7 * i);
        DrawTextString(c);
        if(c!=NULL)
        free(c);
    }
}
void DrawXYLine() {
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseXaxis) {
        SetPenColor("ChoosedColor");
        SetPenSize(3);             //�������x
    }
    MovePen(beginTableX, beginTableY);   //������x��y��
    DrawLine(endTableX - beginTableX, 0);
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseYaxis) {
        SetPenColor("ChoosedColor");   //�������y
        SetPenSize(3);
    }
    MovePen(beginTableX, beginTableY);
    DrawLine(0, endTableY - beginTableY);
}
void drawMainPicture()
{
#if SHOWTIMEDRAW


    clock_t start_time, end_time;
    start_time = clock();   //��ȡ��ʼִ��ʱ��
#endif // SHOWTIME


    DrawDate(NowShowTable);
    DrawXYLine();   //����xy��   ���ѡ�о͸���

    DrawMainLine();  //����Ҫ������ ����������״ͼ

   // printf("DrawWithColumn is  %d\n", DrawWithColumn);
   
   
    DrawBaseline(); //��y���ϵ�������׼��
    DrawArrow();   //xy��ļ�ͷ
    DrawLastTableNum();   //����������ʾ
    Drawlegend();   //��ͼ��
#if SHOWTIMEDRAW
    end_time = clock();
    printf("%lf seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
#endif // DEBUG

    
}
void DrawTextChar(string str,double bx,double by) {   //д�ַ������֣�
    string c;
    
    if (str[1] > 0 && str[1] <= 255)   //�������λ��
    {
        c = (string)malloc(10);
        c[0] = str[0];
        c[1] = str[1];
        c[2] = 0;
    }
    else {
        c = (string)malloc(10);
        c[0] = str[0];
        c[1] = 0;
    }
  
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    if(c!=NULL)
    free(c);   //���c��NULL freeʱ��������
}

void DrawTextZH(string str,double bx,double by) {   //д����
    string c = (string )malloc(sizeof(char)*5);   //������û�㶮Ϊɶ��3freeʱ��ͳ���
    string tmp = c;
    memset(c, 0, sizeof(c));
    c[0] = str[0], c[1] = str[1];
    c[2] = 0;
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    if (tmp != NULL)
    free(tmp);  //���c��NULL freeʱ��������
}
void DrawEachDate(int tmpnum, char* Date, stu_Ptr ptr)
{
    SetPointSize(15);
    double midx = tmpnum * PerX+beginTableX;

    
    double bx= midx , by = beginTableY-0.2 ;
  
   
    MovePen(bx, by);
    SetPenColor("Black");
    if (ptr->IsShowNum) {
        SetPenColor("Red");
    }
    int i;
    for ( i = 0; Date[i]; i++) {
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
    if (IsChangeNum) {  //������ڸ�������ģʽ  ÿ�����������һ��Сѡ���
        SetPenSize(1);
        int i;
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", ptr->IsShowNum);
        stu_Ptr tmp = NowShowTable;
        if (button(GenUIID(tmpnum), bx - FontHeight / 2.5, by - FontHeight, FontHeight * 0.8, FontHeight * 0.8, "")) {
            if (!(ptr->IsShowNum))
            {
                while (tmp != NULL) { //������������ѡ��  ��ô�������Ķ���ΪFALSE��Ϊһ��ֻ�ܸ���һ��
                    if (tmp != ptr)
                        tmp->IsShowNum = FALSE;
                    tmp = tmp->next;
                }
                for (i = 1; i <= TotalColumnNum; i++) {
                    if(ChangingPtrStringNum[i]!=NULL)
                    free(ChangingPtrStringNum[i]);
                }

               
                ChangingPtr = ptr;   //���ı��ptrָ�����
                for (i = 1; i <= TotalColumnNum; i++) {
                    ChangingPtrStringNum[i] = tostring(ptr->Data[i]);
                }
            }
            else {
                ChangingPtr = NULL;   //����ָ��NULL
            }
       
                
            ptr->IsShowNum = !(ptr->IsShowNum);
           
        }
    }
   

}
