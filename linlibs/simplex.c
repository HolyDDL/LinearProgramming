#include<stdio.h>
#include<stdlib.h>
#include"simplex.h"


int FindUnitVector(double** Matrix, Unit* unit, double* obj, int m, int n){
    Unit* head = unit;
    int* onerows = (int*)calloc(m, sizeof(int));
    for(int col = 0; col<n-1; col++){
        int isUnit = 1;
        int unitROW = 0;
        int OneNum = 0;
        for(int row = 0; row<m; row++){

            if(!(Matrix[row][col]>1.0||Matrix[row][col]<1.0)){
                unitROW = row;
                OneNum++;
            }
            if(((Matrix[row][col]>0.0 || Matrix[row][col]<0.0) && (Matrix[row][col]>1.0 || Matrix[row][col]<1.0) )|| OneNum > 1){
                isUnit = 0;
                unitROW = 0;
                break;
            }
        }
        if(isUnit){
            if(onerows[unitROW] == 0){
                onerows[unitROW]++;
                Unit* p = (Unit*)malloc(sizeof(Unit));
                p->col = col;
                p->one_row = unitROW;
                p->next = head->next;
                head->next = p;
                head = p;
                if((obj[col]>0.0)||(obj[col]<0.0))
                    p->isZzero = 0;
                else
                    p->isZzero = 1;
            }
        }
    }
    free(onerows);
    return 0;
}


int Simplex(double** Matrix, double* obj, int m, int n, Unit* unit){
    Unit* head = unit->next;
    while(head){
        if(head->isZzero == 0){
            double sc = obj[head->col];
            for(int i = 0; i<n; i++){
                double temprow = -sc * Matrix[head->one_row][i];
                obj[i] += temprow;
            }
        }
        head = head->next;
    }
    for(int times = 0; times < m*n+1; times++){
        int allnegative = 1;
        double max_z = 0.0;
        int max_z_col = -1;
        for(int col = 0; col<n-1; col++){
            if(obj[col] > max_z ){
                allnegative = 0;
                int negative = 1;
                for(int row=0; row<m; row++){
                    if(Matrix[row][col] > 0.0){
                        negative = 0;
                        break;
                    }
                }
                if(!negative){
                    max_z = obj[col];
                    max_z_col = col;
                }
            }
        }
        if(max_z_col == -1 && !allnegative){
            printf("NO SULOTION!\n");
            return 0;
        }
        if(allnegative){
            printf("****** SOLUTION ******\n");
            printf("The min z is %.2f.\n", obj[n-1]);
            Unit* lasthead = (Unit*)malloc(sizeof(Unit));
            lasthead->next = NULL;
            FindUnitVector(Matrix, lasthead, obj, m, n);
            Unit* p = lasthead->next;
            printf("the solution vector is: \n");
            double* vector = (double*)calloc(n, sizeof(double));
            while(p){
                vector[p->col] = Matrix[p->one_row][n-1];
                p = p->next;
            }
            for(int i = 0; i<n; i++){
                if(i == 0)
                    printf("[%.2f",vector[i]);
                else if(i == n-1)
                    printf(", %.2f]\n", vector[i]);
                else
                    printf(", %.2f", vector[i]);
            }
            return 0;
        }

        double min_ba;
        int firsttimein = 1;
        int min_row = -1;
        for(int row = 0; row<m; row++){
            if(Matrix[row][max_z_col]>0.0){
                if(firsttimein || (Matrix[row][n-1]/Matrix[row][max_z_col]<min_ba)){
                    firsttimein = 0;
                    min_ba = Matrix[row][n-1]/Matrix[row][max_z_col];
                    min_row = row;
                }
            }
        }
        double factor = Matrix[min_row][max_z_col];
        for(int i = 0; i<n; i++){
            Matrix[min_row][i] /= factor;  
        }
        double scale = obj[max_z_col];
        for(int i = 0; i<n; i++){
            double temp = -scale*Matrix[min_row][i];
            obj[i] += temp;
        }
        for(int i = 0; i<m; i++){
            if(i != min_row){
                double _scale = Matrix[i][max_z_col];
                for(int j = 0; j<n; j++){
                    double temp = -_scale * Matrix[min_row][j];
                    Matrix[i][j] += temp;
                }
            }
        }
    }
    return 0;
}