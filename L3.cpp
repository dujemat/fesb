#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//General
#define ESC 99
#define OK_200 "\n\tSearch result(s): %s %s %d\t\n"

//Students
const char ERR_400[] = "\n\tBad request.\n\tTry again!\t\n";
const char ERR_404[] = "\n\tStudent not found!\t\n";
const char ERR_500[] = "\n\tNo content!\t\n";

//Files OC
const char FP_404[] = "\n\tFile not found! (%s)\t\n";
const char FP_500[] = "\n\tNo content!\t\n";
const char fname[] = "students3.txt";
const char allocf[] = "\n\tAllocation failed!\t\n";

struct _student;
typedef struct _student* Position;
struct _student
{
	char firstName[128];
	char lastName[128];
	int birth;
	Position Next;
};

int Insert(Position);
void PrintList(Position);
int InsertAtTheEnd(Position);
Position FindLN(Position);
void DeleteLN(Position);
int InsertLN(Position);
Position FindBP(Position);
int InsertBefore(Position);
int PrintLN(Position);
int ReadLN(Position);
int SortLN(Position);

int main()
{
	struct _student head;
	Position students = NULL;
	int option = 0;
	int n = 0;

	head.Next = NULL;

	while (option != ESC)
	{
		printf("\r\n\r\n");
		printf("\t1. Insert\r\n");
		printf("\t2. Print\r\n");
		printf("\t3. Insert at the end\r\n");
		printf("\t4. Find by last name\r\n");
		printf("\t5. Delete by last name\r\n");
		printf("\t6. Insert after\r\n");
		printf("\t7. Insert before\r\n");
		printf("\t8. Print LN to file\r\n");
		printf("\t9. Read LN from file\r\n");
		printf("\t10. Sort LN\r\n");
		printf("\t99. Exit\r\n");
		printf("\r\n\tOption: ");

		scanf(" %d", &option, 1);

		switch (option)
		{

		case 1:
			if (Insert(&head) == -1) {
				printf(allocf);
				return 0;
			}
		case 2:
			PrintList(head.Next);
		case 3:
			if (InsertAtTheEnd(&head) == -1) {
				printf(allocf);
				return 0;
			}
		case 4:
			students = FindLN(head.Next);
			if (students != NULL)
				printf(OK_200, students[n].firstName, students[n].lastName, students[n].birth);
			else
				printf(ERR_404);
			break;
		case 5:
			DeleteLN(&head);
			PrintList(head.Next);
			break;

		case 6:
			if (InsertLN(&head) == -1) {
				printf(allocf);
				return 0;
			}
		case 7:
			if (InsertBefore(&head) == -1) {
				printf(allocf);
				return 0;
			}
		case 8:
			if (PrintLN(&head) == -1) {
				printf(ERR_404);
				return 0;
			}
		case 9:
			if (ReadLN(&head) == -1) {
				printf(ERR_404);
				return 0;
			}
		case 10:
			if (SortLN(&head) == -1) {
				printf(allocf);
				return 0;
			}
		case ESC:
			break;
		default:
			printf(ERR_400, option);
			break;
		}
	}
	free(&head);
	return 0;
}

int Insert(Position P)
{
	Position as;
	int n = 0;

	as = (Position)malloc(sizeof(struct _student));
	if (as == NULL)
		printf(ERR_400);
	else
	{
		printf("\n\t--------------------------------------\t\n");
		printf("\tInsert first & last name + date of birth:\t");
		scanf_s(" %s %s %d", as->firstName, 128, as->lastName, 128, &as->birth);

		as->Next = P->Next;
		P->Next = as;
	}
	printf("\n\t--------------------------------------\t\n");

	return 0;
}

