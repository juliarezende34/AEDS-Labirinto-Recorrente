#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

class Pessoa{
    public:
        int vida, sacola, casasPercorridas, valorTotal, perigosVisitados;
        Pessoa();
};

#endif