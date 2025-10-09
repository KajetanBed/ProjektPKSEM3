#include "ARX.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> v1 = {11.0};
    vector<double> v2 = {-21.0};

    ARX a1(v1, v2, 2.0);
    vector<double> chuj = a1.getA();
    cout << chuj.at(0);
}