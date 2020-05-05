#pragma once

#include "MyData.h"

static int PolyNum = 3;
static int MonthDate[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };  //�·�����

void DrawPredict();
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string ploy,int ans[4]);
BOOL FindDate(int month, int day);

void    MyFree(stu_Ptr Head);

void polyfit1(int n, double *x, double *y, int poly_n, double a[]); //a�зŵ��Ƿ��ص�ϵ��  3�����Ͼͱ���
void gauss_solve(int n, double A[], double x[], double b[]);//���polyfit1ʳ��


void polyfit2(int n, double* x, double* y, int poly_n, double a[]);//�ҵ��Ķ��Ƚϴ� ���Ǹо�1������  �������ڸ���

void  PreparePredict(stu_Ptr HEAD,int Date[4]);
string GetDate(int month, int day);

int CalY(int num, double c[]);

/*==================polyfit(n,x,y,poly_n,a)===================*/
/*=======���y=a0+a1*x+a2*x^2+����+apoly_n*x^poly_n========*/
/*=====n�����ݸ��� xy������ֵ poly_n�Ƕ���ʽ������======*/
/*===����a0,a1,a2,����a[poly_n]��ϵ����������һ�������=====*/
void polyfit1(int n, double x[], double y[], int poly_n, double a[])
{
    int i, j;
    double *tempx, *tempy, *sumxx, *sumxy, *ata;
    tempx = (double *)malloc(n * sizeof(double));
    sumxx = (double *)malloc((poly_n * 2 + 1) * sizeof(double));
    tempy = (double *)malloc(n * sizeof(double));
    sumxy = (double *)malloc((poly_n + 1) * sizeof(double));
    ata = (double *)malloc(((poly_n + 1) * (poly_n + 1)) * sizeof(double));
    for (i = 0; i < n; i++)
    {
        tempx[i] = 1;
        tempy[i] = y[i];
    }
    for (i = 0; i < 2 * poly_n + 1; i++)
        for (sumxx[i] = 0, j = 0; j < n; j++)
        {
            sumxx[i] += tempx[j];
            tempx[j] *= x[j];
        }
    for (i = 0; i < poly_n + 1; i++)
        for (sumxy[i] = 0, j = 0; j < n; j++)
        {
            sumxy[i] += tempy[j];
            tempy[j] *= x[j];
        }
    for (i = 0; i < poly_n + 1; i++)
        for (j = 0; j < poly_n + 1; j++)
            ata[i * (poly_n + 1) + j] = sumxx[i + j];
    gauss_solve(poly_n + 1, ata, a, sumxy);

    free(tempx);
    free(sumxx);
    free(tempy);
    free(sumxy);
    free(ata);
}

void gauss_solve(int n, double A[], double x[], double b[])
{
    int i, j, k, r;
    double max;
    for (k = 0; k < n - 1; k++)
    {
        max = fabs(A[k * n + k]); /*find maxmum*/
        r = k;
        for (i = k + 1; i < n - 1; i++)
            if (max < fabs(A[i * n + i]))
            {
                max = fabs(A[i * n + i]);
                r = i;
            }
        if (r != k)
            for (i = 0; i < n; i++) /*change array:A[k]&A[r] */
            {
                max = A[k * n + i];
                A[k * n + i] = A[r * n + i];
                A[r * n + i] = max;
            }
        max = b[k]; /*change array:b[k]&b[r]     */
        b[k] = b[r];
        b[r] = max;
        for (i = k + 1; i < n; i++)
        {
            for (j = k + 1; j < n; j++)
                A[i * n + j] -= A[i * n + k] * A[k * n + j] / A[k * n + k];
            b[i] -= A[i * n + k] * b[k] / A[k * n + k];
        }
    }

    for (i = n - 1; i >= 0; x[i] /= A[i * n + i], i--)
        for (j = i + 1, x[i] = b[i]; j < n; j++)
            x[i] -= A[i * n + j] * x[j];
}




