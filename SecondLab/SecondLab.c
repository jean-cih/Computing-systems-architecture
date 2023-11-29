#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char Pmodel[1000];
char Pmodel_new[1000] = "\0";
int LNum = 1;
bool fcF = true;
double avTimee = 0.0;
double avTimee_o = 0.0;
double absErr = 0.0;
double relErr = 0.0;
double taskPef = 0.0;

void PModel();
void determineMatrix(int test, int rang);
void csvFile(double time_spent);
void outEnd();
void avTime();
void absError(double time_spent);
void RelError(double time_spent);
void TaskPerf();

int main(int argc, char **argv) 
{
  if(argc < 3)
  {
    printf("\nYou need to pass at least three parameters\n\n");
    return 0;
  }
  else if(argc > 3)
  {
    printf("\nIn general You only need three parameters But it will do\n\n");
  }

  PModel();
  csvFile(1);

  char *item;
  int test = strtol(argv[2], &item, 10);
  int rang = strtol(argv[1], &item, 10);

  determineMatrix(test, rang);

  return 0;
}

void determineMatrix(int test, int rang) 
{
  for (int i = 0; i < test; i++) 
  {
    double time_spent = 0.0;
    fcF = 1;
    clock_t begin = clock();
    double  **matrixFirst = (double **)malloc(rang * sizeof(double *));
    double **matrixSecond = (double **)malloc(rang * sizeof(double *));
    double **matrixResult = (double **)malloc(rang * sizeof(double *));

    for (int i = 0; i < rang; i++) 
    {
      matrixFirst[i] = (double *)malloc(rang * sizeof(double));
      matrixSecond[i] = (double *)malloc(rang * sizeof(double));
      matrixResult[i] = (double *)malloc(rang * sizeof(double));
    }

    srand(time(NULL));
    for (int i = 0; i < rang; i++)
      for (int j = 0; j < rang; j++) 
      {
        matrixFirst[i][j] = rand() % 100 / 1.1;
        matrixSecond[i][j] = rand() % 100 / 1.1; 
      }

    for (int i = 0; i < rang; i++)
      for (int j = 0; j < rang; j++) 
      {
        matrixResult[i][j] = 0;
        for (int k = 0; k < rang; k++)
          matrixResult[i][j] += matrixFirst[i][k] * matrixSecond[k][j];
      }

    for (int i = 0; i < rang; i++) 
    {
      free(matrixFirst[i]);
      free(matrixSecond[i]);
      free(matrixResult[i]);
    }

    free(matrixFirst);
    free(matrixSecond);
    free(matrixResult);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    avTimee += time_spent;
  
    csvFile(time_spent);
  }
}

void csvFile(double time_spent) 
{
  FILE *file;
  file = fopen("csvFile.csv", "a");
  if (file == NULL) 
  {
    printf("Error!\n");
    exit(0);
  }
  if (!fcF) 
  {
    fprintf(file,
            "PModel;Task;OpType;Opt;InsCount;Timer;Time;LNum;AvTime;AbsErr;"
            "RelErr;TaskPerf\n");
  }

  if (fcF) 
  {
    outEnd();
    avTime();
    absError(time_spent);
    RelError(time_spent);
    TaskPerf();
    fprintf(file, "%s;matrix;int;None;1;clock;%f;%i;%f;%f;%f;%f\n", Pmodel,
            time_spent, LNum, avTimee_o, absErr, relErr, taskPef);
    LNum++;
  }
  fclose(file);
}

void avTime() {avTimee_o = avTimee / LNum; }

void absError(double time_spent) {absErr = fabs((avTimee / LNum) - time_spent); }

void RelError(double time_spent) {relErr = absErr * 100 / time_spent; }

void TaskPerf() {taskPef = 1 / avTimee_o; }

void outEnd() 
{
  for (long unsigned int i = 0; i < strlen(Pmodel); i++) 
  {
    if (Pmodel[i] == '\n') 
    {
      Pmodel[i] = '\0';
      break;
    }
  }
}

void PModel() 
{
  FILE *uname;
  int lastchar;
  uname = popen(
      "lscpu | grep -E '^Имя модели|^Model name' | sed 's/Имя "
      "модели:*\\s*//;s/Model name:*\\s*//'",
      "r");
  lastchar = fread(Pmodel, 1, 1000, uname);
  Pmodel[lastchar] = '\0';
  printf("%s", Pmodel);
  pclose(uname);
}

