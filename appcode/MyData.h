#pragma once 
// �����й�����  MaxX��MaxY
double MaxX, MaxY;
// ��һ������¼�ʱ�������� (lx, ly)
double lx = -1, ly = -1;
// �Ƿ��ڻ�ͼ

char penColor[16] = "Black";
//static int Button1, Button2, Button3;
int IsEraser;
int IsOpen;
string OpenFileName;
int MyError; //errorС��0�Ļ��ͱ���   -1�ļ�δ��
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

int ClassDataNum[10];    //�������ÿ���������������


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