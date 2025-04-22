
#include <iostream>
using namespace std;

void fmtBal(double b) {
    cout << "Bal: $" << (int)(b * 100 + 0.5) / 100.0 << "\n";
}

class Acc {
protected:
    double bal;
    int dep, wth;
    double rate, svc;

public:
    Acc(double b, double r) : bal(b), dep(0), wth(0), rate(r), svc(0) {}

    virtual void add(double amt) {
        bal += amt;
        dep++;
    }

    virtual void sub(double amt) {
        bal -= amt;
        wth++;
    }

    virtual void intCalc() {
        double mRate = rate / 12;
        double mInt = bal * mRate;
        bal += mInt;
    }

    virtual void proc() {
        bal -= svc;
        intCalc();
        dep = 0;
        wth = 0;
        svc = 0;
    }

    double getBal() const {
        return bal;
    }
};
