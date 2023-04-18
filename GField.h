#ifndef GFIELD_H_INCLUDED
#define GFIELD_H_INCLUDED

#include <iostream>
#include <vector>
#include "GFieldElement.h"
using namespace std;

class GField
{
private:
    // NOTE: Currently, the assumption is that we are NOT working in binary extension fields

    vector<GFieldElement> elements;
    int order;

public:
    GField() {
        // Default constructor
        // Set default field to be GF(8) (8 is a power of a prime: 2^3)
        order = 8;
        elements.reserve(8); // Allocate max count of elements
        createElements();
    }
    GField(int ord) {
        order = ord;
        elements.reserve(ord);
        createElements();
    }

    int getOrder() const {
        return order;
    }

    vector<GFieldElement> getElements() const {
        return elements;
    }

    void createElements() {
        for (int i=0; i<getOrder(); i++) {
            GFieldElement x(i, this->order);
            this->elements.push_back(x);
        }
    }

    void printField() {
        for (auto it: this->elements) {
            cout << it << " ";
        }
        cout << endl;
    }

};

#endif // GFIELD_H_INCLUDED
