#include "GWZ.h"
#include "PID.h"
#include "ARX.h"

class UAR
{
private:
    GeneratorWartosciZadanej GWZ;
    PID PID;
    ARX ARX;
};