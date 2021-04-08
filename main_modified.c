#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "node_fun.h"


PASNODE* g_pHead = NULL;
PASNODE* g_pEnd = NULL;
FLINODE* g_pfHead = NULL;
FLINODE* g_pfEnd = NULL;
PASNAMENODE* g_ppHead = NULL;
PASNAMENODE* g_ppEnd = NULL;
int main() {
	//���������ͷ��β
	
	int order = 0;
	int tuichu = 1;
	char name[10] = { 0 };
	char sex[5] = { 0 };
	int age = 0;
	char idn[20] = { 0 };
	int pho_num[12] = { 0 };
	int history_flight = 0;
	char airline_ID[8] = { 0 };
	char departure[10] = { 0 };
	char arrival[10] = { 0 };
	int price = 0;
	float departure_time = 0;
	float arrival_time = 0;
	int passenger_number = 0;
	int tickets_left = 0;
	int distance = 0;
	float date = 0;
	char pasname_1[20] = { 0 };
	char pasname_2[20] = { 0 };
	char pasname_3[20] = { 0 };
	char pasname_4[20] = { 0 };
	char pasname_5[20] = { 0 };

	
	//Hello();

	ReadPasInfoFromFile();
	ReadFliInfoFromFile();

	while (tuichu)
	{
		printf("********************��ӭʹ�÷ɻ�����Ԥ��ϵͳ********************\n");
		printf("*                  1)����ÿ���Ϣ                              *\n");
		printf("*                  2)��ѯĳλ�ÿ���Ϣ                          *\n");
		printf("*                  3)��ѯ�����ÿ���Ϣ                          *\n");
		printf("*                  4)ɾ���ÿ���Ϣ                              *\n");
		printf("*                  5)��Ӻ�����Ϣ                              *\n");
		printf("*                  6)��ѯĳ��������Ϣ                          *\n");
		printf("*                  7)��ѯ���к�����Ϣ                          *\n");
		printf("*                  8)Ԥ������                                  *\n");
		printf("*                  9)ͳ��                                      *\n");
		printf("*                  10)���ݼ۸�ͳ�ƺ���Ԥ������                 *\n");
		printf("*                  0)�˳�ϵͳ                                  *\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			AddPasInfo(name, sex, age, idn, pho_num);
			break;
		case 2:
			ShowSbData(name);
			break;
		case 3:
			ShowPasData();
			break;
		case 4:
			DelPasInfo(name);
			break;
		case 5:
			AddFliInfo(date,airline_ID, departure, arrival, price, departure_time, arrival_time, passenger_number, tickets_left, distance);
			break;
		case 6:
			ShowCertainFliData(airline_ID);
			break;
		case 7:
			ShowFliData();
			break;
		case 8:
			Booking();
			break;
		case 9:
			NumberOfSex();
			break;
		case 10:
			SearchFlightByPrice();
			break;
		default:
			printf("�����ָ��ԣ�\n");
		case 0:
			tuichu = 0;

		//����
		SavePasToFile();
		SaveFliToFile();
		//�ͷ�����
		FreeLinkData();
		FreeFliLinkData();

		system("pause");
		}
	}
		return 0;
}


