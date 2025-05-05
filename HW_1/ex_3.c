#include <stdio.h>
#include <stdlib.h>


int** allocate_matrix(int rows, int cols) {
    int **matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) return NULL;
    }

    return matrix;
}


void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);

    
    int **matrix = allocate_matrix(N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    
    int **transposed = allocate_matrix(M, N);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    
    free_matrix(matrix, N);
    free_matrix(transposed, M);

    return 0;
}
