#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 500
#define MAX_ITER 100
#define TOL 1e-8

// Global function choice variable
int function_choice = 1;

// f(x, y): define based on selected problem
double f(double x, double y) {
    switch (function_choice) {
        case 1: return x + y;           // Problem 1
        case 2: return x * x + y * y;   // Problem 2
        case 3: return sin(x) + y;      // Problem 3
        default: return 0.0;
    }
}

// Picard Iteration Method
double picard(double x0, double y0, double x_target) {
    double h = (x_target - x0) / N;
    double x[N + 1], y_prev[N + 1], y_curr[N + 1];

    // Initialize x and y_prev (initial guess)
    for (int i = 0; i <= N; i++) {
        x[i] = x0 + i * h;
        y_prev[i] = y0;
    }

    for (int iter = 1; iter <= MAX_ITER; iter++) {
        for (int i = 0; i <= N; i++) { 
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                double xj = x[j];
                double xj1 = x[j + 1];

                double yj = y_prev[j];
                double yj1 = y_prev[j + 1];

                double fj = f(xj, yj);
                double fj1 = f(xj1, yj1);
                
                sum += (fj + fj1) * (h / 2.0);
            }
            y_curr[i] = y0 + sum;
        }

        double error = fabs(y_curr[N] - y_prev[N]);
        printf("Iteration %d: y(%.3f) = %.10lf, Error = %.2e\n", iter, x_target, y_curr[N], error);

        if (error < TOL) {
            break;
        }

        for (int i = 0; i <= N; i++) {
            y_prev[i] = y_curr[i];
        }
    }

    return y_curr[N];
}

int main() {
    int choice;
    double x0, y0, x_target;

    printf("Select the differential equation:\n");
    printf("1. dy/dx = x + y,        y(0) = 1, find y(0.1)\n");
    printf("2. dy/dx = x^2 + y^2,    y(0) = 0, find y(0.1)\n");
    printf("3. dy/dx = sin(x) + y,   y(0) = 1, find y(0.2)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    function_choice = choice;

    switch (choice) {
        case 1:
            x0 = 0.0;
            y0 = 1.0;
            x_target = 0.1;
            break;
        case 2:
            x0 = 0.0;
            y0 = 0.0;
            x_target = 0.1;
            break;
        case 3:
            x0 = 0.0;
            y0 = 1.0;
            x_target = 0.2;
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    double result = picard(x0, y0, x_target);
    printf("\nFinal approximation: y(%.3f) = %.10lf\n", x_target, result);

    return 0;
}
