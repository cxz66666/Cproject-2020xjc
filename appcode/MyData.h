#pragma once 
// �����й�����  MaxX��MaxY
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
int ChooseDataNum ;  //һ���ж�����  �������� ȫ����Ⱦ   ������Ⱦ  ȫ������������
BOOL IsChooseData[10];  //�Ƿ�ѡ���˸���  
char *ChooseData[20];  //ÿһ�е�����
char FilePath[100];   //�ļ�·��
char *FileName[20];   //�����ļ���
int FileNum;  //���ļ���Ŀ

double beginTableX, beginTableY;   //��ʼ��ͼ��xy
double endTableX, endTableY;   //������ͼ��xy
int TableMark1, TableMark2, TableMark3, TableMark4;    //��1234��y���ϵĻ�ɫ��

double TableData[10][30][2];    //table����     ��һ��Ϊѡ����   �ڶ���Ϊ����   ������Ϊxy


double PerX, PerY;      //��λ���ȵ�xy
double FontHeight, FontAscent, FontDescent; //������

char* COLOR[] = { "NULL","Red", "Blue", "Green",  "Gray", "Orange","Yellow" };    //��ͼ��ɫ

int ClassDataNum[10];    //�������ÿ���������������


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
struct stu *head, *ptr;