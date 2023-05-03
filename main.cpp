#include <iostream>
#include <chrono>
#include "GField.h"

using namespace std;

void memoDiv(GField &myField) {

    for(int j = 0; j < myField.getOrder(); j++) {
        //cout << j << " / GF(" << myField.getOrder() << ") = ";
        for(int i = 0; i < myField.getOrder(); i++)
        {
            if(myField.getInverse(i) != (myField.getOrder() + 999)) {
                GFieldElement inv(myField.getInverse(i), myField.getOrder());
                GFieldElement res = myField[j] *  inv;
                //cout << myField[j] *  inv<< " ";
            }
            //else
                //cout << "x ";
        }
        //cout << endl;
    }
}

void Div(GField &myField) {
    for(int j = 0; j < myField.getOrder(); j++) {
        //cout << j << " / GF(" << myField.getOrder() << ") = ";
        for(int i = 0; i < myField.getOrder(); i++)
        {
            if(myField[i].has_inverse()) {
                GFieldElement res(myField.getOrder());
                res = myField[j] / myField[i];
                //cout << res << " ";
            }
        }
        //cout << endl;
    }
}

int main() {
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
    GField myField(127);
    //myField.printInverses();
    auto starts = chrono::steady_clock::now();
    memoDiv(myField);
    auto ends = chrono::steady_clock::now();
    cout << "Elapsed time for memoized Division of all elements in GF(" << myField.getOrder() << ") by all elements: "
         << chrono::duration_cast<chrono::nanoseconds>(ends- starts).count() << " ns" << endl;
    starts = chrono::steady_clock::now();
    Div(myField);
    ends = chrono::steady_clock::now();
    cout << "Elapsed time for normal Division of all elements in GF(" << myField.getOrder() << ") by all elements: "
         << chrono::duration_cast<chrono::nanoseconds>(ends- starts).count() << " ns" << endl;
    return 0;
}
