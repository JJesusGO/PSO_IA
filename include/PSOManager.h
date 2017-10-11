#pragma once
#ifndef PSOMANAGER_H

#include <cstdio>
#include "PSO.h"

class PSOManager{

    PSO *pso;
    float error,valor;
    float erroractual;
    int n;
    float *porcentajes;

    public:

    PSOManager(PSO *pso,float valor,float error = -1);
    ~PSOManager();
    void Run();
    void SetPorcentajes(float *porcentajes,int n);


};


#endif // PSOMANAGER_H
