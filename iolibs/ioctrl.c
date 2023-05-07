#include<stdio.h>
#include<stdlib.h>

double* Get_objfunc(int n){
    printf("input object func: \n");
    double* obj = (double*)malloc(n*sizeof(double));
    for(int i =0; i<n ;i++){
        double temp;
        scanf("%lf", &temp);
        obj[i] = temp;
    }
    printf("end input of obj func. \n");
    return obj;
}

double** Get_Matrix(int m, int n){
    printf("------ INPUT MATRIX -----\n");
    
    double** rowhead = (double**)malloc(m*sizeof(double*));
    for(int i = 0; i<m; i++){
        printf("input the %d row of matrix(include RHS col): \n", i+1);
        rowhead[i] = (double*)malloc(n*sizeof(double));
        for(int j = 0; j<n; j++){
            double temp;
            scanf("%lf", &temp);
            rowhead[i][j] = temp;
        }
        printf("finish the input of the %d row.\n", i+1);
    }
    printf("------ END INPUT MATRIX ------\n");
    return rowhead;
}