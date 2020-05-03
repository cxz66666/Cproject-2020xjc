#pragma once 
#include"MyData.h"



BOOL ReadCSVFile(char *Name);

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
    string ans = (string)malloc(N + 1);
    
    tmp = num;

    ans[N] = '\0';

    N--;
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
        MyError = -1;
        return 0;
    }

    else
    {
        int flag = 0;
        char buffer[256];
        char flagbuffer[10];
                             
        while (fscanf(fp, "%[^,\n]", buffer) != EOF) //   �����ʽ  buffer��ŵ�������   flagbuffer��ŵ���,����\n  flag�ǵ�һ���Ƿ�������
        {
            num++;
            fgets(flagbuffer, 2, fp);
          
            if (flag)
            {
                int tmpnum = num % (ChooseDataNum + 1);
                switch (tmpnum)
                {
                case 1:
                    STU = (stu_Ptr)malloc(sizeof(struct stu));

                    STU->IsSelect = TRUE;
                    strcpy(STU->Nowcolor, COLOR[FileTotalNum % (sizeof(COLOR) / sizeof(COLOR[0]))]);
                    strcpy(STU->Changedcolor, "Pink");
                    STU->Date = (char *)malloc(sizeof(buffer) + 1);
                    strcpy(STU->Date, buffer);
                    FileTotalNum++;
                    /* code */
                    break;
                case 0:
                    STU->Data[4] = stoi(buffer);
                    STU->next = NULL;
                    ptr->next = STU;
                    ptr = ptr->next;
                    break;
                default:
                    STU->Data[tmpnum - 1] = stoi(buffer);
                    break;
                }
            }
            else
            {
                ChooseData[num - 1] = (char *)malloc(sizeof(buffer) + 1); //����ŵ���ÿ�еı�ͷ   ��һ�������� ��������   ���е�chooseData����һ��ʼ����
                strcpy(ChooseData[num - 1], buffer);
                // printf("%s\n", ChooseData[num - 1]);
            }
            if (!flag && flagbuffer[0] == 10) {   //����������  10���ǻ���
                flag = 1;  //flag��־�Ƿ�ʼ����struct
                ChooseDataNum = num-1  ;   //��һ��ԭ������������ 
                printf("num is %d\n", num);

            }
        }
        //printf("wanshi");
        return 1;
    }
}
