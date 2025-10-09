#include "ARX.h"
#include <iostream>

ARX::ARX(vector<double> _a, vector<double> _b, double _k)
{
    for (int i = 0; i < _a.size(); i++)
    {
        if (_a[i] > 10.0)
            _a[i] = 10.0;
        else if (_a[i] < -10.0)
            _a[i] = -10.0;
    }
    a = _a;
    for (int i = 0; i < _b.size(); i++)
    {
        if (_b[i] > 10.0)
            _b[i] = 10.0;
        else if (_b[i] < -10.0)
            _b[i] = -10.0;
    }

    if (_k > 1.0)
        _k = 1.0;
    else if (_k < 0.0)
        _k = 0.0;
}
