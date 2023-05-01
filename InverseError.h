#ifndef INVERSEERROR_H_INCLUDED
#define INVERSEERROR_H_INCLUDED

#include <iostream>
using namespace std;

class InverseDNE : public std::exception {
    public:
char * what () {
        return "Element does not have an inverse in this field!\n";
    }
};

#endif