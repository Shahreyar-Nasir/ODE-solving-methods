#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1000
#define TOL 1e-8

// Global function choice variable
int function_choice = 1;

// f(x, y): define based on selected problem (the right-hand side of the ODE)
double f(double x, double y) {
    switch (function_choice) {
        case 1: return x + y;           // Problem 1: dy/dx = x + y
        case 2: return x * x + y * y;   // Problem 2: dy/dx = x^2 + y^2
        case 3: return sin(x) + y;      // Problem 3: dy/dx = sin(x) + y
        default: return 0.0;
    }
}

// First derivative of f(x, y) with respect to y (df/dy)
double df(double x, double y) {
    switch (function_choice) {
        case 1: return 1.0;            // Problem 1: df/dy = 1
        case 2: return 2 * y;          // Problem 2: df/dy = 2y
        case 3: return 1.0;            // Problem 3: df/dy = 1
        default: return 0.0;
    }
}

// Second derivative of f(x, y) with respect to y (d^2f/dy^2)
double d2f(double x, double y) {
    switch (function_choice) {
        case 1: return 0.0;            // Problem 1: d^2f/dy^2 = 0
        case 2: return 2.0;            // Problem 2: d^2f/dy^2 = 2
        case 3: return 0.0;            // Problem 3: d^2f/dy^2 = 0
        default: return 0.0;
    }
}

// Taylor Series Method (Second-order expansion)
double taylor_series(double x0, double y0, double x_target) {
    double h = (x_target - x0) / N;    // Step size
    double x = x0, y =y0;

        for (int i = 0; i < N; i++) {
            double f_val = f(x, y);          // f(x, y)
            double df_val = df(x, y);        // df/dy
            double d2f_val = d2f(x, y);      // d^2f/dy^2

            y += h * f_val + (h*h/2.0) * df_val + (h*h*h/ 6.0) * d2f_val;
            x += h;

        }

    return y;
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

    double result = taylor_series(x0, y0, x_target);
    printf("\nFinal approximation: y(%.3f) = %.10lf\n", x_target, result);

    return 0;
}
