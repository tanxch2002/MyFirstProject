#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <math.h>
#include <windows.h>
struct users
{
	char ac[30];
	char pw[30];
};
struct users use[50];
void Hello();
void registeruser();
void login();

//登录界面 
void Hello()
{
	int se;
	printf("********************************************\n");
	printf("**********飞机航班系统登录界面**********\n");
	printf("********************************************\n\n");
	printf("   \t\t1.-登录账号-\n");
	printf("\t\t2.-注册账号-\n");
	printf("\t\t3.-退出界面-\n\n");
	printf("******************欢迎使用******************\n");
	printf("请选择：");
	scanf("%d", &se);
	switch (se)
	{
	case 1:
		login();
		break;
	case 2:
		registeruser();
		break;
	case 3:
		printf("\n\t\t【成功退出】\n");
		exit(0);
		system("pause");
		break;
	default:
		printf("\n没有这个选项，请重新选择！\n");
		Hello();
	}
}

// 注册账号功能 
void registeruser()
{
	char ac[30]; //账号
	char pw[6], pd[6]; //密码 验证密码
	int	i, a = 0;
	

	printf("\t\t【注册帐号】\n");
	FILE* fp = fopen("账号信息档案.txt", "wb+");
	printf("请输入用户账号和密码(账号、密码可以为数字,中文字母,英文字母,符号,密码必须6位)\n\n\n");
	while (1)
	{
		int v = 0;
		printf("\t请你输入账号：");
		scanf("%s", &ac);
		strcpy(use[a].ac, ac);
		printf("\n\t请你输入密码：");
		for (i = 0; i < 6; i++)
		{
			pw[i] = _getch();
			printf("*");
			use[a].pw[i] = pw[i];
			if (pw[i] == '\r')
			{
				printf("\n\t注册失败，请重新注册账号\n");
				exit(0);
			}
		}
		printf("\n\n\t再次确认密码：");
		for (i = 0; i < 6; i++)
		{
			pd[i] = _getch();
			printf("*");
			if (use[a].pw[i] != pd[i])
			{
				v = v + 1;
			}
		}
		if (v == 0)
			break;
		else
		{
			printf("\n密码不对，请重新注册账号\n");
			continue;
		}
	}
	fprintf(fp, "账号\t密码\n");
	fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
	printf("\n注册成功!!!\n");
	fclose(fp);
	system("pause");
	system("cls");
	login();
}

//登录账号功能 
void login()
{
	char ac[30] = { 0 };
	char ad[20] = { 0 }, pw='0';
	int	i, j, a = 0;
	int	flag = 0;

	printf("--------【登录账号】--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("请输入帐号:");
		scanf("%s", &ac);
		printf("请输入密码:");
		for (j = 0; j < 6; j++)
		{
			pw = _getch();
			printf("*");
			ad[j] = pw;
		}
		FILE* fp;
		fp = fopen("账号信息档案.txt", "r");//读取文件操作
		while (!feof(fp))
		{
			fscanf(fp, "%s %sn", &use[a].ac, &use[a].pw);
			if ((strcmp(ac, use[a].ac) == 0) && (strcmp(ad, use[a].pw) == 0))
			{
				flag = 1;
				fclose(fp);
				break;
			}
			a++;
		}

		if (flag == 1)
		{
			printf("\n登录成功!");
			printf("按任意键进入飞机航班系统!\n");
			system("pause");
			system("cls");
			return;
		}
		else {
			printf("\n账号或者密码输入错误，你还有%d次机会，请重新输入：\n", 2 - i);
		}
	}
	if (i == 3)
	{
		printf("登录失败\n");
		system("pause");
		exit(0) ;
	}
	
}
  