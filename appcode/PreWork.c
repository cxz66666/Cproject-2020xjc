#pragma once

#include"MyData.h"
#include <direct.h>
#define  SHOWTIMEPRE 0 //输出运行时间
#define  DISPLAY   1  //每过400ms进行重新display  因为担心有些操作者按完按钮后不进行鼠标移动无法更新
#define  REFRESHTIME  400

void PreWork();
void FindCSV();
void DefineMycolor();
BOOL CheckName(char* name);
void Calculate(stu_Ptr HEAD);
void AssignTable();
BOOL CheckChangedNum(string str[],string ans);
void InitData();
void  FreeColumn(char *Ptr[]);
void PreWork()
{
    /*定义许多常量  防止以后再获取浪费资源*/
    FontHeight = GetFontHeight();
    FontAscent = GetFontAscent();
    FontDescent = GetFontDescent();
  	//printf("%lf %lf %lf \n", FontHeight, FontAscent, FontDescent);
    
    /*调用direct.h里的currentDirectory接口获取当前目录 并放到FilePath里*/
    GetCurrentDirectory(100, FilePath); 
    //printf("%s\n", FilePath);
    FindCSV(); //找到当前目录下的csv文件并放到FileName中
    MaxX = GetWindowWidth();
    MaxY = GetWindowHeight();
  
    DefineMycolor(); //把需要的颜色全部注册

    /*一下静态数据以后不会变动*/
   	StaticbeginTableX= beginTableX = GetWindowWidth() * 0.2,
    StaticbeginTableY= beginTableY = GetWindowHeight() * 0.2;
  	StaticendTableX=endTableX = GetWindowWidth() * 0.8, 
      StaticendTableY= endTableY = GetWindowHeight() * 0.9;
    /*for (int i = 0; i < FileNum; i++)
        printf("%s\n", FileName[i]);*/
   memset(ChangingPtrStringNum, 0, sizeof(ChangingPtrStringNum));
   
}
void FindCSV()
{
    //"E:\\linux\\Compressed\\LibGraphics2019Hanoi\\demoprj-vs2017\\*.c";
    strcat(FilePath, "\\*.csv");
    //printf("%s", FilePath);
    struct _finddata_t data;
    long handle = _findfirst(FilePath, &data);

    if (handle < 0)
    {
        return;
    }

    int nRet = (handle < 0) ? -1 : 1;
    while (nRet >= 0)
    {
        if (data.attrib == _A_SUBDIR) // 如果是目录
            ;
        else
        {

            FileName[FileNum] = (char *)malloc(sizeof(data.name) + 1);
            strcpy(FileName[FileNum++], data.name);
        }

        nRet = _findnext(handle, &data);
    }
    _findclose(handle); // 关闭当前句柄
}
void DefineMycolor()
{

    DefineColor("MenuFrame", 232.0 / 255, 237.0 / 255, 239.0 / 255); //菜单框
    DefineColor("MenuFrameHot", 236.0 / 255, 232.0 / 255, 223.0 / 255);

    DefineColor("MenuBar", 227.0 / 255, 235.0 / 255, 255.0 / 255); //bar框
    DefineColor("TextBoxFrame", 155.0 / 255, 156.0 / 255, 155.0 / 255);

    DefineColor("TextBoxFrameHot", 124.0 / 255, 205.0 / 255, 244.0 / 255);
    DefineColor("TextBoxLabel", 11.0 / 255, 19.0 / 255, 43.0 / 255); //输入框

    DefineColor("DirSelectionFrameHot", 91.0 / 255, 192.0 / 255, 235.0 / 255); //文件选择框
    DefineColor("DirSelectionFrame", 112.0 / 255, 214.0 / 255, 1.0);
    DefineColor("ChoosedColor", 254.0 / 255, 95.0 / 255, 85.0 / 255); //选中后的颜色

    DefineColor("DataButton", 218.0 / 255, 215.0 / 255, 205.0 / 255); //日期选择框的颜色

    DefineColor("TableColor1", 239.0/255, 106.0/255, 46.0/255);
    DefineColor("TableColor2", 64.0/255, 199.0/255, 120.0/255);
    DefineColor("TableColor3", 37.0/255, 74.0/255, 178.0/255);
    DefineColor("TableColor4", 255.0/255, 33.0/255, 127.0/255);
    DefineColor("TableColor5", 204.0/255, 0, 213.0/255);
    DefineColor("TableColor6", 102.0/255, 44.0/255, 145.0/255);
    DefineColor("TableColor7", 23.0/255, 163.0/255, 152.0/255);
    DefineColor("TableColor8", 255.0 / 255, 198.0 / 255, 255.0 / 255);
    DefineColor("TableColor9", 51.0/255, 49.0/255, 46.0/255);
    DefineColor("TableColor10", 253.0/255, 255.0/255, 182.0/255);
    DefineColor("TableColor11", 202.0/255, 255.0/255, 191.0/255);
    DefineColor("TableColor12", 155.0/255, 246.0/255, 255.0/255);

}

