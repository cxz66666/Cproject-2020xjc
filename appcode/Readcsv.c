#pragma once 
#include"MyData.h"

BOOL SaveToCsv(stu_Ptr HEAD);
BOOL SaveCSV(string InputName,stu_Ptr HEAD);
BOOL ReadCSVFile(char *Name);
BOOL CheckSaveName(string InputName, string WrongAns);

/*ģ��c++���岿��stod/stoi����*/
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
    string ans = (string)malloc(sizeof(char)*(N + 6));  //���鿪���ֹfreeʱ�����
    
    tmp = num;

    ans[N] = '\0';

    N--;
    if (num < 0) {   //������������������
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
    ptr = head;  //��ͷ����   ע��!!!!!!!!

    /*  !!!!  ע���˴�ͷ�ڵ�   �𱻿���   ΪɶҪ��   ��������д��   !!!!*/

    int num = 0; //num������¼��ǰ���ڼ�����
    FILE *fp = fopen(Name, "r+");
    // printf("%s\n",Name);
    if (fp == NULL)
    {
        printf("NULL");
        MyError = -1;  //���û�򿪾�Ҫ������
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
            else  //������ڶ�ȡ��һ��
            {
                ColumnName[num - 1] = (char *)malloc(sizeof(buffer) + 1); //����ŵ���ÿ�еı�ͷ   ��һ�������� ��������   ���е�ColumnName����һ��ʼ����
                strcpy(ColumnName[num - 1], buffer);
                // printf("%s\n", ColumnName[num - 1]);
            }
            if (!flag && flagbuffer[0] == 10) {   //����������  10���ǻ���
                flag = 1;  //flag��־�Ƿ�ʼ����struct
                TotalColumnNum = num-1  ;   //��һ��ԭ��������"����" 
                printf("num is %d\n", num);

            }
        }
        //printf("wanshi");
        fclose(fp);
        return 1;
    }
}


BOOL SaveToCsv(stu_Ptr HEAD) {
    //��HEAD������ݱ��浽csv�ļ�

    static char tips[] = "�����뱣���ļ���";
    static char WrongAns[20] = "";
    static char  InputName[20] = "";
    drawLabel(MaxX / 2 - TextStringWidth(tips)/2, MaxY / 2 + 2 * FontHeight, tips);

    setTextBoxColors("TextBoxFrame", "TextBoxLabel", "TextBoxFrameHot", "TextBoxLabel", 0);

    textbox(GenUIID(0), MaxX / 2 -TextStringWidth(tips)/2, MaxY / 2 - 1, TextStringWidth(tips), FontHeight * 2, InputName, 15);

    if (button(GenUIID(0), MaxX / 2 - TextStringWidth(tips) / 2, MaxY / 2 - 2, 0.6, FontHeight * 1.2, "ȷ��")) {

        if (CheckSaveName(InputName, WrongAns)) {
           if( !SaveCSV(InputName,HEAD))  //���û����ɹ�
               strcpy(WrongAns," ����ʧ��");
           else{
               IsSavingOK = TRUE;
               IsSave = 0;
           }
        }
        SetPenColor("Black");
        SetPenSize(2);
        drawLabel(MaxX / 2 - TextStringWidth(WrongAns), MaxY / 2 - 2.5, WrongAns);
        
    }
    if (button(GenUIID(0), MaxX / 2 + TextStringWidth(tips) / 2-0.6, MaxY / 2 - 2, 0.6, FontHeight * 1.2, "ȡ��")) {

       
        IsSave = 0;
    }


    return TRUE;
}
BOOL SaveCSV(string InputName,stu_Ptr HEAD) {
    FILE *fp= fopen(InputName, "w+");  //ʹ��w+�����ļ�д��
    if (fp == NULL)  //û��ֱ�ӷ���
        return FALSE;

    /*д���һ��*/
    fprintf(fp, "����,");
    int i;
    for ( i= 1; i <= TotalColumnNum; i++) {   //��ÿһ�����ݶ�д��
        fprintf(fp,"%s", ColumnName[i]);
        fprintf(fp,",");
    }
    fprintf(fp, "\n");

    stu_Ptr tmp = HEAD->next;

    /*д��ÿ�����ڲ����Ƿ�ѡ��*/
    while (tmp != NULL) {
        fprintf(fp, "%s,", tmp->Date);
        for (i = 1; i <= TotalColumnNum; i++) {
            fprintf(fp, "%d,", tmp->Data[i]);
        }
        fprintf(fp, "\n");
        tmp = tmp->next;
    }
    if (fp != NULL) {
        fclose(fp);   //�ر�fp���ҷ���
        return TRUE;
    }
    else {
        return FALSE;
    }

}
BOOL CheckSaveName(string InputName, string WrongAns) {
    //��鱣�������  ע����Ҫ����*.csv�ſ���
    int i;
    int flag = 0;
    for (i = 0; InputName[i]; i++) {
        if (InputName[i] == '.') {
            if (InputName[i + 1] == 'c' && InputName[i + 2] == 's' && InputName[i + 3] == 'v') {   //���û�ҵ�.csvֱ�ӱ��������
                strcpy(WrongAns, "�ɹ�����");
                flag = 1;
                return TRUE;
            }
        }
    }
    if (!flag) {
        strcpy(WrongAns, "��������ȷ����");
        return FALSE;
    
    }
    else {
        return TRUE;
    }
}