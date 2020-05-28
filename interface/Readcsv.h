#ifndef _MYDATA_
#define _MYDATA_
#include "MyData.h"
#endif

#ifndef _READCSV_
#define _READCSV_
#include "Readcsv.c"

BOOL SaveToCsv(CaseNode_Ptr HEAD); //保存到csv的画图主函数

BOOL ReadCSVFile(char* Name); //读取csv文件

#endif