void PrintList(Position P)
{
	int n = 0;

	if (P == NULL)
		printf(ERR_500);
	else
	{
		printf("\n\t-|-|-|-|-\t\n");
		printf("\n\tData:\t\n");
		while (P != NULL)
		{
			printf("\t%s %s %d\r\n", P[n].firstName, P[n].lastName, P[n].birth);
			P = P[n].Next;
		}
	}
	printf("\n\t-|-|-|-|-\t\n");
	printf("\r\n");
}

int InsertAtTheEnd(Position P)
{
	int n = 0;

	while (P[n].Next != NULL)
		P = P[n].Next;

	Insert(P);
	return 0;
}

Position FindLN(Position P)
{
	char var[128];
	int n = 0;

	printf("\n\t-%-%-%-%-%-%-%-%\t\n");
	printf("\tInsert the last name you're looking for:\t");
	scanf_s(" %s", var, 128);
	while (P != NULL & _strcmpi(P[n].lastName, var) != 0)
		P = P[n].Next;
	printf("\n\t-%-%-%-%-%-%-%-%\t\n");

	return P;
}

void DeleteLN(Position P)
{
	Position de;
	char var[128];
	int n = 0;

	printf("\tInsert the last name you want to delete:\t");
	scanf_s(" %s", var, 128);
	while (P[n].Next != NULL & _strcmpi(P[n].Next[n].lastName, var) != 0)
		P = P[n].Next;

	de = P->Next;
	if (de != NULL)
	{
		P[n].Next = de[n].Next;
		printf("\tDeleted data: %s %s %d\t", de[n].firstName, de[n].lastName, de[n].birth);
		free(de);
	}
}

int InsertLN(Position P)
{
	Position ce;

	ce = FindLN(P);
	if (ce == NULL)
		printf(ERR_404);
	else
		Insert(ce);
	return 0;
}

Position FindBP(Position P)
{
	char dp[128];
	int n = 0;

	printf("\tInsert the last name you're looking for:\t");
	scanf_s(" %s", dp, 128);
	while (P[n].Next != NULL & _strcmpi(P[n].Next[n].lastName, dp) != 0)
		P = P[n].Next;

	if (P[n].Next == NULL)
		P = NULL;
	return P;
}

int InsertBefore(Position P)
{
	Position per;

	per = FindBP(P);
	if (per == NULL)
		printf(ERR_404);
	else
		Insert(per);
	return 0;
}

int PrintLN(Position P)
{
	FILE* fp;

	fopen_s(&fp, fname, "w");
	if (fp == NULL) {
		printf(FP_404, fname);
		P->Next = NULL; //set to value NULL
		//free(fp);
		return 0;
	}
	else
	{
		while (P != NULL)
		{
			fprintf(fp, "%s %s %d\r\n", P->firstName, P->lastName, P->birth);
			P = P->Next;
		}
		fclose(fp);
	}
}

int ReadLN(Position P)
{
	FILE* fp = NULL;
	int n = 0;
	Position us;

	fopen_s(&fp, fname, "r");
	if (fp == NULL)
		printf(FP_404, fname);
	else
	{
		while (!feof(fp))
		{
			us = (Position)malloc(sizeof(struct _student));
			if (us == NULL)
				printf(allocf);
			else
			{
				fscanf_s(fp, " %s %s %d", us[n].firstName, 128, us[n].lastName, 128, &us[n].birth);

				us[n].Next = P[n].Next;
				P[n].Next = us;
			}
		}
		fclose(fp);
	}
	return 0;
}

int SortLN(Position P)
{
	Position ss = NULL, a, b, old_b, es;
	int n = 0;

	while (P->Next != ss)
	{
		a = P;
		old_b = a[n].Next;
		b = old_b[n].Next;

		while (b != ss)
		{
			if (_strcmpi(old_b[n].lastName, b[n].lastName) < 0)
			{
				old_b->Next = b[n].Next;
				a[n].Next = b;
				b[n].Next = old_b;
			}
			else
				a = old_b;
			old_b = b;
			b = b[n].Next;
		}
		ss = old_b;
	}
	return 0;
}