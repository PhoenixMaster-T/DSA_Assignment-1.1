#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int **readData(const char *file, int n, int *numcase)
{
    const char *file_name = file;
    FILE *f = 0;
    f = fopen(file_name, "r");
    // read number of case
    char *strNumCase = (char *)malloc(5 * sizeof(char));
    fgets(strNumCase, 5, f);
    int start1 = 0;
    int end1 = strlen(strNumCase);
    int numOfCase = 0;
    while (start1 < end1 && strNumCase[start1] <= '9' && strNumCase[start1] >= '0')
    {
        numOfCase = numOfCase * 10 + strNumCase[start1++] - '0';
    }
    *numcase = numOfCase;
    // dynamic allocate for 2D ar
    int **ar = (int **)malloc(numOfCase * sizeof(int *));
    for (int i = 0; i < numOfCase; i++)
        ar[i] = (int *)malloc(n * sizeof(int));

    // read All test case
    int i = 0;
    for (i = 0; i < numOfCase; i++)
    {
        char *str = (char *)malloc(100 * sizeof(char));
        if (feof(f))
            break;
        fgets(str, 100, f);
        if (str == NULL)
            break;
        int start = 0;
        int end = strlen(str);
        int j = 0;
        while (start < end)
        {
            while (start < end && (str[start] > '9' || str[start] < '0'))
                start++;
            if (start > end)
                break;
            int number = 0;
            while (start < end && str[start] <= '9' && str[start] >= '0')
            {
                number = number * 10 + str[start++] - '0';
            }
            ar[i][j] = number;
            j++;
        }
    }
    fclose(f);
    return ar;
}
void writeData(const char *fileName, int **arr, int numOfCases, int sizeArray)
{
    const char *file_name = fileName;
    FILE *f;
    f = fopen(file_name, "w");

    for (int i = 0; i < numOfCases; i++)
    {
        for (int j = 0; j < sizeArray; j++)
        {
            if (j == sizeArray - 1)
                fprintf(f, "a");
            else
                fprintf(f, "a");
        }
        printf("\n");
    }
}
//
/*int S(int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}
int max1(int a[], int n)
{
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (max < a[i])
            max = a[i];
    return max;
}
int min1(int a[], int n)
{
    int min = a[0];
    for (int i = 1; i < n; i++)
        if (min > a[i])
            min = a[i];
    return min;
}
bool sapxep(int a[], int n)
{
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] <= a[i + 1])
        {
            count++;
        }
    }
    if (count == n - 1)
        return true;
    else
        return false;
}
bool sapxepp(int a[], int n)
{
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] >= a[i + 1])
        {
            count++;
        }
    }
    if (count == n - 1)
        return true;
    else
        return false;
}
void SAPXEP(int a[], int n)
{
    if (sapxep(a, n) == 1)
    {
        printf("\n 1");
    }
    else if (sapxepp(a, n) == 1)
    {
        printf("\n -1");
    }
    else
    {
        printf("\n 0");
    }
}
int dmax(int a[], int n)
{
    int max = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int count = 1;
        for (int j = i; j < n - 1; j++)
        {
            if (a[j] <= a[j + 1])
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if (count > max)
        {
            max = count;
        }
    }
    return max;
}*/
int main()
{
    int n = 5;
    int numOfCase;
    const char *file = "bai3_inp.txt";
    int **arr = readData(file, n, &numOfCase);
    writeData("bai3_out.txt", arr, numOfCase, n);
    printf("Msg: read and write successfully\n");
    system("pause");
    return 0;
}