//���һ���ÿ���Ϣ
void AddPasInfo(char name[10], char sex[10], int age, char idn[20], int pho_num[12])
{
	printf("����������");
	scanf_s("%s", name,10);
	printf("�����Ա�");
	scanf_s("%s", sex,10);
	while ((strcmp("��", sex) != 0)&& (strcmp("Ů", sex) != 0))
	{
		printf("��������Ա�ֻ��Ϊ�л�Ů��\n");
		printf("�����Ա�");
		scanf_s("%s", sex, 10);
	}
	printf("�������䣺");
	scanf("%d", &age);
	while (age<0||age>=99)
	{
		printf("�����������ֻ��Ϊ0~99��\n");
		printf("�������䣺");
		scanf("%d", &age);
	}
	printf("�������֤�ţ�");
	scanf_s("%s", idn,20);
	printf("����绰���룺");
	scanf_s("%s", pho_num,12);
	if (name == NULL || sex == NULL )
	{
		printf("�ÿ���Ϣ�������\n");
		return;
	}
	else
	{
		PASNODE* pTemp = malloc(sizeof(PASNODE));

		strcpy(pTemp->name, name);
		strcpy(pTemp->sex, sex);
		pTemp->age = age;
		strcpy(pTemp->idn, idn);
		strcpy(pTemp->pho_num, pho_num);
		pTemp->pNext = NULL;
		pTemp->history_flight = 0;

		//����������
		if (g_pHead == NULL || g_pEnd == NULL)
		{
			g_pHead = pTemp;
			g_pEnd = pTemp;
		}
		else
		{
			g_pEnd->pNext = pTemp;
			g_pEnd = pTemp;
		}
		printf("����¼��ɹ�\n");
	}
}
//���ļ���ȡһ���ÿ���Ϣ
void AddPasInfoFromFile(char name[10], char sex[5], int age, char idn[20], int pho_num[12], int history_flight)
{
	if (name == NULL || sex == NULL || age < 0 || age>100)
	{
		printf("�ÿ���Ϣ�������\n");
		return;
	}
	else
	{
		PASNODE* pTemp = malloc(sizeof(PASNODE));

		strcpy(pTemp->name, name);
		strcpy(pTemp->sex, sex);
		pTemp->age = age;
		strcpy(pTemp->idn, idn);
		strcpy(pTemp->pho_num, pho_num);
		pTemp->pNext = NULL;
		pTemp->history_flight = history_flight;

		//����������
		if (g_pHead == NULL || g_pEnd == NULL)
		{
			g_pHead = pTemp;
			g_pEnd = pTemp;
		}
		else
		{
			g_pEnd->pNext = pTemp;
			g_pEnd = pTemp;
		}
		printf("����¼��ɹ�\n");
	}
}
//�������
void FreeLinkData()
{
	PASNODE* pTemp = g_pHead;
	while (g_pHead != NULL) 
	{
		pTemp = g_pHead;
		g_pHead = g_pHead->pNext;
		free(pTemp);
	}
}
void FreeFliLinkData()
{
	FLINODE* pTemp = g_pfHead;
	while (g_pfHead != NULL)
	{
		pTemp = g_pfHead;
		g_pfHead = g_pfHead->pNext;
		free(pTemp);
	}
}
//���һ��������Ϣ
void AddFliInfo(float date,char airline_ID[8],char departure[10],char arrival[10],int price,float departure_time,float arrival_time,int passenger_number,int tickets_left,int distance)
{
	printf("�������ڣ�����Ӧ��Ϊxx.xx��ʽ����");
	scanf("%f", &date);
	while (date<1||date>13)
	{
		printf("�������\n");
		printf("�������ڣ�");
		scanf_s("%f", &date, 10);
	}
	printf("���뺽��ţ�");
	scanf_s("%s", airline_ID,8);
	printf("������ʼ�أ�");
	scanf("%s", departure);
	printf("����Ŀ�ĵأ�");
	scanf("%s", arrival);
	printf("����Ʊ�ۣ�");
	scanf("%d", &price);
	printf("�����뿪ʱ�䣺");
	scanf("%f", &departure_time);
	printf("���뵽��ʱ�䣺");
	scanf("%f", &arrival_time);
	printf("��������ÿ�������");
	scanf("%d", &passenger_number);
    printf("����ʣ����λ����");
	scanf("%d", &tickets_left);
	printf("������о��룺");
	scanf("%d", &distance);

	if (airline_ID == NULL || departure == NULL || price < 0 )
	{
		printf("�ÿ���Ϣ�������\n");
		return;
	}
	else
	{
		FLINODE* pTemp = malloc(sizeof(FLINODE));

		strcpy(pTemp->airline_ID, airline_ID);
		strcpy(pTemp->departure, departure);
		strcpy(pTemp->arrival, arrival);
		pTemp->price = price;
		pTemp->departure_time = departure_time;
		pTemp->arrival_time = arrival_time;
		pTemp->passenger_number = passenger_number;
		pTemp->tickets_left = tickets_left;
		pTemp->distance = distance;
		pTemp->date = date;

		pTemp->pNext = NULL;

		//����������
		if (g_pfHead == NULL || g_pfEnd == NULL)
		{
			g_pfHead = pTemp;
			g_pfEnd = pTemp;
		}
		else
		{
			g_pfEnd->pNext = pTemp;
			g_pfEnd = pTemp;
		}
		printf("����¼��ɹ�\n");
	}
}
//���ļ���ȡһ��������Ϣ
void AddFliInfoFromFile(float date, char airline_ID[8], char departure[10], char arrival[10], int price, float departure_time, float arrival_time, int passenger_number, int tickets_left, int distance)
{
	if (airline_ID == NULL || departure == NULL || price < 0)
	{
		printf("������Ϣ��ȡ����\n");
		return;
	}
	else
	{
		FLINODE* pTemp = malloc(sizeof(FLINODE));

		pTemp->date = date;
		strcpy(pTemp->airline_ID, airline_ID);
		strcpy(pTemp->departure, departure);
		strcpy(pTemp->arrival, arrival);
		pTemp->price = price;
		pTemp->departure_time = departure_time;
		pTemp->arrival_time = arrival_time;
		pTemp->passenger_number = passenger_number;
		pTemp->tickets_left = tickets_left;
		pTemp->distance = distance;

		pTemp->pNext = NULL;

		//����������
		if (g_pfHead == NULL || g_pfEnd == NULL)
		{
			g_pfHead = pTemp;
			g_pfEnd = pTemp;
		}
		else
		{
			g_pfEnd->pNext = pTemp;
			g_pfEnd = pTemp;
		}
		printf("����¼��ɹ�\n");
	}
}

