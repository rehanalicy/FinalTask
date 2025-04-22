
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

class SavAcc : public Acc {
    private:
        bool act;
    
    public:
        SavAcc(double b, double r) : Acc(b, r), act(b >= 25.0) {}
    
        void sub(double amt) override {
            if (!act) {
                cout << "Inactive.\n";
            } else {
                Acc::sub(amt);
                if (bal < 25.0)
                    act = false;
            }
        }
    
        void add(double amt) override {
            Acc::add(amt);
            if (!act && bal >= 25.0)
                act = true;
        }
    
        void proc() override {
            if (wth > 4) {
                svc += (wth - 4);
            }
            Acc::proc();
            if (bal < 25.0)
                act = false;
        }
    };
    
    class ChkAcc : public Acc {
    public:
        ChkAcc(double b, double r) : Acc(b, r) {}
    
        void sub(double amt) override {
            if (bal - amt < 0) {
                svc += 15.0;
                cout << "Insufficient.\n";
            } else {
                Acc::sub(amt);
            }
        }
    
        void proc() override {
            svc += 5.0 + (wth * 0.10);
            Acc::proc();
        }
    };
    
    int main() {
        SavAcc s(50.0, 0.05);
        ChkAcc c(100.0, 0.03);
    
        cout << "Savings:\n";
        s.add(30.0);
        s.sub(20.0);
        s.sub(15.0);
        s.sub(10.0);
        s.sub(5.0);
        s.sub(5.0);
        s.proc();
        fmtBal(s.getBal());
    
        cout << "Checking:\n";
        c.add(50.0);
        c.sub(30.0);
        c.sub(150.0);
        c.proc();
        fmtBal(c.getBal());
    
        return 0;
    }