BOOL CheckName(char* name)
{
    if (!strlen(name))
        return 0;
    else
    {
    	int i;
        for (i = 0; i < FileNum; i++)
        {
            if (!strcmp(name, FileName[i]))
                return 1;
        }
    }
    return 0;
}
void AssignTable() {   //分配是用柱状图还是折线图
   //一共多少列被选中了
   int i;
    for (i=1; i <= ChooseColumnNum; i++) {
        int column = ChoosedColumn[i];
            IsChooseColumn[column] = 1;   //无论是1还是2 都先设为1
    }

    if (ChooseColumnNum && ChooseColumnNum <4)      //2代表柱状图  1代表折线图  原来默认是1  那我只要改成2 就行
    {
        int change1 = ChoosedColumn[1];    //把第一个选中的置为2
        IsChooseColumn[change1] = 2;
      
        DrawWithColumn = 1;
        DrawWithLine = TotalColumnNum - 1;
    }
    else if (ChooseColumnNum >= 4)
    {
        int change1 = ChoosedColumn[1],change2 = ChoosedColumn[2];
        IsChooseColumn[change1] = 2, IsChooseColumn[change2] = 2;
        DrawWithColumn = 2;
        DrawWithLine = TotalColumnNum - 2;

    }
        
        
}
/*主要检查数据里有没有点或者不是数字*/
BOOL CheckChangedNum(string str[], string ans) {
    int i,j;
    for (i = 1; i <= TotalColumnNum; i++) {
        for (j = 0; str[i][j]; j++) {     //如果有点或者ASCII码不是数字的
            if (str[i][j] == '.'||(str[i][j]<48||str[i][j]>58)) {
                strcpy(ans, "请检测数据");
                return FALSE;
            }
        }
        /*注意atoi返回0则表示有问题   返回数值表示没问题*/
        if (!atoi(str[i]))   //如果返回0就是有问题！！！
        {
            strcpy(ans, "请检查数据");
            return FALSE;
        }
    }
    //将状态改为更新成功
    strcpy(ans, "更新成功");

    for (i = 1; i <= TotalColumnNum; i++) {
    
        ChangingPtr->Data[i] = atoi(str[i]);    //改变Ptr里的各个数据
    }
   
    return TRUE;
}

