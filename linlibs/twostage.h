#include"simplex.h"

double** StageONE(double** Matrix, double* obj, int m, int n, Unit* unit, int supportnum);

int TwoStageMethod(double** Matrix, int m, int n, double* obj);