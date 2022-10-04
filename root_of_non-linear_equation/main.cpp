#include <cmath> 
#include "solver.h"


double nonLinearFunction(double x) {
    double y = sin(x) - x*x/4;
    return y;
}

int main()
{
    double epsilon = 0.1;
    double upper = 2.0;
    double lower = 1.5;

    Solver s(upper, lower, nonLinearFunction);
    s.setEpsilon2(0.01);
    s.setLowerBound(lower);
    s.setUpperBound(upper);
    s.bisection();
    cout << s.getResult() << endl;

    return 0;
}