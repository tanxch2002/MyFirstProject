#pragma warning(disable:4996)
#include <stdio.h>
#ifndef _PASSENGER_H
#define _PASSENGER_H

#pragma once

//ÂÃ¿Í½Úµã
typedef struct _PAS {
	int id;
	char name[20];
	char sex[5];
	int age;
	char idn[20];
	int pho_num[12];
	int history_flight;
	struct _PAS* pNext;
} PASNODE;

typedef struct _fli {
	char airline_ID[8];
	char departure[10];
	char arrival[10];
	int price;
	float departure_time;
	float arrival_time;
	int passenger_number;
	int tickets_left;
	int distance;
	struct _fli* pNext;
} FLINODE;

extern void AddPasInfo(char* name, char sex[5], int age, int idn[20], int pho_num[12]);
extern void FreeLinkData();
extern void ShowPasData();
extern void AddPasInfoToLinkHead();
extern void ShowSbData(char name[20]);
extern PASNODE* FindPasByName(char name[20]);
extern void DelPasInfo(char name[20]);
extern void DelStuNode(PASNODE* pNode);
extern void SavePasToFile();
//extern void ReadPasInfoFromFile();
#endif // !_PASSENGER_H
