// Write a program that first reads how many lines there are in the file, i.e. how many students are enrolled in files.
// After that, it is necessary to dynamically allocate space for a number of student structures(name, surname, points) and load all records from the file.
// Print the name, surname, absoluteand relative number of points on the screen.

// IMPORTANT NOTE: Each line of the file contains the name and surname of the student, and the number of points on the exam.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

const char inputFile[] = "assets/list.txt";
const char E_404[] = "\nFile not found! (%s)";
const char E_500[] = "\nNo content! (%s)";

struct _student
{
	char firstName[128];
	char lastName[128];
	int score;
};

int CountRecords(const char*);
int ReadRecords(const char*, struct _student*);

void main(const char* fname)
{
	FILE* fp = NULL;
	int nCount = 0;
	int nRead = 0;
	int maxScore = 0;
	float avgScore = 0;
	int n = 0;
	struct _student* p_array, * s_array;
	p_array = NULL;

	printf("\t\t---LIST OF STUDENTS---\r\n");
	nCount = CountRecords(inputFile);

	if (nCount <= 0)
		printf(E_500, inputFile);
	else
	{
		printf("\r\nNumber of students in %s: %d\n", inputFile, nCount);
		p_array = (struct _student*)malloc(sizeof(struct _student) * nCount);
		s_array = p_array;
		maxScore = ReadRecords(inputFile, s_array);

		printf("\r\nNum %12s %15s %8s %4s %6s\n", "First name", "Last name", "Score", "Max", "Rel");
		printf("\r---|---------------|---------------|-----|-----|-------");
		nRead = 0;
		while (nRead < nCount)
		{
			printf("\r\n%#2d. %12s %15s %7d / %3d = %#6.2f", nRead + 1, s_array[n].firstName, s_array[n].lastName, s_array[n].score, maxScore, (float)s_array[n].score / maxScore * 100);
			s_array++;
			nRead++;
		}
		free(p_array);
	}
	printf("\r\n\r\n");
}

int CountRecords(const char* inputFile)
{
	int n = 0;
	FILE* fp = NULL;
	char buff[1024] = { 0 };
	fp = fopen(inputFile, "r");

	if (fp == NULL)
		printf(E_404, inputFile);
	else {
		while (!feof(fp)) {
			fgets(buff, 1024, fp);
			n++;
		}
		fclose(fp);
	}
	return n;
}

int ReadRecords(const char* inputFile, struct _student* S)
{
	int n = 0;
	FILE* fp = NULL;
	fp = fopen(inputFile, "r");

	if (fp == NULL)
		printf(E_404, inputFile);
	else {
		while (!feof(fp)) {
			fscanf_s(fp, "%s %s %d", S->firstName, 128, S->lastName, 128, &S->score);
			if (S->score > n)
				n = S->score;
			S++;
		}
		fclose(fp);
	}
	return n;
}