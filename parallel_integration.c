#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

double f(double x) {
    return sqrt(4 - x * x);
}

double trapezoidal_integral(int N, int rank, int size) {
    double a = 0.0, b = 2.0;
    double h = (b - a) / N;
    double local_integral = 0.0;

    // Определяем границы для каждого процесса
    int local_N = N / size;
    double local_a = a + rank * local_N * h;
    double local_b = local_a + local_N * h;

    // Считаем интеграл на локальном отрезке
    local_integral += (f(local_a) + f(local_b)) / 2.0;
    for (int i = 1; i < local_N; i++) {
        double x_i = local_a + i * h;
        local_integral += f(x_i);
    }
    local_integral *= h;

    // Сбор всех локальных интегралов
    double global_integral = 0.0;
    MPI_Reduce(&local_integral, &global_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return global_integral;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: %s <number of intervals>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int N = atoi(argv[1]);
    double result = trapezoidal_integral(N, rank, size);

    if (rank == 0) {
        printf("Integral: %.6f\n", result);
    }

    MPI_Finalize();
    return 0;
}