void Calculate(stu_Ptr HEAD)
{
#if  SHOWTIMEPRE
    clock_t start_time, end_time;
    start_time = clock();   //获取开始执行时间
#endif //  SHOWTIME

    if (HEAD == NULL) {
        printf("内存错误无法计算\n");
        return;
    }

    memset(CubicEquation, 0, sizeof(CubicEquation));   //每次计算出的方程都不一样  都得清空了再说
    int ShowNum = 0;
    int Maxnum = 0;
    stu_Ptr tmp = HEAD->next;   //所有的都有头节点的  注意了
    while (tmp != NULL)  
    {
     
        if (tmp->IsSelect)
        {
            tail = tmp;   //tail表示的是最后一个被选中的日期
            ShowNum++;
            int i; 
            for (i=1; i <= ChooseColumnNum; i++)
            {
                int column = ChoosedColumn[i];
                
                    Maxnum = max(Maxnum, tmp->Data[column]);
                
            }
        }

        tmp = tmp->next;
    }
    ShowDateNum = ShowNum;   //显示的日期数目
    //printf("Maxnum=%d   ShowNum=%d\n", Maxnum,ShowNum);
    if (Maxnum > 1000) {

        (Maxnum / 6) % 100 > 50 ? (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 100) + 100) : (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 100));

    }
    else if (Maxnum > 100) {
        (Maxnum / 6) % 10 > 5 ? (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 10) + 10) : (TableMark1 = ((Maxnum / 6) - (Maxnum / 6) % 10));

    }
    else TableMark1 = 10;
    TableMark2 = TableMark1 * 2;
    TableMark3 = TableMark1 * 3;
    TableMark4 = TableMark1 * 4;
    TableMark5 = TableMark1 * 5;
    TableMark6 = TableMark1 * 6;
     PerY = (endTableY - beginTableY) / 7 / TableMark1;
    PerX = (endTableX - beginTableX) / (ShowNum + 1.0);
    //printf("%lf %lf \n", endTableX, endTableY);
    
    
    tmp = HEAD->next;
    
  
    int tmpX = 0;
    //TableData   第一层是选择的种类   第二层是各个日期   第三层是x y
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
   // printf("px py分别为%.3lf %.3lf\n", PerX, PerY);

    while (tmp != NULL) {
        if (tmp->IsSelect) {
           
            tmpX++;
            int  i; 
            for (i=1; i <= ChooseColumnNum; i++) {
                 {
                    int column = ChoosedColumn[i];
                    
                    tmp->XPosition[column] = tmpX * PerX + beginTableX;                 //对这个TableData和结构体里的X，Yposition赋同样的值
                    TableData[column][++ClassDataNum[column]][0] = tmpX * PerX + beginTableX;
                

                    tmp->YPosition[column] = beginTableY + tmp->Data[column] * PerY;
                    TableData[column][ClassDataNum[column]][1] = beginTableY + tmp->Data[column] * PerY;   //对y赋值
                 //   printf("%d\n", tmp->Data[column]);
                  
                  //  printf("这是第%d个元素 第%d种数据 其xy分别为%.3lf %.3lf\n", tmpX, i, tmp->XPosition[column], tmp->YPosition[column]);
                }
            }
         
        }
        tmp = tmp->next;
    }
    AssignTable();//把折线图的设为1   柱状图设为2     柱状图数目不超过两个 尽量平均分配
    ColumnWidth = min(0.2, 0.25 * PerX);
    
#if  SHOWTIMEPRE
    end_time = clock();     //获取结束时间
    double Times = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("计算用时为%lf seconds\n", Times);

#endif //  SHOWTIME

}
void InitData() {
    
    memset(IsChooseColumn, 0, sizeof(IsChooseColumn));
    memset(ChoosedColumn, 0, sizeof(ChoosedColumn));
    ChooseColumnNum = 0;
    TotalColumnNum = 0;
    NowDateColumn = 0;
    memset(ClassDataNum, 0, sizeof(ClassDataNum));
    ChooseLineMoveX = ChooseLineMoveY = 0;
    ChooseLineNum = ChooseHistogramNum = 0;
    memset(ChangingPtrStringNum, 0, sizeof(ChangingPtrStringNum));
    ChangingPtr = NULL;
    IsPredict = IsChangeNum = IsSave=FALSE;
    IsRedisplay = 0;
    IsChooseXaxis = FALSE, IsChooseYaxis = FALSE, IsChooseLine = FALSE, IsChooseHistogram = FALSE;
    DrawWithLine = DrawWithColumn = DrawWithColumnNow = 0;
    FileTotalNum = 0;
    NowDateNum = NowDateColumn = 0;
}

void  FreeColumn(char* Ptr[]) {
    for (int i = 1; i <= TotalColumnNum; i++) {
        if (Ptr[i] != NULL)
            if(Ptr[i][0] != 0)
            free(Ptr[i]);
    }
}