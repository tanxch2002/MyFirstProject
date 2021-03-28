#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "node_fun.h"


PASNODE* g_pHead = NULL;
PASNODE* g_pEnd = NULL;
FLINODE* g_pfHead = NULL;
FLINODE* g_pfEnd = NULL;
int main() {
	//���������ͷ��β
	
	int order = 0;
	int tuichu = 1;
	int id = 0; 
	char name[10] = { 0 };
	char sex[5] = { 0 };
	int age = 0;
	int idn[20] = { 0 };
	int pho_num[12] = { 0 };
	int history_flight = 0;
	//ReadPasInfoFromFile();

	while (tuichu)
	{
		printf("********************��ӭʹ�÷ɻ�����Ԥ��ϵͳ********************\n");
		printf("*                  1)����ÿ���Ϣ                              *\n");
		printf("*                  2)��ѯĳλ�ÿ���Ϣ                          *\n");
		printf("*                  3)��ѯ�����ÿ���Ϣ                          *\n");
		printf("*                  4)ɾ���ÿ���Ϣ                              *\n");
		printf("*                  5)��ѯ������Ϣ                              *\n");
		printf("*                  6)�޸ĺ�����Ϣ                              *\n");
		printf("*                  7)Ԥ������                                  *\n");
		printf("*                  0)�˳�ϵͳ                                  *\n");
		scanf("%d", &order);
		switch (order) {
		case 1:
			AddPasInfo(id, name, sex, age, idn, pho_num);
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
		default:
			printf("�����ָ��ԣ�\n");
		case 0:
			tuichu = 0;

		//����
		SavePasToFile();
		//�ͷ�����
		FreeLinkData();
		system("pause");
		}
	}
		return 0;
}


//���һ���ÿ���Ϣ
void AddPasInfo(int id, char name[10], char sex[5], int age, int idn[20], int pho_num[12])
{
	printf("����������");
	scanf("%s", name);
	printf("�����Ա�");
	scanf("%s", sex);
	printf("�������䣺");
	scanf("%d", &age);
	printf("�������֤�ţ�");
	scanf("%s", idn);
	printf("����绰���룺");
	scanf("%s", pho_num);
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
//��ӡĳ���ÿ�����
void ShowSbData(char name[20])
{
	//��������
	printf("��������");
	scanf("%s", name);
	//����
	PASNODE* pTemp = FindPasByName(name);
	//��ӡ
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

//ɾ��ָ��ѧ��
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

//��ȡ�ļ��е�ѧ����Ϣ
/*void ReadPasInfoFromFile()
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
	int count = 0;
    
	if (pFile == NULL)
	{
 		printf("û���ÿ���Ϣ\n");
		return;
	}
	//��ȡ�ÿ���Ϣ
	while (fgets(strbuf, 150, pFile) != NULL)
	{
		int i = 0;
		for (i = 0; strbuf[i] != '\r'; i++)
		{
			if (0 == count)
			{
				int j = 0;
				strname[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					count++;
				}
			}
			else if (1 == count)
			{
				int j = 0;
				strsex[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					count++;
				}
			}
			else if (2 == count)
			{
				int j = 0;
				strage[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					count++;
				}
			}
			else if (3 == count)
			{
				int j = 0;
				stridn[j] = strbuf[i];
				j++;
				if ('.' == strbuf[i])
				{
					count++;
				}
			}
			else if (4 == count)
			{
				int j = 0;
				j++;
				strpho_num[j] = strbuf[i];
				
			}
		}
	}

	fclose(pFile);
	return;
}*/
/*char name[20];
char sex[5];
int age;
char idn[20];
int pho_num[12];
int history_flight;*/







