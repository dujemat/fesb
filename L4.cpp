#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

const char ERR_404[] = "\r\nFile %s not found!";
const char ERR_500[] = "\r\nFile %s is empty!";
const char allocf[] = "\n\tAllocation failed!\t\n";

const char inputFile[] = "assets/pol.txt";

typedef struct _Poly
{
	int koef;
	int expo;
} Poly;

struct Node
{
	Poly pol;
	struct Node* next;
};

int ReadPol(struct Node*);
int PrintPol(struct Node*);
int SumPol(struct Node*, struct Node*, struct Node*);
int MulPol(struct Node*, struct Node*, struct Node*);
int DelLN(struct Node*);

int main(int)
{
	struct Node* headP1, struct Node* headP2, struct Node* headSum, struct Node* headMul;
	headP1->next = NULL;
	headP2->next = NULL;
	headSum->next = NULL;
	headMul->next = NULL;
	int isValid = 0;

	printf("P(x)\n");

	isValid = ReadPol(headP1);

	if (isValid == -1)
	{
		DelLN(headP1);
		return 0;
	}

	printf("Q(x)\n");

	isValid = ReadPol(headP2);

	if (isValid == -1)
	{
		DelLN(headP1);
		DelLN(headP2);
		return 0;
	}

	printf("P(x) = ");
	PrintPol(headP1->next);
	printf("\nQ(x) = ");
	PrintPol(headP2->next);
	printf("\nSum: ");

	isValid = SumPol(headP1->next, headP2->next, headSum);
	if (isValid == -1)
	{
		DelLN(headP1);
		DelLN(headP2);
		DelLN(headSum);
		return 0;
	}

	PrintPol(headSum->next);
	printf("\nProduct: ");
	isValid = MulPol(headP1->next, headP2->next, headSum);
	if (isValid == -1)
	{
		DelLN(headP1);
		DelLN(headP2);
		DelLN(headSum);
		DelLN(headMul);
		return 0;
	}
	PrintPol(headSum->next);
	DelLN(headP1);
	DelLN(headP2);
	DelLN(headSum);
	DelLN(headMul);

	return 0;

}

int ReadPol(struct Node* head)
{
	FILE* fp;
	struct Node* pol;

	fp = fopen(inputFile, "r");
	if (fp == NULL)
		printf(ERR_404, fp);

	while (!feof(fp))
	{
		pol = (struct Node*)malloc(sizeof(struct Node));
		if (pol == NULL)
		{
			printf(allocf);
			return -1;
		}
		fscanf(fp, "%d %d", &pol->pol.koef, &pol->pol.expo);
		pol->next = head->next;
		head->next = pol;
	}
	fclose(fp);
}

int PrintPol(struct Node* head)
{
	if (head == NULL)
		printf(ERR_500);

	while (head != NULL)
	{
		printf("%d x^%d", head->pol.koef, head->pol.expo);
		head = head->next;
		if (head != NULL)
			printf(" + ");
	}
	return 0;
}

int SumPol(struct Node* headP1, struct Node* headP2, struct Node* hrez)
{
	struct Node* pol, * temp;

	while (headP1 != NULL && headP2 != NULL)
	{
		pol = (struct Node*)malloc(sizeof(struct Node));

		if (pol == NULL)
		{
			printf(allocf);
			return -1;
		}

		if (headP1->pol.expo > headP2->pol.expo)
		{
			pol->pol.koef = headP1->pol.koef;
			pol->pol.expo = headP1->pol.expo;
			headP1 = headP1->next;
		}
		else if (headP1->pol.expo < headP2->pol.expo)
		{
			pol->pol.koef = headP2->pol.koef;
			pol->pol.expo = headP2->pol.expo;
			headP2 = headP2->next;
		}
		else
		{
			pol->pol.expo = headP1->pol.expo;
			pol->pol.koef = headP1->pol.koef + headP2->pol.koef;
			headP1 = headP1->next;
			headP2 = headP2->next;
		}
		pol->next = hrez->next;
		hrez->next = pol;
		hrez = hrez->next;
	}

	if (headP1 == NULL)
		temp = headP2;
	else
		temp = headP1;

	while (temp != NULL)
	{
		pol = (struct Node*)malloc(sizeof(struct Node));

		if (pol == NULL)
		{
			printf(allocf);
			return -1;
		}

		pol->pol.koef = temp->pol.koef;
		pol->pol.expo = temp->pol.expo;

		temp = temp->next;
		pol->next = hrez->next;
		hrez = hrez->next;
	}
	return 0;
}

int MulPol(struct Node* headP1, struct Node* headP2, struct Node* hrez)
{
	struct Node* i, * j, * pol, * temp;
	i = headP1;

	while (i != NULL)
	{
		j = headP2;
		while (j != NULL)
		{
			pol = (struct Node*)malloc(sizeof(struct Node));
			if (pol == NULL)
			{
				printf(allocf);
				return -1;
			}
			pol->pol.expo = i->pol.expo + j->pol.expo;
			pol->pol.koef = i->pol.koef * j->pol.koef;
			temp = hrez;

			while (temp->next != NULL && temp->next->pol.expo > pol->pol.expo)
				temp = temp->next;

			if (temp->next != NULL && temp->next->pol.expo == pol->pol.expo)
			{
				temp->next->pol.koef += pol->pol.koef;
				free(pol);
			}
			else
			{
				pol->next = temp->next;
				temp->next = pol;
			}
			j = j->next;
		}
		i = i->next;
	}
	return 0;
}

int DelLN(struct Node* head)
{
	struct Node* temp;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}