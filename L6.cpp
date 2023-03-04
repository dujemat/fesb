#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#define min 10
#define max 100

const char wrong[] = "\nWrong choice. Try again.\n\n";
const char add[] = "\nValue %d added!\n";
const char del[] = "\nDeleted value: %d.\n";

const char ERR_404[] = "No elements to pop!\n";
const char ERR_500[] = "\n\tNo content!\t\n";

struct node;
typedef struct node* position;

struct node {
	int element;
	position next;
};

int RandomNum(int, int);
void PrintList(position);
void PushStack(position, int);
void PushRow(position, int);
void Pop(position);
int DelLN(struct Node*);


int main()
{
	node stack, row;
	stack.next = NULL;
	row.next = NULL;

	int sel = 1;
	int isValid = 0;

	while (sel != 0)
	{
		printf("\n\n\t\t-> Main menu <-\n");
		printf("\n\t 0 - End");
		printf("\n\t 1 - Push (stack)");
		printf("\n\t 2 - Pop (stack)");
		printf("\n\t 3 - Push (row)");
		printf("\n\t 4 - Pop (row)");

		printf("\n\nSelection:\t");
		scanf_s(" %d", &sel);

		switch (sel)
		{
		case 1:
			PushStack(&stack, RandomNum(min, max));
			PrintList(stack.next);
			break;

		case 2:
			if (stack.next == 0) {
				printf(ERR_404); //if empty, return to menu without ending
				break;
			}
			else {
				Pop(&stack);
				PrintList(stack.next);
				break;
			}
		case 3:
			PushRow(&row, RandomNum(min, max));
			PrintList(row.next);
			break;
		case 4:
			if (row.next == 0) {
				printf(ERR_404);
				break;
			}
			else {
				Pop(&row);
				PrintList(row.next);
				break;
			}
		case 0:
			sel = 0;
			break;
		default:
			printf(wrong);
		}
	}
	system("pause");
	return 0;
	
        DelLN(&stack);
	DelLN(&row);
}

int RandomNum(int minV, int maxV)
{
	int val;
	val = rand() % (maxV - minV) + minV;
	return val;
}

void PrintList(position p) {
	
	if (p == NULL) {
		printf(ERR_500);
	}
	else {
		printf("\nElements: \n");
		while (p)
		{
			printf("%d ", p->element);
			p = p->next;
		}
	}
}

void PushStack(position p, int value) {

	position tmp;
	tmp = (position)malloc(sizeof(node));

	if (tmp) {
		tmp->element = value;
		tmp->next = p->next;
		p->next = tmp;

		printf(add, value);
	}
}

void PushRow(position p, int value) {

	position tmp;
	static position last;

	if (p->next == NULL)
		last = p;

	tmp = (position)malloc(sizeof(struct node));
	if (tmp)
	{
		tmp->element = value;
		tmp->next = last->next;
		last->next = tmp;
		last = tmp;

		printf(add, value);
	}
}

void Pop(position p) {
	position tmp;

	if (p->next != NULL) {
		tmp = p->next;
		printf(del, tmp->element);

		p->next = tmp->next;
		free(tmp);
	}
}
int DelLN(struct Node* head)
{
	struct Node* tmp;
	while (head->next != NULL)
	{
		tmp = head->next;
		head->next = tmp->next;
		free(tmp);
	}
	return 0;
}
