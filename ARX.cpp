#include "ARX.h"
#include <iostream>
#include <numeric>

ARX::ARX(vector<double> _a, vector<double> _b, double _k) : a(_a), b(_b), k(_k)
{
    for (int i = 0; i < _a.size(); i++)
        yHist.push_front(0.0);

    for (int i = 0; i < _b.size(); i++)
        uHist.push_front(0.0);

    for (int i = 0; i < k; i++)
        kBuffer.push_front(0.0);
}

double ARX::symuluj(double u)
{
    kBuffer.push_front(u);
    double uDelayed = kBuffer.back();
    kBuffer.pop_back();

    uHist.push_front(uDelayed);
    uHist.pop_back();

    // obliczenie czesci przy b
    double y = std::inner_product(b.begin(), b.end(), uHist.begin(), 0.0);

    // obliczenie czesci przy a
    y -= std::inner_product(a.begin(), a.end(), yHist.begin(), 0.0);

    yHist.push_front(y);
    yHist.pop_back();
    return y;
}
