

static BOOL SaveCSV(string InputName, CaseNode_Ptr HEAD); //保存csv文件的实现

static BOOL CheckSaveName(string InputName, string WrongAns); //检查文件名称

/*模仿c++定义部分stod/stoi函数*/
double stod(string str) //string to double
{
    double ans;
    sscanf(str, "%lf", &ans);
    return ans;
}
int stoi(string str) //string to int
{
    int ans;
    sscanf(str, "%d", &ans);
    return ans;
}

string tostring(int num)
{ //需要手动free了 用完后
    int tmp = num;
    int N1 = 0;
    while (tmp)
    {
        N1++;
        tmp /= 10;
    }
    string ans = (string)malloc(sizeof(char) * (N1 + 6)); //数组开大防止free时候出错

    tmp = num;

    ans[N1] = '\0';

    N1--;
    if (num < 0)
    { //如果负数情况特殊讨论
        N1++;
        ans[N1 + 1] = '\0';
        ans[0] = '-';
    }
    tmp = abs(tmp);
    while (tmp)
    {
        ans[N1] = tmp % 10 + '0';
        tmp /= 10;
        N1--;
    }
    return ans;
}

BOOL ReadCSVFile(char *Name)
{
    FileHead = (CaseNode_Ptr)malloc(sizeof(struct CaseNode));
    ptr = FileHead; //带头结点的   注意!!!!!!!!
    FileHead->next = NULL;

    /*  !!!!  注意了带头节点   别被坑了   为啥要带   我懒得重写了   !!!!*/

    int num = 0; //num用来记录当前到第几个了
    FILE *fp = fopen(Name, "r+");
    //printf("%s\n",Name);
    if (fp == NULL)
    {
        //printf("NULL");

        MyError = -1; //如果没打开就要报错了
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
                    CaseNodePtr = (CaseNode_Ptr)malloc(sizeof(struct CaseNode)); //申请
                    CaseNodePtr->IsSelect = TRUE;                                //以下均为初始化
                    CaseNodePtr->IsShowNum = FALSE;
                    strcpy(CaseNodePtr->Nowcolor, COLOR[FileTotalNum % (sizeof(COLOR) / sizeof(COLOR[0]))]);
                    strcpy(CaseNodePtr->Changedcolor, "Black");
                    CaseNodePtr->Date = (char *)malloc(sizeof(buffer) + 1);
                    strcpy(CaseNodePtr->Date, buffer);
                    FileTotalNum++;
                    /* code */
                    break;
                case 0: //挂载节点
                    CaseNodePtr->Data[TotalColumnNum] = stoi(buffer);
                    CaseNodePtr->next = NULL;
                    ptr->next = CaseNodePtr;
                    ptr = ptr->next;
                    break;
                default: //写入数据
                    CaseNodePtr->Data[tmpnum - 1] = stoi(buffer);
                    break;
                }
            }
            else //如果正在读取第一列
            {
                ColumnName[num - 1] = (char *)malloc(sizeof(buffer) + 1); //这里放的是每列的表头   第一个是日期 所以跳过   所有的ColumnName都从一开始计数
                strcpy(ColumnName[num - 1], buffer);
                // printf("%s\n", ColumnName[num - 1]);
            }
            if (!flag && flagbuffer[0] == 10)
            { //读到换行了  10就是换行
                if (num != 1)
                {                             //num=1为空文件
                    flag = 1;                 //flag标志是否开始创建struct
                    TotalColumnNum = num - 1; //减一的原因是算了"日期"
                                              // printf("num is %d\n", num);
                }
                else
                {

                    MyError = -2; //两种情况  -1是文件未打开  -2是文件打开了但是是空的
                    return FALSE;
                }
            }
        }

        fclose(fp);
        if (!num) //加一步判断 如果文件是空的  那就返回FALSE
        {
            MyError = -2; //两种情况  -1是文件未打开  -2是文件打开了但是是空的
            return FALSE;
        }

        else
            return TRUE;
    }
}

BOOL SaveToCsv(CaseNode_Ptr HEAD)
{
    //将HEAD里的数据保存到csv文件

    static char tips[] = "请输入保存文件名";
    static char WrongAns[20] = "";
    static char InputName[20] = "";
    SetPenColor("Black");
    drawLabel(MaxX / 2 - TextStringWidth(tips) / 2 + 0.3, MaxY / 2 + 2 * FontHeight - 0.5, tips);

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    textbox(GenUIID(0), MaxX / 2 - TextStringWidth(tips) / 2 + 0.3, MaxY / 2 - 1, TextStringWidth(tips), FontHeight * 2, InputName, 15);

    if (button(GenUIID(0), MaxX / 2 - TextStringWidth(tips) / 2 + 0.15, MaxY / 2 - 2, 1, FontHeight * 1.2, "确认"))
    {

        if (CheckSaveName(InputName, WrongAns))
        {
            if (!SaveCSV(InputName, HEAD)) //如果没保存成功
                strcpy(WrongAns, " 保存失败");
            else
            {
                IsSavingOK = TRUE;
                IsSave = 0;
            }
        }
        SetPenColor("Black");
        SetPenSize(2);
        drawLabel(MaxX / 2 - TextStringWidth(WrongAns), MaxY / 2 - 2.5, WrongAns);
    }
    if (button(GenUIID(0), MaxX / 2 + TextStringWidth(tips) / 2 - 0.6, MaxY / 2 - 2, 1, FontHeight * 1.2, "取消"))
    {

        IsSave = 0;
    }

    return TRUE;
}
static BOOL SaveCSV(string InputName, CaseNode_Ptr HEAD)
{
    FILE *fp = fopen(InputName, "w+"); //使用w+进行文件写入
    if (fp == NULL)                    //没打开直接返回
        return FALSE;

    /*写入第一行*/
    fprintf(fp, "日期,");
    int i;
    for (i = 1; i <= TotalColumnNum; i++)
    { //将每一列数据都写入
        fprintf(fp, "%s", ColumnName[i]);
        fprintf(fp, ",");
    }
    fprintf(fp, "\n");

    CaseNode_Ptr tmp = HEAD->next;

    /*写入每个日期不管是否选中*/
    while (tmp != NULL)
    {
        fprintf(fp, "%s,", tmp->Date);
        for (i = 1; i <= TotalColumnNum; i++)
        {
            fprintf(fp, "%d,", tmp->Data[i]);
        }
        fprintf(fp, "\n");
        tmp = tmp->next;
    }
    if (fp != NULL)
    {
        fclose(fp); //关闭fp并且返回
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
BOOL CheckSaveName(string InputName, string WrongAns)
{
    //检查保存的名字  注意需要满足*.csv才可以
    SetPenColor("Red");
    int i;
    int flag = 0;
    for (i = 0; InputName[i]; i++)
    {
        if (InputName[i] == '.')
        {
            if (InputName[i + 1] == 'c' && InputName[i + 2] == 's' && InputName[i + 3] == 'v')
            { //如果没找到.csv直接报错就完事
                strcpy(WrongAns, "成功保存");
                flag = 1;
                return TRUE;
            }
        }
    }
    if (!flag)
    {
        strcpy(WrongAns, "请输入正确扩展名"); //没找到csv文件拓展名
        return FALSE;
    }
    else
    {
        return TRUE; //文件名正确
    }
}
