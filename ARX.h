#pragma once
#include <vector>
#include <deque>
using namespace std;

class ARX
{
private:
    vector<double> a;
    vector<double> b;
    double k;
    deque<double> yHist;
    deque<double> uHist;
    deque<double> kBuffer;

public:
    ARX(vector<double>, vector<double>, double);
    double symuluj(double);
};