#include <iostream>
#include "Galois.h"

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
    GFieldElement divis = myField[4] / myField[3];
    cout << divis << endl;

    return 0;
}