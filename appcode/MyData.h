#pragma once 
// 窗口有关坐标  MaxX和MaxY
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
int ChooseDataNum ;  //一共有多少列  就是类似 全国感染   湖北感染  全国疑似这种列
BOOL IsChooseData[10];  //是否选择了该列  
char *ChooseData[20];  //每一列的名字
char FilePath[100];   //文件路径
char *FileName[20];   //各个文件名
int FileNum;  //总文件数目

double beginTableX, beginTableY;   //开始画图的xy
double endTableX, endTableY;   //结束画图的xy
int TableMark1, TableMark2, TableMark3, TableMark4;    //第1234条y轴上的灰色线

double TableData[10][30][2];    //table数据     第一个为选的列   第二个为日期   第三个为xy


double PerX, PerY;      //单位长度的xy
double FontHeight, FontAscent, FontDescent; //见定义

char* COLOR[] = { "NULL","Red", "Blue", "Green",  "Gray", "Orange","Yellow" };    //画图颜色

int ClassDataNum[10];    //用来存放每个种类的日期数量


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
struct stu *head, *ptr;