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

unsigned long merge(int values[], int scratch[], int first_ix, int mid_ix, int last_ix)
{
    int diff = mid_ix - first_ix,
        i, j, k;
    unsigned long inversions = 0L;

    for (i = 0; i <= diff; ++i)
    {
        scratch[i] = values[first_ix + i];
    }
    i = 0;
    j = mid_ix + 1;

    k = first_ix;
    while (i <= diff && j <= last_ix)
    {
        if (values[j] < scratch[i])
        {
            inversions += j - k;
            values[k] = values[j++];
        }
        else
        {
            values[k] = scratch[i++];
        }
        ++k;
    }
    while (i <= diff)
    {
        values[k++] = scratch[i++];
    }
    return inversions;
}

unsigned long merge_sort(int values[], int scratch[], int first_ix, int last_ix)
{
    int diff = last_ix - first_ix;

    if (diff <= 0)
        return 0L;
    int mid_ix = first_ix + diff / 2;

    unsigned long leftInversions;
    unsigned long rightInversions;
    unsigned long mergeInversions;

    leftInversions = merge_sort(values, scratch, first_ix, mid_ix);
    rightInversions = merge_sort(values, scratch, mid_ix + 1, last_ix);
    mergeInversions = merge(values, scratch, first_ix, mid_ix, last_ix);

    return leftInversions + rightInversions + mergeInversions;
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
    scratchArray = (int *)malloc((numDigits / 2 + 1) * sizeof(int));

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
    numInversions = merge_sort(digitArray, scratchArray, 0, numDigits);
    t = clock() - t;
    timeTaken = ((double)t) / CLOCKS_PER_SEC;

    printf("The number of inversions calculated was %lu.\n", numInversions);
    printf("Merge sort took %f seconds to calculate the number of inversions", timeTaken);

    return 0;
}