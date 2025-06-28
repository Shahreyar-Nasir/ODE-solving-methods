#include <stdio.h>
#include <math.h>

// Function pointer type
typedef double (*Func)(double, double);

// Euler's method implementation
double euler(Func f, double a, double b, int N, double xi) {
    double h = (b - a) / N;
    double t = a;
    double x = xi;

    for (int i = 0; i < N; ++i) {
        x = x + h * f(t, x);
        t = t + h;
    }

    return x;
}

// Define f(t, x) for each case
double f1(double t, double x) {
    return 1.0 + x * x + t * t * t;
}

double f2(double t, double x) {
    return 2.0 + (x - t - 1.0) * (x - t - 1.0);
}

double f3(double t, double x) {
    return 1.0 + x / t;
}

double f4(double t, double x) {
    return (1.0 / t*t) - (x/t) - (x*x);
}

double f5(double t, double x) {
    return -x;
}

int main() {
    printf("Using Euler's Method :\n");

    // Case 1
    printf("f1: x(b) = %.10lf\n", euler(f1, 1.0, 2.0, 100, -4.0));

    // Case 2
    printf("f2: x(b) = %.10lf\n", euler(f2, 1.0, 1.5625, 72, 2.0));

    // Case 3
    printf("f3: x(b) = %.10lf\n", euler(f3, 1.0, 2.0, 72, 1.0));

    // Case 4
    printf("f4: x(b) = %.10lf\n", euler(f4, 1.0, 2.0, 72, -1.0));

    // Case 5
    printf("f5: x(b) = %.10lf\n", euler(f5, 0.0, 1.0, 512, 1.0));

    return 0;
}
