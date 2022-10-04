#include <iostream>

using namespace std;

class Solver
{
public:
    Solver();
    Solver(double ub, double lb, double (*pf)(double x));
    ~Solver();
    bool bisection();
    bool setUpperBound(double ub);
    bool setLowerBound(double lb);
    bool setEpsilon1(double epsilon1);
    bool setEpsilon2(double epsilon2);
    double getResult();
    int getIterationNum();
    bool clear();
private:
    double (*pf_)(double x); 
    double upper_bound_, lower_bound_;
    double result_;
    double epsilon1_;
    double epsilon2_;
    
    bool is_epsilon1_set = false;
    bool is_epsilon2_set = false;
    bool is_upper_bound_set = false;
    bool is_lower_bound_set = false;

    int iteration_num_ = 0;

    bool check();
};

Solver::Solver() {};

Solver::Solver(double ub, double lb, double (*pf)(double x)) : upper_bound_(ub), lower_bound_(lb), pf_(pf) {};

Solver::~Solver() {};

bool Solver::bisection() {
    if(!check()) {
        cout << "please check" << endl;
        return false;
    }
    double x;
    double a = lower_bound_;
    double b = upper_bound_;
    while ((b-a) > epsilon2_) {
        x = (b-a)/2;
        double y = pf_(x);
        if(y*pf_(a)<0) {
            b = x;
        } else {
            a = x;
        }
        ++iteration_num_;
    }
    result_ = x;
    return true;    
}


bool Solver::setUpperBound(double ub) {
    upper_bound_ = ub;
    is_upper_bound_set = true;
    return true;
}

bool Solver::setLowerBound(double lb) {
    lower_bound_ = lb;
    is_lower_bound_set = true;
    return true;
}

bool Solver::setEpsilon1(double epsilon1) {
    epsilon1_ = epsilon1;
    is_epsilon1_set = true;
    return true;
}
bool Solver::setEpsilon2(double epsilon2) {
    epsilon2_ = epsilon2;
    is_epsilon2_set = true;
    return true;
}

double Solver::getResult() {
    return result_;
    return true;
}

int Solver::getIterationNum() {
    return iteration_num_;
}

bool Solver::clear() {
    iteration_num_ = 0;
    is_epsilon1_set = false;
    is_upper_bound_set = false;
    is_lower_bound_set = false;
    return true;
}

bool Solver::check() {
    if(is_epsilon2_set && is_lower_bound_set && is_upper_bound_set) {
        return true;
    }
    return false;
}