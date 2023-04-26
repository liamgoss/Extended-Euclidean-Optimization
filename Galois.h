#ifndef GALOIS_H
#define GALOIS_H


#include <iostream>
#include <vector>
#include <tuple>
#include <stdexcept>
using namespace std;


class GField; // forward declaration

class GFieldElement
{
    GField* parentField;
    int value;
    int mod;
public:
    //default constructor
    GFieldElement() {
        parentField = nullptr;
    }

    //constructor with mod input
    GFieldElement(int m, GField* field) {
        mod = m;
        parentField = field;
    }

    //constructor with data and mod input
    GFieldElement(int data, int m, GField* field) {
        mod = m;
        value = data % m;
        parentField = field;
        
    }
    
    int getValue();
    void setValue(int);
    int getMod();
    GField* getParentField();
    bool has_inverse();
    GFieldElement inverse_iterative();
    // Operator overload for <<
    friend std::ostream& operator<<(std::ostream& os, const GFieldElement& GF) {
        os << GF.value;
        return os;
    }
    

};

class GField
{
private:
    // NOTE: Currently, the assumption is that we are NOT working in binary extension fields

    vector<GFieldElement> elements;
    int order;
    GFieldElement* computedInverses; // pointer to array of integers
    bool memoizationFlag = false; 
         
public:
    const int TESTINT = 6942069;
    GField() {
        // Default constructor
        // Set default field to be GF(17)
        order = 17;
        elements.reserve(order); // Allocate max count of elements
        createElements();
        computedInverses = new GFieldElement[order]; // dynamically allocate array with size
        garbageifyInverses();
    }
    GField(int ord) {
        order = ord;
        elements.reserve(ord);
        createElements();
        computedInverses = new GFieldElement[order]; // dynamically allocate array with size
        garbageifyInverses();
    }

    GField(int ord, bool enableMemoization) {
        order = ord;
        elements.reserve(ord);
        createElements();
        computedInverses = new GFieldElement[order]; // dynamically allocate array with size
        memoizationFlag = enableMemoization;
        garbageifyInverses();
    }

    void garbageifyInverses() {
        for (int i=0; i<order; i++) {
            // Fill the array with "garbage" values so that we can later quickly check if the inverse has been computed yet or not
            GFieldElement garbage(order + 99999, order, this);
            computedInverses[i] = garbage;
        }
    }

    ~GField() {
        delete[] computedInverses; // free memory when object is destroyed
    }

    int getOrder() const {
        return order;
    }

    vector<GFieldElement> getElements() const {
        return elements;
    }

    // Overload the [] operator so that you can do GField[x] to get the xth element object
    GFieldElement& operator[] (int index) {
        return elements[index];
    }


    void createElements() {
        if (memoizationFlag) {
            for (int i=0; i<getOrder(); i++) {
                GFieldElement x(i, this->order, this);
                this->elements.push_back(x);
            }
        } else {
            for (int i=0; i<getOrder(); i++) {
                GFieldElement x(i, this->order, this);
                this->elements.push_back(x);
            }
        }
        
    }

    void printField() {
        for (auto it: this->elements) {
            cout << it << " ";
        }
        cout << endl;
    }

    // Unoptimized Extended Euclidean Algorithm (recursive)
    /*
            PSEUDOCODE
            algo(a,b) {
                // d == a*s + b*t
                // returns (d,s,t)
                
                if (b == 0) return (a, 1, 0)
                (d1, s1, t1) = algo(b, a % b)
                d = d1
                s = t1
                t = s1 - (a intDivision b) * t1
                return (d, s, t)
            }
        */
    
    tuple <int, int, int> extendedEuclideanAlgo(int a, int b) {
        if (b == 0) {
            return {a, 1, 0};
        }
        tuple<int, int, int> d1_s1_t1 = extendedEuclideanAlgo(b, a % b);
        int d = std::get<0>(d1_s1_t1);
        int s = std::get<2>(d1_s1_t1);
        int t = std::get<1>(d1_s1_t1) - (a / b) * std::get<2>(d1_s1_t1); // t = s1 - (a intDivision b) * t1
        
        return {d, s, t};
    }

    GFieldElement inverse(GFieldElement x) {
        // Call the algorithm
        tuple<int, int, int> ext = extendedEuclideanAlgo(x.getValue(), this->order);
        // Returned: {inverse value, bezout coefficient s, bezout coeffient t}
        // Convert inverse value to element
        return GFieldElement(std::get<0>(ext), this->order, this);
    }
    

};






int GFieldElement::getValue() {
    return value;
}

void GFieldElement::setValue(int val) {
    value = val & mod;
}

int GFieldElement::getMod() {
    return mod;
}



GField* GFieldElement::getParentField() {
    return parentField;
}

bool GFieldElement::has_inverse() {
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

// Unoptimized Extended Euclidean Algorithm (iterative)
GFieldElement GFieldElement::inverse_iterative() {
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
        GFieldElement inv(t0, this->mod, this->parentField);
        return inv;
    } else {
        throw runtime_error("Element does not have an inverse!");
    }
}


//operator overload for +
GFieldElement operator + (GFieldElement& GF1, GFieldElement& GF2) {
    if(GF1.getMod() != GF2.getMod()) {
        throw invalid_argument("Not in the same field!" );
        
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        ret.setValue(GF1.getValue());
        return ret;
    }
    else {
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        ret.setValue(GF1.getValue() + GF2.getValue());
        ret.setValue(ret.getValue() % ret.getMod());
        return ret;
    }
}

//operator overload for -
GFieldElement operator - (GFieldElement& GF1, GFieldElement& GF2) {
    if(GF1.getMod() != GF2.getMod()) {
        throw invalid_argument("Not in the same field!" );
        
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        ret.setValue(GF1.getValue());
        return ret;
    }
    else {
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        ret.setValue(GF1.getValue() - GF2.getValue());
        while(ret.getValue() < 0)
            ret.setValue(ret.getValue() + ret.getMod());
        ret.setValue(ret.getValue() % ret.getMod());
        return ret;
    }
}

//operator overload for *
GFieldElement operator * (GFieldElement& GF1, GFieldElement& GF2) {
    if(GF1.getMod() != GF2.getMod()) {
        throw invalid_argument("Not in the same field!" );
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        ret.setValue(GF1.getValue());
        return ret;
    }
    else {
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        ret.setValue(GF1.getValue() * GF2.getValue());
        ret.setValue(ret.getValue() % ret.getMod());
        return ret;
    }
}

//operator overload for /
GFieldElement operator / (GFieldElement& GF1, GFieldElement& GF2) {
    if(GF1.getMod() != GF2.getMod()) {
        throw invalid_argument("Not in the same field!" );
    }
    else if ((GF2.has_inverse())) {
        GFieldElement ret(GF1.getMod(), GF1.getParentField());
        // Need to do ret.value = this-> value * Gf.inverse()
        
        GFieldElement inv = GF2.getParentField()->inverse(GF2);
        ret = GF1 * inv;  // Use parentheses to call the operator overload function
        return ret;
        
    }
    else {
        throw runtime_error("Division cannot be done with noninvertible element!");
    }
}



#endif