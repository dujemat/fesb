#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ESC 9
#define OK_200 "\n\tSearch result(s): %s %s %d\t\n"

const char ERR_400[] = "\n\tBad request.\n\tTry again!\t\n";
const char ERR_404[] = "\n\tStudent not found!\t\n";
const char ERR_500[] = "\n\tNo content!\t\n";

struct _student;
typedef struct _student* Position;
struct _student
{
	char firstName[128];
	char lastName[128];
	int birth;
	Position Next;
};

void Insert(Position);
void PrintList(Position);
void InsertAtTheEnd(Position);
Position FindLN(Position);
void DeleteLN(Position);

void main(void)
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
		printf("\t9. Exit\r\n");
		printf("\r\n\tOption: ");

		scanf(" %d", &option, 1);

		switch (option)
		{
		case 1:
			Insert(&head);
			break;
		case 2:
			PrintList(head.Next);
			break;
		case 3:
			InsertAtTheEnd(&head);
			break;
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
		case ESC:
			break;
		default:
			printf(ERR_400, option);
			break;
		}
	}
}

void Insert(Position P)
{
	Position q;
	int n = 0;

	q = (Position)malloc(sizeof(struct _student));
	if (q == NULL)
		printf(ERR_400);
	else
	{
		printf("\n\t--------------------------------------\t\n");
		printf("\tInsert first & last name + date of birth:\t");
		scanf_s(" %s %s %d", q[n].firstName, 128, q[n].lastName, 128, &q[n].birth);

		q[n].Next = P[n].Next;
		P[n].Next = q;
	}
	printf("\n\t--------------------------------------\t\n");
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

void InsertAtTheEnd(Position P)
{
	int n = 0;

	while (P[n].Next != NULL)
		P = P[n].Next;

	Insert(P);
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