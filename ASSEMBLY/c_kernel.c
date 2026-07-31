double c_kernel(int n, double vA[], double vB[]) {
    double sum = 0, prod = 0;
    int i;
    for (i = 0; i < n; i++) {
        prod = vA[i] * vB[i];
        sum += prod;
    }

    return sum;
}