#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern double multiplier(int n, double vA[], double vB[]);

double testProgram(int exp);

int main() {

    // Runtime Test
    int exponents=3;
    int* exponentArray;
    exponentArray = (int*)malloc(exponents* sizeof(*exponentArray));
    exponentArray[0] = 20;
    exponentArray[1] = 24;
    exponentArray[2] = 28;

    int iterations = 20;
    double* runtimeArray = NULL;
    double avg = 0.0;
    for (int i = 0; i < exponents; i++)
    {
        runtimeArray = (double*)malloc(iterations * sizeof(*runtimeArray));
        printf("\n\nTesting exponent 2^%d\n", exponentArray[i]);
        for (int j = 0; j < iterations; j++)
        {
            printf("ITERATION %d:\n", j + 1);
            runtimeArray[j] = testProgram(exponentArray[i]);
            printf("RUNTIME: %fms\n\n", runtimeArray[j] * 1000);
        }

        printf("\n\nALL TESTING FINISHED. PRINTING RUNTIMES...\n\n");

        for (int j = 0; j < iterations; j++)
        {
            printf("Test %d: %fms\n", j, runtimeArray[j] * 1000);
            avg += runtimeArray[j];
        }
        avg /= iterations;
        printf("\nAVERAGE RUNTIME: %fms", avg * 1000);
        free(runtimeArray);
    }

    // Actual Program

    int x = 0, n = 0, count = 0;
    char ch = '\0', input[257];
    char* token;
    double* vectorA = NULL;
    double* vectorB = NULL;
    double answer = 0.0;

    do {
        if (scanf_s("%c", &ch, (unsigned int)sizeof(ch)) != 1) {
            break;
        }
        if (ch != '\n' && x < 256) {
            input[x] = ch;
            x++;
        }
    } while (ch != '\n');
    input[x] = '\0';

    token = strtok(input, " ");
    if (token != NULL) {
        n = atoi(token);
    }

    if (n <= 0) {
        printf("Invalid vector size.\n");
        return 1;
    }

    vectorA = (double*)malloc(n * sizeof(*vectorA));
    vectorB = (double*)malloc(n * sizeof(*vectorB));

    if (vectorA == NULL || vectorB == NULL) {
        printf("Memory allocation failed.\n");
        free(vectorA);
        free(vectorB);
        return 1;
    }

    while ((token = strtok(NULL, " ")) != NULL) {
        double value = strtod(token, NULL);
        if (count < n) {
            vectorA[count] = value;
        }
        else if ((count - n) < n) {
            vectorB[count - n] = value;
        }
        count++;
    }

    answer = multiplier(n, vectorA, vectorB);

    printf("Dot Product: %f\n", answer);

    free(vectorA);
    free(vectorB);

    return 0;
}

double testProgram(int exp) {
    int n = 1;

    for (int i = 0; i < exp;i++)
    {
        n *= 2;
    }
    printf("SIZE=2^%d (%d). ", exp, n);

    double* vectorA = NULL;
    double* vectorB = NULL;
    double answer;
    vectorA = (double*)malloc(n * sizeof(*vectorA));
    vectorB = (double*)malloc(n * sizeof(*vectorB));

    printf("GENERATE. ");
    for (int i = 0; i < n; i++)
    {
        vectorA[i] = 1.0;
        vectorB[i] = 2.0;
    }
    printf("DONE. CALCULATE. ");

    clock_t begin = clock();
    answer = multiplier(n, vectorA, vectorB);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("DOT PRODUCT: %.2f\n", answer);

    free(vectorA);
    free(vectorB);

    return time_spent;
}