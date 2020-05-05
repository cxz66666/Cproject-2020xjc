#pragma once
#include"MyData.h"
#include "Readcsv.c"
#include "MyDrawTable.c"
#include "MyPredict.c"
void DrawOpenDir();
void DrawMenu();

void HandleFileButton(int selection);
void HandleToolButton(int selection);

void DrawLeftButton(stu_Ptr Head);
void drawMainPicture();
void DrawEachDate(int tmpnum, char* Date);
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

#define   MY_DRAW_K  10  //在画table的时候 两个x直接画多少个点
#define  SHOWTIMEDRAW 0 //输出运行时间
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
    char InputWelcome[] = "您也可以输入文件全称";
    SetPenSize(2);
    char NameDemo[] = "demo.csv";
    if (!FileNum)
    {

        char tmpLabel[] = "当前目录下无csv文件";
        drawLabel(MaxX / 2 - TextStringWidth(tmpLabel) / 2, BeginY, tmpLabel);
    }
    else
    {
        char tmplabel[40] = "";
        sprintf(tmplabel, "当前目录下共有%d个csv文件", FileNum);
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
                if (ReadCSVFile(FileName[i - 1]))  //read正确返回1   不正确返回0
                {
                    if (!FileTotalNum)
                    {
                        SetPenColor("Red");
                        drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 3.5 * BoxHeight, "呜呜呜请确保文件已经关闭且不为NaN呢");
                    }
                    else
                    {
                        NowShowTable = head;
                        IsOpen = 2;   //2的时候就是可以进行画图了
                        Calculate(NowShowTable);
                       
                        return;
                    }
                }
            }
        }
    }

    static char dirName[30] = "";

    SetPenColor("TextBoxLabel");
    drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 0.5 * BoxHeight, InputWelcome); //这里的y   简单说一哈 一个boxheight是两倍的字体高度  一个按钮占1.5倍的boxheight  其中上下各空出0.25boxheight

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);
    textbox(GenUIID(0), MaxX / 2 - 1, BeginY - FileNum * BoxHeight * 1.5 - 2 * BoxHeight, 2, BoxHeight, dirName, 30); //这里的输入宽度为1 最多输30个 谁能输那么多啊
    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    if (button(GenUIID(0), MaxX / 2 + 1.5, BeginY - FileNum * BoxHeight * 1.5 - 2 * BoxHeight, 1, BoxHeight, "确认"))
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
                    drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 3.5 * BoxHeight, "呜呜呜请确保文件已经关闭且不为NaN呢");
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
            drawLabel(MaxX / 2 - TextStringWidth(InputWelcome) / 2, BeginY - FileNum * BoxHeight * 1.5 - 3.5 * BoxHeight, "请确保输入了正确的文件名哦");
        }
    };
    
}


