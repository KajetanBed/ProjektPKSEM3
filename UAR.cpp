#include "UAR.h"
//
double UAR::symuluj(double zadanie)
{
    double e = zadanie - y_prev;
    double u = pid.oblicz(e);
    double y = model.symuluj(u);
    y_prev = y;
    return y;
}

double UAR::symuluj()
{
    double zadanie = GWZ.obliczSygnal();
    double e = zadanie - y_prev;
    double u = pid.oblicz(e);
    double y = model.symuluj(u);
    y_prev = y;
    return y;
}