#ifndef _MYDATA_
#define _MYDATA_
#include "MyData.h"
#endif

#ifndef _READCSV_
#define _READCSV_
#include "Readcsv.c"

BOOL SaveToCsv(CaseNode_Ptr HEAD); //���浽csv�Ļ�ͼ������
BOOL SaveCSV(string InputName, CaseNode_Ptr HEAD); //����csv�ļ���ʵ��
BOOL ReadCSVFile(char* Name); //��ȡcsv�ļ�

#endif

