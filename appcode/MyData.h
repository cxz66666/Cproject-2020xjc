#pragma once 
// 窗口有关坐标  MaxX和MaxY
double MaxX, MaxY;
// 上一个鼠标事件时鼠标的坐标 (lx, ly)
double lx = -1, ly = -1;
// 是否在画图

char penColor[16] = "Black";
//static int Button1, Button2, Button3;
int IsEraser;
int IsOpen;
string OpenFileName;
int MyError; //error小于0的话就报错   -1文件未打开
int IsMusic;
int IsOpenOther;
int IsOpenAdvance;

int FileTotalNum;
int ChooseDataNum = 4;
BOOL IsChooseData[10];
char *ChooseData[20];
char FilePath[100];
char *FileName[20];
int FileNum;

double beginTableX, beginTableY;
double endTableX, endTableY;
int TableMark1, TableMark2, TableMark3, TableMark4;

double TableData[10][30][2];

double PerX, PerY;
double FontHeight, FontAscent, FontDescent;

char* COLOR[] = { "NULL","Red", "Blue", "Green",  "Gray", "Orange","Yellow" };

int ClassDataNum[10];    //用来存放每个种类的日期数量


typedef struct stu* stu_Ptr;
struct stu
{
    char* Date;

    int Data[10];
    stu_Ptr next;
    char Nowcolor[16];
    char Changedcolor[16];
    BOOL IsSelect;
    double nowx, nowy;
    double XPosition[10],YPosition[10];

} *STU;
struct stu *head, *ptr;