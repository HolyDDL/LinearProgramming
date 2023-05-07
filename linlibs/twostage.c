#include<stdio.h>
#include<stdlib.h>
#include"simplex.h"


double** StageONE(double** Matrix, double* obj, int m, int n, Unit* unit, int supportnum){
    Unit* head = unit->next;
    while(head){
        if(head->isZzero == 0){
            double scale = obj[head->col];
            for(int i = 0; i<n; i++){
                double temprow = -scale * Matrix[head->one_row][i];
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
        if(allnegative){
           if(!((obj[n-1]-0.0)<1e-7)){
                printf("NO SULOTION!\n");
                return NULL;
           }
           else{
                double** AfterMatrix = (double**)malloc(m*sizeof(double*));
                for(int i =0; i<m; i++){
                    double* line = (double*)malloc((n - supportnum)*sizeof(double));
                    for(int j = 0; j<n-supportnum-1; j++){
                        line[j] = Matrix[i][j];
                    }
                    line[n-supportnum-1] = Matrix[i][n-1];
                    AfterMatrix[i] = line;
                }
                return AfterMatrix;
           }
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
    return NULL;
}

int TwoStageMethod(double** Matrix, int m, int n, double* obj){
    Unit* head = (Unit*)malloc(sizeof(Unit));
    head->next = NULL;
    FindUnitVector(Matrix, head, obj, m, n);
    int* UnitROW = (int*)calloc(m, sizeof(int));
    int unitrow_num = 0;
    Unit* p = head->next;
    while(p){
        UnitROW[p->one_row] = 1;
        p = p->next;
        unitrow_num++;
    }
    // int* UnitMASK = (int*)malloc(m*sizeof(int));
    // for(int i = 0; i<m; i++)
    //     UnitMASK[i] = 1 - UnitROW[i];
    int needVARSnum = m - unitrow_num;
    double** BuildMatrix = (double**)malloc(m*sizeof(double*));
    for(int i = 0; i<m; i++){
        double* line = (double*)calloc(needVARSnum, sizeof(double));
        BuildMatrix[i] = line;
    }
    for(int j = 0; j<needVARSnum; j++){
        for(int i = 0; i<m; i++){
            if(UnitROW[i] == 0){
                UnitROW[i] = 1;
                BuildMatrix[i][j] = 1.0;
                break;
            }
        }
    }
    double** LPMatrix = (double**)malloc(m*sizeof(double*));
    for(int i = 0; i<m; i++){
        double* line = (double*)malloc((n+needVARSnum)*sizeof(double));
        for(int j = 0; j<n-1; j++){
            line[j] = Matrix[i][j];
        }
        for(int j = 0; j<needVARSnum; j++){
            line[n+j-1] = BuildMatrix[i][j];
        }
        line[n+needVARSnum-1] = Matrix[i][n-1];
        LPMatrix[i] = line;
    }
    double* supportobj = (double*)calloc((n+needVARSnum), sizeof(double));
    for(int j = 0; j<needVARSnum; j++){
        supportobj[n+j-1] = -1;
    }
    int supportm = m;
    int supportn = n+needVARSnum;
    Unit* supporthead = (Unit*)malloc(sizeof(Unit));
    supporthead->next = NULL;
    FindUnitVector(LPMatrix, supporthead, supportobj, supportm, supportn);
    double** AfterMatrix = StageONE(LPMatrix, supportobj, supportm, supportn, supporthead, needVARSnum);
    if(!AfterMatrix)
        return 1;
    Unit* Afterhead = (Unit*)malloc(sizeof(Unit));
    Afterhead->next = NULL;
    FindUnitVector(AfterMatrix, Afterhead, obj, m ,n);
    Simplex(AfterMatrix, obj, m, n, Afterhead);
    return 0;
}