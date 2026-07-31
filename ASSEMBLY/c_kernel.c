void c_kernel(int n, double vA[], double vB[], double *sdot) {
    *sdot = 0.0;
    for (int i = 0; i < n; i++) {
        *sdot += vA[i] * vB[i];
    }
}