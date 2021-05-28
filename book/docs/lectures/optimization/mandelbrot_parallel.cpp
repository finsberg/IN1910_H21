#include <iostream>

using namespace std;

int mandelbrot_pixel(double cx, double cy, int maxiter) {
    double x = cx;
    double y = cy;

    for (int n=0; n<maxiter; n++) {
        double x2 = x*x;
        double y2 = y*y;

        if (x2 + y2 > 4.0) {
            return n;
        }

        y = 2*x*y + cy;
        x = x2 - y2 + cx;

    }
    return 0;
}

void mandelbrot_image(double xmin, double xmax,
                      double ymin, double ymax, 
                      int width, int height,
                      int maxiter, int *output) {
    int i, j;

    double* xlin = new double[width];
    double* ylin = new double[height];
    double dx = (xmax - xmin)/(width-1);
    double dy = (ymax - ymin)/(height-1);

    for (i=0; i<width; i++) {
        xlin[i] = xmin + i*dx;
    }

    for (j=0; j<height; j++) {
        ylin[j] = ymin + j*dy;
    }

    #pragma omp parallel for
    for (i=0; i<width; i++) {
        for (j=0; j<height; j++) {
            output[i*height + j] = mandelbrot_pixel(xlin[i], ylin[j], maxiter);
        }
    }

    delete[] xlin;
    delete[] ylin;
}

void benchmark() {
    double xmin = -0.74877;
    double xmax = -0.74872;
    double ymin = 0.065053;
    double ymax = 0.065103;
    int width = 1000;
    int height = 1000;
    int maxiter = 2048;

    int* output = new int[width*height];
    mandelbrot_image(xmin, xmax, ymin, ymax,
                     width, height, maxiter, output);
    delete[] output;
}


int main() {
    benchmark();

    return 0;
}