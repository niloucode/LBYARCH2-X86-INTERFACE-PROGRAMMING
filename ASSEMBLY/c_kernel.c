void c_kernel(int n, double vA[], double vB[], double *sdot) {
    int i;
    for (i = 0; i < n; i++) {
        *sdot += vA[i] * vB[i];
    }
}