void DrawPredict() {
    static char InputMonth[20] = "", InputDay[20] = "";
    static char DateLength[20] = "", PredictLength[20] = ""; //��ʼ��ʱ��   ģ��ԭʼ���ݳ��� Ԥ������
    static char Poly[20] ="";
    static char WrongTip[30] = "";
    int ans[4] = { 0 };
   static BOOL ISOK = TRUE;  //�Ƿ���Ҫ��ʾ
    SetPenColor("TextBoxLabel");
    SetPenSize(3);
    double beginY = MaxY * 0.8;
    drawLabel(MaxX * 0.9, beginY, "Ԥ����ʼ����");

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 3, "��");
    drawLabel(MaxX * 0.94, beginY , "��");
    textbox(GenUIID(0), MaxX * 0.915, beginY-=1.5*FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);
    textbox(GenUIID(0), MaxX * 0.955, beginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "��������");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, DateLength, 20);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "Ԥ������");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, PredictLength, 20);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "ģ�ͽ���");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, Poly, 20);

    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    
    

    if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 4, MaxX * 0.05, FontHeight * 2, "Ԥ��")) {

        if (CheckPredict(WrongTip, InputMonth, InputDay, DateLength, PredictLength,Poly, ans)) {
            MyFree(PreHead);
            IsPredict = TRUE;
            ISOK = TRUE;
            PreparePredict(PredictHead,ans);
            NowShowTable = PreHead;
            Calculate(NowShowTable);
            //printf("Check!!\n");
       }
        else {
            ISOK = FALSE;
        }

    }
    if (!IsPredict && !ISOK) {
        SetPenColor("Red");
        SetPenSize(3);
        drawLabel(0.99 * MaxX - TextStringWidth(WrongTip), beginY -= 2 * FontHeight, WrongTip);
    
        SetPenSize(1);
    }
 

    if (NowShowTable == PreHead) {   //���չʾԤ��Ͳ���ʾ�����ť
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "��ԭ")) {

            NowShowTable = head;   //�ı���ͼ   ��Ϊչʾԭ�����е�����
            IsPredict = FALSE;
            Calculate(NowShowTable);   //���¼���
        }
    }
}
string GetDate(int month, int day) {

    while (day > MonthDate[month]) {
        day -= MonthDate[month];
        month++;
        if (month > 12)
            month -= 12;
    }    //������¼���
    char tmpdate[20] = "";
    sprintf(tmpdate, "%d��%d��", month, day);   //��ֵ

    string ans = (string)malloc(sizeof(tmpdate) + 1);
    strcpy(ans, tmpdate);
    
    return ans;

}
void  PreparePredict(stu_Ptr HEAD,int Date[4]) { //Ԥ�����ݵ�����Ҳ��ͷ�ڵ�

    char TargetDate[20] = "";
    
    double coefficient[7] = { 0 };

    double* x = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    double *y = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    stu_Ptr OldPtr=HEAD;    // ԭ��HEAD�����ԭ���ݱ��ϵ� ���ܶ�������в���   Ӧ���ȴ�����   �Ȱ�ԭ�����ϵ��Ǹ�ָ��Ĵ����� ��һ�������ݵ�ʱ���õõ�
    stu_Ptr tmp1 = OldPtr,tmp2;
    PreHead = (stu_Ptr)malloc(sizeof(struct stu));



    int HaveNum = 0;    //ԭ�������û��������Ҫ����ô��   �ȼ�����
    while (tmp1 != NULL&&HaveNum<Date[2]) {    //date��2������Ӧ�òɼ���������
        HaveNum++;
        tmp1 = tmp1->next;        
    }   //����havenum�� �ǿ��Բɼ���������
     
    //���ݿ��Բɼ��Ŀ�ʼmalloc

    tmp1 = PreHead;
    int i;
    for (i = 0; i < HaveNum + Date[3]; i++) {
        tmp2 = (stu_Ptr)malloc(sizeof(struct stu));
        tmp1->next = tmp2;
        tmp1 = tmp1->next;
    }    //��������
    tmp1->next = NULL;


    for (int i = 1; i <= TotalColumnNum; i++) {
        
        int nownum = 0;
        memset(x, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(y, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(coefficient, 0, sizeof(double) * 6);
        tmp1 = OldPtr;
        while (tmp1 != NULL && nownum < HaveNum) {
            x[nownum] = nownum + 1;
            y[nownum] = tmp1->Data[i];    //x����Ϊ1,2,3,4.....,��y����Ϊ����
            nownum++;
            tmp1 = tmp1->next;
        }
       
        polyfit1(nownum, x, y, PolyNum, coefficient);  //���м���  ����õĶ���ʽ��ϵ�ϵ���ŵ�coefficient��

        for (int i = 0; i < nownum; i++) {
            printf("�� %d��xΪ%lf yΪ%lf", i, x[i], y[i]);
        }
        printf("\n");
        for (int i = 0; i <= PolyNum; i++) {
            printf("��%d��ϵ��Ϊ%lf   ", i, coefficient[i]);
        }
        printf("\n");
        nownum = 0;
        tmp1 = PreHead->next;   //��ͷ�ڵ�   ��ʼ��������
        while (tmp1 != NULL) {
            tmp1->Date = GetDate(Date[0], Date[1] + nownum );
            tmp1->IsSelect = TRUE;
            nownum++;
            tmp1->Data[i] = CalY(nownum, coefficient);
            tmp1 = tmp1->next;
        }


    }
         
    
}
int CalY(int num, double  c[]) {
    double ans = 0;
    for (int i = 0; i <= PolyNum; i++) {
        ans += pow(num, i) * c[i];
    }
    return (int)ans;

}
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string poly,int ans[4]) {
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(PredictLength) || !strcmp(InputMonth, "��")||!strlen(poly) || !strcmp(InputDay, "��") || InputMonth[0] < 0 || InputDay[0] < 0) {

        strcpy(WrongTip, "��������������");
        return FALSE;
    }   //����ǿյ�  ���߻��ǳ�ʼ����  ��   ֱ�ӷ���

    int month = atoi(InputMonth), day = atoi(InputDay), Datelen = atoi(DateLength), Predict = atoi(PredictLength),polynum=atoi(poly);   //����쳣ֱ��atoi����0
    if (month <= 0 || month > 12) {
        strcpy(WrongTip, "��������ȷ�·�");
        return FALSE;
    }
    if (day <= 0 || day > 31)
    {
        strcpy(WrongTip, "��������ȷ����");
        return FALSE;
    }
    if (!Datelen) {
        strcpy(WrongTip, "��������ȷ����");
        return FALSE;
    }
    if (Datelen > 20) {
        strcpy(WrongTip, "�����������ܳ���20Ŷ");
        return FALSE;
    }
    if (!Predict) {
        strcpy(WrongTip, "��������ȷԤ��");
        return FALSE;
    }
    if (Predict > 20) {
        strcpy(WrongTip, "Ԥ���������ܳ���20Ŷ");
        return FALSE;
    }
    if (polynum <= 0)
    {
        strcpy(WrongTip, "ģ�ͽ�������");
        return FALSE;
    }
    if (polynum > 5) {
        strcpy(WrongTip, "����̫������");
        return FALSE;
    }
    if (FindDate(month, day)) {
        WrongTip = "";
        ans[0] = month, ans[1] = day, ans[2] = Datelen, ans[3] = Predict;
        PolyNum = polynum;
        return TRUE;
    }
    else {
        strcpy(WrongTip, "����δ�ҵ�");
        return FALSE;
    }

}
BOOL FindDate(int month, int day) {
    char TargetDate[20] = "";
    sprintf(TargetDate, "%d��%d��",month, day);
   // printf("TargetDate is %s\n", TargetDate);

    PredictHead = head;

    stu_Ptr tmp = head->next;   //����һ��  head��ͷ�ڵ�

    while (tmp!=NULL)
    {
        if (!strcmp(tmp->Date, TargetDate)) {  //����ҵ���
            PredictHead = tmp;
            break;
        }
        tmp = tmp->next;
    }
    if (PredictHead != head)
        return TRUE;
    else return FALSE;

}

void    MyFree(stu_Ptr Head) {

    if (Head == NULL)
        return;
    stu_Ptr next=Head,tmp=Head;
    while (next!=NULL)
    {
        tmp =next;
        next = tmp->next;
        free(tmp);
    }
   
}