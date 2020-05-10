#pragma once
#include "MyData.h"
#include "graphics.h"
#define   XTOLERANCE  0.1   //选中xy轴伸缩的允许误差
#define   YTOLERANCE  0.1
#define   LINETOLERANCE  0.08   //选中直线移动的允许误差

BOOL  ChooseXaxis(double nowx,double  nowy);
BOOL  ChooseYaxis(double nowx,double  nowy);
BOOL  ChooseLine(double nowx, double  nowy);
BOOL	ChooseHistogram(double nowx, double nowy);


BOOL  ChooseXaxis(double nowx, double nowy) {
	if (nowx > beginTableX && nowx < endTableX &&
		fabs(nowy - beginTableY) <= XTOLERANCE)
		return 1;
	else return 0;
}

BOOL  ChooseYaxis(double nowx, double  nowy) {
	if (nowx > beginTableY && nowx < endTableY &&
		fabs(nowx - beginTableX) <= YTOLERANCE)
		return 1;
	else return 0;
}

BOOL ChooseLine(double nowx, double nowy) {
	

	if (nowx <= beginTableX+PerX || nowy <= beginTableY||nowx>endTableX||nowy>endTableY)
		return 0;
	int SNum = (nowx - beginTableX - PerX) / PerX;   //用第几个三次方程表达式

	double MinPos = 0;
	int tmpNum=0;
	int i;
	for (i = 1; i <= TotalColumnNum; i++) {
		if (IsChooseColumn[i] == 1) {
			double* PtrTmp = CubicEquation[i][SNum];   //这个指针放着 abcd   就是三次多项式的方程
			double xtmp = nowx - (SNum + (double)1) * PerX-beginTableX;    // 放当前nowx到前一个节点的横向距离
			double postmp = PtrTmp[0] + xtmp * PtrTmp[1] + pow(xtmp, 2) * PtrTmp[2] + pow(xtmp, 3) * PtrTmp[3];
		//	printf("snum=%d  nowx=%lf\n", SNum,nowx);
			//printf("PerX为%lf  tmpx为%lf  计算出来的y值为%lf   鼠标y值为%lf \n  ",PerX,xtmp, postmp,nowy);
	
			//SetPenColor("Black");
			//SetPenSize(2);
			//MovePen(nowx, postmp);
			//DrawLine(0, 0.5);   小测试  就画个位置我看看

			if (fabs(nowy - postmp) < LINETOLERANCE) {
				if (MinPos == 0) {
					MinPos = nowy - postmp;
					tmpNum = i;
				}
				else {
					if (nowy - postmp < MinPos) {
						MinPos = nowy - postmp;
						tmpNum = i;
					}
				}
			}

		}
	}
	if (tmpNum) {
		ChooseLineNum = tmpNum;
		return 1;
	}
	else return 0;
}
BOOL	ChooseHistogram(double nowx, double nowy) {
	int i;
	if (DrawWithColumn == 2) {
		
		
		
			for (i = 1; i <= ShowDateNum; i++) {
				if (nowx >= Histogram[i][0] - ColumnWidth && nowx <= Histogram[i][0] && nowy >= beginTableY && nowy <= Histogram[i][1]) {
					ChooseHistogramNum = ChoosedColumn[1];
					return TRUE;
				}
			}
			for (i = 1; i <= ShowDateNum; i++) {
				if (nowx >= Histogram[i][2] && nowx <= Histogram[i][2] + ColumnWidth && nowy >= beginTableY && nowy <= Histogram[i][3]) {
					ChooseHistogramNum = ChoosedColumn[2];
					return TRUE;
				}
			}
			return FALSE;
	}
	else if (DrawWithColumn == 1) {


		for (i = 1; i <= ShowDateNum; i++) {
			if (nowx >= Histogram[i][0] - ColumnWidth/2 && nowx <= Histogram[i][0]+ColumnWidth/2 && nowy >= beginTableY && nowy <= Histogram[i][1]) {
				ChooseHistogramNum = ChoosedColumn[1];  //我设置这里第一个放的是第一个柱状图的序号  第二个放的是第二个柱状图的序号
				return TRUE;
			}
		}
		
		return FALSE;
	}
	return FALSE;
}
BOOL HandleMouse(int x, int y, int button, int event) {

	

	double nowx, nowy;
	static double oldx = 0, oldy = 0;			 //用静态存储存原来的x，y
	static bool IsMove = FALSE;                   //是否移动
	nowx = ScaleXInches(x);						 //转换成英寸
	nowy = ScaleYInches(y);
	BOOL ReCalculate = FALSE;
	switch (event)
	{
	case BUTTON_DOWN:
	//	printf("%d %d %d %d\n", IsChooseXaxis, IsChooseYaxis, IsChooseLine, IsChooseHistogram);
		if (button == LEFT_BUTTON&&!IsChooseXaxis&&
			!IsChooseYaxis&&!IsChooseLine&&!IsChooseHistogram)   //前提是左键 + 其他没有被选中
		{
			if (IsChooseXaxis == FALSE && ChooseXaxis(nowx, nowy))  //
				IsChooseXaxis = TRUE;
			else if (IsChooseYaxis == FALSE && ChooseYaxis(nowx, nowy))
				IsChooseYaxis = TRUE;
			else if (IsChooseLine == FALSE && ChooseLine(nowx, nowy))
				IsChooseLine = TRUE;
			else if (IsChooseHistogram == FALSE && ChooseHistogram(nowx, nowy))
			{
				printf("nowx is %lf nowy is %lf\n", nowx, nowy);
				IsChooseHistogram = TRUE;
			}
		
		}
		if (button == RIGHT_BUTTON && (IsChooseXaxis || IsChooseYaxis || IsChooseLine||IsChooseHistogram )) {
			IsChooseXaxis = IsChooseYaxis = IsChooseLine =IsChooseHistogram= 0;
			ChooseLineNum = 0;
			ChooseHistogramNum = 0;
			ChooseLineMoveX = ChooseLineMoveY = 0;

		}   //右键直接置零

		if ((IsChooseXaxis || IsChooseYaxis || IsChooseLine))
			IsMove = TRUE;

		oldx = nowx, oldy = nowy;
		break;
	case BUTTON_UP:
		ReCalculate = TRUE;
		if(button == LEFT_BUTTON)
			IsMove = FALSE;

		break;
	case MOUSEMOVE:
		
		if (IsMove) {
			ReCalculate = TRUE;
			if (IsChooseXaxis) {
				endTableX += nowx - oldx;
			}
			else if (IsChooseYaxis) {
				endTableY += nowy - oldy;
			}
			else if (IsChooseLine) {
				ChooseLineMoveX += nowx - oldx;
				ChooseLineMoveY += nowy - oldy;
			}
		}
		oldx = nowx, oldy = nowy;
	default:
		break;
	}
	return ReCalculate;
}
