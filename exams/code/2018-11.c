typedef struct {
    int* matrixRow;
    int numCols;
} ThreadArgs;

void* rowsum(void* v) {
    ThreadArgs* threadArgs = (ThreadArgs*)v;
    int rowSum = 0;
    for (int i = 0; i < threadArgs->numCols; i++) {
        rowSum += threadArgs->matrixRow[i];
    }
    return (void*)rowSum;
}

int matrixsum(int** matrix, int rows, int cols) {
    int sum = 0;
    pthread_t ids[cols];
    for (int i = 0; i < rows; i++) {
        int* matrixRow = matrix[i];
        ThreadArgs threadArgs;
        threadArgs.matrixRow = matrixRow;
        threadArgs.numCols = cols;
        pthread_create(&ids[i], rowsum, &threadArgs);
    }
    for (int i = 0; i < rows; i++) {
        void* val;
        pthread_join(ids[i], &val);
        sum += (int)val;
    }
    return sum;
}
