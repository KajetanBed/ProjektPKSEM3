#include "ARX.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    vector<double> v1 = {-0.4}; // a
    vector<double> v2 = {0.6};  // b

    ARX a1(v1, v2, 1.0);
    vector<double> u = {0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    for (int i = 0; i < 7; i++)
    {
        cout << a1.symuluj(u[i]) << endl;
    }
}