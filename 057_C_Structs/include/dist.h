#ifndef _DIST_H
#define _DIST_H

struct CDistLib {
    void (*normal_dist)(double, double);
    void (*poisson_dist)(int);
    void (*uniform_dist)(float, float);
};

typedef struct {
    void (*normal_dist)(double, double);
    void (*uniform_dist)(float, float);
    void (*poisson_dist)(int);
} CPPDistLib;

#endif