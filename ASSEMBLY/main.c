#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// function declarations
extern void asm_kernel(int n, double vA[], double vB[], double* sdot);
extern void c_kernel(int n, double vA[], double vB[], double* sdot);

double getAsmRuntime(int n, double* vectorA, double* vectorB, double* sdot);
double getCRuntime(int n, double* vectorA, double* vectorB, double* sdot);

const MAX_VALUE = 100.0;
const MIN_VALUE = -100.0;

// since C's "release" is extremely optimized, we need to use a buffer variable like this to keep the result,
// and keep the timer counting in "release" mode.
volatile double prevent_optimization;

// Hello sir! Please call the function testProgram() in main if you want to test the program's runtime
void testProgram();


int main() {
    testProgram();

    // Actual Program

    int x = 0, n = 0, count = 0;
    char ch = '\0', input[257];
    char* token;
    double* vectorA = NULL;
    double* vectorB = NULL;
    double* sdot = NULL;

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
    sdot = (double*)malloc(sizeof(sdot));

    if (vectorA == NULL || vectorB == NULL) {
        printf("Memory allocation failed.\n");
        free(vectorA);
        free(vectorB);
        free(sdot);
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

    asm_kernel(n, vectorA, vectorB, &sdot);

    printf("Dot Product: %f\n", sdot);

    free(vectorA);
    free(vectorB);
    free(sdot);

    return 0;
}

void testProgram() {
    // Runtime Test
    int iterations = 20;

    int exponentArray[] = { 20, 24, 28 };
    int exponents = sizeof(exponentArray)/sizeof(exponentArray[0]);

    double* asmRuntimes = NULL;
    double asmAvg = 0.0;

    double* cRuntimes = NULL;
    double cAvg = 0.0;

    for (int i = 0; i < exponents; i++)
    {
        printf("\n\nTesting exponent 2^%d\n", exponentArray[i]);

        int n = 1;
        double* vectorA = NULL;
        double* vectorB = NULL;
        double sdot = 0.0;

        asmRuntimes = (double*)malloc(iterations * sizeof(*asmRuntimes));
        cRuntimes = (double*)malloc(iterations * sizeof(*cRuntimes));

        for (int j = 0; j < exponentArray[i];j++)
        {
            n *= 2;
        }

        vectorA = (double*)malloc(n * sizeof(*vectorA));
        vectorB = (double*)malloc(n * sizeof(*vectorB));

        srand(time(NULL));

        for (int j = 0; j < n; j++)
        {
            vectorA[j] = MIN_VALUE + ((double)rand() / RAND_MAX) * (MAX_VALUE - MIN_VALUE);
            vectorB[j] = MIN_VALUE + ((double)rand() / RAND_MAX) * (MAX_VALUE - MIN_VALUE);
        }


        for (int j = 0; j < iterations; j++)
        {
            //printf("ITERATION %d:\n", j + 1);
            asmRuntimes[j] = getAsmRuntime(n,vectorA,vectorB, &sdot) * 1000;
            cRuntimes[j] = getCRuntime(n, vectorA, vectorB, &sdot) * 1000;
            //printf("RUNTIME: %7fms %7fms\n\n", asmRuntimes[j], cRuntimes[j]);
        }


        printf("\n\RUNTIME for 2^%d...\n\n",exponentArray[i]);
        printf("\t\tASSEMBLY\tC\n");
        for (int j = 0; j < iterations; j++)
        {
            printf("Test %d: \t%7fms\t%7fms\n", j, asmRuntimes[j], cRuntimes[j]);
            asmAvg += asmRuntimes[j];
            cAvg += cRuntimes[j];
        }
        asmAvg /= iterations;
        cAvg /= iterations;

        printf("\nAVERAGE RUNTIME: %7fms %7fms", asmAvg,cAvg);

        free(vectorA);
        free(vectorB);

        free(asmRuntimes);
        free(cRuntimes);
    }
}

double getAsmRuntime(int n, double* vectorA, double* vectorB, double* sdot) {

    clock_t begin = clock();
    asm_kernel(n, vectorA, vectorB, sdot);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    //printf("DOT PRODUCT: %.2f\n", answer);
    return time_spent;
}

double getCRuntime(int n, double* vectorA, double* vectorB, double* sdot) {
    clock_t begin = clock();
    c_kernel(n, vectorA, vectorB, sdot);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    //printf("DOT PRODUCT: %.2f\n", answer);
    return time_spent;
}
