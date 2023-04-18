#ifndef GFIELD_H_INCLUDED
#define GFIELD_H_INCLUDED

#include <iostream>

using namespace std;

class GField
{
    int value;
    int mod;

public:
    //default constructor
    GField() {
    }

    //constructor with mod input
    GField(int m) {
        mod = m;
    }

    //constructor with data and mod input
    GField(int data, int m) {
        mod = m;
        value = data % m;
    }

    //operator overload for =
    void operator = (int data) {
        value = data % mod;
    }

    //operator overload for <<
    friend ostream& operator << (ostream& os, const GField& GF) {
        os << GF.value;
        return os;
    }

    //operator overload for +
    GField operator + (const GField& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GField ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GField ret(this->mod);
            ret.value = this->value + GF.value;
            ret.value = ret.value % ret.mod;
            return ret;
        }
    }

    //operator overload for -
    GField operator - (const GField& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GField ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GField ret(this->mod);
            ret.value = this->value - GF.value;
            while(ret.value < 0)
                ret.value = ret.value + ret.mod;
            ret.value = ret.value % ret.mod;
            return ret;
        }
    }

    //operator overload for *
    GField operator * (const GField& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GField ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GField ret(this->mod);
            ret.value = this->value * GF.value;
            ret.value = ret.value % ret.mod;
            return ret;
        }
    }

    //operator overload for /
    GField operator / (const GField& GF) {
        if(this->mod != GF.mod) {
            cout << "Not in the same field\n";
            GField ret(this->mod);
            ret.value = this->value;
            return ret;
        }
        else {
            GField ret(this->mod);
            ret.value = this->value / GF.value;
            return ret;
        }
    }
};

#endif // GFIELD_H_INCLUDED
