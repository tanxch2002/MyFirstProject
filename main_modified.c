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
	//声明链表的头和尾
	
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
		printf("********************欢迎使用飞机航班预定系统********************\n");
		printf("*                  1)添加旅客信息                              *\n");
		printf("*                  2)查询某位旅客信息                          *\n");
		printf("*                  3)查询所有旅客信息                          *\n");
		printf("*                  4)删除旅客信息                              *\n");
		printf("*                  5)添加航班信息                              *\n");
		printf("*                  6)查询某个航班信息                          *\n");
		printf("*                  7)查询所有航班信息                          *\n");
		printf("*                  8)预定航班                                  *\n");
		printf("*                  9)统计                                      *\n");
		printf("*                  10)根据价格统计航班预定人数                 *\n");
		printf("*                  0)退出系统                                  *\n");
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
			printf("输入的指令不对！\n");
		case 0:
			tuichu = 0;

		//保存
		SavePasToFile();
		SaveFliToFile();
		//释放链表
		FreeLinkData();
		FreeFliLinkData();

		system("pause");
		}
	}
		return 0;
}


//添加一个旅客信息
void AddPasInfo(char name[10], char sex[10], int age, char idn[20], int pho_num[12])
{
	printf("输入姓名：");
	scanf_s("%s", name,10);
	printf("输入性别：");
	scanf_s("%s", sex,10);
	while ((strcmp("男", sex) != 0)&& (strcmp("女", sex) != 0))
	{
		printf("输入错误，性别只能为男或女。\n");
		printf("输入性别：");
		scanf_s("%s", sex, 10);
	}
	printf("输入年龄：");
	scanf("%d", &age);
	while (age<0||age>=99)
	{
		printf("输入错误，年龄只能为0~99。\n");
		printf("输入年龄：");
		scanf("%d", &age);
	}
	printf("输入身份证号：");
	scanf_s("%s", idn,20);
	printf("输入电话号码：");
	scanf_s("%s", pho_num,12);
	if (name == NULL || sex == NULL )
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
//从文件读取一个旅客信息
void AddPasInfoFromFile(char name[10], char sex[5], int age, char idn[20], int pho_num[12], int history_flight)
{
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
		pTemp->history_flight = history_flight;

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
//添加一个航班信息
void AddFliInfo(float date,char airline_ID[8],char departure[10],char arrival[10],int price,float departure_time,float arrival_time,int passenger_number,int tickets_left,int distance)
{
	printf("输入日期（日期应该为xx.xx格式）：");
	scanf("%f", &date);
	while (date<1||date>13)
	{
		printf("输入错误\n");
		printf("输入日期：");
		scanf_s("%f", &date, 10);
	}
	printf("输入航班号：");
	scanf_s("%s", airline_ID,8);
	printf("输入起始地：");
	scanf("%s", departure);
	printf("输入目的地：");
	scanf("%s", arrival);
	printf("输入票价：");
	scanf("%d", &price);
	printf("输入离开时间：");
	scanf("%f", &departure_time);
	printf("输入到达时间：");
	scanf("%f", &arrival_time);
	printf("输入核载旅客人数：");
	scanf("%d", &passenger_number);
    printf("输入剩余座位数：");
	scanf("%d", &tickets_left);
	printf("输入飞行距离：");
	scanf("%d", &distance);

	if (airline_ID == NULL || departure == NULL || price < 0 )
	{
		printf("旅客信息输入错误\n");
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

		//接在链表上
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
		printf("数据录入成功\n");
	}
}
//从文件读取一个航班信息
void AddFliInfoFromFile(float date, char airline_ID[8], char departure[10], char arrival[10], int price, float departure_time, float arrival_time, int passenger_number, int tickets_left, int distance)
{
	if (airline_ID == NULL || departure == NULL || price < 0)
	{
		printf("航班信息读取错误\n");
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

		//接在链表上
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
		printf("数据录入成功\n");
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
//打印航班数据
void ShowFliData()
{
	FLINODE * pTemp = g_pfHead;
    while (pTemp != NULL)
    {
		printf("日期：%.2f， ", pTemp->date);
		printf("航班号：%s， ", pTemp->airline_ID);
	    printf("起始地：%s， ", pTemp->departure);
	    printf("目的地：%s， ", pTemp->arrival);
	    printf("票价：%d， ", pTemp->price);
	    printf("起飞时间：%.2f， ", pTemp->departure_time);
	    printf("到达时间：%.2f, ", pTemp->arrival_time);
	    printf("荷载旅客人数：%d， ", pTemp->passenger_number);
	    printf("剩余票数：%d， ", pTemp->tickets_left);
	    printf("飞行距离：%d\n ", pTemp->distance);
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
void ShowSbData(char name[20])
{
	//输入姓名
	printf("输入姓名");
	scanf("%s", name);
	//查找
	PASNODE* pTemp = FindPasByName(name);
	//打印
	if (NULL == pTemp)
	{
		printf("查无此人\n");
	}
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
//打印某个航班数据
FLINODE* FindFliByID(char airlineID[10])
{
	//检测参数合法性
	if (NULL == airlineID)
	{
		printf("航班号输入错误\n");
		return NULL;
	}
	//判断链表是否是空
	if (NULL == g_pfHead || NULL == g_pfEnd)
	{
		printf("无此节点\n");
		return NULL;
	}
	//遍历链表
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
	printf("无此节点\n");
}
void ShowCertainFliData(char airlineID[10])
{
	//输入航班号
	printf("输入航班号");
	scanf("%s", airlineID);
	//查找
	FLINODE* pTemp = FindFliByID(airlineID);
	//打印
	if (NULL != pTemp)
	{
		printf("日期：%.2f， ", pTemp->date);
		printf("航班号：%s， ", pTemp->airline_ID);
		printf("起始地：%s， ", pTemp->departure);
		printf("目的地：%s， ", pTemp->arrival);
		printf("票价：%d， ", pTemp->price);
		printf("起飞时间：%.2f， ", pTemp->departure_time);
		printf("到达时间：%.2f, ", pTemp->arrival_time);
		printf("荷载旅客人数：%d， ", pTemp->passenger_number);
		printf("剩余票数：%d， ", pTemp->tickets_left);
		printf("飞行距离：%d\n ", pTemp->distance);
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
//读取文件中的旅客信息
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
		printf("没有旅客信息\n");
		return;
	}
	//读取旅客信息
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
//保存航班信息
void SaveFliToFile()
{
	//判断链表是否为空
	if (NULL == g_pfHead)
	{
		printf("没有航班信息");
		return;
	}
	//打开文件
	FILE* pFile = NULL;
	pFile = fopen("datafli.txt", "wb+");
	if (NULL == pFile)
	{
		printf("文件打开失败");
		return;
	}
	//操作文件指针
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
		//保存日期
		sprintf(Strdate, "%.2f", pTemp->date);
		strcpy(StrBuf, Strdate);
		strcat(StrBuf, ";");
		//保存航班号
		strcat(StrBuf, pTemp->airline_ID);
		strcat(StrBuf, ";");
		//保存起始地
		strcat(StrBuf, pTemp->departure);
		strcat(StrBuf, ";");
		//保存目的地
		strcat(StrBuf, pTemp->arrival);
		strcat(StrBuf, ";");
		//保存价格
		itoa(pTemp->price, StrPrice, 10);
		strcat(StrBuf, StrPrice);
		strcat(StrBuf, ";");
		//保存起始时间
		sprintf(Strdeparture_time, "%.2f", pTemp->departure_time);
		strcat(StrBuf, Strdeparture_time);
		strcat(StrBuf, ";");
		//保存到达时间
		sprintf(Strarrival_time, "%.2f", pTemp->arrival_time);
		strcat(StrBuf, Strarrival_time);
		strcat(StrBuf, ";");
		//保存荷载旅客人数
		itoa(pTemp->passenger_number, Strpassenger_number, 10);
		strcat(StrBuf, Strpassenger_number);
		strcat(StrBuf, ";");
		//保存剩余票数
		itoa(pTemp->tickets_left, Strtickets_left, 10);
		strcat(StrBuf, Strtickets_left);
		strcat(StrBuf, ";");
		//保存飞行距离
		itoa(pTemp->distance, Strdistance, 10);
		strcat(StrBuf, Strdistance);
		

		strcat(StrBuf, ";");

		fwrite(StrBuf, 1, strlen(StrBuf), pFile);
		fwrite("\r\n", 1, strlen("\r\n"), pFile);

		pTemp = pTemp->pNext;
	}
}
//读取文件中的航班信息
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
		printf("没有航班信息\n");
		return;
	}
	//读取航班信息
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


//预定航班
FLINODE* FindFliByID_Date(float date, char airlineID[10])
{
	//检测参数合法性
	if (NULL == airlineID)
	{
		printf("航班号输入错误\n");
		return NULL;
	}
	//判断链表是否是空
	if (NULL == g_pfHead || NULL == g_pfEnd)
	{
		printf("无此节点\n");
		return NULL;
	}
	//遍历链表
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
	printf("无此节点\n");
}
void Booking()
{
	char name[10] = { 0 };
	char airlineID[10] = { 0 };
	float date = 0;
	//输入姓名
	printf("输入姓名");
	scanf("%s", name);
	//查找
	PASNODE* pPas = FindPasByName(name);
	if (NULL == pPas)
	{
		printf("查无此人\n");
		return;
	}
	
	printf("输入航班号");
	scanf("%s", airlineID);
	printf("输入预定航班日期(1.01-12.31)");
	scanf("%f", &date); 
	//查找
	FLINODE* pFli = FindFliByID_Date(date, airlineID);
	if (NULL == pFli)
	{
		printf("查无此航班\n");
		return;
	}
	srand((unsigned)time(NULL));
	int price = rand() % 101 + pFli->price;
	if (NULL != pFli)
	{
	    printf("日期：%.2f， ", pFli->date);
		printf("航班号：%s， ", pFli->airline_ID);
		printf("起始地：%s， ", pFli->departure);
		printf("目的地：%s， ", pFli->arrival);
		if (pPas->history_flight >= 100)
		{
			price = 0;
		}
		printf("票价：%d， ", price);
		printf("起飞时间：%.2f， ", pFli->departure_time);
		printf("到达时间：%.2f, ", pFli->arrival_time);
		printf("荷载旅客人数：%d， ", pFli->passenger_number);
		printf("剩余票数：%d， ", pFli->tickets_left);
		printf("飞行距离：%d\n ", pFli->distance);
	}
	printf("是否预定：\n");
	printf("1:是 2：否\n");
	int n = 0;

	scanf("%d", &n);
	switch (n)
	{
	case 1:
		printf("预定成功\n");
		pPas->history_flight++;
		pFli->tickets_left--;
		break;
	case 2:
		printf("预定失败\n");
		break;
	}
	return;
}


//按性别统计旅客人数
void NumberOfSex()
{
	printf("按性别查询旅客人数\n");
	printf("1: 男性 2：女性\n");
	int n;
	scanf("%d", &n);
	switch(n){
	case 1:
		ShowNumBySex("男");
		break;
	case 2:
		ShowNumBySex("女");
		break;
	default:
		printf("输入错误");
		break;
	}
	return;
}

void ShowNumBySex(char sex[5])
{
	int num = 0;
	//检测参数合法性
	//判断链表是否是空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf("无节点\n");
		return ;
	}
	//遍历链表
	PASNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (0 == strcmp(pTemp->sex, sex))
		{
			num++;
		}
		pTemp = pTemp->pNext;
	}
	printf("有%d人\n", num);
}


	

void SearchFlightByPrice()
{
	printf("请输入价格区间");
	int price1 = 0, price2 = 0;
	printf("最低价");
	scanf("%d", &price1);
	printf("最高价");
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
		printf("此价格区间内无航班\n");
		return;
	}
	else
	{
		pTemp = g_pfHead;
		printf("此价格区间内航班有：\n");
		while (pTemp != NULL)
		{
			if (pTemp->price >= price1 && pTemp->price <= price2)
			{
				printf("日期：%.2f， ", pTemp->date);
				printf("航班号：%s\n", pTemp->airline_ID);
			}
			pTemp = pTemp->pNext;
		}
		printf("共%d条航线\n",count);
		ave_pas_num = sum_pas_num / count;
		printf("此价格区间内航班旅客的平均值为：");
		printf("%d\n", ave_pas_num);
		return;
	}


}


