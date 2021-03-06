#pragma once 
#include "MyData.h"



void parspl(double p[][2], int n, int k);   //一种插值法进行计算的函数
void lineto(double x, double y);   //从当前位置画直线到xy
void Cubic_Spline(double data[][2], int num, int k,  int ColumnNum);   //三次样条插值法c语言实现
void DrawHistogram(double TableData[][2], int num);   //画柱状图的算法


void lineto(double x, double y)   //画一条当前位置到x，y的直线   
{
    double nowx = GetCurrentX(), nowy = GetCurrentY();
    DrawLine(x - nowx, y - nowy);
}
void DrawHistogram(double TableData[][2], int num) {
   
    if (DrawWithColumn == 2) {  //如果一共要画两个柱状图
        if (!DrawWithColumnNow) { 
            DrawWithColumnNow++;   //记录一共画到了第几个
            int i;
            for (i = 1; i <= num; i++) {  //画第一个的情况
                drawRectangle(TableData[i][0], beginTableY, -1 * ColumnWidth, TableData[i][1] - beginTableY, 1);
                Histogram[i][0] = TableData[i][0], Histogram[i][1] = TableData[i][1];

            }
        }
        else {
            int i;
            for (i = 1; i <= num; i++) {  //画第二个的情况
                drawRectangle(TableData[i][0], beginTableY, ColumnWidth, TableData[i][1] - beginTableY, 1);
                Histogram[i][2] = TableData[i][0], Histogram[i][3] = TableData[i][1];
            }
        }
    }
    else if (DrawWithColumn == 1) {  //如果只用画一个柱状图
        int i;
        for (i = 1; i <= num; i++) {
            drawRectangle(TableData[i][0] - ColumnWidth / 2, beginTableY, ColumnWidth, TableData[i][1] - beginTableY, 1);   //直接在中间画出即可
            Histogram[i][0] = TableData[i][0], Histogram[i][1] = TableData[i][1];
        }
    }
}
void parspl(double p[][2], int n, int k)   //这个同样也是画曲线图的算法   但是没有三次样条插值法合适  具体实现原理同样不表 
{ //这个没有用到  但是同样是一种插值法的形式
    int i, j;
    double t1, t2, t3, t, a, b, c, d, x, y;
    p[0][0] = p[1][0];
    p[0][1] = p[1][1];
    double prex=p[0][0], prey=p[0][1];
    p[n + 1][0] = p[n][0];
    p[n + 1][1] = p[n][1];
    t = 0.5 / k;
    lineto(p[1][0], p[1][1]);
    for (i = 0; i < n - 1; i++)
    {
        for (j = 1; j < k; j++)
        {
            t1 = j * t;
            t2 = t1 * t1;
            t3 = t2 * t1;
            a = 4 * t2 - t1 - 4 * t3;
            b = 1 - 10 * t2 + 12 * t3;
            c = t1 + 8 * t2 - 12 * t3;
            d = 4 * t3 - 2 * t2;
            x = a * p[i][0] + b * p[i + 1][0] + c * p[i + 2][0] + d * p[i + 3][0];
            y = a * p[i][1] + b * p[i + 1][1] + c * p[i + 2][1] + d * p[i + 3][1];
        //    printf("x=%.3lf y=%.3lf\n", x, y);
            DrawLine(x - prex, y - prey);
            prex = x, prey = y;
        }
    }
    lineto(p[i + 2][0], p[i + 2][1]);
}
#define N 100   //最大的数据量

void Cubic_Spline(double data[][2], int num, int k,int ColumnNum)   //具体算法细节不表  实现原理自行百度
{
    int i, j;

    int n = num - 1;
    double x[N + 1], y[N + 1], h[N], A[N], l[N + 1],
        u[N + 1], z[N + 1], c[N + 1], b[N], d[N];
    
    memset(A, 0, sizeof(A));

    for (i = 0; i < n + 1; ++i)
        x[i] = data[i + 1][0], y[i] = data[i + 1][1];

    for (i = 0; i <= n - 1; ++i)
        h[i] = x[i + 1] - x[i];

    for (i = 1; i <= n - 1; ++i)
        A[i] = 3 * (y[i + 1] - y[i]) / h[i] - 3 * (y[i] - y[i - 1]) / h[i - 1];

    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    for (i = 1; i <= n - 1; ++i)
    {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    for (j = n - 1; j >= 0; --j)
    {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }
    /*为了能实现选中曲线 我们这里必须记着曲线的三次方程*/
    for (i = 0; i < n; ++i) {
        CubicEquation[ColumnNum][i][0] = y[i];
        CubicEquation[ColumnNum][i][1] = b[i];
        CubicEquation[ColumnNum][i][2] = c[i];
        CubicEquation[ColumnNum][i][3] = d[i];
    }
   // printf("%2s %8s %8s %8s %8s\n", "i", "ai", "bi", "ci", "di");
   // for (i = 0; i < n; ++i)
     //   printf("%2d %8.2f %8.2f %8.2f %8.2f\n", i, y[i], b[i], c[i], d[i]);
    MovePen(x[0], y[0]);
    double tmpy = y[0], tmpx = x[0];
    double prey = tmpy;
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) {
            tmpx += h[i] / k;
            tmpy = pow((tmpx - x[i]), 3) * d[i] + pow((tmpx - x[i]), 2) * c[i] + (tmpx - x[i]) * b[i] + y[i];
            DrawLine(h[i] / k, tmpy - prey);   //原理就是画一极小段线
            prey = tmpy;
           // printf("%.4lf %.4lf \n", GetCurrentX(), GetCurrentY());
        }
    }

}
