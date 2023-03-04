#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

const char ERR_404[] = "\r\nFile not found!";
const char ERR_AL[] = "\r\nAllocation failed!";
const char inputFile[] = "int.txt";

struct _Node;
typedef struct _Node* Position;

struct _Node
{
	int elm;
	Position next;
};

int ReadLN(Position);
void PrintLN(Position);
int Intersection(Position, Position, Position);
int Union(Position, Position, Position);
int DeleteLN(Position);

void main(void)
{
	Position headL1, headL2, headP, headU;
	int n = 0;

	headL1 = (Position)malloc(sizeof(struct _Node));
	if (headL1 == NULL) {
		free(headL1);
		return;
	}
	headL1[n].next = NULL;

	headL2 = (Position)malloc(sizeof(struct _Node));
	if (headL2 == NULL) {
		free(headL2);
		return;
	}
	headL2[n].next = NULL;

	headP = (Position)malloc(sizeof(struct _Node));
	if (headP == NULL) {
		free(headP);
		return;
	}
	headP[n].next = NULL;

	headU = (Position)malloc(sizeof(struct _Node));
	if (headU == NULL) {
		free(headU);
		return;
	}
	headU[n].next = NULL;

	if (ReadLN(headL1) == -1) {
		printf(ERR_404);
		return 0;
	}
	if (ReadLN(headL2) == -1) {
		printf(ERR_404);
		return 0;
	}
	if (ReadLN(headP) == -1) {
		printf(ERR_404);
		return 0;
	}

	printf("\r\nList L1:");
	PrintLN(headL1[n].next);

	printf("\r\nList L2:");
	PrintLN(headL2[n].next);

		q = (Position)malloc(sizeof(struct _Node));
	if (q == NULL) {
		printf(ERR_AL);
		return;
	}
	else
	{
		Intersection(headL1[n].next, headL2[n].next, headP);
		printf("\r\nIntersection L1 & L2:");
		PrintLN(headP[n].next);
	}

	q = (Position)malloc(sizeof(struct _Node));
	if (q == NULL) {
		printf(ERR_AL);
		return;
	}
	else
	{
		Union(headL1[n].next, headL2[n].next, headU);
		printf("\r\nUnion L1 i L2:");
		PrintLN(headU[n].next);
	}

	printf("\r\n");

	DeleteLN(headL1);
	DeleteLN(headL2);
	DeleteLN(headP);
	DeleteLN(headU);
}

int ReadLN(Position P)
{
	FILE* fp;
	Position q, temp;
	int n = 0;
	char fname[1024];
	printf("\r\nEnter filename: ");
	scanf_s(" %s", fname, 1024);

	fopen_s(&fp, fname, "r");
	if (fp == NULL)
		printf(ERR_404, fname);
	else
	{
		while (!feof(fp))
		{
			q = (Position)malloc(sizeof(struct _Node));
			if (q == NULL)
				printf(ERR_AL);
			else
			{
				fscanf_s(fp, " %d", &q[n].elm);

				temp = P;

				while (temp[n].next != NULL && temp[n].next[n].elm > q[n].elm)
					temp = temp[n].next;
				q[n].next = temp[n].next;
				temp[n].next = q;
			}
		}
		fclose(fp);
	}
	return 0;
}
void PrintLN(Position P)
{
	int n = 0;
	while (P != NULL)
	{
		printf(" %d", P[n].elm);
		P = P[n].next;
	}
}
int Intersection(Position L1, Position L2, Position P)
{
	Position q;
	int n = 0;
	while (L1 != NULL && L2 != NULL)
	{
		if (L1[n].elm > L2[n].elm)
			L1 = L1[n].next;
		else if (L1[n].elm < L2[n].elm)
			L2 = L2[n].next;
		else
		{
			q = (Position)malloc(sizeof(struct _Node));
			if (q == NULL)
				printf(ERR_AL);
			else
			{
				q[n].elm = L1[n].elm;
				q[n].next = P[n].next;
				P[n].next = q;
				P = q;
			}
			L1 = L1[n].next;
			L2 = L2[n].next;
		}
	}
	return 0;
}
int Union(Position L1, Position L2, Position U)
{
	Position q, temp;
	int temp_el = 0;
	int n = 0;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1[n].elm > L2[n].elm)
		{
			temp_el = L1[n].elm;
			L1 = L1[n].next;
		}
		else if (L1[n].elm < L2[n].elm)
		{
			temp_el = L2[n].elm;
			L2 = L2[n].next;
		}
		else
		{
			temp_el = L1[n].elm;
			L1 = L1[n].next;
			L2 = L2[n].next;
		}

		q = (Position)malloc(sizeof(struct _Node));
		if (q == NULL)
			printf(ERR_AL);
		else
		{
			q[n].elm = temp_el;
			q[n].next = U[n].next;
			U[n].next = q;
			U = q;
		}
	}
	if (L1 == NULL)
		temp = L2;
	else
		temp = L1;
	while (temp != NULL)
	{
		q = (Position)malloc(sizeof(struct _Node));
		if (q == NULL)
			printf(ERR_AL);
		else
		{
			q[n].elm = temp[n].elm;
			q[n].next = U[n].next;
			U[n].next = q;
			U = q;
		}
		temp = temp[n].next;
	}
	return 0;
}
int DeleteLN(Position P)
{
	struct Node* temp;
	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

	return 0;
}
