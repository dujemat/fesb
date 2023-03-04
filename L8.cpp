#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

const char filename[] = "datot.txt";

struct _Node;
typedef struct _Node* Position;

struct _Node
{
	int el;
	Position Next;
};

void Push(Position, int);
int Pop(Position);
int Cn(int, char, int);

void main(void)
{
	struct _Node S;
	FILE* stream;
	char filename[1024] = { 0 };

	S.Next = NULL;

	printf("\r\n\t\t-- Postfix --");
	printf("\r\n\r\nRead:\t");

	fopen_s(&stream, filename, "r");
	if (stream == NULL)
		printf("\r\nFile not opened!", filename);
	else
	{
		while (!feof(stream))
		{
			char data[32] = { 0 };
			int x;

			fscanf(stream, " %s", data, 32);
			printf(" %s", data);

			x = atoi(data);
			if (x == 0 && data[0] != '0')
			{
				int x, y, n;

				y = Pop(&S);
				x = Pop(&S);
				n = Cn(x, data[0], y);
				Push(&S, n);
			}
			else
				Push(&S, x);
		}
		fclose(stream);
	}

	printf("\r\n\r\n\r\nResult :\t%d\r\n\r\n", S.Next->el);
	free(S.Next);
}

void Push(Position P, int n)
{
	Position q;

	q = (Position)malloc(sizeof(struct _Node));
	if (q)
	{
		q->el = n;
		q->Next = P->Next;
		P->Next = q;
	}
}

int Pop(Position P)
{
	Position tmp;
	int n = 0;

	if (P->Next != NULL)
	{
		tmp = P->Next;
		P->Next = tmp->Next;
		n = tmp->el;
		free(tmp);
	}
	return n;
}

int Cn(int x, char o, int y)
{
	int n = 0;
	switch (o)
	{
	case '+':
		n = x + y;
		break;
	case '-':
		n = x - y;
		break;
	case '*':
		n = x * y;
		break;
	case '/':
		if (y != 0)
			n = x / y;
		else
			printf("\r\nDivide overflow!\r\n");
		break;
	case '%':
		n = x % y;
		break;
	default:
		;
	}
	return n;
}