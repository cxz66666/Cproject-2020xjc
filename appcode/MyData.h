#pragma once 

#include "genlib.h"

#define MAXCOLUMN 13  // 数据的最多列数 
#define MAXDATE   60  // 最多支持的日期 

double MaxX, MaxY; //最大宽度 长度

double lx = -1, ly = -1;
int IsRedisplay;

char penColor[16] = "Black";
//static int Button1, Button2, Button3;
int IsOpen;//是否在打开文件  1为选择界面  2为展示数据
int IsNew;//是否在新建文件
string OpenFileName=NULL;   //打开文件的名字
int IsSave;    //是否正在保存了
int MyError; //error小于0的话就报错   -1文件未打开
int IsMusic; //放音乐就算了
int IsOpenOther;
int IsOpenAdvance;
int IsHelp; 

int FileTotalNum;    //一共多少日期
int NowDateNum;     //当前展示第几列date   翻页时候用
int TotalColumnNum ;  //一共有多少列  就是类似 全国感染   湖北感染  全国疑似这种列
int NowDateColumn; //当前展示第几列column   翻页时候用
BOOL IsChooseColumn[MAXCOLUMN];  //是否选择了该列    只要非零都为选中 
int ChooseColumnNum;   //选中的column的数目  相当于一个数据结构
int ChoosedColumn[MAXCOLUMN];   //放所有选中的column的序号  

char *ColumnName[MAXCOLUMN];  //每一列的名字
char* TmpColumnName[MAXCOLUMN]; //暂时存放地址
char FilePath[100];   //文件路径
char *FileName[20];   //各个文件名
int FileNum;  //总文件数目

double beginTableX, beginTableY;   //开始画图的xy
double endTableX, endTableY;   //结束画图的xy
double StaticbeginTableX, StaticbeginTableY;  //定死的数据
double StaticendTableX, StaticendTableY;
int TableMark1, TableMark2, TableMark3, TableMark4, TableMark5,TableMark6;    //第123456条y轴上的灰色线

double TableData[MAXCOLUMN][MAXDATE][2];    //table数据     第一个为选的列   第二个为日期   第三个为xy
double CubicEquation[MAXCOLUMN][MAXDATE][4]; //放三次方程的数据  第一个为各列   第二个为日期    第三个分别为a b c d  对应 y=a+bx+cx^2+dx^3

double PerX, PerY;      //单位长度的xy
double FontHeight, FontAscent, FontDescent; //见定义

char* COLOR[] = { "NULL","TableColor1","TableColor2" ,"TableColor3" , "TableColor4" , "TableColor5" , "TableColor6" ,
"TableColor7" , "TableColor8","TableColor9","TableColor10","TableColor11","TableColor12" };    //画图颜色

int ClassDataNum[MAXCOLUMN];    //用来存放每个种类的展示的日期数量


int ShowDateNum; //选中的日期数

int DrawWithLine, DrawWithColumn; //用折线图画的   用散点图画的数   柱状图不能超锅两个   超过两个画图显示效果就很可惜了
int DrawWithColumnNow;       //如果用折线画那么画到第几个了   反正就俩 大力讨论


double ColumnWidth;    //柱状图的宽度

double Histogram[MAXDATE][4];  //存柱状图的各个数据   【0】为x  【1】为y


typedef struct stu* stu_Ptr;
struct stu    //每一天
{
    char* Date;   //日期
     
    int Data[10];    //每一行的数据
    stu_Ptr next;   //下一个
    char Nowcolor[16];   //颜色
    char Changedcolor[16];   //选中的颜色
    BOOL IsSelect;   //是否显示   左侧按钮可以改变这个状态
    double nowx, nowy;   //
    double XPosition[10],YPosition[10];    //每一个数据的xy位置
    BOOL IsShowNum;  //是否正在更改
} *STU;
struct stu *head, *ptr,*tail;
struct stu* PredictHead;  //这个放在原链表中找到相同日期的那个节点  这个只是个标志 不对它做任何malloc有关的东西
struct stu* PreHead;      //这个放新创建的链表  存放预测的数据  预测数据用的

struct stu* NowShowTable;   //两种可能   一种是show head 就是展示现有的数据 一种是show 预测的 展示预测的数据


BOOL IsChooseXaxis=FALSE, IsChooseYaxis = FALSE,IsChooseLine = FALSE, IsChooseHistogram = FALSE;    //是否选中了xy轴 进行拉伸缩短等操作

double ChooseLineMoveX, ChooseLineMoveY;    // 选择的线的移动的x，y

int ChooseLineNum,ChooseHistogramNum;  //选中的column的序号   从1开始计数

BOOL IsPredict;   //是否在预测


BOOL IsChangeNum;   //是否在 改数据

stu_Ptr ChangingPtr;    //正在改变的Ptr

string ChangingPtrStringNum[20];    //更改数据框里的数据   本质就是ChangingPtr里的data数据里的string化

BOOL IsSavingOK;  //是否保存正确
