#ifndef _MYDATA_
#define _MYDATA_
#include "MyData.h"
#endif // ! _MYDATA_

#ifndef _MYDRAWTABLE_
#define _MYDRAWTABLE_
#include "MyDrawTable.c"


void Cubic_Spline(double data[][2], int num, int k, int ColumnNum); //����������ֵ��c����ʵ��
void DrawHistogram(double TableData[][2], int num);                 //����״ͼ���㷨

#endif
