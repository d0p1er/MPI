//
// Created by d0p1er on 15/05/23.
//
/* Transport Equation
 * du/dt - du/dx = t + x
 * u(0,x) = cos(PI * x) = phi(x)
 * u(t,0) = exp(-t) = psi(t)
 * x = (0; 1]
 * t = (0; 1]
 *
 * Stability if a * tau <= h
 * BEST if a * tau = h
 */
#include "transport_equation.h"

const double a = 2.0;
const double X = 1.0;
const double T = 1.0;

const double h = 0.002;
const double tau = 0.001;

double f(double t, double x)
{
    return x / X + t / T;
}

double phi(double x)
{
    return cos(M_PI * x / X );
}

double psi(double t)
{
    return exp(-t / T);
}