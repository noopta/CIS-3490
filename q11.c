#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long insertionSort(int arr[], int n)
{
    unsigned long numInversions = 0;
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            numInversions++;
        }
        arr[j + 1] = key;
    }

    return numInversions;
}

long countInversions(int arr[], int arr_count)
{
    int i, j, k;
    long count = 0;

    for (j = 0; j < arr_count; j++)
    {
        for (k = j + 1; k < arr_count; k++)
        {
            if (arr[j] > arr[k])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                count++;
            }
        }
    }

    return count;
}

int main()
{
    char *fileName = "./data_A2_Q1.txt";
    FILE *filePointer = fopen(fileName, "r");
    char *splitStrings;
    char currentLine[1000];
    unsigned long numInversions = 0;
    int numDigits = 0;
    int i = 0;
    int testArray[4];
    int *scratchArray;
    clock_t t;
    double timeTaken = 0.0;

    while (fgets(currentLine, sizeof(currentLine), filePointer))
    {
        splitStrings = strtok(currentLine, " ");

        while (splitStrings)
        {

            if (strcmp(splitStrings, "\n") != 0)
            {
                numDigits++;
            }

            splitStrings = strtok(NULL, " ");
        }
    }

    fclose(filePointer);

    int digitArray[numDigits];

    filePointer = fopen(fileName, "r");

    while (fgets(currentLine, sizeof(currentLine), filePointer))
    {
        splitStrings = strtok(currentLine, " ");
        while (splitStrings)
        {

            if (strcmp(splitStrings, "\n") != 0)
            {
                digitArray[i] = atoi(splitStrings);
                i++;
            }

            splitStrings = strtok(NULL, " ");
        }
    }

    fclose(filePointer);

    t = clock();
    numInversions = insertionSort(digitArray, numDigits);
    t = clock() - t;
    timeTaken = ((double)t) / CLOCKS_PER_SEC;

    printf("The number of inversions calculated was %lu.\n", numInversions);
    printf("Insertion sort took %f seconds to calculate the number of inversions", timeTaken);

    return 0;
}