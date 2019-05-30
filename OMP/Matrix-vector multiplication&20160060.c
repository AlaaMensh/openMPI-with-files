#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
    int matrixsize;int vectorsize;
    int row;
    int col;
    printf("please enter the row size");
    scanf("%d",&row);
    printf("please enter the col size");
    scanf("%d",&col);
    printf("please enter the vector size");
    scanf("%d",&vectorsize);
    int i, j, n, matrix[row][col], vector[vectorsize], res[row];
    if(vectorsize!=col){printf("invalid multiplication\n ");return;}

    n= matrixsize;
    //bool falg=false;
int l=0;

    printf("Matrix A\n");
int counter=1;

    #pragma omp parallel private(i,j) shared(matrix)
    {
        #pragma omp for
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            //scanf("%d",&a[i][j]);
            matrix[i][j]=counter;
            printf("%d ", matrix[i][j]);
            counter++;
        }
        printf("\n");
    }
    }
    printf("\nMatrix B\n");

    #pragma omp parallel private(i) shared(vector)
    {
        #pragma omp for
        for (i = 0; i < col; ++i) {
            vector[i] = 1;
            printf("%d\n", vector[i]);
        }
    }
   // printf("////////////////////////////////////\n");

    printf("\nA * B\n");

    #pragma omp parallel private(i) shared(res)
    {
        #pragma omp for
        for (i = 0; i < vectorsize; ++i) {
            res[i] = 0;
        }
    }


    #pragma omp parallel private(i,j) shared(matrix,vector,res)
    {
        #pragma omp for schedule(dynamic)
        for (i = 0; i < row; ++i) {


            for (j = 0; j < col; ++j) {

                res[i] += vector[j] * matrix[i][j];
               // printf("%d\n", c[i]);
            }
        }

    }



    #pragma omp parallel private(i) shared(res)
    {
        #pragma omp for
       for (i = 0; i < row; ++i) {

            printf ("IN thread %d SUM = %d\n" , omp_get_thread_num() , res[i] );
        }
    }



    return 0;
}