//��ӡ�ÿ�����
void ShowPasData()
{
	PASNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		printf("������%s�� ", pTemp->name);
		printf("�Ա�%s�� ", pTemp->sex);
		printf("���䣺%d�� ", pTemp->age);
		printf("���֤�ţ�%s�� ", pTemp->idn);
		printf("�ֻ��ţ�%s�� ", pTemp->pho_num);
		printf("���д�����%d\n", pTemp->history_flight);
		//������һ��
		pTemp = pTemp->pNext;
	}
}
//��ӡ��������
void ShowFliData()
{
	FLINODE * pTemp = g_pfHead;
    while (pTemp != NULL)
    {
		printf("���ڣ�%.2f�� ", pTemp->date);
		printf("����ţ�%s�� ", pTemp->airline_ID);
	    printf("��ʼ�أ�%s�� ", pTemp->departure);
	    printf("Ŀ�ĵأ�%s�� ", pTemp->arrival);
	    printf("Ʊ�ۣ�%d�� ", pTemp->price);
	    printf("���ʱ�䣺%.2f�� ", pTemp->departure_time);
	    printf("����ʱ�䣺%.2f, ", pTemp->arrival_time);
	    printf("�����ÿ�������%d�� ", pTemp->passenger_number);
	    printf("ʣ��Ʊ����%d�� ", pTemp->tickets_left);
	    printf("���о��룺%d\n ", pTemp->distance);
	    //������һ��
	    pTemp = pTemp->pNext;
    }
}
//��ӡָ���ÿ�����
PASNODE* FindPasByName(char name[20])
{
	//�������Ϸ���
	if (NULL == name)
	{
		printf("�����������\n");
		return NULL;
	}
	//�ж������Ƿ��ǿ�
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("�޴˽ڵ�\n");
		return NULL;
	}
	//��������
	PASNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->name, name))
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
	printf("�޴˽ڵ�\n");
}
void ShowSbData(char name[20])
{
	//��������
	printf("��������");
	scanf("%s", name);
	//����
	PASNODE* pTemp = FindPasByName(name);
	//��ӡ
	if (NULL == pTemp)
	{
		printf("���޴���\n");
	}
	if (NULL != pTemp)
	{
		printf("������%s�� ", pTemp->name);
		printf("�Ա�%s�� ", pTemp->sex);
		printf("���䣺%d�� ", pTemp->age);
		printf("���֤�ţ�%s�� ", pTemp->idn);
		printf("�ֻ��ţ�%s�� ", pTemp->pho_num);
		printf("���д�����%d\n", pTemp->history_flight);
	}
}
//��ӡĳ����������
FLINODE* FindFliByID(char airlineID[10])
{
	//�������Ϸ���
	if (NULL == airlineID)
	{
		printf("������������\n");
		return NULL;
	}
	//�ж������Ƿ��ǿ�
	if (NULL == g_pfHead || NULL == g_pfEnd)
	{
		printf("�޴˽ڵ�\n");
		return NULL;
	}
	//��������
	FLINODE* pTemp = g_pfHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->airline_ID, airlineID))
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
	printf("�޴˽ڵ�\n");
}
void ShowCertainFliData(char airlineID[10])
{
	//���뺽���
	printf("���뺽���");
	scanf("%s", airlineID);
	//����
	FLINODE* pTemp = FindFliByID(airlineID);
	//��ӡ
	if (NULL != pTemp)
	{
		printf("���ڣ�%.2f�� ", pTemp->date);
		printf("����ţ�%s�� ", pTemp->airline_ID);
		printf("��ʼ�أ�%s�� ", pTemp->departure);
		printf("Ŀ�ĵأ�%s�� ", pTemp->arrival);
		printf("Ʊ�ۣ�%d�� ", pTemp->price);
		printf("���ʱ�䣺%.2f�� ", pTemp->departure_time);
		printf("����ʱ�䣺%.2f, ", pTemp->arrival_time);
		printf("�����ÿ�������%d�� ", pTemp->passenger_number);
		printf("ʣ��Ʊ����%d�� ", pTemp->tickets_left);
		printf("���о��룺%d\n ", pTemp->distance);
	}
}


