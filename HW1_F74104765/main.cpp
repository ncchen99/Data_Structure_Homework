#include <bits/stdc++.h>
using namespace std;

class MatrixTerm {
private:
    int row, col, value;
    friend class SparseMatrix;

public:
    void Set(int r, int c, int v) {
        row = r;
        col = c;
        value = v;
    }
};

class SparseMatrix {
private:
    int rows, cols, terms, capacity;
    MatrixTerm* smArray;

public:
    SparseMatrix(int r, int c, int t) {
        rows = r;
        cols = c;
        terms = t;
        smArray = new MatrixTerm[terms];
    };
    void LoadFrom2dArray(int rows, int cols, int** mat) {
        int termsIndex = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (mat[i][j] != 0)
                    smArray[termsIndex++].Set(i, j, mat[i][j]);
    }
    void AssignMatrixTerm(MatrixTerm* terms) {
        memcpy(smArray, terms, sizeof(terms));
    }
    void PrintTerm(int termsIndex) {
        printf("(%d, %d, %d)", smArray[termsIndex].row, smArray[termsIndex].col, smArray[termsIndex].value);
    }
    void PrintTransposeTerm(int termsIndex) {
        printf("(%d, %d, %d)", smArray[termsIndex].col, smArray[termsIndex].row, smArray[termsIndex].value);
    }
    SparseMatrix Transpose() {
        SparseMatrix tmp(rows, cols, terms);
        if (terms > 0) {
            int current = 0;
            for (int c = 0; c < cols; c++) {
                for (int i = 0; i < terms; i++) {
                    if (smArray[i].col == c) {
                        tmp.smArray[current].row = c;
                        tmp.smArray[current].col = smArray[i].row;
                        tmp.smArray[current++].value = smArray[i].value;
                    }
                }
            }
        }
        return tmp;
    };
};

int main() {
    int n, m, r, c, v;
    int termsCount = 0;

    cin >> n >> m;

    int** traMat = new int*[n];
    for (int i = 0; i < n; i++) {
        traMat[i] = new int[m];
        for (int j = 0; j < m; j++)
            traMat[i][j] = 0;
    }

    while (cin >> r >> c >> v) {
        traMat[r][c] = v;
        termsCount++;
    }

    SparseMatrix mat(n, m, termsCount);
    mat.LoadFrom2dArray(n, m, (int**)traMat);

    int** traMatTmp = new int*[m];
    for (int i = 0; i < m; i++)
        traMatTmp[i] = new int[n];

    ////////////////////////////////////////////////////////////////
    clock_t traT = clock();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            traMatTmp[j][i] = traMat[i][j];

    memcpy(traMat, traMatTmp, sizeof(traMatTmp));
    traT = clock() - traT;
    ////////////////////////////////////////////////////////////////
    clock_t spaT = clock();
    SparseMatrix matTransposed = mat.Transpose();
    spaT = clock() - spaT;
    ////////////////////////////////////////////////////////////////
    for (int i = 0; i < termsCount; i++) {
        mat.PrintTerm(i);
        printf(" becomes ");
        mat.PrintTransposeTerm(i);
        printf(" in the transpose\n");
    }
    printf("%ld ms\n%ld ms\n", traT, spaT);
}
