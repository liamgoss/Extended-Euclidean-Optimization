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
    vector<int> inverses;
    int order;

public:
    GField() {
        // Default constructor
        // Set default field to be GF(8) (8 is a power of a prime: 2^3)
        order = 8;
        elements.reserve(8); // Allocate max count of elements
        inverses.reserve(8); //Allocate max count of inverses
        createElements();
        createInverses();
    }
    GField(int ord) {
        order = ord;
        elements.reserve(ord);
        inverses.reserve(ord);
        createElements();
        createInverses();
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

    int getInverse(int index) {
        return inverses[index];
    }


    void createElements() {
        for (int i=0; i<getOrder(); i++) {
            GFieldElement x(i, this->order);
            this->elements.push_back(x);
        }
    }

    void createInverses() {
        for (int i=0; i<getOrder(); i++) {
            if(elements[i].has_inverse()) {
                GFieldElement inv = elements[i].inverse();
                this->inverses.push_back(inv.getValue());
            }
            else
                this->inverses.push_back(this->order + 999);
        }
    }

    void printField() {
        for (auto it: this->elements) {
            cout << it << " ";
        }
        cout << endl;
    }

    void printInverses() {
        for (auto it: this->inverses) {
            cout << it << " ";
        }
        cout << endl;
    }

};

#endif // GFIELD_H_INCLUDED
