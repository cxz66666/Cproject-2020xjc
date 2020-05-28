

static BOOL SaveCSV(string InputName, CaseNode_Ptr HEAD); //����csv�ļ���ʵ��

static BOOL CheckSaveName(string InputName, string WrongAns); //����ļ�����

/*ģ��c++���岿��stod/stoi����*/
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
{ //��Ҫ�ֶ�free�� �����
    int tmp = num;
    int N1 = 0;
    while (tmp)
    {
        N1++;
        tmp /= 10;
    }
    string ans = (string)malloc(sizeof(char) * (N1 + 6)); //���鿪���ֹfreeʱ�����

    tmp = num;

    ans[N1] = '\0';

    N1--;
    if (num < 0)
    { //������������������
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
    ptr = FileHead; //��ͷ����   ע��!!!!!!!!
    FileHead->next = NULL;

    /*  !!!!  ע���˴�ͷ�ڵ�   �𱻿���   ΪɶҪ��   ��������д��   !!!!*/

    int num = 0; //num������¼��ǰ���ڼ�����
    FILE *fp = fopen(Name, "r+");
    //printf("%s\n",Name);
    if (fp == NULL)
    {
        //printf("NULL");

        MyError = -1; //���û�򿪾�Ҫ������
        return 0;
    }

    else
    {
        int flag = 0;
        char buffer[256];
        char flagbuffer[10];

        while (fscanf(fp, "%[^,\n]", buffer) != EOF) //   ʹ�ò���������ʽ  buffer��ŵ�������   flagbuffer��ŵ���,����\n  flag�ǵ�һ���Ƿ��ȡ���  �Ƿ�Ӧ�ý����ȡ����ģʽ
        {
            num++;
            fgets(flagbuffer, 2, fp); //��ȡһ������

            if (flag)
            {
                int tmpnum = num % (TotalColumnNum + 1);
                /*ֻ���������   0  1  ���� 
                0����Ҫ���ؽڵ�
                1����Ҫ����  ��ʼ���ڵ�
                ������Ҫ��ֵ
                */
                switch (tmpnum)
                {
                case 1:
                    CaseNodePtr = (CaseNode_Ptr)malloc(sizeof(struct CaseNode)); //����
                    CaseNodePtr->IsSelect = TRUE;                                //���¾�Ϊ��ʼ��
                    CaseNodePtr->IsShowNum = FALSE;
                    strcpy(CaseNodePtr->Nowcolor, COLOR[FileTotalNum % (sizeof(COLOR) / sizeof(COLOR[0]))]);
                    strcpy(CaseNodePtr->Changedcolor, "Black");
                    CaseNodePtr->Date = (char *)malloc(sizeof(buffer) + 1);
                    strcpy(CaseNodePtr->Date, buffer);
                    FileTotalNum++;
                    /* code */
                    break;
                case 0: //���ؽڵ�
                    CaseNodePtr->Data[TotalColumnNum] = stoi(buffer);
                    CaseNodePtr->next = NULL;
                    ptr->next = CaseNodePtr;
                    ptr = ptr->next;
                    break;
                default: //д������
                    CaseNodePtr->Data[tmpnum - 1] = stoi(buffer);
                    break;
                }
            }
            else //������ڶ�ȡ��һ��
            {
                ColumnName[num - 1] = (char *)malloc(sizeof(buffer) + 1); //����ŵ���ÿ�еı�ͷ   ��һ�������� ��������   ���е�ColumnName����һ��ʼ����
                strcpy(ColumnName[num - 1], buffer);
                // printf("%s\n", ColumnName[num - 1]);
            }
            if (!flag && flagbuffer[0] == 10)
            { //����������  10���ǻ���
                if (num != 1)
                {                             //num=1Ϊ���ļ�
                    flag = 1;                 //flag��־�Ƿ�ʼ����struct
                    TotalColumnNum = num - 1; //��һ��ԭ��������"����"
                                              // printf("num is %d\n", num);
                }
                else
                {

                    MyError = -2; //�������  -1���ļ�δ��  -2���ļ����˵����ǿյ�
                    return FALSE;
                }
            }
        }

        fclose(fp);
        if (!num) //��һ���ж� ����ļ��ǿյ�  �Ǿͷ���FALSE
        {
            MyError = -2; //�������  -1���ļ�δ��  -2���ļ����˵����ǿյ�
            return FALSE;
        }

        else
            return TRUE;
    }
}

BOOL SaveToCsv(CaseNode_Ptr HEAD)
{
    //��HEAD������ݱ��浽csv�ļ�

    static char tips[] = "�����뱣���ļ���";
    static char WrongAns[20] = "";
    static char InputName[20] = "";
    SetPenColor("Black");
    drawLabel(MaxX / 2 - TextStringWidth(tips) / 2 + 0.3, MaxY / 2 + 2 * FontHeight - 0.5, tips);

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    textbox(GenUIID(0), MaxX / 2 - TextStringWidth(tips) / 2 + 0.3, MaxY / 2 - 1, TextStringWidth(tips), FontHeight * 2, InputName, 15);

    if (button(GenUIID(0), MaxX / 2 - TextStringWidth(tips) / 2 + 0.15, MaxY / 2 - 2, 1, FontHeight * 1.2, "ȷ��"))
    {

        if (CheckSaveName(InputName, WrongAns))
        {
            if (!SaveCSV(InputName, HEAD)) //���û����ɹ�
                strcpy(WrongAns, " ����ʧ��");
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
    if (button(GenUIID(0), MaxX / 2 + TextStringWidth(tips) / 2 - 0.6, MaxY / 2 - 2, 1, FontHeight * 1.2, "ȡ��"))
    {

        IsSave = 0;
    }

    return TRUE;
}
static BOOL SaveCSV(string InputName, CaseNode_Ptr HEAD)
{
    FILE *fp = fopen(InputName, "w+"); //ʹ��w+�����ļ�д��
    if (fp == NULL)                    //û��ֱ�ӷ���
        return FALSE;

    /*д���һ��*/
    fprintf(fp, "����,");
    int i;
    for (i = 1; i <= TotalColumnNum; i++)
    { //��ÿһ�����ݶ�д��
        fprintf(fp, "%s", ColumnName[i]);
        fprintf(fp, ",");
    }
    fprintf(fp, "\n");

    CaseNode_Ptr tmp = HEAD->next;

    /*д��ÿ�����ڲ����Ƿ�ѡ��*/
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
        fclose(fp); //�ر�fp���ҷ���
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
BOOL CheckSaveName(string InputName, string WrongAns)
{
    //��鱣�������  ע����Ҫ����*.csv�ſ���
    SetPenColor("Red");
    int i;
    int flag = 0;
    for (i = 0; InputName[i]; i++)
    {
        if (InputName[i] == '.')
        {
            if (InputName[i + 1] == 'c' && InputName[i + 2] == 's' && InputName[i + 3] == 'v')
            { //���û�ҵ�.csvֱ�ӱ��������
                strcpy(WrongAns, "�ɹ�����");
                flag = 1;
                return TRUE;
            }
        }
    }
    if (!flag)
    {
        strcpy(WrongAns, "��������ȷ��չ��"); //û�ҵ�csv�ļ���չ��
        return FALSE;
    }
    else
    {
        return TRUE; //�ļ�����ȷ
    }
}
