#pragma once 

#include "genlib.h"

double MaxX, MaxY; //����� ����

double lx = -1, ly = -1;


char penColor[16] = "Black";
//static int Button1, Button2, Button3;
int IsOpen;//�Ƿ��ڴ��ļ�  1Ϊѡ�����  2Ϊչʾ����
string OpenFileName;   //���ļ�������
int MyError; //errorС��0�Ļ��ͱ���   -1�ļ�δ��
int IsMusic; //�����־�����
int IsOpenOther;
int IsOpenAdvance;

int FileTotalNum;    //һ����������
int TotalColumnNum ;  //һ���ж�����  �������� ȫ����Ⱦ   ������Ⱦ  ȫ������������
BOOL IsChooseColumn[13];  //�Ƿ�ѡ���˸���    ֻҪ���㶼Ϊѡ�� 
int ChooseColumnNum;   //ѡ�е�column����Ŀ
int ChoosedColumn[13];   //������ѡ�е�column�����  

char *ColumnName[20];  //ÿһ�е�����
char FilePath[100];   //�ļ�·��
char *FileName[20];   //�����ļ���
int FileNum;  //���ļ���Ŀ

double beginTableX, beginTableY;   //��ʼ��ͼ��xy
double endTableX, endTableY;   //������ͼ��xy
double StaticbeginTableX, StaticbeginTableY;  //����������
double StaticendTableX, StaticendTableY;
int TableMark1, TableMark2, TableMark3, TableMark4, TableMark5,TableMark6;    //��1234��y���ϵĻ�ɫ��

double TableData[13][30][2];    //table����     ��һ��Ϊѡ����   �ڶ���Ϊ����   ������Ϊxy
double CubicEquation[13][50][4]; //�����η��̵�����  ��һ��Ϊ����   �ڶ���Ϊ����    �������ֱ�Ϊa b c d  ��Ӧ y=a+bx+cx^2+dx^3

double PerX, PerY;      //��λ���ȵ�xy
double FontHeight, FontAscent, FontDescent; //������

char* COLOR[] = { "NULL","TableColor1","TableColor2" ,"TableColor3" , "TableColor4" , "TableColor5" , "TableColor6" ,
"TableColor7" , "TableColor8","TableColor9","TableColor10","TableColor11","TableColor12" };    //��ͼ��ɫ

int ClassDataNum[13];    //�������ÿ�������չʾ����������


int ShowDateNum; //ѡ�е�������

int DrawWithLine, DrawWithColumn; //������ͼ����   ��ɢ��ͼ������   ����ͼ���ܳ�������   ����������ͼ��ʾЧ���ͺܿ�ϧ��
int DrawWithColumnNow;       //��������߻���ô�����ڼ�����   �������� ��������


double ColumnWidth;    //��״ͼ�Ŀ��




typedef struct stu* stu_Ptr;
struct stu    //ÿһ��
{
    char* Date;   //����
     
    int Data[10];    //ÿһ�е�����
    stu_Ptr next;   //��һ��
    char Nowcolor[16];   //��ɫ
    char Changedcolor[16];   //ѡ�е���ɫ
    BOOL IsSelect;   //�Ƿ���ʾ   ��ఴť���Ըı����״̬
    double nowx, nowy;   //
    double XPosition[10],YPosition[10];    //ÿһ�����ݵ�xyλ��

} *STU;
struct stu *head, *ptr,*tail;


BOOL IsChooseXaxis, IsChooseYaxis,IsChooseLine;    //�Ƿ�ѡ����xy�� �����������̵Ȳ���

double ChooseLineMoveX, ChooseLineMoveY;    // ѡ����ߵ��ƶ���x��y
int ChooseLineNum;  //ѡ�е�column�����   ��1��ʼ����
