#pragma once 

#include "genlib.h"

#define MAXCOLUMN 21  // ���ݵ�������� 
#define MAXDATE   60  // ���֧�ֵ����� 

double MaxX, MaxY; //����� ����

double lx = -1, ly = -1;
int IsRedisplay;

char penColor[16] = "Black";
//static int Button1, Button2, Button3;
int IsOpen;//�Ƿ��ڴ��ļ�  1Ϊѡ�����  2Ϊչʾ����
int IsNew;//�Ƿ����½��ļ�
string OpenFileName=NULL;   //���ļ�������
int IsSave;    //�Ƿ����ڱ�����
int MyError; //errorС��0�Ļ��ͱ���   -1�ļ�δ��

int IsHelp; 

int FileTotalNum;    //һ����������
int NowDateNum;     //��ǰչʾ�ڼ���date   ��ҳʱ����
int TotalColumnNum ;  //һ���ж�����  �������� ȫ����Ⱦ   ������Ⱦ  ȫ������������
int NowDateColumn; //��ǰչʾ�ڼ���column   ��ҳʱ����
BOOL IsChooseColumn[MAXCOLUMN];  //�Ƿ�ѡ���˸���    ֻҪ���㶼Ϊѡ�� 
int ChooseColumnNum;   //ѡ�е�column����Ŀ  �൱��һ�����ݽṹ
int ChoosedColumn[MAXCOLUMN];   //������ѡ�е�column�����  

char *ColumnName[MAXCOLUMN];  //ÿһ�е�����
char* TmpColumnName[MAXCOLUMN]; //��ʱ��ŵ�ַ
char FilePath[100];   //�ļ�·��
char *FileName[20];   //�����ļ���
int FileNum;  //���ļ���Ŀ

double beginTableX, beginTableY;   //��ʼ��ͼ��xy
double endTableX, endTableY;   //������ͼ��xy
double StaticbeginTableX, StaticbeginTableY;  //����������
double StaticendTableX, StaticendTableY;
int TableMark1, TableMark2, TableMark3, TableMark4, TableMark5,TableMark6;    //��123456��y���ϵĻ�ɫ��

double TableData[MAXCOLUMN][MAXDATE][2];    //table����     ��һ��Ϊѡ����   �ڶ���Ϊ����   ������Ϊxy
double CubicEquation[MAXCOLUMN][MAXDATE][4]; //�����η��̵�����  ��һ��Ϊ����   �ڶ���Ϊ����    �������ֱ�Ϊa b c d  ��Ӧ y=a+bx+cx^2+dx^3

double PerX, PerY;      //��λ���ȵ�xy
double FontHeight, FontAscent, FontDescent; //������

char* COLOR[] = { "NULL","TableColor1","TableColor2" ,"TableColor3" , "TableColor4" , "TableColor5" , "TableColor6" ,
"TableColor7" , "TableColor8","TableColor9","TableColor10","TableColor11","TableColor12" };    //��ͼ��ɫ

int ClassDataNum[MAXCOLUMN];    //�������ÿ�������չʾ����������


int ShowDateNum; //ѡ�е�������

int DrawWithLine, DrawWithColumn; //������ͼ����   ��ɢ��ͼ������   ��״ͼ���ܳ�������   ����������ͼ��ʾЧ���ͺܿ�ϧ��
int DrawWithColumnNow;       //��������߻���ô�����ڼ�����   �������� ��������


double ColumnWidth;    //��״ͼ�Ŀ��

double Histogram[MAXDATE][4];  //����״ͼ�ĸ�������   ��0��Ϊx  ��1��Ϊy


typedef struct CaseNode* CaseNode_Ptr;
struct CaseNode    //ÿһ��
{
    char* Date;   //����
     
    int Data[MAXCOLUMN];    //ÿһ�е�����
    CaseNode_Ptr next;   //��һ��
    char Nowcolor[16];   //��ɫ
    char Changedcolor[16];   //ѡ�е���ɫ
    BOOL IsSelect;   //�Ƿ���ʾ   ��ఴť���Ըı����״̬
    double nowx, nowy;   //
    double XPosition[MAXCOLUMN],YPosition[MAXCOLUMN];    //ÿһ�����ݵ�xyλ��
    BOOL IsShowNum;  //�Ƿ����ڸ���
}*CaseNodePtr ;
struct CaseNode *FileHead, *ptr,*FileTail;
struct CaseNode* PredictHead;  //�������ԭ�������ҵ���ͬ���ڵ��Ǹ��ڵ�  ���ֻ�Ǹ���־ ���������κ�malloc�йصĶ���
struct CaseNode* PreHead;      //������´���������  ���Ԥ�������  Ԥ�������õ�

struct CaseNode* NowShowTable;   //���ֿ���   һ����show FileHead ����չʾ���е����� һ����show Ԥ��� չʾԤ�������


BOOL IsChooseXaxis=FALSE, IsChooseYaxis = FALSE,IsChooseLine = FALSE, IsChooseHistogram = FALSE;    //�Ƿ�ѡ����xy�� �����������̵Ȳ���

double ChooseLineMoveX, ChooseLineMoveY;    // ѡ����ߵ��ƶ���x��y

int ChooseLineNum,ChooseHistogramNum;  //ѡ�е�column�����   ��1��ʼ����

BOOL IsPredict;   //�Ƿ���Ԥ��


BOOL IsChangeNum;   //�Ƿ��� ������

CaseNode_Ptr ChangingPtr;    //���ڸı��Ptr

string ChangingPtrStringNum[MAXCOLUMN];    //�������ݿ��������   ���ʾ���ChangingPtr���data�������string��

BOOL IsSavingOK;  //�Ƿ񱣴���ȷ
