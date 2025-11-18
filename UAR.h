#pragma once

#include "PID.h"
#include "ARX.h"

class UAR
{
private:
    ARX model;
    PID pid;   
    double y_prev;

public:
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
