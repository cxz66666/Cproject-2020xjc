#pragma once

#include "MyData.h"

static int PolyNum = 3;
static int MonthDate[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };  //月份天数

void DrawPredict();
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string ploy,int ans[4]);
BOOL FindDate(int month, int day);

void    MyFree(stu_Ptr Head);

void polyfit1(int n, double *x, double *y, int poly_n, double a[]); //a中放的是返回的系数  3阶以上就暴毙
void gauss_solve(int n, double A[], double x[], double b[]);//配合polyfit1食用


void polyfit2(int n, double* x, double* y, int poly_n, double a[]);//找到的都比较蠢 但是感觉1有问题  所以先挖个坑

void  PreparePredict(stu_Ptr HEAD,int Date[4]);
string GetDate(int month, int day);

int CalY(int num, double c[]);

/*==================polyfit(n,x,y,poly_n,a)===================*/
/*=======拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n========*/
/*=====n是数据个数 xy是数据值 poly_n是多项式的项数======*/
/*===返回a0,a1,a2,……a[poly_n]，系数比项数多一（常数项）=====*/
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
    static char DateLength[20] = "", PredictLength[20] = ""; //起始的时间   模型原始数据长度 预测天数
    static char Poly[20] ="";
    static char WrongTip[30] = "";
    int ans[4] = { 0 };
   static BOOL ISOK = TRUE;  //是否需要提示
    SetPenColor("TextBoxLabel");
    SetPenSize(3);
    double beginY = MaxY * 0.8;
    drawLabel(MaxX * 0.9, beginY, "预测起始日期");

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 3, "月");
    drawLabel(MaxX * 0.94, beginY , "日");
    textbox(GenUIID(0), MaxX * 0.915, beginY-=1.5*FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);
    textbox(GenUIID(0), MaxX * 0.955, beginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "采样天数");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, DateLength, 20);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "预测天数");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, PredictLength, 20);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "模型阶数");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, Poly, 20);

    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    
    

    if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 4, MaxX * 0.05, FontHeight * 2, "预测")) {

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
 

    if (NowShowTable == PreHead) {   //如果展示预测就不显示这个按钮
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "还原")) {

            NowShowTable = head;   //改变视图   改为展示原来已有的数据
            IsPredict = FALSE;
            Calculate(NowShowTable);   //重新计算
        }
    }
}
string GetDate(int month, int day) {

    while (day > MonthDate[month]) {
        day -= MonthDate[month];
        month++;
        if (month > 12)
            month -= 12;
    }    //算出几月几日
    char tmpdate[20] = "";
    sprintf(tmpdate, "%d月%d日", month, day);   //赋值

    string ans = (string)malloc(sizeof(tmpdate) + 1);
    strcpy(ans, tmpdate);
    
    return ans;

}
void  PreparePredict(stu_Ptr HEAD,int Date[4]) { //预测数据的链表也带头节点

    char TargetDate[20] = "";
    
    double coefficient[7] = { 0 };

    double* x = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    double *y = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    stu_Ptr OldPtr=HEAD;    // 原来HEAD存的是原数据表上的 不能对这个进行操作   应该先存起来   先把原来表上的那个指针的存起来 ，一会跑数据的时候用得到
    stu_Ptr tmp1 = OldPtr,tmp2;
    PreHead = (stu_Ptr)malloc(sizeof(struct stu));



    int HaveNum = 0;    //原来里可能没有我们需要的那么多   先记下来
    while (tmp1 != NULL&&HaveNum<Date[2]) {    //date【2】里是应该采集的数据量
        HaveNum++;
        tmp1 = tmp1->next;        
    }   //现在havenum里 是可以采集的数据量
     
    //根据可以采集的开始malloc

    tmp1 = PreHead;
    int i;
    for (i = 0; i < HaveNum + Date[3]; i++) {
        tmp2 = (stu_Ptr)malloc(sizeof(struct stu));
        tmp1->next = tmp2;
        tmp1 = tmp1->next;
    }    //创建链表
    tmp1->next = NULL;


    for (int i = 1; i <= TotalColumnNum; i++) {
        
        int nownum = 0;
        memset(x, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(y, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(coefficient, 0, sizeof(double) * 6);
        tmp1 = OldPtr;
        while (tmp1 != NULL && nownum < HaveNum) {
            x[nownum] = nownum + 1;
            y[nownum] = tmp1->Data[i];    //x坐标为1,2,3,4.....,，y坐标为人数
            nownum++;
            tmp1 = tmp1->next;
        }
       
        polyfit1(nownum, x, y, PolyNum, coefficient);  //进行计算  将算得的多项式拟合的系数放到coefficient里

        for (int i = 0; i < nownum; i++) {
            printf("第 %d个x为%lf y为%lf", i, x[i], y[i]);
        }
        printf("\n");
        for (int i = 0; i <= PolyNum; i++) {
            printf("第%d个系数为%lf   ", i, coefficient[i]);
        }
        printf("\n");
        nownum = 0;
        tmp1 = PreHead->next;   //有头节点   开始塞数据了
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
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(PredictLength) || !strcmp(InputMonth, "月")||!strlen(poly) || !strcmp(InputDay, "日") || InputMonth[0] < 0 || InputDay[0] < 0) {

        strcpy(WrongTip, "请输入完整数据");
        return FALSE;
    }   //如果是空的  或者还是初始的月  日   直接返回

    int month = atoi(InputMonth), day = atoi(InputDay), Datelen = atoi(DateLength), Predict = atoi(PredictLength),polynum=atoi(poly);   //如果异常直接atoi返回0
    if (month <= 0 || month > 12) {
        strcpy(WrongTip, "请输入正确月份");
        return FALSE;
    }
    if (day <= 0 || day > 31)
    {
        strcpy(WrongTip, "请输入正确日期");
        return FALSE;
    }
    if (!Datelen) {
        strcpy(WrongTip, "请输入正确长度");
        return FALSE;
    }
    if (Datelen > 20) {
        strcpy(WrongTip, "采样天数不能超过20哦");
        return FALSE;
    }
    if (!Predict) {
        strcpy(WrongTip, "请输入正确预测");
        return FALSE;
    }
    if (Predict > 20) {
        strcpy(WrongTip, "预测天数不能超过20哦");
        return FALSE;
    }
    if (polynum <= 0)
    {
        strcpy(WrongTip, "模型阶数错误");
        return FALSE;
    }
    if (polynum > 5) {
        strcpy(WrongTip, "阶数太大了呜");
        return FALSE;
    }
    if (FindDate(month, day)) {
        WrongTip = "";
        ans[0] = month, ans[1] = day, ans[2] = Datelen, ans[3] = Predict;
        PolyNum = polynum;
        return TRUE;
    }
    else {
        strcpy(WrongTip, "日期未找到");
        return FALSE;
    }

}
BOOL FindDate(int month, int day) {
    char TargetDate[20] = "";
    sprintf(TargetDate, "%d月%d日",month, day);
   // printf("TargetDate is %s\n", TargetDate);

    PredictHead = head;

    stu_Ptr tmp = head->next;   //重申一遍  head有头节点

    while (tmp!=NULL)
    {
        if (!strcmp(tmp->Date, TargetDate)) {  //如果找到了
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