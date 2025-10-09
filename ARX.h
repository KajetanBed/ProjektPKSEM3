#pragma once
#include <vector>
#include <queue>
using namespace std;

class ARX
{
private:
    vector<double> a;
    vector<double> b;
    double k;
    queue<double> uHist;
    queue<double> yHist;

public:
    ARX(vector<double>, vector<double>, double);
    double getFromQueue(queue<double>, int);
    double Symuluj(double);
    vector<double> getA()
    {
        return a;
    }
};