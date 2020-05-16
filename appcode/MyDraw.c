#pragma once
#include"MyData.h"
#include "Readcsv.c"
#include "MyDrawTable.c"
#include "MyPredict.c"
#include "MyCreat.c"
/*声明的函数基本按照功能来了 
绝大部分采用大驼峰命名法
应该按功能来看 不能硬看
*/
void display(); //最主要的展示函数
void DrawPicture(stu_Ptr Head); //画最重要的图

void DrawMain();//Main部分
void DrawOpenDir(); //打开各个文件按钮
void DrawMenu();//工具栏
void DrawCreateNewFile();//创建新文件
void DrawStatus(); //左下角状态
void HandleFileButton(int selection);//处理工具栏的输入
void HandleToolButton(int selection);

void DrawLeftButton(stu_Ptr Head);//左侧的选择日期 选择列的显示
void drawMainPicture();
void DrawEachDate(int tmpnum, char* Date,stu_Ptr ptr);//画每一天的日期
void DrawDate(stu_Ptr HEAD);  //画下方的日期
void DrawTextZH(string str, double bx, double by);//输出中文
void DrawTextChar(string str, double bx, double by);//输出字符
void DrawArrow();//画xy箭头
void DrawLastTableNum();//画嘴上
void Drawlegend(); //画图例  
void DrawHistogram(double TableData[][2],int ClassDataNum);//画柱状图
void DrawXYLine();//画xy线
void DrawBaseline(); //画6条基准线
void DrawMainLine();//画主要的线
void Add(int num);
void Delete(int num);

void WriteTitle(); //标题函数 
void DrawVirusAll();//画病毒的函数 
void DrawVirus();
void DrawMagnifier();//画放大镜的函数 
void DrawPart(double x,double y,double degree);
void DrawWelcomeWindow();


#define   MY_DRAW_K  20  //在画table的时候 两个x直接画多少个点
#define  SHOWTIMEDRAW 0 //输出运行时间







#define titleX       7
#define titleY       10
#define textX        9
#define textY        7
#define PI           3.1415926


static double currentX=0.0,currentY=0.0; //当前画笔所在位置 



// 显示界面
/*注意为了输入中文开发者将textbox进行些许的修改 使其可以输入GBK编码的中文*/
void display()
{
    if (!IsSave&&!IsNew)   //如果不在保存界面上  就update  因为保存界面可能输入中文  使用update无法输入中文
        UpdateDisplay();
    DisplayClear();//清屏

    DrawMain(); //画下方的
    DrawMenu();//画菜单
    //先画主要的部分再画菜单  防止遮挡
}


void DrawMain()
{   
    DisplayClear();
   
     if (IsNew == 1) {       //展示图像有几种情况   如果正在新建  画出新建的情况 Isopendir选择打开的
       
        DrawCreateNewFile();
    }
    else if( IsOpen == 0){
    	DrawWelcomeWindow();//画欢迎界面 
    }
	else if (IsOpen == 1)
    {
        DrawOpenDir();//画选择文件框
    }
    else if (IsOpen == 2)    //如果读取到了该csv文件那么将isopen值设为2
    {
        
            DrawPicture(NowShowTable);  //非预测模式就按照文件里的数据画图 预测模式就按照预测的链表画图
     

        if (IsSave == 1)  //如果正在保存状态
        {
            SaveToCsv(NowShowTable);  //保存当前的链表
        }
    }
    DrawStatus();   //左下角画当前状态
}


