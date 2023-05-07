
typedef struct un{
    int col;
    int one_row;
    int isZzero;
    struct un* next;
}Unit;

// 用于找到单位向量
int FindUnitVector(double** Matrix, Unit* unit, double* obj, int m, int n);

// 单纯形方法
int Simplex(double** Matrix, double* obj, int m, int n, Unit* unit);