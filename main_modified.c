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
	//声明链表的头和尾
	
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
		printf("********************欢迎使用飞机航班预定系统********************\n");
		printf("*                  1)添加旅客信息                              *\n");
		printf("*                  2)查询某位旅客信息                          *\n");
		printf("*                  3)查询所有旅客信息                          *\n");
		printf("*                  4)删除旅客信息                              *\n");
		printf("*                  5)查询航班信息                              *\n");
		printf("*                  6)修改航班信息                              *\n");
		printf("*                  7)预定航班                                  *\n");
		printf("*                  0)退出系统                                  *\n");
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
			printf("输入的指令不对！\n");
		case 0:
			tuichu = 0;

		//保存
		SavePasToFile();
		//释放链表
		FreeLinkData();
		system("pause");
		}
	}
		return 0;
}


//添加一个旅客信息
void AddPasInfo(int id, char name[10], char sex[5], int age, int idn[20], int pho_num[12])
{
	printf("输入姓名：");
	scanf("%s", name);
	printf("输入性别：");
	scanf("%s", sex);
	printf("输入年龄：");
	scanf("%d", &age);
	printf("输入身份证号：");
	scanf("%s", idn);
	printf("输入电话号码：");
	scanf("%s", pho_num);
	if (name == NULL || sex == NULL || age < 0 || age>100)
	{
		printf("旅客信息输入错误\n");
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

		//接在链表上
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
		printf("数据录入成功\n");
	}
}
//清空链表
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
//打印旅客数据
void ShowPasData()
{
	PASNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		printf("姓名：%s， ", pTemp->name);
		printf("性别：%s， ", pTemp->sex);
		printf("年龄：%d， ", pTemp->age);
		printf("身份证号：%s， ", pTemp->idn);
		printf("手机号：%s， ", pTemp->pho_num);
		printf("飞行次数：%d\n", pTemp->history_flight);
		//向下走一步
		pTemp = pTemp->pNext;
	}
}
//打印指定旅客数据
PASNODE* FindPasByName(char name[20])
{
	//检测参数合法性
	if (NULL == name)
	{
		printf("姓名输入错误\n");
		return NULL;
	}
	//判断链表是否是空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("无此节点\n");
		return NULL;
	}
	//遍历链表
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
	printf("无此节点\n");
}
//打印某个旅客数据
void ShowSbData(char name[20])
{
	//输入姓名
	printf("输入姓名");
	scanf("%s", name);
	//查找
	PASNODE* pTemp = FindPasByName(name);
	//打印
	if (NULL != pTemp)
	{
		printf("姓名：%s， ", pTemp->name);
		printf("性别：%s， ", pTemp->sex);
		printf("年龄：%d， ", pTemp->age);
		printf("身份证号：%s， ", pTemp->idn);
		printf("手机号：%s， ", pTemp->pho_num);
		printf("飞行次数：%d\n", pTemp->history_flight);
	}
}
//删除旅客信息
void DelPasInfo(char name[20])
{
	//输入姓名
	printf("输入姓名");
	scanf("%s", name);
	
	//查找
	PASNODE* pTemp = FindPasByName(name);

	//删除这个节点
	if (NULL != pTemp)
	{
		DelStuNode(pTemp);
	}
}

//删除指定学生
void DelStuNode(PASNODE* pNode)
{
	//只有一个节点
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
		printf("删除成功1\n");
	}
	//有俩节点
	else if (g_pHead->pNext == g_pEnd)
	{
		if (g_pHead == pNode)
		{
			free(g_pHead);
			g_pHead = g_pEnd;
			printf("删除成功2.1\n");
		}
		else
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->pNext = NULL;
			printf("删除成功2.2\n");
		}
	}
	//节点数大于三
	else
	{
		PASNODE* pTemp = g_pHead;
		//判断第一个节点
		if (g_pHead == pNode)
		{
			pTemp = g_pHead;
			g_pHead = g_pHead->pNext;
			free(pTemp);
			pTemp = NULL;
			printf("删除成功3.1\n");
			return;
		}
		//判断剩余节点
		while (pTemp != NULL)
		{
			if (pTemp->pNext == pNode)
			{
				//判断尾节点
				if (pNode == g_pEnd)
				{
					free(pNode);
					pNode = NULL;
					g_pEnd = pTemp;
					g_pEnd->pNext = NULL;
					printf("删除成功3.3\n");
					return;
				}
				//判断除头和尾的剩余节点
				else
				{
					//记录要删除的节点
					PASNODE* p = pNode;
					//将要删除的节点的前一个节点尾部接到要删除节点的后一个节点
					pTemp->pNext = pTemp->pNext->pNext;
					free(p);
					p = NULL;
					printf("删除成功3.2\n");
					return;
				}
			}
			pTemp = pTemp->pNext;
		}
	}
}
//保存旅客信息
void SavePasToFile()
{
	//判断链表是否为空
	if (NULL == g_pHead)
	{
		printf("没有旅客信息");
		return;
	}
	//打开文件
	FILE* pFile = NULL;
	pFile = fopen("data.txt", "wb+");
	if (NULL == pFile)
	{
		printf("文件打开失败");
		return;
	}
   //操作文件指针
	PASNODE* pTemp = g_pHead;
	char StrBuf[100] = { 0 };
	char StrAge[5] = { 0 };
	char StrHF[5] = { 0 };
	while (pTemp != NULL)
	{
		//保存姓名
		strcpy(StrBuf, pTemp->name);
		strcat(StrBuf, ".");
		//保存性别
		strcat(StrBuf, pTemp->sex);
		strcat(StrBuf, ".");
		//保存年龄
		itoa(pTemp->age, StrAge, 10);
		strcat(StrBuf, StrAge);
		strcat(StrBuf, ".");
		//保存身份证号
		strcat(StrBuf, pTemp->idn);
		strcat(StrBuf, ".");
		//保存手机号
		strcat(StrBuf, pTemp->pho_num);
		strcat(StrBuf, ".");
		//保存历史飞行记录
		itoa(pTemp->history_flight, StrHF, 2);
		strcat(StrBuf, StrHF);
		  
        fwrite(StrBuf, 1, strlen(StrBuf), pFile);
		fwrite("\r\n", 1, strlen("\r\n"), pFile);

		pTemp = pTemp->pNext;
	}
	//关闭文件
	fclose(pFile);
}

//读取文件中的学生信息
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
 		printf("没有旅客信息\n");
		return;
	}
	//读取旅客信息
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







