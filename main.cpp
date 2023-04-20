#include <iostream>
#include "GField.h"
#include "GFieldElement.h"

using namespace std;



int main(int argc, char *argv[]) {
    GField myField(8);
    
    GFieldElement divis = myField[6] / myField[4];
    

    return 0;
}