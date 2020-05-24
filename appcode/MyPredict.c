#pragma once

#include "MyData.h"

#define PREDICT 1

static int PolyNum = 3;
int MonthDate[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };  //�·�����

double  PolyPredictData[MAXCOLUMN+1][10] ; //���ÿ�����ݵ���Ͻ���     ��һ������Ϊ����  �ڶ�������Ϊÿ���ϵ��  ���� ��0��ŵ������ϵ��  ֮�� 1��2��3...���η�ֹ�����һ����Դ�����

void DrawPredict();
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string ploy,int ans[4]);
BOOL FindDate(int month, int day);

void    MyFree(CaseNode_Ptr Head);

void polyfit1(int n, double *x, double *y, int poly_n, double a[]); //a�зŵ��Ƿ��ص�ϵ��  3�����Ͼͱ���
void gauss_solve(int n, double A[], double x[], double b[]);//���polyfit1ʳ��


void polyfit2(int n, double* x, double* y, int poly_n, double a[]);//�����Ȱ�2д�������л���Ļ��ٽ������

void  PreparePredict(CaseNode_Ptr HEAD,int Date[4]);
string GetDate(int month, int day);

void FindBestPredict(int n, double* x, double* y, double a[]);

int CalY(int num, double c[]);
void DrawOldPoint(double PointData[][2], int Num);   //����ԭ���ĵ�
void DrawSelectedInf();
/*==================polyfit(n,x,y,poly_n,a)===================*/
/*=======���y=a0+a1*x+a2*x^2+����+apoly_n*x^poly_n========*/
/*=====n�����ݸ��� xy������ֵ poly_n�Ƕ���ʽ������======*/
/*===����a0,a1,a2,����a[poly_n]��ϵ����������һ�������=====*/


//����ʵ�ֹ������ﲻ��׸��   �õ���matlab�е�polyfit��c����ʵ��
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
    
#if PREDICT    //��������ý���ʼ����д��
    static char InputMonth[20] = "2", InputDay[20] = "1";
    static char DateLength[20] = "20", PredictLength[20] = "10"; //��ʼ��ʱ��   ģ��ԭʼ���ݳ��� Ԥ������
    static char Poly[20] = "";
    static char WrongTip[30] = "";
#else 
    static char InputMonth[20] = "", InputDay[20] = "";
    static char DateLength[20] = "", PredictLength[20] = ""; //��ʼ��ʱ��   ģ��ԭʼ���ݳ��� Ԥ������
    static char Poly[20] = "";
    static char WrongTip[30] = "";
