#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "dist.h"

#define N_SAMPLES 10000
#define HIST_SIZE 50   // adjust depending on expected range

// Normal distribution (Box-Muller transform)
void show_normal_dist(double mean, double std) {
    int hist[HIST_SIZE] = {0};

    for (int i = 0; i < N_SAMPLES; i++) {
        double u1 = (rand() + 1.0) / (RAND_MAX + 1.0);
        double u2 = (rand() + 1.0) / (RAND_MAX + 1.0);
        double z0 = sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);

        int val = (int) lround(mean + std * z0);
        if (val >= 0 && val < HIST_SIZE)
            hist[val]++;
    }

    for (int i = 0; i < HIST_SIZE; i++) {
        if (hist[i] > 0) {
            printf("%2d ", i);
            for (int j = 0; j < hist[i] / 200; j++) printf("*");
            printf("\n");
        }
    }
}

// Poisson distribution (Knuth algorithm)
void show_poisson_dist(int lambda) {
    int hist[HIST_SIZE] = {0};

    for (int i = 0; i < N_SAMPLES; i++) {
        int k = 0;
        double p = 1.0;
        double L = exp(-lambda);

        do {
            k++;
            double u = (rand() + 1.0) / (RAND_MAX + 1.0);
            p *= u;
        } while (p > L);

        int val = k - 1;
        if (val >= 0 && val < HIST_SIZE)
            hist[val]++;
    }

    for (int i = 0; i < HIST_SIZE; i++) {
        if (hist[i] > 0) {
            printf("%2d ", i);
            for (int j = 0; j < hist[i] / 100; j++) printf("*");
            printf("\n");
        }
    }
}

// Uniform distribution
void show_uniform_dist(float min, float max) {
    int hist[HIST_SIZE] = {0};

    for (int i = 0; i < N_SAMPLES; i++) {
        double u = (rand() / (double) RAND_MAX);
        int val = (int) lround(min + u * (max - min));

        if (val >= 0 && val < HIST_SIZE)
            hist[val]++;
    }

    for (int i = 0; i < HIST_SIZE; i++) {
        if (hist[i] > 0) {
            printf("%2d ", i);
            for (int j = 0; j < hist[i] / 200; j++) printf("*");
            printf("\n");
        }
    }
}

static struct CDistLib plot_dist = {
    .normal_dist = show_normal_dist,
    .uniform_dist = show_uniform_dist,
    .poisson_dist = show_poisson_dist
};

static CPPDistLib def_plot_dist = {
    .normal_dist = show_normal_dist,
    .uniform_dist = show_uniform_dist,
    .poisson_dist = show_poisson_dist
};

int main() {
    srand(time(NULL));  // seed RNG

    printf("Normal distribution (mean=25, std=5):\n");
    plot_dist.normal_dist(25, 5);

    printf("\nPoisson distribution (lambda=4):\n");
    def_plot_dist.poisson_dist(4);

    printf("\nUniform distribution (0..20):\n");
    plot_dist.uniform_dist(0, 20);

    return 0;
}
