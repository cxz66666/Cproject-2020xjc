
#ifndef _MYDATA_
#define _MYDATA_
#include "MyData.h"
#endif

#ifndef _PREWORK_
#define _PREWORK_
#include "PreWork.c"

#include <direct.h>

void PreWork();   //做准备工作

BOOL CheckName(char* name); //检查文件名是否正确
void InitData();            //初始化所有数据
void Calculate(CaseNode_Ptr HEAD);   //最重要的计算函数
string GetDate(int month, int day);   //获取日期
void AssignTable();  //分配折线图和柱状图
BOOL CheckChangedNum(string str[], string ans);

void FreeColumn(char* Ptr[]); //free每个列名占用的内存
void ChangeIsSelect(CaseNode_Ptr HEAD);

void MyFree(CaseNode_Ptr Head); //free所有申请出来的节点

void InitStatus();     //文件关闭时候使用
#endif