void DrawLeftButton(stu_Ptr Head)
{
    double fH = GetFontHeight();
    int nowNum = 0;
    Head = Head->next;   //是有头节点啊啊啊啊啊嗷嗷嗷嗷哦哦哦哦哦哦

    while (Head != NULL)  
    {
        int IsSelect = Head->IsSelect;
        setButtonColors("Orange", "Red", "Black", "Red", IsSelect);
        nowNum++;
        if (button(GenUIID(nowNum), 0.1, MaxY - (1.2 * nowNum + 1.5) * GetFontHeight(), 0.08, 0.08, ""))
        {
            Head->IsSelect = !(Head->IsSelect);
            Calculate(NowShowTable);

        }
        drawLabel(0.3, MaxY - (1.2 * nowNum + 1.5) * GetFontHeight(), Head->Date);
        Head = Head->next;
    }
	int i;
    for (i=1; i <= TotalColumnNum; i++)
    {
        setButtonColors("Orange", "Red", "Black", "Red", IsChooseColumn[i]);
        if (button(GenUIID(i), 0.1, 4 - (1.4 * i + 1.5) * GetFontHeight(), 0.15, 0.15, ""))
        {
            IsChooseColumn[i] = !IsChooseColumn[i];
            if (IsChooseColumn[i]) 
                Add(i); //把i加到已经选择的里面 
            else Delete(i); //把i删去

            Calculate(NowShowTable);
        
        }
        drawLabel(0.4, 4 - (1.4 * i + 1.5) * GetFontHeight(), ColumnName[i]);
    }


    //画复原按钮   就是如果移动了xy轴或者某条曲线   则会显示这个按钮
    if (IsChooseXaxis || IsChooseYaxis || IsChooseLine) {
        setButtonColors("Orange", "Red", "Black", "Red", IsChooseColumn[i]);
        if (button(GenUIID(0), 0.95 * MaxX, 0.9 * MaxY, 1, 0.5, "复原"))
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
void DrawLastTableNum() {
    stu_Ptr tmp = tail;
    int i;
    for (i=1; i <= ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            string ShowNum = tostring(tmp->Data[column]);
            MovePen(tmp->XPosition[column] + 0.05, tmp->YPosition[column]);
            SetPenColor(COLOR[column]);
            DrawTextString(ShowNum);
            free(ShowNum);
        
    }
}
void Drawlegend()  //画图例 
{  
    double  NowX = beginTableX + PerX,NowY=beginTableY/2.5;
    int presize = GetPenSize();
    string precolor = GetPenColor();
    int i;
    for (i = 1; i <=ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            NowX += 0.8;  //0.8是两两是间隔

            MovePen(NowX, NowY);
         
           IsChooseColumn[column]==1? SetPenSize(2):SetPenSize(5);     //画的是折线还是柱
            SetPenColor(COLOR[column]);
            DrawLine(0.6, 0);
            MovePen(GetCurrentX() + 0.25, GetCurrentY());         
            DrawTextString(ColumnName[column]);

            NowX = GetCurrentX(), NowY = GetCurrentY();
            if (NowX > endTableX - PerX)   //换行
            {
                NowX = beginTableX + PerX;
                NowY -= FontHeight * 1.5;
            
            }
     
    }
    SetPenColor(precolor); //换回原来颜色
    SetPenSize(presize);   //换回原来尺寸
}
void DrawDate(stu_Ptr HEAD) {
    SetPenColor("Black");
    stu_Ptr tmp = HEAD->next;
    int tmpnum = 0;
    while (tmp != NULL) {
        if (tmp->IsSelect) {
            ++tmpnum;
            DrawEachDate(tmpnum, tmp->Date);
        }
        tmp = tmp->next;
    }      //画日期和两道线
}
void DrawMainLine() {
    
    DrawWithColumnNow = 0;   //已经画了几个柱状图了 因为 cxz设定最多画两个 所以好讨论
    int i,j;
    for (i=1; i <= ChooseColumnNum; i++) {


        SetPenSize(2);
        MovePen(beginTableX, beginTableY);
        int column = ChoosedColumn[i];
        SetPenColor(COLOR[column]);   //正常的准备工作


        if (IsChooseLine&& column == ChooseLineNum) {   //如果这根线被选中
            SetPenColor("ChoosedColor");
            SetPenSize(4); 
            
            for (j = 1; j <= ClassDataNum[column]; j++) {
                TableData[column][j][0] += ChooseLineMoveX;
                TableData[column][j][1] += ChooseLineMoveY;
            }    //把它的xy坐标改了
           
        }
            if (IsChooseColumn[column] == 1)   //1是画曲线   2是柱状图
                Cubic_Spline(TableData[column], ClassDataNum[column], MY_DRAW_K, i);
            else {
                DrawHistogram(TableData[column], ClassDataNum[column]);
            }
            if (IsChooseLine && column == ChooseLineNum) {
                for (j = 1; j <= ClassDataNum[column]; j++) {
                    TableData[column][j][0] -= ChooseLineMoveX;
                    TableData[column][j][1] -= ChooseLineMoveY;
                }    //把它的xy减了  
            }

    }   //!!!!   画线部分   核心 !!!!  曲线用到三次样条插值法  柱状图倒没啥  感觉还行 找了一整天（
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
    ChoosedColumn[++ChooseColumnNum] = num;
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
    }   //画线  

    SetPenColor("Black");
    
    for ( i = 1; i <= 6; i++) {
        string c = tostring(TableMark1 * i);
        MovePen(beginTableX - 0.1 - TextStringWidth(c), beginTableY + (endTableY - beginTableY) / 7 * i);
        DrawTextString(c);
        free(c);
    }
}
void DrawXYLine() {
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseXaxis) {
        SetPenColor("ChoosedColor");
        SetPenSize(3);             //如果高亮x
    }
    MovePen(beginTableX, beginTableY);   //两条线x轴y轴
    DrawLine(endTableX - beginTableX, 0);
    SetPenColor("Black");
    SetPenSize(1);
    if (IsChooseYaxis) {
        SetPenColor("ChoosedColor");   //如果高亮y
        SetPenSize(3);
    }
    MovePen(beginTableX, beginTableY);
    DrawLine(0, endTableY - beginTableY);
}
void drawMainPicture()
{
#if SHOWTIMEDRAW


    clock_t start_time, end_time;
    start_time = clock();   //获取开始执行时间
#endif // SHOWTIME


    DrawDate(NowShowTable);
    DrawXYLine();   //画出xy轴   如果选中就高亮

    DrawMainLine();  //最重要的曲线 啊啊还有柱状图

   // printf("DrawWithColumn is  %d\n", DrawWithColumn);
   
   
    DrawBaseline(); //画y轴上的六条基准线
    DrawArrow();   //xy轴的箭头
    DrawLastTableNum();   //最后的数字显示
    Drawlegend();   //画图例
#if SHOWTIMEDRAW
    end_time = clock();
    printf("%lf seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
#endif // DEBUG

    
}
void DrawTextChar(string str,double bx,double by) {   //写字符（数字）
    string c;
    c = (string)malloc(3);

    if (str[1] > 0 && str[1] <= 255)   //如果是两位数
    {
      
        c[0] = str[0];
        c[1] = str[1];
        c[2] = 0;
    }
    else {
       
        c[0] = str[0];
        c[1] = 0;
    }
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
   // free(c); 
}

void DrawTextZH(string str,double bx,double by) {   //写中文
    char* c = (string )malloc(3);
    c[0] = str[0], c[1] = str[1], c[2] = 0;
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    //free(c);
}
void DrawEachDate(int tmpnum, char* Date)
{
    SetPointSize(15);
    double midx = tmpnum * PerX+beginTableX;


    double bx= midx , by = beginTableY ;

    MovePen(bx, by);
    int i;
    for ( i = 0; Date[i]; i++) {
        if (Date[i] > 0 && Date[i] < 255) {  //是数字
            by -= FontHeight;
            DrawTextChar(Date + i,bx,by);
           
            if (Date[i + 1] > 0 && Date[i + 1] <= 255)
                i++; //如果数字是两位 需要把i++了

        }
        else {   //是中文
            by -= FontHeight;
            DrawTextZH(Date+i,bx,by);
            i++;
        }
     
    }
}
