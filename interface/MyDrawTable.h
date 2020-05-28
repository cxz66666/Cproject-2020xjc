#ifndef _MYDATA_
#define _MYDATA_
#include "MyData.h"
#endif // ! _MYDATA_

#ifndef _MYDRAWTABLE_
#define _MYDRAWTABLE_
#include "MyDrawTable.c"


void Cubic_Spline(double data[][2], int num, int k, int ColumnNum); //三次样条插值法c语言实现
void DrawHistogram(double TableData[][2], int num);                 //画柱状图的算法

#endif