#endif // PREDICT

    int ans[4] = { 0 };   //�ֱ��¼Inputmonth��day ��datelength��predictlength
   static BOOL ISOK = TRUE;  //�Ƿ���Ҫ��ʾ
    SetPenColor("TextBoxLabel");
    SetPenSize(3);
    double beginY = MaxY * 0.8;
    drawLabel(MaxX * 0.9-0.3, beginY, "Ԥ����ʼ����");

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    drawLabel(MaxX * 0.915, beginY -= FontHeight * 3, "��");
    drawLabel(MaxX * 0.96, beginY , "��");
    textbox(GenUIID(0), MaxX * 0.89, beginY-=1.5*FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);   //���������
    textbox(GenUIID(0), MaxX * 0.935, beginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "��������");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, DateLength, 20);    //����Ĳ�������

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "Ԥ������");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, PredictLength, 20);   //Ԥ������

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "ģ�ͽ���");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, Poly, 20);

    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    
    

    if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 4, MaxX * 0.05, FontHeight * 2, "Ԥ��")) {

        if (CheckPredict(WrongTip, InputMonth, InputDay, DateLength, PredictLength,Poly, ans)) {
            
            if (IsPredict)
                MyFree(PreHead);//��һ���ܹؼ�   ���֮ǰû��free���Ͳ�����free  ����free֮ǰ��
            NowDateNum = NowDateColumn = 0;
            
            PreparePredict(PredictHead,ans);  //�����ڴ�    ��������  ��ǰ����ô浽preHead��
            IsPredict = TRUE;
            ISOK = TRUE;
            memset(InputMonth, 0, sizeof(InputMonth));
            memset(InputDay, 0, sizeof(InputDay));
            memset(DateLength, 0, sizeof(DateLength));
            memset(PredictLength, 0, sizeof(PredictLength));
            memset(Poly, 0, sizeof(Poly));
            memset(WrongTip, 0, sizeof(WrongTip));  //��ÿ�����鶼����
            memset(ans, 0, sizeof(ans));    //��������

            NowShowTable = PreHead;
            ChangeIsSelect(NowShowTable);  //����ѡ������Ϊ20��
            Calculate(NowShowTable);
            //printf("Check!!\n");
       }
        else {
            ISOK = FALSE;
        }

    }
    if ( !ISOK) {
        SetPenColor("Red");
        SetPenSize(3);
        drawLabel(0.99 * MaxX - TextStringWidth(WrongTip), beginY -= 2 * FontHeight, WrongTip);   //������ʾ
    
        SetPenSize(1);
    }
 

    if (NowShowTable == PreHead) {   //���չʾԤ��Ͳ���ʾ�����ť
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "��ԭ")) {

            NowShowTable = FileHead;   //�ı���ͼ   ��Ϊչʾԭ�����е�����
            IsPredict = FALSE;
            NowDateNum = NowDateColumn = 0;
            Calculate(NowShowTable);   //���¼���
        }
    }
    if (!IsChangeNum) {   //���չʾԤ��Ͳ���ʾ�����ť
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "��������")) {

            IsChangeNum = TRUE;
        }
    }
    else {
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "��������")) {


            IsChangeNum = FALSE;
          CaseNode_Ptr  tmp = NowShowTable->next;    //������ǰչʾ�����ݽ�����IsShowNum��ΪFALSE
            while (tmp!=NULL)
            {
                tmp->IsShowNum = FALSE;
                tmp = tmp->next;
            }
        }
    }
} 
string GetDate(int month, int day) {    //��ʼmonth   ��ʼday+�߹���day

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
void  PreparePredict(CaseNode_Ptr HEAD,int Date[4]) { //Ԥ�����ݵ�����Ҳ��ͷ�ڵ�

    char TargetDate[20] = "";
    int OldPolyNum = PolyNum;
    double coefficient[7] = { 0 };

    double* x = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    double *y = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    CaseNode_Ptr OldPtr=HEAD;    // ԭ��HEAD�����ԭ���ݱ��ϵ� ���ܶ�������в���   Ӧ���ȴ�����   �Ȱ�ԭ�����ϵ��Ǹ�ָ��Ĵ����� ��һ�������ݵ�ʱ���õõ�
    CaseNode_Ptr tmp1=NULL ,tmp2=NULL;
    tmp1 = HEAD;
    PreHead = (CaseNode_Ptr)malloc(sizeof(struct CaseNode));



    int HaveNum = 0;    //ԭ�������û��������Ҫ����ô��   �ȼ�����
    while (tmp1 != NULL&&HaveNum<Date[2]) {    //date��2������Ӧ�òɼ���������
        HaveNum++;
        tmp1 = tmp1->next;        
    }   //����havenum�� �ǿ��Բɼ���������
     
    //���ݿ��Բɼ��Ŀ�ʼmalloc

    tmp1 = PreHead;
    int i,j;
    for (i = 0; i < HaveNum + Date[3]; i++) {
        tmp2 = (CaseNode_Ptr)malloc(sizeof(struct CaseNode));
        memset(tmp2->Data, 0, sizeof(tmp2->Data));
        tmp2->Date = NULL;
        tmp1->next = tmp2;
        tmp1 = tmp1->next;
    }    //��������
    tmp1->next = NULL;


    for ( i = 1; i <= TotalColumnNum; i++) {
        
        int nownum = 0;
        
        memset(x, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(y, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(coefficient, 0, sizeof(double) * 6);
        tmp1 = OldPtr;
        while (tmp1 != NULL && nownum < HaveNum) {
            x[nownum] = nownum + 1.0;
            y[nownum] = tmp1->Data[i];    //x����Ϊ1,2,3,4.....,��y����Ϊ����
            nownum++;
            tmp1 = tmp1->next;
        }
       
        if (PolyNum == -1) {
            FindBestPredict(nownum, x, y, coefficient);  //��polynum��Ϊ���ʵ�ֵ 0-5֮��
           
        }
       
       if(PolyNum>0)   //�������0
        polyfit1(nownum, x, y, PolyNum, coefficient);  //���м���  ����õĶ���ʽ��ϵ�ϵ���ŵ�coefficient��
       else if(!PolyNum){
           for (j = 0; j < nownum; j++)
               y[j] = log(y[j]);

           polyfit1(nownum, x, y, 1, coefficient);
       }
       PolyPredictData[i][0] = PolyNum;
       for ( j = 0; j <= PolyNum; j++)
           PolyPredictData[i][j + 1] = coefficient[j];
      
      // printf("��%d�����ݵ���Ͻ���Ϊ%d\n", i, PolyNum);
   /*    printf("������ϵ��Ϊ%d\n", PolyNum);
        for (int i = 0; i < nownum; i++) {
            printf("�� %d��xΪ%lf yΪ%lf", i, x[i], y[i]);
        }
        printf("\n");
        for (int i = 0; i <= PolyNum; i++) {
            printf("��%d��ϵ��Ϊ%lf   ", i, coefficient[i]);
        }
        printf("\n");*/

        nownum = 0;
        tmp1 = PreHead->next;   //��ͷ�ڵ�   ��ʼ��������
        while (tmp1 != NULL) {
            tmp1->Date = GetDate(Date[0], Date[1] + nownum );
            tmp1->IsSelect = TRUE;
            nownum++;
            tmp1->IsShowNum = FALSE;
            tmp1->Data[i] = CalY(nownum, coefficient);
            if (nownum <= Date[2])
                strcpy(tmp1->Changedcolor, "Light Gray");

            else strcpy(tmp1->Changedcolor, "Dark Gray");
            tmp1 = tmp1->next;
        }

        
        PolyNum = OldPolyNum; //����Ϊ��ʼ��ϵ������ѭ������
        

    }
         
   
}

void FindBestPredict(int n, double* x, double* y, double a[]) {
    int Findpoly=0;   //Ŀ�Ľ���
    int i, j;
    double R_2 = -100;
    double TmpR_2;

    double AverageY = 0;

    for (i = 0; i < n; i++) {
        AverageY += y[i];
    }
    AverageY /= n;


    for (i = 0; i <= 5; i++) {
        double SSE = 0, SST = 0;   //SSRΪ�ع�ƽ���ͣ�SSEΪ�в�ƽ���ͣ�SSTΪ�����ƽ����
            if (!i)
            for (j = 0; j < n; j++) {
                y[j] = log(y[j]);

            }   //���i��0��ȡ����

            if (i) {
                polyfit1(n, x, y, i, a);
                if (a[i] < 0)
                    continue;
            }
            
            else {
                polyfit1(n, x, y, 1, a);   //�����i=0 �Ǿ������Ե�lny=lnk+ax
                if (a[1] < 0)
                {
                    for (j = 0; j < n; j++) 
                        y[j] = exp(y[j]);
                    
                    continue;
                }
                   
            }
         
        
        PolyNum = i;  //����Ϊi
        for (j = 0; j < n; j++) {
            double tmp = CalY(j + 1, a);
            SSE += pow((y[j] - tmp), 2);
            SST += pow(y[j] - AverageY, 2);
        }


        TmpR_2 = 1.0 - SSE / SST; //�ؼ�һ��

       // printf("��%d��ģ����϶�Ϊ%lf\n", i, TmpR_2);

        if (TmpR_2 > R_2) {   //����������
            R_2 = TmpR_2;
            Findpoly = i;
        }

        if (!i)  //����ղ�ȡ�˶��� �Ǿ����±��ȥ ��ֹӰ�����ʹ��
        {
            for (j = 0; j < n; j++) {
                y[j] = exp(y[j]);
                
            }
           
        }
    }
    PolyNum = Findpoly;
}
int CalY(int num, double  c[]) {  //����Y��ֵ  ���������
    double ans = 0;
    int i=0;
    if (PolyNum) {
        for (i = 0; i <= PolyNum; i++) {    //����Ƕ���ʽ���  �Ͱ�������
        ans += pow(num, i) * c[i];
        }
    }
    
    else {
            ans= exp(c[0]) * exp(num * c[1]);  //�����ָ�����  ��������
    }
    return (int)ans;

}
/*���м��ĺ���  ���źܶ� ��ʵ˼·�ܼ�*/
//ʹ��atoi������stoi
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string poly,int ans[4]) {
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(PredictLength) || !strcmp(InputMonth, "��") ||!strcmp(InputDay, "��") || InputMonth[0] < 0 || InputDay[0] < 0) {

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
    if (Datelen <10) {
        strcpy(WrongTip, "����������������10Ŷ");
        return  FALSE;
    }
    if (!Predict) {
        strcpy(WrongTip, "��������ȷԤ��");
        return FALSE;
    }
    if (Predict > 20) {
        strcpy(WrongTip, "Ԥ���������ܳ���20Ŷ");
        return FALSE;
    }
    if (!strlen(poly)) {
        polynum = -1;
    }
    else  if (polynum < 0)
    {
        strcpy(WrongTip, "ģ�ͽ�������");
        return FALSE;
    }
    else if (polynum > 5) {
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
    sprintf(TargetDate, "%d��%d��",month, day); //д��Ŀ������
   // printf("TargetDate is %s\n", TargetDate);

    PredictHead = FileHead;

    CaseNode_Ptr tmp = FileHead->next;   //����һ��  FileHead��ͷ�ڵ�

    while (tmp!=NULL)
    {
        if (!strcmp(tmp->Date, TargetDate)) {  //����ҵ���
            PredictHead = tmp;
            printf("zhaodaole\n");
            break;
        }
        tmp = tmp->next;
    }
    if (PredictHead != FileHead)   //���������˵���ҵ���
        return TRUE;
    else return FALSE;

}

void    MyFree(CaseNode_Ptr Head) {

    if (Head == NULL)
        return;
    CaseNode_Ptr next=Head,tmp=Head;
   
    next = tmp->next;
    free(tmp);   //ͷ�ڵ㵥���ͷ�
    
    tmp = NULL;

    while (next!=NULL)
    {
        tmp =next; 
        next = tmp->next;
        free(tmp->Date);   //���ڵ����ͷ�
        free(tmp);  //���������ͷ�
    }
   
}
void DrawSelectedInf() {
    char OutChoosed[100];
    int NowChooseColumn = 0;
    memset(OutChoosed, 0, sizeof(OutChoosed));
    if (IsChooseLine) {  //���ѡ�����ֱ��
        sprintf(OutChoosed, "��ǰѡ��ֱ��Ϊ%s", ColumnName[ChooseLineNum]);
        NowChooseColumn = ChooseLineNum;
    }
    else if (IsChooseHistogram) {   //���ѡ�������״ͼ
        sprintf(OutChoosed, "��ǰѡ����״ͼΪ%s", ColumnName[ChooseHistogramNum]);
        NowChooseColumn = ChooseHistogramNum;
    }
    else return;
    if (strlen(OutChoosed)) {
        SetPenColor("PreWordColor");
        SetPenSize(2);
        MovePen(beginTableX + 0.5, MaxY * 0.9);
        DrawTextString( OutChoosed);    //������ǰѡ�в���
    }
    if (IsPredict) {
        MovePen(beginTableX  +0.5, MaxY * 0.9-FontHeight*2);
        sprintf(OutChoosed, "ģ�ͽ���Ϊ%.0lf��", PolyPredictData[NowChooseColumn][0]);
        DrawTextString(OutChoosed);
        memset(OutChoosed, 0, sizeof(OutChoosed));
        strcpy(OutChoosed, "������߷���Ϊy=");   //����������ߵķ���
        int i;
        char OutEquationTmp[20];
        for (i = 0; i <= PolyPredictData[NowChooseColumn][0]; i++) {
            if (!i)   //������
                sprintf(OutEquationTmp, "%.1lf", PolyPredictData[NowChooseColumn][1]);
            else if(i==1)//һ����
                sprintf(OutEquationTmp, "%.1lfx", PolyPredictData[NowChooseColumn][2]);
            else   sprintf(OutEquationTmp, "%.1lfx^%d", PolyPredictData[NowChooseColumn][i+1],i);  //�������ϵ���
            strcat(OutChoosed, OutEquationTmp);
            if (i != PolyPredictData[NowChooseColumn][0])
                if(PolyPredictData[NowChooseColumn][i+2]>0)
                strcat(OutChoosed, "+");   //������Ǹ����ͼ��ϼӺ�

        }
        printf("%s\n", OutChoosed);
        MovePen((beginTableX + StaticendTableX) / 2 , MaxY * 0.9 );
        DrawTextString(OutChoosed);
    }
}
//����ԭʼ���ݵ�СԲ��
void ShowOldPoint() {   
    if (IsPredict && (IsChooseLine || IsChooseHistogram))
    {
        int i,column = 0;
        column = IsChooseLine ? ChooseLineNum : ChooseHistogramNum;      //���ѡ����ֱ�߾���ֱ�ߵ� ���������״ͼ��
        if (PreHead == NULL)   //�����NULL �ͷ���
            return;
        CaseNode_Ptr tmp1 = PredictHead, tmp2 = NowShowTable->next;  //tmp1�����ԭʼ����  tmp2��Ԥ������
        double PointData[MAXDATE + 1][2] = { 0 };
        int nownum = 0;
        while (tmp1 != NULL && tmp2 != NULL) {   //�����ڹ鲢����
            if (tmp2->IsSelect) {
                if (!strcmp(tmp1->Date, tmp2->Date)) {   //�����������
                    nownum++;
                    PointData[nownum][0] = nownum ;
                    PointData[nownum][1] = tmp1->Data[column];
                    tmp1 = tmp1->next;  //������������   ����ȫ��������һ��
                    tmp2 = tmp2->next;
                }
                else {
                    tmp1 = tmp1->next;   //����ԭʼ���ݽ�����һ��
                }
            }
            else {
                tmp2 = tmp2->next;   //���tmp2û��ѡ��  now���ݽ�����һ��
            }
        }
        if (nownum) {
            for (i = 1; i <= nownum; i++) {
                PointData[i][0] = beginTableX + i * PerX;    //��x����д��
                PointData[i][1] = beginTableY + PointData[i][1] * PerY;   //�����y����
            }
            DrawOldPoint(PointData, nownum);   //��������
        }
    }
    else return;
}
void DrawOldPoint(double PointData[][2],int Num) {
    int i;
    SetPenColor("Blue");
    //StartFilledRegion(0.8);
    for (i = 1; i <= Num; i++)
    {
        MovePen(PointData[i][0] + 0.06, PointData[i][1]);
        DrawArc(0.06, 0, 360);
    }
   // StartFilledRegion(0.1);
}