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

//��¼���� 
void Hello()
{
	int se;
	printf("********************************************\n");
	printf("**********�ɻ�����ϵͳ��¼����**********\n");
	printf("********************************************\n\n");
	printf("   \t\t1.-��¼�˺�-\n");
	printf("\t\t2.-ע���˺�-\n");
	printf("\t\t3.-�˳�����-\n\n");
	printf("******************��ӭʹ��******************\n");
	printf("��ѡ��");
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
		printf("\n\t\t���ɹ��˳���\n");
		exit(0);
		system("pause");
		break;
	default:
		printf("\nû�����ѡ�������ѡ��\n");
		Hello();
	}
}

// ע���˺Ź��� 
void registeruser()
{
	char ac[30]; //�˺�
	char pw[6], pd[6]; //���� ��֤����
	int	i, a = 0;
	

	printf("\t\t��ע���ʺš�\n");
	FILE* fp = fopen("�˺���Ϣ����.txt", "wb+");
	printf("�������û��˺ź�����(�˺š��������Ϊ����,������ĸ,Ӣ����ĸ,����,�������6λ)\n\n\n");
	while (1)
	{
		int v = 0;
		printf("\t���������˺ţ�");
		scanf("%s", &ac);
		strcpy(use[a].ac, ac);
		printf("\n\t�����������룺");
		for (i = 0; i < 6; i++)
		{
			pw[i] = _getch();
			printf("*");
			use[a].pw[i] = pw[i];
			if (pw[i] == '\r')
			{
				printf("\n\tע��ʧ�ܣ�������ע���˺�\n");
				exit(0);
			}
		}
		printf("\n\n\t�ٴ�ȷ�����룺");
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
			printf("\n���벻�ԣ�������ע���˺�\n");
			continue;
		}
	}
	fprintf(fp, "�˺�\t����\n");
	fprintf(fp, "%s\t%s\n", use[a].ac, use[a].pw);
	printf("\nע��ɹ�!!!\n");
	fclose(fp);
	system("pause");
	system("cls");
	login();
}

//��¼�˺Ź��� 
void login()
{
	char ac[30] = { 0 };
	char ad[20] = { 0 }, pw='0';
	int	i, j, a = 0;
	int	flag = 0;

	printf("--------����¼�˺š�--------\n");
	for (i = 0; i < 3; i++)
	{
		printf("�������ʺ�:");
		scanf("%s", &ac);
		printf("����������:");
		for (j = 0; j < 6; j++)
		{
			pw = _getch();
			printf("*");
			ad[j] = pw;
		}
		FILE* fp;
		fp = fopen("�˺���Ϣ����.txt", "r");//��ȡ�ļ�����
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
			printf("\n��¼�ɹ�!");
			printf("�����������ɻ�����ϵͳ!\n");
			system("pause");
			system("cls");
			return;
		}
		else {
			printf("\n�˺Ż���������������㻹��%d�λ��ᣬ���������룺\n", 2 - i);
		}
	}
	if (i == 3)
	{
		printf("��¼ʧ��\n");
		system("pause");
		exit(0) ;
	}
	
}
  