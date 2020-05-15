#pragma once 
#include"MyData.h"

BOOL SaveToCsv(stu_Ptr HEAD);
BOOL SaveCSV(string InputName,stu_Ptr HEAD);
BOOL ReadCSVFile(char *Name);
BOOL CheckSaveName(string InputName, string WrongAns);

/*模仿c++定义部分stod/stoi函数*/
double stod(string str)    //string to double
{ 
    double ans;
    sscanf(str, "%lf", &ans);
    return ans;
}
int stoi(string str)  //string to int 
{
    int ans;
    sscanf(str, "%d", &ans);
    return ans;
}

string tostring(int num) {
    int tmp = num;
    int N = 0;
    while (tmp) {
        N++;
        tmp /= 10;
    }
    string ans = (string)malloc(sizeof(char)*(N + 6));  //数组开大防止free时候出错
    
    tmp = num;

    ans[N] = '\0';

    N--;
    if (num < 0) {   //如果负数情况特殊讨论
        N++;
        ans[N + 1] = '\0';
        ans[0] = '-';
    }
    tmp = abs(tmp);
    while (tmp) {
        ans[N] = tmp % 10+'0';
        tmp /= 10;
        N--;
    }
    return  ans;
}

BOOL ReadCSVFile(char *Name)
{
    head = (stu_Ptr)malloc(sizeof(struct stu));
    ptr = head;  //带头结点的   注意!!!!!!!!

    /*  !!!!  注意了带头节点   别被坑了   为啥要带   我懒得重写了   !!!!*/

    int num = 0; //num用来记录当前到第几个了
    FILE *fp = fopen(Name, "r+");
    // printf("%s\n",Name);
    if (fp == NULL)
    {
        printf("NULL");
        MyError = -1;  //如果没打开就要报错了
        return 0;
    }

    else
    {
        int flag = 0;
        char buffer[256];
        char flagbuffer[10];
                             
        while (fscanf(fp, "%[^,\n]", buffer) != EOF) //   使用部分正则表达式  buffer里放的是数据   flagbuffer里放的是,或者\n  flag是第一行是否读取完毕  是否应该进入读取日期模式
        {
            num++;
            fgets(flagbuffer, 2, fp); //读取一个逗号
          
            if (flag)
            {
                int tmpnum = num % (TotalColumnNum + 1);
                /*只有三种情况   0  1  其他 
                0是需要挂载节点
                1是需要申请  初始化节点
                其他需要赋值
                */
                switch (tmpnum)
                {
                case 1:
                    STU = (stu_Ptr)malloc(sizeof(struct stu));

                    STU->IsSelect = TRUE;
                    STU->IsShowNum = FALSE;
                    strcpy(STU->Nowcolor, COLOR[FileTotalNum % (sizeof(COLOR) / sizeof(COLOR[0]))]);
                    strcpy(STU->Changedcolor, "Pink");
                    STU->Date = (char *)malloc(sizeof(buffer) + 1);
                    strcpy(STU->Date, buffer);
                    FileTotalNum++;
                    /* code */
                    break;
                case 0:
                    STU->Data[TotalColumnNum] = stoi(buffer);
                    STU->next = NULL;
                    ptr->next = STU;
                    ptr = ptr->next;
                    break;
                default:
                    STU->Data[tmpnum - 1] = stoi(buffer);
                    break;
                }
            }
            else  //如果正在读取第一列
            {
                ColumnName[num - 1] = (char *)malloc(sizeof(buffer) + 1); //这里放的是每列的表头   第一个是日期 所以跳过   所有的ColumnName都从一开始计数
                strcpy(ColumnName[num - 1], buffer);
                // printf("%s\n", ColumnName[num - 1]);
            }
            if (!flag && flagbuffer[0] == 10) {   //读到换行了  10就是换行
                flag = 1;  //flag标志是否开始创建struct
                TotalColumnNum = num-1  ;   //减一的原因是算了"日期" 
                printf("num is %d\n", num);

            }
        }
        //printf("wanshi");
        fclose(fp);
        return 1;
    }
}


BOOL SaveToCsv(stu_Ptr HEAD) {
    //将HEAD里的数据保存到csv文件

    static char tips[] = "请输入保存文件名";
    static char WrongAns[20] = "";
    static char  InputName[20] = "";
    drawLabel(MaxX / 2 - TextStringWidth(tips)/2, MaxY / 2 + 2 * FontHeight, tips);

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    textbox(GenUIID(0), MaxX / 2 -TextStringWidth(tips)/2, MaxY / 2 - 1, TextStringWidth(tips), FontHeight * 2, InputName, 15);

    if (button(GenUIID(0), MaxX / 2 - TextStringWidth(tips) / 2, MaxY / 2 - 2, 0.6, FontHeight * 1.2, "确认")) {

        if (CheckSaveName(InputName, WrongAns)) {
           if( !SaveCSV(InputName,HEAD))  //如果没保存成功
               strcpy(WrongAns," 保存失败");
           else{
               IsSavingOK = TRUE;
               IsSave = 0;
           }
        }
        SetPenColor("Black");
        SetPenSize(2);
        drawLabel(MaxX / 2 - TextStringWidth(WrongAns), MaxY / 2 - 2.5, WrongAns);
        
    }
    if (button(GenUIID(0), MaxX / 2 + TextStringWidth(tips) / 2-0.6, MaxY / 2 - 2, 0.6, FontHeight * 1.2, "取消")) {

       
        IsSave = 0;
    }


    return TRUE;
}
BOOL SaveCSV(string InputName,stu_Ptr HEAD) {
    FILE *fp= fopen(InputName, "w+");  //使用w+进行文件写入
    if (fp == NULL)  //没打开直接返回
        return FALSE;

    /*写入第一行*/
    fprintf(fp, "日期,");
    int i;
    for ( i= 1; i <= TotalColumnNum; i++) {   //将每一列数据都写入
        fprintf(fp,"%s", ColumnName[i]);
        fprintf(fp,",");
    }
    fprintf(fp, "\n");

    stu_Ptr tmp = HEAD->next;

    /*写入每个日期不管是否选中*/
    while (tmp != NULL) {
        fprintf(fp, "%s,", tmp->Date);
        for (i = 1; i <= TotalColumnNum; i++) {
            fprintf(fp, "%d,", tmp->Data[i]);
        }
        fprintf(fp, "\n");
        tmp = tmp->next;
    }
    if (fp != NULL) {
        fclose(fp);   //关闭fp并且返回
        return TRUE;
    }
    else {
        return FALSE;
    }

}
BOOL CheckSaveName(string InputName, string WrongAns) {
    //检查保存的名字  注意需要满足*.csv才可以
    int i;
    int flag = 0;
    for (i = 0; InputName[i]; i++) {
        if (InputName[i] == '.') {
            if (InputName[i + 1] == 'c' && InputName[i + 2] == 's' && InputName[i + 3] == 'v') {   //如果没找到.csv直接报错就完事
                strcpy(WrongAns, "成功保存");
                flag = 1;
                return TRUE;
            }
        }
    }
    if (!flag) {
        strcpy(WrongAns, "请输入正确名称");
        return FALSE;
    
    }
    else {
        return TRUE;
    }
}