#pragma once

#include "PID.h"
#include "ARX.h"

class UAR
{
private:
    ARX model;   // kompozycja — własny model
    PID pid;     // kompozycja — własny regulator PID
    double y_prev;

public:
    // konstruktor musi skopiować parametry PID i ARX,
    // ale NIE polegać na kopiowaniu obiektu ARX (ma usunięty copy ctor)
    UAR(const ARX& m, const PID& r)
        : model(m),  
        pid(r),
        y_prev(0.0)
    {
        model.przelaczLimity(false);
        model.przelaczSzum(false);
    }

    double symuluj(double zadanie);
};
