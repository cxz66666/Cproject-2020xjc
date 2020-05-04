#pragma once 

#include "genlib.h"

double MaxX, MaxY; //最大宽度 长度

double lx = -1, ly = -1;


char penColor[16] = "Black";
//static int Button1, Button2, Button3;
int IsOpen;//是否在打开文件  1为选择界面  2为展示数据
string OpenFileName;   //打开文件的名字
int MyError; //error小于0的话就报错   -1文件未打开
int IsMusic; //放音乐就算了
int IsOpenOther;
int IsOpenAdvance;

int FileTotalNum;    //一共多少日期
int TotalColumnNum ;  //一共有多少列  就是类似 全国感染   湖北感染  全国疑似这种列
BOOL IsChooseColumn[13];  //是否选择了该列    只要非零都为选中 
int ChooseColumnNum;   //选中的column的数目
int ChoosedColumn[13];   //放所有选中的column的序号  

char *ColumnName[20];  //每一列的名字
char FilePath[100];   //文件路径
char *FileName[20];   //各个文件名
int FileNum;  //总文件数目

double beginTableX, beginTableY;   //开始画图的xy
double endTableX, endTableY;   //结束画图的xy
double StaticbeginTableX, StaticbeginTableY;  //定死的数据
double StaticendTableX, StaticendTableY;
int TableMark1, TableMark2, TableMark3, TableMark4, TableMark5,TableMark6;    //第1234条y轴上的灰色线

double TableData[13][30][2];    //table数据     第一个为选的列   第二个为日期   第三个为xy
double CubicEquation[13][50][4]; //放三次方程的数据  第一个为各列   第二个为日期    第三个分别为a b c d  对应 y=a+bx+cx^2+dx^3

double PerX, PerY;      //单位长度的xy
double FontHeight, FontAscent, FontDescent; //见定义

char* COLOR[] = { "NULL","TableColor1","TableColor2" ,"TableColor3" , "TableColor4" , "TableColor5" , "TableColor6" ,
"TableColor7" , "TableColor8","TableColor9","TableColor10","TableColor11","TableColor12" };    //画图颜色

int ClassDataNum[13];    //用来存放每个种类的展示的日期数量


int ShowDateNum; //选中的日期数

int DrawWithLine, DrawWithColumn; //用折线图画的   用散点图画的数   折线图不能超锅两个   超过两个画图显示效果就很可惜了
int DrawWithColumnNow;       //如果用折线画那么画到第几个了   反正就俩 大力讨论


double ColumnWidth;    //柱状图的宽度




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

} *STU;
struct stu *head, *ptr,*tail;


BOOL IsChooseXaxis, IsChooseYaxis,IsChooseLine;    //是否选中了xy轴 进行拉伸缩短等操作

double ChooseLineMoveX, ChooseLineMoveY;    // 选择的线的移动的x，y
int ChooseLineNum;  //选中的column的序号   从1开始计数