//ɾ���ÿ���Ϣ
void DelPasInfo(char name[20])
{
	//��������
	printf("��������");
	scanf("%s", name);
	
	//����
	PASNODE* pTemp = FindPasByName(name);

	//ɾ������ڵ�
	if (NULL != pTemp)
	{
		DelStuNode(pTemp);
	}
}
void DelStuNode(PASNODE* pNode)
{
	//ֻ��һ���ڵ�
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
		printf("ɾ���ɹ�1\n");
	}
	//�����ڵ�
	else if (g_pHead->pNext == g_pEnd)
	{
		if (g_pHead == pNode)
		{
			free(g_pHead);
			g_pHead = g_pEnd;
			printf("ɾ���ɹ�2.1\n");
		}
		else
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->pNext = NULL;
			printf("ɾ���ɹ�2.2\n");
		}
	}
	//�ڵ���������
	else
	{
		PASNODE* pTemp = g_pHead;
		//�жϵ�һ���ڵ�
		if (g_pHead == pNode)
		{
			pTemp = g_pHead;
			g_pHead = g_pHead->pNext;
			free(pTemp);
			pTemp = NULL;
			printf("ɾ���ɹ�3.1\n");
			return;
		}
		//�ж�ʣ��ڵ�
		while (pTemp != NULL)
		{
			if (pTemp->pNext == pNode)
			{
				//�ж�β�ڵ�
				if (pNode == g_pEnd)
				{
					free(pNode);
					pNode = NULL;
					g_pEnd = pTemp;
					g_pEnd->pNext = NULL;
					printf("ɾ���ɹ�3.3\n");
					return;
				}
				//�жϳ�ͷ��β��ʣ��ڵ�
				else
				{
					//��¼Ҫɾ���Ľڵ�
					PASNODE* p = pNode;
					//��Ҫɾ���Ľڵ��ǰһ���ڵ�β���ӵ�Ҫɾ���ڵ�ĺ�һ���ڵ�
					pTemp->pNext = pTemp->pNext->pNext;
					free(p);
					p = NULL;
					printf("ɾ���ɹ�3.2\n");
					return;
				}
			}
			pTemp = pTemp->pNext;
		}
	}
}
//�����ÿ���Ϣ
void SavePasToFile()
{
	//�ж������Ƿ�Ϊ��
	if (NULL == g_pHead)
	{
		printf("û���ÿ���Ϣ");
		return;
	}
	//���ļ�
	FILE* pFile = NULL;
	pFile = fopen("data.txt", "wb+");
	if (NULL == pFile)
	{
		printf("�ļ���ʧ��");
		return;
	}
   //�����ļ�ָ��
	PASNODE* pTemp = g_pHead;
	char StrBuf[100] = { 0 };
	char StrAge[5] = { 0 };
	char StrHF[5] = { 0 };
	while (pTemp != NULL)
	{
		//��������
		strcpy(StrBuf, pTemp->name);
		strcat(StrBuf, ".");
		//�����Ա�
		strcat(StrBuf, pTemp->sex);
		strcat(StrBuf, ".");
		//��������
		itoa(pTemp->age, StrAge, 10);
		strcat(StrBuf, StrAge);
		strcat(StrBuf, ".");
		//�������֤��
		strcat(StrBuf, pTemp->idn);
		strcat(StrBuf, ".");
		//�����ֻ���
		strcat(StrBuf, pTemp->pho_num);
		strcat(StrBuf, ".");
		//������ʷ���м�¼
		itoa(pTemp->history_flight, StrHF, 2);
		strcat(StrBuf, StrHF);
		  
        fwrite(StrBuf, 1, strlen(StrBuf), pFile);
		fwrite("\r\n", 1, strlen("\r\n"), pFile);

		pTemp = pTemp->pNext;
	}
	//�ر��ļ�
	fclose(pFile);
}
//��ȡ�ļ��е��ÿ���Ϣ
void ReadPasInfoFromFile()
{
	FILE* pFile = NULL;
	pFile = fopen("data.txt", "r");

	char strbuf[100] = { 0 };

	char strname[20] = { 0 };
	char strsex[5] = { 0 };
	char strage[5] = { 0 };
	char stridn[30] = { 0 };
	char strpho_num[15] = { 0 };
	char history_flight[3] = { 0 };

	if (pFile == NULL)
	{
		printf("û���ÿ���Ϣ\n");
		return;
	}
	//��ȡ�ÿ���Ϣ
	while (fgets(strbuf, 150, pFile) != NULL)
	{
		int i = 0, j = 0, count = 0;
		for (i = 0; strbuf[i] != '\n'; i++)
		{
			if (0 == count)
			{
				strname[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					strname[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (1 == count)
			{
				strsex[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					strsex[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (2 == count)
			{
				strage[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					strage[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (3 == count)
			{
				stridn[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					stridn[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (4 == count)
			{
				strpho_num[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					strpho_num[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (5 == count)
			{
				history_flight[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					history_flight[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
		}
		AddPasInfoFromFile(strname, strsex, atoi(strage), stridn, strpho_num, atoi(history_flight));
	}

	fclose(pFile);
	return;
}
//���溽����Ϣ
void SaveFliToFile()
{
	//�ж������Ƿ�Ϊ��
	if (NULL == g_pfHead)
	{
		printf("û�к�����Ϣ");
		return;
	}
	//���ļ�
	FILE* pFile = NULL;
	pFile = fopen("datafli.txt", "wb+");
	if (NULL == pFile)
	{
		printf("�ļ���ʧ��");
		return;
	}
	//�����ļ�ָ��
	FLINODE* pTemp = g_pfHead;
	char StrBuf[300] = { 0 };
	char Strdate[5] = { 0 };
	char StrPrice[5] = { 0 };
	char Strdeparture_time[10] = { 0 };
	char Strarrival_time[10] = { 0 };
	char Strpassenger_number[5] = { 0 };
	char Strtickets_left[5] = { 0 };
	char Strdistance[5] = { 0 };
	

	while (pTemp != NULL)
	{
		//��������
		sprintf(Strdate, "%.2f", pTemp->date);
		strcpy(StrBuf, Strdate);
		strcat(StrBuf, ";");
		//���溽���
		strcat(StrBuf, pTemp->airline_ID);
		strcat(StrBuf, ";");
		//������ʼ��
		strcat(StrBuf, pTemp->departure);
		strcat(StrBuf, ";");
		//����Ŀ�ĵ�
		strcat(StrBuf, pTemp->arrival);
		strcat(StrBuf, ";");
		//����۸�
		itoa(pTemp->price, StrPrice, 10);
		strcat(StrBuf, StrPrice);
		strcat(StrBuf, ";");
		//������ʼʱ��
		sprintf(Strdeparture_time, "%.2f", pTemp->departure_time);
		strcat(StrBuf, Strdeparture_time);
		strcat(StrBuf, ";");
		//���浽��ʱ��
		sprintf(Strarrival_time, "%.2f", pTemp->arrival_time);
		strcat(StrBuf, Strarrival_time);
		strcat(StrBuf, ";");
		//��������ÿ�����
		itoa(pTemp->passenger_number, Strpassenger_number, 10);
		strcat(StrBuf, Strpassenger_number);
		strcat(StrBuf, ";");
		//����ʣ��Ʊ��
		itoa(pTemp->tickets_left, Strtickets_left, 10);
		strcat(StrBuf, Strtickets_left);
		strcat(StrBuf, ";");
		//������о���
		itoa(pTemp->distance, Strdistance, 10);
		strcat(StrBuf, Strdistance);
		

		strcat(StrBuf, ";");

		fwrite(StrBuf, 1, strlen(StrBuf), pFile);
		fwrite("\r\n", 1, strlen("\r\n"), pFile);

		pTemp = pTemp->pNext;
	}
}
//��ȡ�ļ��еĺ�����Ϣ
void ReadFliInfoFromFile()
{
	FILE* pFile = NULL;
	pFile = fopen("datafli.txt", "r");

	char strbuf[300] = { 0 };

	char Strdate[10] = { 0 };
	char Strairline_ID[10] = { 0 };
	char Strdeparture[10] = { 0 };
	char Strarrival[10] = { 0 };
	char StrPrice[5] = { 0 };
	char Strdeparture_time[10] = { 0 };
	char Strarrival_time[10] = { 0 };
	char Strpassenger_number[5] = { 0 };
	char Strtickets_left[5] = { 0 };
	char Strdistance[5] = { 0 };


	if (pFile == NULL)
	{
		printf("û�к�����Ϣ\n");
		return;
	}
	//��ȡ������Ϣ
	while (fgets(strbuf, 300, pFile) != NULL)
	{
		int i = 0, j = 0, count = -1;
		for (i = 0; strbuf[i] != '\n'; i++)
		{
			
			if (-1 == count)
			{
				Strdate[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strdate[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (0 == count)
			{
				Strairline_ID[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strairline_ID[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (1 == count)
			{
				Strdeparture[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strdeparture[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (2 == count)
			{
				Strarrival[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strarrival[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (3 == count)
			{
				StrPrice[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					StrPrice[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (4 == count)
			{
				Strdeparture_time[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strdeparture_time[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (5 == count)
			{
				Strarrival_time[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strarrival_time[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (6 == count)
			{
				Strpassenger_number[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strpassenger_number[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (7 == count)
			{
				Strtickets_left[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strtickets_left[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			else if (8 == count)
			{
				Strdistance[j] = strbuf[i];
				j++;
				if (';' == strbuf[i])
				{
					Strdistance[j - 1] = '\0';
					j = 0;
					count++;
				}
			}
			
			
		}
		AddFliInfoFromFile(atof(Strdate),Strairline_ID, Strdeparture, Strarrival, atoi(StrPrice), atof(Strdeparture_time), atof(Strarrival_time), atoi(Strpassenger_number), atoi(Strtickets_left), atoi(Strdistance)
			);
	}

	fclose(pFile);
	return;
}


//Ԥ������
FLINODE* FindFliByID_Date(float date, char airlineID[10])
{
	//�������Ϸ���
	if (NULL == airlineID)
	{
		printf("������������\n");
		return NULL;
	}
	//�ж������Ƿ��ǿ�
	if (NULL == g_pfHead || NULL == g_pfEnd)
	{
		printf("�޴˽ڵ�\n");
		return NULL;
	}
	//��������
	FLINODE* pTemp = g_pfHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->airline_ID, airlineID))
		{
			if (date == pTemp->date)
			{
				return pTemp;
			}
		}
		pTemp = pTemp->pNext;
	}

	return NULL;
	printf("�޴˽ڵ�\n");
}
void Booking()
{
	char name[10] = { 0 };
	char airlineID[10] = { 0 };
	float date = 0;
	//��������
	printf("��������");
	scanf("%s", name);
	//����
	PASNODE* pPas = FindPasByName(name);
	if (NULL == pPas)
	{
		printf("���޴���\n");
		return;
	}
	
	printf("���뺽���");
	scanf("%s", airlineID);
	printf("����Ԥ����������(1.01-12.31)");
	scanf("%f", &date); 
	//����
	FLINODE* pFli = FindFliByID_Date(date, airlineID);
	if (NULL == pFli)
	{
		printf("���޴˺���\n");
		return;
	}
	srand((unsigned)time(NULL));
	int price = rand() % 101 + pFli->price;
	if (NULL != pFli)
	{
	    printf("���ڣ�%.2f�� ", pFli->date);
		printf("����ţ�%s�� ", pFli->airline_ID);
		printf("��ʼ�أ�%s�� ", pFli->departure);
		printf("Ŀ�ĵأ�%s�� ", pFli->arrival);
		if (pPas->history_flight >= 100)
		{
			price = 0;
		}
		printf("Ʊ�ۣ�%d�� ", price);
		printf("���ʱ�䣺%.2f�� ", pFli->departure_time);
		printf("����ʱ�䣺%.2f, ", pFli->arrival_time);
		printf("�����ÿ�������%d�� ", pFli->passenger_number);
		printf("ʣ��Ʊ����%d�� ", pFli->tickets_left);
		printf("���о��룺%d\n ", pFli->distance);
	}
	printf("�Ƿ�Ԥ����\n");
	printf("1:�� 2����\n");
	int n = 0;

	scanf("%d", &n);
	switch (n)
	{
	case 1:
		printf("Ԥ���ɹ�\n");
		pPas->history_flight++;
		pFli->tickets_left--;
		break;
	case 2:
		printf("Ԥ��ʧ��\n");
		break;
	}
	return;
}


//���Ա�ͳ���ÿ�����
void NumberOfSex()
{
	printf("���Ա��ѯ�ÿ�����\n");
	printf("1: ���� 2��Ů��\n");
	int n;
	scanf("%d", &n);
	switch(n){
	case 1:
		ShowNumBySex("��");
		break;
	case 2:
		ShowNumBySex("Ů");
		break;
	default:
		printf("�������");
		break;
	}
	return;
}

void ShowNumBySex(char sex[5])
{
	int num = 0;
	//�������Ϸ���
	//�ж������Ƿ��ǿ�
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("�޽ڵ�\n");
		return ;
	}
	//��������
	PASNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->sex, sex))
		{
			num++;
		}
		pTemp = pTemp->pNext;
	}
	printf("��%d��\n", num);
}


	

void SearchFlightByPrice()
{
	printf("������۸�����");
	int price1 = 0, price2 = 0;
	printf("��ͼ�");
	scanf("%d", &price1);
	printf("��߼�");
	scanf("%d", &price2);
	int count = 0;
	int sum_pas_num=0;
	int ave_pas_num = 0;
	FLINODE* pTemp = g_pfHead;
	while (pTemp != NULL)
	{
		if (pTemp->price>=price1&&pTemp->price<=price2)
		{
			count++;
			sum_pas_num = (pTemp->passenger_number - pTemp->tickets_left);
			
		}
		pTemp = pTemp->pNext;
	}
	if (count == 0)
	{
		printf("�˼۸��������޺���\n");
		return;
	}
	else
	{
		pTemp = g_pfHead;
		printf("�˼۸������ں����У�\n");
		while (pTemp != NULL)
		{
			if (pTemp->price >= price1 && pTemp->price <= price2)
			{
				printf("���ڣ�%.2f�� ", pTemp->date);
				printf("����ţ�%s\n", pTemp->airline_ID);
			}
			pTemp = pTemp->pNext;
		}
		printf("��%d������\n",count);
		ave_pas_num = sum_pas_num / count;
		printf("�˼۸������ں����ÿ͵�ƽ��ֵΪ��");
		printf("%d\n", ave_pas_num);
		return;
	}


}


