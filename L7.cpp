//NIJE DOVRŠENO!
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

const char wrong[] = "\nWrong option. Try again.\n\n";
const char ERR_404[] = "Not found!\n";
const char ERR_500[] = "\n\tNo content!\t\n";

struct _Node;
typedef struct _Node* Position;
struct _Node
{
	int el;
	int prior;
	Position next;
};

int GetVal(int, int);
int PushOnStack(Position, int, int);
int PopFromStack(Position, int);
void PrintListS(Position, int);
void PushInOrder(Position, int);
void PopFromOrder(Position);
void PrintListO(Position);
int DeleteList(Position);

void main(void)
{
	struct _Node S, R;
	char option = 0;
	int n = 0;
	int max = 0;
	int isValid = 0;


	S.next = NULL;
	S.el = -1;
	R.next = NULL;

	while (max < 5)
	{
		printf("\r\nEnter size from range <5-20>: ");
		scanf_s(" %d", &max);
		if (max < 5 || max > 20)
		{
			max = 0;
			printf(wrong);
		}
	}

	S.next = NULL;
	srand((unsigned)time(NULL));

	while (option != 'K' && option != 'k')
	{

		printf("\r\n\t\t1.\tPush on stack");
		printf("\r\n\t\t2.\tPop from stack");
		printf("\r\n\t\t3.\tPush in order");
		printf("\r\n\t\t4.\tPop from order");
		printf("\r\n\t\tk.\tEnd");
		printf("\r\n\r\nOption: ");
		scanf_s(" %c", &option, 1);

		switch (option)
		{
		case '1':
			if (n < max)
				n = PushOnStack(&S, GetVal(0, 10000), n);
			else
				printf("\r\nStack is full!\r\n");
			PrintListS(S.next, n);
			break;
		case '2':
			if (n > 0)
				n = PopFromStack(&S, n);
			PrintListS(S.next, n);
			break;
		case '3':
			PushInOrder(&R, GetVal(0, 10000));
			PrintListO(R.next);
			break;
		case '4':
			PopFromOrder(&R);
			PrintListO(R.next);
			break;
		case 'K':
		case 'k':
			break;
		default:
			printf(wrong);
		}
	}
	DeleteList(&S);
	DeleteList(&R);
}

int GetVal(int min, int max)
{
	int x = 0;
	x = rand() % (max - min) + min;
	return x;
}

int PushOnStack(Position P, int x, int n)
{
	static Position last;
	Position q;

	q = (Position)malloc(sizeof(struct _Node));
	if (q)
	{
		if (P->next == NULL)
			last = q;
		q->el = x;
		printf("\r\nAdding %d.", x);
		q->next = P->next;
		P->next = q;

		last->next = q;
		n++;
	}
	return n;
}

int PopFromStack(Position P, int n)
{
	static Position last = NULL;
	Position tmp;

	if (P->next != NULL)
	{
		tmp = P->next;
		printf("\r\nRemoving %d.", tmp->el);
		P->next = tmp->next;

		if (last == NULL && n > 1)
		{
			while (P->next != tmp)
				P = P->next;
			last = P;
		}

		last->next = tmp->next;
		free(tmp);
		n--;
		if (n == 0)
			last = NULL;
	}
	else
		printf(ERR_500);

	return n;
}

void PrintListS(Position P, int n)
{
	printf("\r\n\r\nThere are %d elements:\r\n", n);
	while (n > 0)
	{
		printf(" %d", P->el);
		P = P->next;
		n--;
	}
}
void PopFromOrder(Position P)
{
	Position tmp;

	if (P->next != NULL)
	{
		tmp = P->next;

		printf("\r\nRemoving %d %d.", tmp->el, tmp->prior);

		P->next = tmp->next;
		free(tmp);
	}
	else
		printf(ERR_500);
}

void PrintListO(Position P)
{
	printf("\r\n\r\nThere are:\r\n");
	while (P)
	{
		printf(" ( %d %d )", P->el, P->prior);
		P = P->next;
	}
}

void PushInOrder(Position P, int n)
{
	Position q;

	q = (Position)malloc(sizeof(struct _Node));
	if (q)
	{
		q->el = n;
		q->prior = GetVal(1, 5);
		printf("\r\nSaving ( %d %d )", q->el, q->prior);

		while (P->next != NULL && P->next->prior >= q->prior)
			P = P->next;

		q->next = P->next;
		P->next = q;
	}
}
int DeleteList(Position P)
{
	FILE* fp;
	struct Node* tmp;
	if (fp == NULL) {
		printf(ERR_404, fname);
		return -1;
	}

	while (P->next != NULL)
	{
		tmp = P->next;
		P->next = tmp->next;
		free(tmp);
	}

	return 0;
}
