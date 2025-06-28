#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000

double f1(double x, double y) { return x + y; }
double f2(double x, double y) { return x * x + y * y; }
double f3(double x, double y) { return sin(x) + y; }

double rk4(double (*f)(double, double), double x, double y, double h) {
    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 2.0, y + k1 / 2.0);
    double k3 = h * f(x + h / 2.0, y + k2 / 2.0);
    double k4 = h * f(x + h, y + k3);
    return y + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
}

double MilneCorrector(double (*f)(double, double), double a, double b, double y0) {
    double h = (b - a) / N;
    double x[N + 1], y[N + 1], f_val[N + 1];

    // Initial values using RK4
    x[0] = a;
    y[0] = y0;
    for (int i = 1; i <= 3; i++) {
        x[i] = x[i - 1] + h;
        y[i] = rk4(f, x[i - 1], y[i - 1], h);
    }

    // Compute function values
    for (int i = 0; i <= 3; i++) {
        f_val[i] = f(x[i], y[i]);
    }

    // Main loop
    for(int i=3; i < N; i++){
        x[i + 1]=x[i] + h;
        
          // Predictor
          double yP = y[i - 3] + (4*h / 3.0)*(2*f_val[i - 2] - f_val[i - 1] + 2*f_val[i]);

          double fP = f(x[i + 1], yP);
          
          // Corrector
          y[i + 1] = y[i - 1] + (h / 3.0)*( f_val[i-1] + 4*f_val[i] + fP);

          f_val[i + 1] = f(x[i + 1], y[i + 1]);
    }

    return y[N];
}

int main() {
    int choice;
    double (*f[])(double, double) = {f1, f2, f3};
    double x0[] = {0.0, 0.0, 0.0};
    double y0[] = {1.0, 0.0, 1.0};
    double x_target[] = {0.1, 0.1, 0.2};

    printf("Select the differential equation:\n");
    printf("1. dy/dx = x + y,        y(0) = 1, find y(0.1)\n");
    printf("2. dy/dx = x^2 + y^2,    y(0) = 0, find y(0.1)\n");
    printf("3. dy/dx = sin(x) + y,   y(0) = 1, find y(0.2)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice.\n");
        return 1;
    }

    double result = MilneCorrector(f[choice - 1], x0[choice - 1], x_target[choice - 1], y0[choice - 1]);

    printf("\nFinal approximation using Adams-Bashforth Predictor-Corrector:\n");
    printf("y(%.3f) = %.10lf\n", x_target[choice - 1], result);

    return 0;
}
