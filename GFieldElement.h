#ifndef GFIELDELEMENT_H_INCLUDED
#define GFIELDELEMENT_H_INCLUDED

#include <iostream>
#include <stdexcept>
#include "InverseError.h"
using namespace std;

class GFieldElement
{
    int value;
    int mod;
    bool isInverseCalculated = false;

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

    GFieldElement& operator=(const GFieldElement& other) {
        if (this != &other) {
            value = other.value;
            mod = other.mod;
            isInverseCalculated = other.isInverseCalculated;
        }
        return *this;
    }


    //operator overload for <<
    friend ostream& operator << (ostream& os, const GFieldElement& GF) {
        os << GF.value;
        return os;
    }

    //operator overload for +
    GFieldElement operator + (const GFieldElement& GF) {
        if(this->mod != GF.mod) {
            throw runtime_error("Not in the same field!" );
            
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
            throw runtime_error("Not in the same field!" );
            
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
            throw runtime_error("Not in the same field!" );
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
            throw runtime_error("Not in the same field!" );
        }
        else if (GF.getValue() == 0) {
            throw InverseDNE();
        }
        else if ((GF.has_inverse())) {
            GFieldElement ret(this->mod);
            // Need to do ret.value = this-> value * Gf.inverse()
            const GFieldElement inv = GF.inverse();
            setInverseStatus(true);
            ret = (*this) * inv;  // Use parentheses to call the operator overload function
            return ret;
            
        }
        else {
            throw runtime_error("Division cannot be done with noninvertible element!");
        }
    }
    bool has_inverse() {
        if (value == 0) {
            throw InverseDNE();
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
        if (this->getValue() == 0) {
            setInverseStatus(true);
            throw InverseDNE();
        }
        if (this->has_inverse() && !this->isInverseCalculated) {
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
            setInverseStatus(true);
            return inv;
        } else {
            throw InverseDNE(); // Custom exception class from "InverseError.h"

            // In order to avoid pointers to the parent field class (see Galois.h - it didnt work) 
            // we can do this to notify the parent field to set the DNEValue in the inverses vector
        }
        
    }

    int getValue() {
        return value;
    }

    void setValue(int val) {
        value = val;
    }
    void setMod(int m) {
        mod = m;
    }


    bool getInverseStatus() { return this->isInverseCalculated; }
    void setInverseStatus(bool stat) { this->isInverseCalculated = stat; }
    



};

#endif // GFIELDELEMENT_H_INCLUDED
