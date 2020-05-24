#pragma once

#include "MyData.h"

#define PREDICT 1

static int PolyNum = 3;
int MonthDate[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };  //月份天数

double  PolyPredictData[MAXCOLUMN+1][10] ; //存放每个数据的拟合阶数     第一个括号为列数  第二个括号为每项的系数  其中 第0项放的是拟合系数  之后 1，2，3...依次防止常数项，一次项，以此类推

void DrawPredict();
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string ploy,int ans[4]);
BOOL FindDate(int month, int day);

void    MyFree(CaseNode_Ptr Head);

void polyfit1(int n, double *x, double *y, int poly_n, double a[]); //a中放的是返回的系数  3阶以上就暴毙
void gauss_solve(int n, double A[], double x[], double b[]);//配合polyfit1食用


void polyfit2(int n, double* x, double* y, int poly_n, double a[]);//这里先把2写出来，有机会的话再进行添加

void  PreparePredict(CaseNode_Ptr HEAD,int Date[4]);
string GetDate(int month, int day);

void FindBestPredict(int n, double* x, double* y, double a[]);

int CalY(int num, double c[]);
void DrawOldPoint(double PointData[][2], int Num);   //画出原来的点
void DrawSelectedInf();
/*==================polyfit(n,x,y,poly_n,a)===================*/
/*=======拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n========*/
/*=====n是数据个数 xy是数据值 poly_n是多项式的项数======*/
/*===返回a0,a1,a2,……a[poly_n]，系数比项数多一（常数项）=====*/


//具体实现过程这里不在赘述   用的是matlab中的polyfit的c语言实现
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
    
#if PREDICT    //方便测试用将初始数据写入
    static char InputMonth[20] = "2", InputDay[20] = "1";
    static char DateLength[20] = "20", PredictLength[20] = "10"; //起始的时间   模型原始数据长度 预测天数
    static char Poly[20] = "";
    static char WrongTip[30] = "";
#else 
    static char InputMonth[20] = "", InputDay[20] = "";
    static char DateLength[20] = "", PredictLength[20] = ""; //起始的时间   模型原始数据长度 预测天数
    static char Poly[20] = "";
    static char WrongTip[30] = "";
