#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define ERR_ALL "Allocation failed!\n"
#define ERR_FILE "File not opened\n"
#define MembershipList "assets/memberships.txt"


struct _membership;
typedef struct _membership* MembershipP;

typedef struct _membership {
    char userId[32];
    char firstName[32];
    char lastName[32];
    int month;
    int year;
    int price;
    MembershipP next;
} Membership;

MembershipP createMember(char*, char*, char*, int, int, int);
MembershipP insertMember(MembershipP head, MembershipP newMember);
void printList(MembershipP head);
void freeList(MembershipP head);

int main() {
    FILE* fp;
    MembershipP head = NULL;
    char userId[32], firstName[32], lastName[32], monthYear[8];
    int month, year, price;

    fp = fopen(MembershipList, "r");
    if (fp == NULL) {
        printf(ERR_FILE);
        return 0;
    }

    while (fscanf(fp, "%s %s %s %s %d", userId, firstName, lastName, monthYear, &price) == 5) {
        month = atoi(strtok(monthYear, "-"));
        year = atoi(strtok(NULL, "-"));
        MembershipP newMember = createMember(userId, firstName, lastName, month, year, price);
        head = insertMember(head, newMember);
    }

    fclose(fp);
    printList(head);
    freeList(head);

    _getch(); //display
    return 0;
}
MembershipP createMember(char* userId, char* firstName, char* lastName, int month, int year, int price) {
    MembershipP member = (MembershipP)malloc(sizeof(Membership));
    if (member == NULL) {
        printf(ERR_ALL);
        return 0;
    }
    strcpy(member->userId, userId);
    strcpy(member->firstName, firstName);
    strcpy(member->lastName, lastName);
    member->month = month;
    member->year = year;
    member->price = price;
    member->next = NULL;
    return member;
}

MembershipP insertMember(MembershipP head, MembershipP newMember) {
    if (head == NULL) {
        head = newMember;
    }
    else if (head->year < newMember->year || (head->year == newMember->year && head->month < newMember->month)) {
        newMember->next = head;
        head = newMember;
    }
    else {
        head->next = insertMember(head->next, newMember);
    }
    return head;
}

void printList(MembershipP head) {
    printf("Memberships:\n");
    while (head != NULL) {
        printf("%s %s %s %d-%d %d\n", head->userId, head->firstName, head->lastName, head->month, head->year, head->price);
        head = head->next;
    }
}

void freeList(MembershipP head) {
    MembershipP current = head;
    while (current != NULL) {
        head = current->next;
        free(current);
        current = head;
    }
}
