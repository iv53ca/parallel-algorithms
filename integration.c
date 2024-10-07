#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x) {
    return sqrt(4 - x * x);
}

double integrate(double a, double b, int N) {
    double h = (b - a) / N;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < N; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    double a = 0.0;
    double b = 2.0;
    double result = integrate(a, b, N);
    printf("%.6f\n", result);
    return 0;
}