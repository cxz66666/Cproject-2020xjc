#pragma once
#include "MyData.h"
#include "graphics.h"
#define   XTOLERANCE  0.1   //ѡ��xy���������������
#define   YTOLERANCE  0.1
#define   LINETOLERANCE  0.08   //ѡ��ֱ���ƶ����������

BOOL  ChooseXaxis(double nowx,double  nowy);
BOOL  ChooseYaxis(double nowx,double  nowy);
BOOL  ChooseLine(double nowx, double  nowy);



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
	int SNum = (nowx - beginTableX - PerX) / PerX;   //�õڼ������η��̱��ʽ

	double MinPos = 0;
	int tmpNum=0;
	int i;
	for (i = 1; i <= TotalColumnNum; i++) {
		if (IsChooseColumn[i] == 1) {
			double* PtrTmp = CubicEquation[i][SNum];   //���ָ����� abcd   �������ζ���ʽ�ķ���
			double xtmp = nowx - (SNum + (double)1) * PerX-beginTableX;    // �ŵ�ǰnowx��ǰһ���ڵ�ĺ������
			double postmp = PtrTmp[0] + xtmp * PtrTmp[1] + pow(xtmp, 2) * PtrTmp[2] + pow(xtmp, 3) * PtrTmp[3];
		//	printf("snum=%d  nowx=%lf\n", SNum,nowx);
			//printf("PerXΪ%lf  tmpxΪ%lf  ���������yֵΪ%lf   ���yֵΪ%lf \n  ",PerX,xtmp, postmp,nowy);
	
			SetPenColor("Black");
			SetPenSize(2);
			MovePen(nowx, postmp);
			DrawLine(0, 0.5);

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

BOOL HandleMouse(int x, int y, int button, int event) {
	double nowx, nowy;
	static double oldx = 0, oldy = 0;			 //�þ�̬�洢��ԭ����x��y
	static bool IsMove = FALSE;                   //�Ƿ��ƶ�
	nowx = ScaleXInches(x);						 //ת����Ӣ��
	nowy = ScaleYInches(y);
	BOOL ReCalculate = FALSE;
	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON&&!IsChooseXaxis&&
			!IsChooseYaxis&&!IsChooseLine)   //ǰ������� + ����û�б�ѡ��
		{
			if (IsChooseXaxis == FALSE && ChooseXaxis(nowx, nowy))  //
				IsChooseXaxis = TRUE;
			else if (IsChooseYaxis == FALSE && ChooseYaxis(nowx, nowy))
				IsChooseYaxis = TRUE;
			else if (IsChooseLine == FALSE && ChooseLine(nowx, nowy))
				IsChooseLine = TRUE;
		}
		if (button == RIGHT_BUTTON && (IsChooseXaxis || IsChooseYaxis || IsChooseLine)) {
			IsChooseXaxis = IsChooseYaxis = IsChooseLine = 0;
			ChooseLineNum = 0;
			ChooseLineMoveX = ChooseLineMoveY = 0;
		}   //�Ҽ�ֱ������

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
