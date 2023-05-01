#include <iostream>
#include <chrono>
#include "GField.h"
#include "GFieldElement.h"
#include "InverseError.h"
using namespace std;



int main(int argc, char *argv[]) {
    
    /*
        Multiplicative inverses GF(7)
        * | 1  2  3  4  5  6 
        --------------------
        1 | 1  2  3  4  5  6 
        2 | 2  4  6  1  3  5 
        3 | 3  6  2  5  1  4 
        4 | 4  1  5  2  6  3 
        5 | 5  3  1  6  4  2 
        6 | 6  5  4  3  2  1 
    */
    GField myField(7);
    myField.printField();
    // Performing 4 / 3; Expecting 6 for GF(7)
    vector<long long> times;
    // Compute every inverse
    for (int i=0; i<7; i++) {
        for (int j=0; j<7; j++) {
            auto start = chrono::steady_clock::now();
            GFieldElement dividend = myField[i];
            GFieldElement divisor = myField[j];
            try {
                GFieldElement quotient = dividend / divisor;
                cout << quotient << endl;
                myField.insertInverse(divisor.inverse(), divisor.getValue());
            } catch (InverseDNE idne) {
                // Element is not invertible
                cout << idne.what(); 
                myField.insertInverse(myField.getDNEElement(), divisor.getValue());
            }

            auto end = chrono::steady_clock::now();
            auto dur = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
            times.push_back(dur);
        }
    }


    long long avg = 0;
    for (auto it: times) {
        avg += it;
    }
    avg /= times.size();

    cout << "Average time to compute every division possibility: " << avg << "ns" << endl;

    vector<GFieldElement> elems = myField.getElements();
    vector<GFieldElement> invs = myField.getInverses();
    cout << "elems size: " << elems.size() << endl;
    cout << "invs size: " << invs.size() << endl;
    for (int i=0; i<7; i++) {
        cout << elems[i].getValue() << ":" << invs[i].getValue() << "\t";
    }
    cout << endl;
    
    

    return 0;
}