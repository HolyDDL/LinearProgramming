#include<stdio.h>
#include"ioctrl.h"
#include"twostage.h"

int main(){
    printf("Before input, you should transform the linear programing question to a normalized matrix, which has constraint equations' numbers rows and variables' number rows\n");
    printf("And the object function must be optimized to its minimum value.\n");
    printf("input rows number(m): ");
    int m;
    scanf("%d", &m);
    printf("input cols number(n): ");
    int n;
    scanf("%d", &n);
    double** Matrix = Get_Matrix(m, n);
    double* obj = Get_objfunc(n);
    TwoStageMethod(Matrix, m, n, obj);
    return 0;
}