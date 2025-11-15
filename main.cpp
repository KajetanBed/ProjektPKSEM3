#include "ARX.h"
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

int main()
{
    vector<double> v1 = {-0.4}; // a
    vector<double> v2 = {0.6};  // b

    ARX a1(v1, v2, 1);
    vector<double> u = {0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    for (int i = 0; i < 7; i++)
    {
        cout << setprecision(3) << fixed << a1.symuluj(u[i]) << endl;
    }
}