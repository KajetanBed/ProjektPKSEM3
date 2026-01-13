#include "PID.h"
#include <cmath>

PID::PID(double _k, double _TI, double _TD)
    : k(_k), TI(_TI), TD(_TD), typCalkowania(trybCalki::wew),
      sumaUchybu(0.0), poprzedniUchyb(0.0),
      lastP(0.0), lastI(0.0), lastD(0.0) // Inicjalizacja
{
}

void PID::setK(double newK) { k = newK; }
void PID::setTI(double newTI) { TI = newTI; }
void PID::setTD(double newTD) { TD = newTD; }

void PID::setTryb(trybCalki nowyTryb)
{
    if (typCalkowania == nowyTryb) return;

    if (TI != 0.0)
    {
        if (typCalkowania == trybCalki::zew && nowyTryb == trybCalki::wew)
            sumaUchybu /= TI;
        else if (typCalkowania == trybCalki::wew && nowyTryb == trybCalki::zew)
            sumaUchybu *= TI;
    }
    typCalkowania = nowyTryb;
}

void PID::resetujSumeUchybu()
{
    sumaUchybu = 0.0;
    poprzedniUchyb = 0.0;
    lastI = 0.0; // Reset też tutaj
}

double PID::oblicz(double uchyb)
{
    // Obliczenie P
    double uP = k * uchyb;

    // Obliczenie I
    double uI = 0.0;
    if (TI != 0.0)
    {
        if (typCalkowania == trybCalki::zew)
        {
            sumaUchybu += uchyb;
            uI = (1.0 / TI) * sumaUchybu;
        }
        else
        {
            sumaUchybu += uchyb / TI;
            uI = sumaUchybu;
        }
    }

    // Obliczenie D
    double uD = TD * (uchyb - poprzedniUchyb);
    poprzedniUchyb = uchyb;

    // ZAPIS DO ZMIENNYCH (aby można było je pobrać do wykresu)
    lastP = uP;
    lastI = uI;
    lastD = uD;

    return uP + uI + uD;
}
