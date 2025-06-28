#include <stdio.h>
#include <math.h>

// Function pointer type
typedef double (*Func)(double, double);

// Runge-Kutta 4th Order Method
double rk4(Func f, double a, double b, int N, double xi) {
    double h = (b - a) / N;
    double t = a;
    double x = xi;

    for (int i = 0; i < N; ++i) {
        double k1 = h * f(t, x);
        double k2 = h * f(t + h / 2.0, x + k1 / 2.0);
        double k3 = h * f(t + h / 2.0, x + k2 / 2.0);
        double k4 = h * f(t + h, x + k3);
        x += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t += h;
    }

    return x;
}

// Define each f(t, x) function
double f1(double t, double x) {
    return 1.0 + x * x + pow(t, 3);
}

double f2(double t, double x) {
    return 2.0 + pow((x - t - 1.0), 2);
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
    printf("Using Runge-Kutta 4th Order (double precision):\n");

    // Case 1
    printf("f1: x(b) = %lf\n", rk4(f1, 1.0, 2.0, 100, -4.0));

    // Case 2
    printf("f2: x(b) = %lf\n", rk4(f2, 1.0, 1.5625, 72, 2.0));

    // Case 3
    printf("f3: x(b) = %lf\n", rk4(f3, 1.0, 2.0, 72, 1.0));

    // Case 4
    printf("f4: x(b) = %lf\n", rk4(f4, 1.0, 2.0, 72, -1.0));

    // Case 5
    printf("f5: x(b) = %lf\n", rk4(f5, 0.0, 1.0, 512, 1.0));

    return 0;
}
