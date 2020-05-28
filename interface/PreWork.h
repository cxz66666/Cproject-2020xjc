
#ifndef _MYDATA_
#define _MYDATA_
#include "MyData.h"
#endif

#ifndef _PREWORK_
#define _PREWORK_
#include "PreWork.c"

#include <direct.h>

void PreWork();

BOOL CheckName(char* name); //����ļ����Ƿ���ȷ
void InitData();            //��ʼ����������
void Calculate(CaseNode_Ptr HEAD);
string GetDate(int month, int day);
void AssignTable();
BOOL CheckChangedNum(string str[], string ans);

void FreeColumn(char* Ptr[]);
void ChangeIsSelect(CaseNode_Ptr HEAD);

void MyFree(CaseNode_Ptr Head); //free������������Ľڵ�
#endif

