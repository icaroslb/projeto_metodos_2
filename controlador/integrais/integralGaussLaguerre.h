#ifndef INTEGRAL_GAUSS_LAGURERRE_H
#define INTEGRAL_GAUSS_LAGURERRE_H

#include <iostream>
#include <cmath>
#include "../parser/parser.h"

float gaussLaguerre (const int &qtdPontos, expre::expre *equacao);

float gaussLaguerreN2 (expre::expre *equacao);
float gaussLaguerreN3 (expre::expre *equacao);
float gaussLaguerreN4 (expre::expre *equacao);

#endif //INTEGRAL_GAUSS_LAGURERRE_H