#ifndef GFIELD_H_INCLUDED
#define GFIELD_H_INCLUDED

#include <iostream>

using namespace std;

class GFieldElement
{
    int value;
    int mod;

public:
    //default constructor
    GFieldElement() {
    }

    //constructor with mod input
    GFieldElement(int m) {
        mod = m;
    }

    //constructor with data and mod input
    GFieldElement(int data, int m) {
        mod = m;
        value = data % m;
    }

    //operator overload for =
    void operator = (int data) {
        value = data % mod;
    }

    //operator overload for <<
    friend ostream& operator << (ostream& os, const GFieldElement& GF) {
        os << GF.value;
        return os;
    }

    //operator overload for +
    GFieldElement operator + (const GFieldElement& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GFieldElement ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GFieldElement ret(this->mod);
            ret.value = this->value + GF.value;
            ret.value = ret.value % ret.mod;
            return ret;
        }
    }

    //operator overload for -
    GFieldElement operator - (const GFieldElement& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GFieldElement ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GFieldElement ret(this->mod);
            ret.value = this->value - GF.value;
            while(ret.value < 0)
                ret.value = ret.value + ret.mod;
            ret.value = ret.value % ret.mod;
            return ret;
        }
    }

    //operator overload for *
    GFieldElement operator * (const GFieldElement& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GFieldElement ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GFieldElement ret(this->mod);
            ret.value = this->value * GF.value;
            ret.value = ret.value % ret.mod;
            return ret;
        }
    }

    //operator overload for /
    GFieldElement operator / (const GFieldElement& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GFieldElement ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GFieldElement ret(this->mod);
            ret.value = this->value / GF.value;
            return ret;
        }
    }
};

#endif // GFIELD_H_INCLUDED