void DrawPicture(stu_Ptr Head)
{

    DrawLeftButton(Head);   //左侧的一堆按钮

    drawMainPicture();   //主要那个表
    DrawPredict();     //画预测的输入框
   
  
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
    SetPointSize(15);
    if (IsSave)
        strcpy(NowStatus, "正在文件保存");
    else if (IsChooseXaxis)
        strcpy(NowStatus, "正在移动X轴");
    else if (IsChooseYaxis)
        strcpy(NowStatus, "正在移动Y轴");
    else if (IsChooseLine)
        strcpy(NowStatus, "正在移动曲线");
    else if (IsChooseHistogram)
        strcpy(NowStatus, "选中柱体");
    else if (IsChangeNum)
        strcpy(NowStatus, "正在更改数据");
    else if (IsPredict)
        strcpy(NowStatus, "正在进行预测");
    else if (IsOpen == 1)
        strcpy(NowStatus, "正在打开文件");
    else if (IsOpen == 2)
        sprintf(NowStatus, "正在查看%s文件", OpenFileName);
    else if (IsNew == 1)
        strcpy(NowStatus, "正在新建文件");
    else if ( IsOpen == 0);
    else
        strcpy(NowStatus, "正在摸鱼");
    
    MovePen(0.1, 0.1);

    DrawTextString(NowStatus);
}
void DrawMenu()
{
	 /*menulistFile和MenulistTool里放两个工具栏里的东西*/
	SetPointSize(16);
    static char *menuListFile[] = {"File",
                                    "New | Ctrl-N",
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
    //画出Bar的颜色
    drawMenuBar(0, y - height, GetWindowWidth(), height);
    //画出两个功能选项
    setMenuColors("MenuBar", "Black", "MenuFrameHot", "Black", 1);
    int selection;
    selection = menuList(GenUIID(0), x, y - height, w * 1.5, w * 3, height, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
    HandleFileButton(selection);//每个菜单对应handle函数
    selection = menuList(GenUIID(0), x + w * 1.5, y - height, w * 1.5, w * 3, height, menuListTool, sizeof(menuListFile) / sizeof(menuListFile[0]));
    HandleToolButton(selection);
}
void DrawOpenDir()
{   
    SetPointSize(18);
    double BoxHeight = GetFontHeight() * 2;
    double BeginY = MaxY - MaxY / 4;
    SetPenColor("TextBoxLabel");
    char InputWelcome[] = "您也可以输入文件全称";
    SetPenSize(2);
    char NameDemo[] = "demo.csv";
    if (!FileNum)//如果没找到csv文件
    {
       
        char tmpLabel[] = "当前目录下无csv文件";
        drawLabel(MaxX / 2 - TextStringWidth(tmpLabel) / 2, BeginY, tmpLabel);
    }
    else
    {
    	 //画出一共有多少个
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
                    if (!FileTotalNum)//如果当前目录没有csv文件
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
    }
    
}


void DrawLeftButton(stu_Ptr Head)
{
	
    double fH = GetFontHeight();
    int nowNum = 0;
    Head = Head->next;   //所有的数据链表是有头节点的
    

  

    
    SetPenSize(1);
    while (Head != NULL)  
    {   
        int IsSelect = Head->IsSelect;//主要用来判断是否填涂
        setButtonColors("Black", "Black", "Red", "Red", IsSelect);//注意是否填涂
        nowNum++;
       /*这里设定10个就显示翻页   只显示当前十个*/
        if (nowNum > 10 * NowDateNum&&nowNum<=10*(NowDateNum+1)) {
            if (button(GenUIID(nowNum), 0.1, MaxY - (1.2 * ((nowNum-1)%10+1) + 1.5) * FontHeight, 0.08, 0.08, ""))
            {
                Head->IsSelect = !(Head->IsSelect);
                Calculate(NowShowTable);

            }
            /*！！这些位置基本可以微调一哈  注意了！！*/
            SetPenColor("Black");
            drawLabel(0.3, MaxY - (1.2 * ((nowNum - 1) % 10 + 1) + 1.5) * FontHeight, Head->Date);
        
        }
        if (nowNum+1 > 10 * (NowDateNum + 1))
            break; //只显示10个多了就翻页
        Head = Head->next;
     
    }
    SetPenSize(2);
    SetPointSize(15); 

    
    if (NowDateNum) { //如果不是第0页就显示上一页按钮
        setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot","Black", 0);
        if (button(GenUIID(0), 0.2, MaxY - 15 * FontHeight, 1, FontHeight, "上一页"))
        { 
            IsRedisplay = 1;
            NowDateNum--;//日期的换页
        //display();
        }

    }
    if (nowNum != FileTotalNum) {
        setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
        if (button(GenUIID(0), 0.2, MaxY - 17 * FontHeight, 1, FontHeight, "下一页"))
        {
            IsRedisplay = 1;
            NowDateNum++;//日期的换页
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
                //把i加到已经选择的里面 
            else
            {
                Delete(i); //把i删去
               /* int j;
                for (j = 1; j <= ChooseColumnNum; j++)
                    printf("%d ", ChoosedColumn[j]);
                printf("\n");*/
            }
                

            Calculate(NowShowTable);
        
        }
        drawLabel(0.4, 4 - (1.4 * ((i - 1) % 4 + 1)  + 1.5) * GetFontHeight(), ColumnName[i]);

        //画是否在更改/显示数据  是一个颜色蛮好看的输入框
        if (IsChangeNum&&ChangingPtr!=NULL) {
            setTextBoxColors("TextBoxFrame", COLOR[i], "TextBoxFrameHot", COLOR[i], 0);

            textbox(GenUIID(i), 0.5 + TextStringWidth(ColumnName[i]), 4.0 - (1.4 * ((i - 1) % 4 + 1) + 1.5) * GetFontHeight(), 1.5, FontHeight*1.2, ChangingPtrStringNum[i], 10);
        }

        if (NowDateColumn) { //如果不在第一页
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, 4 - 9 * FontHeight, 1, FontHeight, "上一页"))
            {
                IsRedisplay = 1;
                NowDateColumn--;   //列的换页
                //display();
            }
        }

        if ((NowDateColumn + 1) * 4 < TotalColumnNum) { //如果不在最后一页
            setButtonColors("DirSelectionFrame", "Black", "DirSelectionFrameHot", "Black", 0);
            if (button(GenUIID(0), 0.2, 4 - 11 * FontHeight, 1, FontHeight, "下一页"))
            {
                IsRedisplay = 1;
                NowDateColumn++;//列的换页
                //display();
            }

        }

    }
    static char ErrorAns[20];  //放置检查输入返回的值
    //画确认按钮  确认之后立刻使用更新
    if (IsChangeNum&&ChangingPtr!=NULL) {
        setButtonColors("Orange", "Red", "Black", "Red", 0);
        if (button(GenUIID(0), 1.5, 0.9 , 0.8, 0.4, "确认"))
        {
            if (CheckChangedNum(ChangingPtrStringNum, ErrorAns)) {//传数据和返回的提示语数组
                Calculate(NowShowTable);//注意需要重新计算
               
            }
            drawLabel(2.5, 0.9, ErrorAns);
        }
    }

    //画复原按钮   就是如果移动了xy轴或者某条曲线   则会显示这个按钮
    if (IsChooseXaxis || IsChooseYaxis || IsChooseLine) {
        setButtonColors("Orange", "Red", "Black", "Black", IsChooseColumn[i]);
        if (button(GenUIID(0), 0.95 * MaxX, 0.9 * MaxY, 1, 0.5, "复原"))
        {
        	
        	  /*将所有改变还原
            改变包括是否选中 选中的列数   移动的长度   图表结束位置*/
            IsChooseXaxis = IsChooseYaxis = IsChooseLine = 0;
            ChooseLineNum = 0;
            ChooseLineMoveX = ChooseLineMoveY = 0;
            endTableX = StaticendTableX;
            endTableY = StaticendTableY;
            Calculate(NowShowTable);//务必记住重新计算
        }
    }



}

