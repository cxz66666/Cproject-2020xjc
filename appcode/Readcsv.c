#pragma once 
#include"MyData.h"



BOOL ReadCSVFile(char *Name);

double stod(string str)
{
    double ans;
    sscanf(str, "%lf", &ans);
    return ans;
}
int stoi(string str)
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

        char buffer[256];
        fseek(fp, 3, 0);                                //txt�ļ�ǰ��������ʹ�ñ���ı�ʶ�� ����
        while (fscanf(fp, "%[^,\n]%*c", buffer) != EOF) //%*c��������һ���ַ�
        {
            num++;
            if (num > 5)
            {
                switch (num % 5)
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
                case 2:
                    STU->Data[1] = stoi(buffer);
                    break;
                case 3:
                    STU->Data[2] = stoi(buffer);
                    break;
                case 4:
                    STU->Data[3] = stoi(buffer);
                    break;
                case 0:
                    STU->Data[4] = stoi(buffer);
                    STU->next = NULL;
                    ptr->next = STU;
                    ptr = ptr->next;
                }
            }
            else
            {
                ChooseData[num - 1] = (char *)malloc(sizeof(buffer) + 1);
                strcpy(ChooseData[num - 1], buffer);
                // printf("%s\n", ChooseData[num - 1]);
            }
        }
        //printf("wanshi");
        return 1;
    }
}
