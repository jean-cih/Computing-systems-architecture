#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitCalculate(int N, int M);
void DGEMM_BLAS(double **matrixFirst, double **matrixSecond, double **matrixThird, int N);
void DGEMM_opt_1(double **matrixFirst, double **matrixSecond, double **matrixThird, int N);
void DrawingMatrix(double **matrixFirst, double **matrixSecond, double **matrixThird, int N);
void PrintMatrix(double ** matrix, int N);
void FreeMatrix(double **matrixFirst, double **matrixSecond, double **matrixThird, int N);
void FillMatrix(double **matrix, int N);

int main(int argc, char **argv)
{   
    int M;
    printf("\nDo You need to show matrices?\n");
    printf("\nClick on the button\n Yes - 1\n No - 0\n");
    scanf("%d", &M);

    char *item;
    int rang;
    
    if(argc > 1 && argc < 3)
    {
        rang = strtol(argv[1], &item, 10);
        if(rang <= 0) 
        {
            printf("Negative size of matrix\n");
            return 0;
        }
    }
    else
    {
        printf("Enter the size of matrixs\n");
        scanf("%d", &rang);
    }

    InitCalculate(rang, M);
    
    return 0;
}

void InitCalculate(int N, int M)
{
    double **matrixFirst = (double**)malloc(N * sizeof(double*));
    double **matrixSecond = (double**)malloc(N * sizeof(double*));
    double **matrixThird = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++)
    {
        matrixFirst[i] = (double*)malloc(N * sizeof(double));
        matrixSecond[i] = (double*)malloc(N * sizeof(double));
        matrixThird[i] = (double*)malloc(N * sizeof(double));
    }

    FillMatrix(matrixFirst, N);
    FillMatrix(matrixSecond, N);
    
    clock_t beginOne = clock();
    srand(time(NULL));
    DGEMM_BLAS(matrixFirst, matrixSecond, matrixThird, N);
    clock_t endOne = clock();
    double timeSpentOne = 0.0;
    timeSpentOne += (double)(endOne - beginOne) / CLOCKS_PER_SEC;

    clock_t beginTwo = clock();
    srand(time(NULL));
    DGEMM_opt_1(matrixFirst, matrixSecond, matrixThird, N);
    clock_t endTwo = clock();
    double timeSpentTwo = 0.0;
    timeSpentTwo += (double)(endTwo - beginTwo) / CLOCKS_PER_SEC;

    printf("_______________________________________________\n");
    printf("|   Size   |   DGEMM_BLAS   |   DGEMM_opt_1   |\n");
    printf("|__________|________________|_________________|\n");
    printf("|%7d   |%13f   |%14f   |\n", N, timeSpentOne, timeSpentTwo);
    printf("|__________|________________|_________________|\n");

    if(M == 1){
        DrawingMatrix(matrixFirst, matrixSecond, matrixThird, N);
    }

    FreeMatrix(matrixFirst, matrixSecond, matrixThird, N);

}


void DGEMM_BLAS(double **matrixFirst, double **matrixSecond, double **matrixThird, int N)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            matrixThird[i][j] = 0;
            for(int k = 0; k < N; k++)
                matrixThird[i][j] += matrixFirst[i][k] * matrixSecond[k][j];
        }
}

void DGEMM_opt_1(double **matrixFirst, double **matrixSecond, double **matrixThird, int N)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            matrixThird[i][j] = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            for(int k = 0; k < N; k++)
                matrixThird[i][k] += matrixFirst[i][j] * matrixSecond[j][k];
}

void DrawingMatrix(double **matrixFirst, double **matrixSecond, double **matrixThird, int N)
{
    printf("\nmatrix A\n");
    PrintMatrix(matrixFirst, N);

    printf("\nmatrix B\n");
    PrintMatrix(matrixSecond, N);

    printf("\nthe result of multiplying\n");
    PrintMatrix(matrixThird, N);
}

void PrintMatrix(double ** matrix, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%3f ", matrix[i][j]);
        printf("\n");
    }
}

void FreeMatrix(double **matrixFirst, double **matrixSecond, double **matrixThird, int N)
{
    for (int i = 0; i < N; i++)
    {
        free(matrixFirst[i]);
        free(matrixSecond[i]);
        free(matrixThird[i]);
    }
    free(matrixFirst);
    free(matrixSecond);
    free(matrixThird);
}

void FillMatrix(double **matrix, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = (double)(rand() % 10) / 1.1;
        }
    }
}
