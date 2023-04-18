#include <iostream>
#include "GField.h"
#include "GFieldElement.h"

using namespace std;



int main(int argc, char *argv[]) {
    GField myField(8);
    myField.printField();

    return 0;
}