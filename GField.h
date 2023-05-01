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
    vector<GFieldElement> inverses;
    int order;
    int sentinelValue;
    int DNEValue;

    GFieldElement sentinelElement;
    GFieldElement DNEElement;

public:
    GField() {
        // Default constructor
        // Set default field to be GF(8) (8 is a power of a prime: 2^3)
        order = 8;
        elements.reserve(8); // Allocate max count of elements
        inverses.reserve(8);
        createElements();
        sentinelValue = order + 9999;
        DNEValue = sentinelValue + 1;

        sentinelElement.setValue(sentinelValue);
        sentinelElement.setMod(this->order);
        
        DNEElement.setValue(DNEValue);
        DNEElement.setMod(this->order);

        std::fill(inverses.begin(), inverses.end(), sentinelElement);

    }
    GField(int ord) {
        order = ord;
        elements.reserve(ord);
        inverses.reserve(ord);
        createElements();
        sentinelValue = order + 9999;
        DNEValue = sentinelValue + 1;
        std::fill(inverses.begin(), inverses.end(), sentinelElement);
    }

    int getOrder() const {
        return order;
    }

    vector<GFieldElement> getElements() const {
        return elements;
    }

    vector<GFieldElement> getInverses() {
        return inverses;
    }

    // Overload the [] operator so that you can do GField[x] to get the xth element object
    GFieldElement& operator[] (int index) {
        return elements[index];
    }

    bool isInverseCalculated(int index) {
        // If the value is the sentinel (dummy) value then it has not been calculated yet
        return inverses[index].getValue() != sentinelValue || inverses[index].getValue() != DNEValue;
    }


    void insertInverse(GFieldElement inv, int index) {
        inverses[index] = inv;
    }

    void createElements() {
        for (int i=0; i<getOrder(); i++) {
            GFieldElement x(i, this->order);
            this->elements.push_back(x);
            this->inverses.push_back(sentinelElement);
        }
    }

    void printField() {
        for (auto it: this->elements) {
            cout << it << " ";
        }
        cout << endl;
    }

    GFieldElement getDNEElement() {
        return this->DNEElement;
    }


};

#endif // GFIELD_H_INCLUDED
