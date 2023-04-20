#ifndef GFIELDELEMENT_H_INCLUDED
#define GFIELDELEMENT_H_INCLUDED

#include <iostream>
#include <stdexcept>

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
            throw invalid_argument("Not in the same field!" );
            
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
            throw invalid_argument("Not in the same field!" );
            
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
    GFieldElement operator * (const GFieldElement& GF) const {
        if(this->mod != GF.mod) {
            throw invalid_argument("Not in the same field!" );
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
    GFieldElement operator / (GFieldElement& GF) {
        if(this->mod != GF.mod) {
            throw invalid_argument("Not in the same field!" );
        }
        else if ((GF.has_inverse())) {
            GFieldElement ret(this->mod);
            // Need to do ret.value = this-> value * Gf.inverse()
            const GFieldElement inv = GF.inverse();
            ret = (*this) * inv;  // Use parentheses to call the operator overload function
            return ret;
            
        }
        else {
            throw runtime_error("Division cannot be done with noninvertible element!");
        }
    }
    bool has_inverse() {
        if (value == 0) {
            return false;  // 0 does not have an inverse
        }
        for (int i = 2; i <= mod; i++) {
            if (mod % i == 0 && value % i == 0) {
                return false;  // element is not relatively prime to mod, so it does not have an inverse
            }
        }
        return true;  // element has an inverse
    }

    // Extended Euclidean Algorithm
    GFieldElement inverse() {
        if (this->has_inverse()) {
            int r0 = this->mod;
            int r1 = this->value;
            int t0 = 0;
            int t1 = 1;
            while (r1 != 0) {
                int q = r0 / r1;
                int r = r0 % r1;
                int t = t0 - q * t1;
                r0 = r1;
                r1 = r;
                t0 = t1;
                t1 = t;
            }
            if (t0 < 0) {
                t0 += this->mod;  // ensure t0 is positive
            }
            GFieldElement inv(t0, this->mod);
            return inv;
        } else {
            throw runtime_error("Element does not have an inverse!");
        }
        
    }

    

};

#endif // GFIELDELEMENT_H_INCLUDED
