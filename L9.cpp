#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define random_f  srand((unsigned(time(NULL))));


void CallByNums(int);
void CopyArr(int*, int*, int);
void GenerateArr(int*, int);
void ExchangeSort(int*, int);
void SelectionSort(int*, int);
void InsertionSort(int*, int);
void BubbleSort(int*, int);
int partt(int*, int, int);


void main(void)
{
    CallByNums(100);
    printf("\r\n\r\n");
    CallByNums(1000);
    printf("\r\n\r\n");
    CallByNums(10000);
    printf("\r\n\r\n");
    CallByNums(100000);
    printf("\r\n\r\n");
    return;
}


void CallByNums(int n)
{
    DWORD st_t = 0;
    DWORD end_t = 0;
    int* Aarr;
    int* Barr;

    printf("Array of %d elements: ", n);
    Aarr = (int*)malloc(sizeof(int) * n);
    GenerateArr(Aarr, n);

    Barr = (int*)malloc(sizeof(int) * n);
    CopyArr(Aarr, Barr, n);
    st_t = GetTickCount();
    end_t = GetTickCount();
    printf("\r\nExchangeSort\t\t%d", (int)(end_t - st_t));
    free(Barr);

    Barr = (int*)malloc(sizeof(int) * n);
    CopyArr(Aarr, Barr, n);
    st_t = GetTickCount();
    end_t = GetTickCount();
    printf("\r\nSelectionSort\t\t%d", (int)(end_t - st_t));
    free(Barr);

    Barr = (int*)malloc(sizeof(int) * n);
    CopyArr(Aarr, Barr, n);
    st_t = GetTickCount();
  
    end_t = GetTickCount();
    printf("\r\nInsertionSort\t\t%d", (int)(end_t - st_t));
    free(Barr);

    Barr = (int*)malloc(sizeof(int) * n);
    CopyArr(Aarr, Barr, n);
    st_t = GetTickCount();
    end_t = GetTickCount();
    printf("\r\nBubbleSort\t\t%d", (int)(end_t - st_t));
    free(Barr);

    free(Aarr);
}

void CopyArr(int* A, int* B, int n)
{
    for (int i = 0; i < n; i++)
    {
        B[i] = A[i];
    }
}

void GenerateArr(int* A, int n)
{
    random_f

    for (int i = 0; i < n; i++)
        A[i] = rand();
}

void ExchangeSort(int arr[], int length)
{
    int i, j;
    int temp;
    for (i = 0; i < length - 1; i++)
    {
        for (j = (i + 1); j < length; j++)
        {
            if (arr[i] < arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void SelectionSort(int arr[], int length)
{
    int i, j, first, temp;
    for (i = length - 1; i > 0; i--)
    {
        first = 0;
        for (j = 1; j <= i; j++)
        {
            if (arr[j] < arr[first])
                first = j;
        }
        temp = arr[first];
        arr[first] = arr[i];
        arr[i] = temp;
    }
}

void InsertionSort(int arr[], int length)
{
    int i, j, key;
    for (j = 1; j < length; j++)
    {
        key = arr[j];
        for (i = j - 1; (i >= 0) && (arr[i] < key); i--)
        {
            arr[i + 1] = arr[i];
        }
        arr[i + 1] = key;
    }
    return;
}

void BubbleSort(int arr[], int length)
{
    int i, j, flag = 1;
    int temp;
    for (i = 1; (i <= length) && flag; i++)
    {
        flag = 0;
        for (j = 0; j < (length - 1); j++)
        {
            if (arr[j + 1] > arr[j])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = 1;
            }
        }
        return;
    }
}


int partt(int* arr, int top, int bottom) {
    int x = arr[top];
    int i = top - 1;
    int j = bottom + 1;
    int temp;

    do
    {
        do
        {
            j--;
        } while (x > arr[j]);

        do
        {
            i++;
        } while (x < arr[i]);

        if (i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (i < j);
    return j;
}