void HandleFileButton(int selection)
{
    switch (selection) {
    
    case 1:
        IsNew = 1;    //对于每个操作改变data里的设定值
        break;
    case 2:
        IsOpen = 1;  //进入选择csv文件界面
        IsNew = 0;
        InitData();   //提前把数据初始化了

        break;
    case 3:
        IsOpen = 0;
        IsNew = 0; 
        MyFree(NowShowTable);//close时候要把申请的节点free了 
        FreeColumn(TmpColumnName); //再把申请的存储列的空间free了
        break;
    case 4:
        IsSave = 1;
        break;
    case 5:
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


/*作用
画尾部的数字显示
如果某数据被选中  那么显示所有日期的数据

*/
void DrawLastTableNum() {
    stu_Ptr tmp = tail;//注意tail放的是所有选中日期的最后一个节点
    int i;
    for (i=1; i <= ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            string ShowNum = tostring(tmp->Data[column]); //这里申请出来的最后需要free掉
            SetPenColor(COLOR[column]); //将颜色变为设定的颜色
            if (column != ChooseLineNum&&column!=ChooseHistogramNum) {
                MovePen(tmp->XPosition[column] + 0.05, tmp->YPosition[column]);
                DrawTextString(ShowNum);
            }
         
            else  if (column == ChooseLineNum||column==ChooseHistogramNum) { //如果该列是选中的直线或者柱状图
               
               
                stu_Ptr tmp1 = NowShowTable->next;//开始将每个选中的日期都画数字
                
                while (tmp1 != NULL) {
                    if (tmp1->IsSelect) {
                        string ShowNum1 = tostring(tmp1->Data[column]);
                        if (column == ChooseLineNum)//如果是选的直线
                            MovePen(tmp1->XPosition[column] + ChooseLineMoveX + 0.05, tmp1->YPosition[column] + ChooseLineMoveY + 0.2);
                        else //否则就是选的列，
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

void Drawlegend()  //画图例 
{  
    double  NowX = beginTableX + PerX,NowY=beginTableY/4;
    int presize = GetPenSize();//拿到当前笔的数据，之后会恢复
    string precolor = GetPenColor();
    int i;
    for (i = 1; i <=ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            NowX += 0.8;  //0.8是两两是间隔

            MovePen(NowX, NowY);
         
           IsChooseColumn[column]==1? SetPenSize(2):SetPenSize(5);     //画的是折线还是柱   1就是折现  2是柱
            SetPenColor(COLOR[column]);
            DrawLine(0.6, 0);//画图例的线
            MovePen(GetCurrentX() + 0.25, GetCurrentY());         
            DrawTextString(ColumnName[column]);//写列信息

            NowX = GetCurrentX(), NowY = GetCurrentY();
            if (NowX > endTableX - PerX)   //换行
            {
                NowX = beginTableX + PerX;   //注意这个换行
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
            DrawEachDate(tmpnum, tmp->Date,tmp);//画每一天的日期  传参数为当前过了多少天，主要用来计算显示的横坐标位置  和日期
        }
        tmp = tmp->next;
    }      //画日期和两道线
}
void DrawMainLine() {
    
    DrawWithColumnNow = 0;   //已经画了几个柱状图了 因为 cxz设定最多画两个 所以好讨论
    int i,j;
    for (i=1; i <= ChooseColumnNum; i++) {

        /*正常的准备工作
        size  笔的位置
        */
        SetPenSize(2);
        MovePen(beginTableX, beginTableY);
        int column = ChoosedColumn[i];
        SetPenColor(COLOR[column]);   //正常的准备工作


        if (IsChooseLine&& column == ChooseLineNum) {   //如果这根线被选中
            SetPenColor("ChoosedColor");
            SetPenSize(4); 
            //把这条线坐标全部加上偏移量  之后再减去
            for (j = 1; j <= ClassDataNum[column]; j++) {
                TableData[column][j][0] += ChooseLineMoveX;
                TableData[column][j][1] += ChooseLineMoveY;
            }    //把它的xy坐标改了
           
        }
        if (IsChooseHistogram && column == ChooseHistogramNum)
        {
            SetPenColor("ChoosedColor");
            SetPenSize(2);
        }
            if (IsChooseColumn[column] == 1)   //1是画曲线   2是柱状图
                //1用三次样条插值法 
				Cubic_Spline(TableData[column], ClassDataNum[column], MY_DRAW_K, column);
            else {
                //2用画柱状图常规算法
				DrawHistogram(TableData[column], ClassDataNum[column]);
            }
            if (IsChooseLine && column == ChooseLineNum) {
                for (j = 1; j <= ClassDataNum[column]; j++) {
                    TableData[column][j][0] -= ChooseLineMoveX;
                    TableData[column][j][1] -= ChooseLineMoveY;
                }   //由于之前加上了偏移量  现在要减去  
            }

    }   //!!!!   画线部分   核心 !!!!  曲线用到三次样条插值法  柱状图倒没啥  感觉还行 找了一整天（
}
void DrawArrow() {
    SetPenColor("Black");
    SetPenSize(1);
     /*X轴  分是否被选中讨论*/
    if (IsChooseXaxis)
        SetPenColor("ChoosedColor"), SetPenSize(3);
    MovePen(endTableX, beginTableY);
    DrawLine(-0.2, 0.2 );
    MovePen(endTableX, beginTableY);
    DrawLine(-0.2 , -0.2 );
    /*Y轴  分是否被选中讨论*/
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
        if (ChoosedColumn[i] == num)//找到该num
            break;
    }
    for (i; i < ChooseColumnNum; i++)//每一位往前移动
        ChoosedColumn[i] = ChoosedColumn[i + 1];
    ChooseColumnNum--;
}
void DrawBaseline() {
	//六条基准线的属性设置
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
        if(c!=NULL)
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
    
    if (str[1] > 0 && str[1] <= 255)   //如果是两位数
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
    free(c);   //如果c是NULL free时候会出问题
}

void DrawTextZH(string str,double bx,double by) {   //写中文
    string c = (string )malloc(sizeof(char)*5);   //开3free时候报错
    string tmp = c;
    memset(c, 0, sizeof(c));
    c[0] = str[0], c[1] = str[1];
    c[2] = 0;
    MovePen(bx - TextStringWidth(c) / 2, by);
    DrawTextString(c);
    if (tmp != NULL)
    free(tmp);  //如果c是NULL free时候会出问题
}
void DrawEachDate(int tmpnum, char* Date, stu_Ptr ptr)
{
    SetPointSize(15);
    double midx = tmpnum * PerX+beginTableX;

    
    double bx= midx , by = beginTableY-0.2 ;
  //对每个日期都进行判断  颜色、是否被选中、位置
   
    MovePen(bx, by);
    SetPenColor("Black");
    if (ptr->IsShowNum) {
        SetPenColor("Red");
    }
    int i;
    for ( i = 0; Date[i]; i++) {
        if (Date[i] > 0 && Date[i] < 255) {  //是数字
            by -= FontHeight;
            DrawTextChar(Date + i,bx,by);
           
            if (Date[i + 1] > 0 && Date[i + 1] <= 255)
                i++; //如果数字是两位 需要把i++ 因为已经随着drawtextchar输出了

        }
        else {   //是中文
            by -= FontHeight;
            DrawTextZH(Date+i,bx,by);
            i++;
        }
    }
    if (IsChangeNum) {  //如果处在更改数据模式  每个日期下面放一个小选择框
        SetPenSize(2);
        int i;
        setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", ptr->IsShowNum);
        stu_Ptr tmp = NowShowTable;
        if (button(GenUIID(tmpnum), bx - FontHeight / 2.5, by - FontHeight, FontHeight * 0.8, FontHeight * 0.8, "")) {
            if (!(ptr->IsShowNum))
            {
                while (tmp != NULL) { //如果这个即将被选中  那么把其他的都置为FALSE因为一次只能更改一个
                    if (tmp != ptr)
                        tmp->IsShowNum = FALSE;
                    tmp = tmp->next;
                }
                for (i = 1; i <= TotalColumnNum; i++) {
                    if(ChangingPtrStringNum[i]!=NULL)
                    free(ChangingPtrStringNum[i]);
                }

               
                ChangingPtr = ptr;   //将改变的ptr指向这个
                for (i = 1; i <= TotalColumnNum; i++) {
                    ChangingPtrStringNum[i] = tostring(ptr->Data[i]);
                    printf("%s\n", ChangingPtrStringNum[i]);
                }
            }
            else {
                ChangingPtr = NULL;   //否则指向NULL
            }
       
                
            ptr->IsShowNum = !(ptr->IsShowNum);//按一下就切换是否被选中
           
        }
    }
   

}


void DrawWelcomeWindow(){
	
	
	
		//获得窗口尺寸 
	currentX = GetWindowWidth();
    currentY = GetWindowHeight();
	
	
	//定义了一堆颜色 
	
	
	
	
	WriteTitle();
	DrawVirusAll();

	DrawMagnifier();

}


void WriteTitle(){
    SetPointSize(70); 
    SetPenColor("TitleColor");
    SetPenSize(8); 
	SetFont("圆体");
	drawLabel(titleX,titleY,"战疫，我们在一起");
	SetFont("宋体");
	SetPointSize(25);
	SetPenColor("TextColor"); 
	drawLabel(textX,textY,"欢迎使用疫情数据分析工具") ;
}


 
void DrawVirusAll(){
	MovePen(9.9,3);
	DrawVirus();
    MovePen(11.5,3);
    DrawVirus();   
    MovePen(10.7,4.3);
    DrawVirus();
    
}
 
void DrawVirus(){
	double cx=0.0,cy=0.0;
	int i=0;
	cx=2;
	cy=2;
	SetPenSize(3);
	SetPenColor("VirusColor");
	for(i=0;i<8;i++){
	DrawArc(0.24,45*i,45);
	cx=GetCurrentX();
	cy=GetCurrentY();
	DrawPart(cx,cy,45*i+45);
	} 
	
} 
 
 void DrawPart(double x,double y,double degree){
 	MovePen(x,y);
 	double px=0.0,py=0.0;
 	px=cos(degree/180*PI);
 	py=sin(degree/180*PI);
 	DrawLine(0.15*px,0.15*py);
 	DrawLine(0.06*py,-0.06*px);
 	DrawLine(0.06*px,0.06*py);
 	DrawLine(-0.18*py,0.18*px);
 	DrawLine(-0.06*px,-0.06*py);
 	DrawLine(0.06*py,-0.06*px);
 	DrawLine(-0.15*px,-0.15*py);
}

void DrawMagnifier(){
    MovePen(14.7,4.5);
    SetPenSize(1);
    SetPenColor("CircleColor");
    StartFilledRegion(0.2);
    DrawArc(1,0,360);
    EndFilledRegion();
    SetPenColor("WoodColor");
    SetPenSize(6);
    DrawArc(1,0,360);
    MovePen(14.45,4.8);
    SetPenColor("White");
    SetPenSize(7);
    DrawArc(1,30,60);
    MovePen(14.5,3.85);
    SetPenSize(6);
    SetPenColor("WoodColor");
    StartFilledRegion(0.5);
    DrawLine(1.1,-1.1);
    DrawLine(-0.2,-0.2);
	DrawLine(-1.1,1.1);
	DrawLine(0.2,0.2); 
	EndFilledRegion();
}