#endif // PREDICT

    int ans[4] = { 0 };   //分别记录Inputmonth，day ，datelength，predictlength
   static BOOL ISOK = TRUE;  //是否需要提示
    SetPenColor("TextBoxLabel");
    SetPenSize(3);
    double beginY = MaxY * 0.8;
    drawLabel(MaxX * 0.9-0.3, beginY, "预测起始日期");

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    drawLabel(MaxX * 0.915, beginY -= FontHeight * 3, "月");
    drawLabel(MaxX * 0.96, beginY , "日");
    textbox(GenUIID(0), MaxX * 0.89, beginY-=1.5*FontDescent, MaxX * 0.02, FontHeight * 1.3, InputMonth, 3);   //输入的日月
    textbox(GenUIID(0), MaxX * 0.935, beginY, MaxX * 0.02, FontHeight * 1.3, InputDay, 3);

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "采样天数");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, DateLength, 20);    //输入的采样天数

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "预测天数");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, PredictLength, 20);   //预测天数

    drawLabel(MaxX * 0.9, beginY -= FontHeight * 2, "模型阶数");
    textbox(GenUIID(0), MaxX * 0.9, beginY -= FontHeight * 3, MaxX * 0.04, FontHeight * 1.3, Poly, 20);

    setButtonColors("DirSelectionFrame", "White", "DirSelectionFrameHot", "White", 1);
    
    

    if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 4, MaxX * 0.05, FontHeight * 2, "预测")) {

        if (CheckPredict(WrongTip, InputMonth, InputDay, DateLength, PredictLength,Poly, ans)) {
            
            if (IsPredict)
                MyFree(PreHead);//这一步很关键   如果之前没有free过就不进行free  否则free之前的
            NowDateNum = NowDateColumn = 0;
            
            PreparePredict(PredictHead,ans);  //申请内存    计算数据  提前计算好存到preHead里
            IsPredict = TRUE;
            ISOK = TRUE;
            memset(InputMonth, 0, sizeof(InputMonth));
            memset(InputDay, 0, sizeof(InputDay));
            memset(DateLength, 0, sizeof(DateLength));
            memset(PredictLength, 0, sizeof(PredictLength));
            memset(Poly, 0, sizeof(Poly));
            memset(WrongTip, 0, sizeof(WrongTip));  //对每个数组都置零
            memset(ans, 0, sizeof(ans));    //重新清零

            NowShowTable = PreHead;
            ChangeIsSelect(NowShowTable);  //日期选中上限为20个
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
        drawLabel(0.99 * MaxX - TextStringWidth(WrongTip), beginY -= 2 * FontHeight, WrongTip);   //错误提示
    
        SetPenSize(1);
    }
 

    if (NowShowTable == PreHead) {   //如果展示预测就不显示这个按钮
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "还原")) {

            NowShowTable = FileHead;   //改变视图   改为展示原来已有的数据
            IsPredict = FALSE;
            NowDateNum = NowDateColumn = 0;
            Calculate(NowShowTable);   //重新计算
        }
    }
    if (!IsChangeNum) {   //如果展示预测就不显示这个按钮
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "更改数据")) {

            IsChangeNum = TRUE;
        }
    }
    else {
        if (button(GenUIID(0), MaxX * 0.90, beginY -= FontHeight * 3, MaxX * 0.05, FontHeight * 2, "撤销更改")) {


            IsChangeNum = FALSE;
          CaseNode_Ptr  tmp = NowShowTable->next;    //遍历当前展示的数据将所有IsShowNum改为FALSE
            while (tmp!=NULL)
            {
                tmp->IsShowNum = FALSE;
                tmp = tmp->next;
            }
        }
    }
} 
string GetDate(int month, int day) {    //初始month   初始day+走过的day

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
void  PreparePredict(CaseNode_Ptr HEAD,int Date[4]) { //预测数据的链表也带头节点

    char TargetDate[20] = "";
    int OldPolyNum = PolyNum;
    double coefficient[7] = { 0 };

    double* x = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    double *y = (double*)malloc(sizeof(double) * (Date[2] + Date[3]));
    CaseNode_Ptr OldPtr=HEAD;    // 原来HEAD存的是原数据表上的 不能对这个进行操作   应该先存起来   先把原来表上的那个指针的存起来 ，一会跑数据的时候用得到
    CaseNode_Ptr tmp1=NULL ,tmp2=NULL;
    tmp1 = HEAD;
    PreHead = (CaseNode_Ptr)malloc(sizeof(struct CaseNode));



    int HaveNum = 0;    //原来里可能没有我们需要的那么多   先记下来
    while (tmp1 != NULL&&HaveNum<Date[2]) {    //date【2】里是应该采集的数据量
        HaveNum++;
        tmp1 = tmp1->next;        
    }   //现在havenum里 是可以采集的数据量
     
    //根据可以采集的开始malloc

    tmp1 = PreHead;
    int i,j;
    for (i = 0; i < HaveNum + Date[3]; i++) {
        tmp2 = (CaseNode_Ptr)malloc(sizeof(struct CaseNode));
        memset(tmp2->Data, 0, sizeof(tmp2->Data));
        tmp2->Date = NULL;
        tmp1->next = tmp2;
        tmp1 = tmp1->next;
    }    //创建链表
    tmp1->next = NULL;


    for ( i = 1; i <= TotalColumnNum; i++) {
        
        int nownum = 0;
        
        memset(x, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(y, 0, sizeof(double) * (Date[2] + Date[3]));
        memset(coefficient, 0, sizeof(double) * 6);
        tmp1 = OldPtr;
        while (tmp1 != NULL && nownum < HaveNum) {
            x[nownum] = nownum + 1.0;
            y[nownum] = tmp1->Data[i];    //x坐标为1,2,3,4.....,，y坐标为人数
            nownum++;
            tmp1 = tmp1->next;
        }
       
        if (PolyNum == -1) {
            FindBestPredict(nownum, x, y, coefficient);  //将polynum置为合适的值 0-5之间
           
        }
       
       if(PolyNum>0)   //如果不是0
        polyfit1(nownum, x, y, PolyNum, coefficient);  //进行计算  将算得的多项式拟合的系数放到coefficient里
       else if(!PolyNum){
           for (j = 0; j < nownum; j++)
               y[j] = log(y[j]);

           polyfit1(nownum, x, y, 1, coefficient);
       }
       PolyPredictData[i][0] = PolyNum;
       for ( j = 0; j <= PolyNum; j++)
           PolyPredictData[i][j + 1] = coefficient[j];
      
      // printf("第%d个数据的拟合阶数为%d\n", i, PolyNum);
   /*    printf("最佳拟合系数为%d\n", PolyNum);
        for (int i = 0; i < nownum; i++) {
            printf("第 %d个x为%lf y为%lf", i, x[i], y[i]);
        }
        printf("\n");
        for (int i = 0; i <= PolyNum; i++) {
            printf("第%d个系数为%lf   ", i, coefficient[i]);
        }
        printf("\n");*/

        nownum = 0;
        tmp1 = PreHead->next;   //有头节点   开始塞数据了
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

        
        PolyNum = OldPolyNum; //重置为初始的系数方便循环遍历
        

    }
         
   
}

void FindBestPredict(int n, double* x, double* y, double a[]) {
    int Findpoly=0;   //目的阶数
    int i, j;
    double R_2 = -100;
    double TmpR_2;

    double AverageY = 0;

    for (i = 0; i < n; i++) {
        AverageY += y[i];
    }
    AverageY /= n;


    for (i = 0; i <= 5; i++) {
        double SSE = 0, SST = 0;   //SSR为回归平方和，SSE为残差平方和，SST为总离差平方和
            if (!i)
            for (j = 0; j < n; j++) {
                y[j] = log(y[j]);

            }   //如果i是0先取对数

            if (i) {
                polyfit1(n, x, y, i, a);
                if (a[i] < 0)
                    continue;
            }
            
            else {
                polyfit1(n, x, y, 1, a);   //如果是i=0 那就用线性的lny=lnk+ax
                if (a[1] < 0)
                {
                    for (j = 0; j < n; j++) 
                        y[j] = exp(y[j]);
                    
                    continue;
                }
                   
            }
         
        
        PolyNum = i;  //先置为i
        for (j = 0; j < n; j++) {
            double tmp = CalY(j + 1, a);
            SSE += pow((y[j] - tmp), 2);
            SST += pow(y[j] - AverageY, 2);
        }


        TmpR_2 = 1.0 - SSE / SST; //关键一步

       // printf("第%d个模型拟合度为%lf\n", i, TmpR_2);

        if (TmpR_2 > R_2) {   //如果更加拟合
            R_2 = TmpR_2;
            Findpoly = i;
        }

        if (!i)  //如果刚才取了对数 那就重新变回去 防止影响后续使用
        {
            for (j = 0; j < n; j++) {
                y[j] = exp(y[j]);
                
            }
           
        }
    }
    PolyNum = Findpoly;
}
int CalY(int num, double  c[]) {  //计算Y的值  分情况讨论
    double ans = 0;
    int i=0;
    if (PolyNum) {
        for (i = 0; i <= PolyNum; i++) {    //如果是多项式拟合  就按这样算
        ans += pow(num, i) * c[i];
        }
    }
    
    else {
            ans= exp(c[0]) * exp(num * c[1]);  //如果是指数拟合  就这样算
    }
    return (int)ans;

}
/*进行检查的函数  看着很多 其实思路很简单*/
//使用atoi而不是stoi
BOOL CheckPredict(string WrongTip, string InputMonth, string InputDay, string  DateLength, string PredictLength, string poly,int ans[4]) {
    if (!strlen(InputMonth) || !strlen(InputDay) || !strlen(DateLength) || !strlen(PredictLength) || !strcmp(InputMonth, "月") ||!strcmp(InputDay, "日") || InputMonth[0] < 0 || InputDay[0] < 0) {

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
    if (Datelen <10) {
        strcpy(WrongTip, "采样天数不能少于10哦");
        return  FALSE;
    }
    if (!Predict) {
        strcpy(WrongTip, "请输入正确预测");
        return FALSE;
    }
    if (Predict > 20) {
        strcpy(WrongTip, "预测天数不能超过20哦");
        return FALSE;
    }
    if (!strlen(poly)) {
        polynum = -1;
    }
    else  if (polynum < 0)
    {
        strcpy(WrongTip, "模型阶数错误");
        return FALSE;
    }
    else if (polynum > 5) {
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
    sprintf(TargetDate, "%d月%d日",month, day); //写入目标天数
   // printf("TargetDate is %s\n", TargetDate);

    PredictHead = FileHead;

    CaseNode_Ptr tmp = FileHead->next;   //重申一遍  FileHead有头节点

    while (tmp!=NULL)
    {
        if (!strcmp(tmp->Date, TargetDate)) {  //如果找到了
            PredictHead = tmp;
            printf("zhaodaole\n");
            break;
        }
        tmp = tmp->next;
    }
    if (PredictHead != FileHead)   //如果不等于说明找到了
        return TRUE;
    else return FALSE;

}

void    MyFree(CaseNode_Ptr Head) {

    if (Head == NULL)
        return;
    CaseNode_Ptr next=Head,tmp=Head;
   
    next = tmp->next;
    free(tmp);   //头节点单独释放
    
    tmp = NULL;

    while (next!=NULL)
    {
        tmp =next; 
        next = tmp->next;
        free(tmp->Date);   //日期单独释放
        free(tmp);  //其余正常释放
    }
   
}
void DrawSelectedInf() {
    char OutChoosed[100];
    int NowChooseColumn = 0;
    memset(OutChoosed, 0, sizeof(OutChoosed));
    if (IsChooseLine) {  //如果选择的是直线
        sprintf(OutChoosed, "当前选中直线为%s", ColumnName[ChooseLineNum]);
        NowChooseColumn = ChooseLineNum;
    }
    else if (IsChooseHistogram) {   //如果选择的是柱状图
        sprintf(OutChoosed, "当前选中柱状图为%s", ColumnName[ChooseHistogramNum]);
        NowChooseColumn = ChooseHistogramNum;
    }
    else return;
    if (strlen(OutChoosed)) {
        SetPenColor("PreWordColor");
        SetPenSize(2);
        MovePen(beginTableX + 0.5, MaxY * 0.9);
        DrawTextString( OutChoosed);    //画出当前选中参数
    }
    if (IsPredict) {
        MovePen(beginTableX  +0.5, MaxY * 0.9-FontHeight*2);
        sprintf(OutChoosed, "模型阶数为%.0lf阶", PolyPredictData[NowChooseColumn][0]);
        DrawTextString(OutChoosed);
        memset(OutChoosed, 0, sizeof(OutChoosed));
        strcpy(OutChoosed, "拟合曲线方程为y=");   //画出拟合曲线的方程
        int i;
        char OutEquationTmp[20];
        for (i = 0; i <= PolyPredictData[NowChooseColumn][0]; i++) {
            if (!i)   //常数项
                sprintf(OutEquationTmp, "%.1lf", PolyPredictData[NowChooseColumn][1]);
            else if(i==1)//一次项
                sprintf(OutEquationTmp, "%.1lfx", PolyPredictData[NowChooseColumn][2]);
            else   sprintf(OutEquationTmp, "%.1lfx^%d", PolyPredictData[NowChooseColumn][i+1],i);  //二次以上的项
            strcat(OutChoosed, OutEquationTmp);
            if (i != PolyPredictData[NowChooseColumn][0])
                if(PolyPredictData[NowChooseColumn][i+2]>0)
                strcat(OutChoosed, "+");   //如果不是负数就加上加号

        }
        printf("%s\n", OutChoosed);
        MovePen((beginTableX + StaticendTableX) / 2 , MaxY * 0.9 );
        DrawTextString(OutChoosed);
    }
}
//画出原始数据的小圆点
void ShowOldPoint() {   
    if (IsPredict && (IsChooseLine || IsChooseHistogram))
    {
        int i,column = 0;
        column = IsChooseLine ? ChooseLineNum : ChooseHistogramNum;      //如果选的是直线就用直线的 否则就用柱状图的
        if (PreHead == NULL)   //如果是NULL 就返回
            return;
        CaseNode_Ptr tmp1 = PredictHead, tmp2 = NowShowTable->next;  //tmp1存的是原始数据  tmp2是预测数组
        double PointData[MAXDATE + 1][2] = { 0 };
        int nownum = 0;
        while (tmp1 != NULL && tmp2 != NULL) {   //类似于归并排序
            if (tmp2->IsSelect) {
                if (!strcmp(tmp1->Date, tmp2->Date)) {   //两者日期相等
                    nownum++;
                    PointData[nownum][0] = nownum ;
                    PointData[nownum][1] = tmp1->Data[column];
                    tmp1 = tmp1->next;  //如果两个都相等   两者全部进入下一个
                    tmp2 = tmp2->next;
                }
                else {
                    tmp1 = tmp1->next;   //否则原始数据进入下一个
                }
            }
            else {
                tmp2 = tmp2->next;   //如果tmp2没被选中  now数据进入下一个
            }
        }
        if (nownum) {
            for (i = 1; i <= nownum; i++) {
                PointData[i][0] = beginTableX + i * PerX;    //把x数据写入
                PointData[i][1] = beginTableY + PointData[i][1] * PerY;   //计算出y数据
            }
            DrawOldPoint(PointData, nownum);   //画出数据
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