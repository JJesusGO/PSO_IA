#include <iostream>
#include <cmath>
#include "Random.h"
#include "Particula.h"
#include "PSO.h"
#include "PSOManager.h"

float Evaluacion1(Particula &particula){
    float suma = 0;
    for(unsigned int i=0;i<particula.GetDimensiones();i++)
        suma += particula.GetPosicion(i)*particula.GetPosicion(i);
    return suma;
}
float Evaluacion2(Particula &particula){
    float suma = 0,
          multiplicacion = 1;
    for(unsigned int i=0;i<particula.GetDimensiones();i++){
        suma += fabs(particula.GetPosicion(i));
        multiplicacion *= particula.GetPosicion(i);
    }
    return suma + multiplicacion;
}
float Evaluacion3(Particula &particula){
    float suma = 0,
           aux = 0;
    for(unsigned int i=0;i<particula.GetDimensiones();i++){
        aux = particula.GetPosicion(i) + 0.5f;
        aux *=aux;
        suma += aux;
    }
    return suma;
}
float Evaluacion4(Particula &particula){
    float maximo = particula.GetPosicion(0);
    for(unsigned int i=1;i<particula.GetDimensiones();i++){
        maximo = (fabs(particula.GetPosicion(i))>maximo) ? fabs(particula.GetPosicion(i)) : maximo;
    }
    return maximo;
}

int Actualizar(Particula &particula){
    if( fabs(particula.GetFitnessX()) < fabs(particula.GetFitnessP()))
        return 1;
    return 0;
}
int Seleccionar(Particula &particula,Particula &mejor){
    if(fabs(particula.GetFitnessP()) < fabs(mejor.GetFitnessP()) )
        return 1;
    return 0;
}

void MostrarTelon(){
    printf("\n\n--------------------------------------\n\n");
}

int main(){

    Random::SetRandom();
    Random::SetSeed(Seed(6));

    int       t = 0;
    float  rmin[100],
           rmax[100];
    for(unsigned int i=0;i<100;i++){
        rmin[i] = -5.12f;
        rmax[i] =  5.12f;
    }
    //float porcentajes[] = {0,10,20,30,40,50,60,70,80,90};

    PSO pso(100,rmin,rmax,30,100000);
        pso.SetFunciones(Evaluacion2,Actualizar,Seleccionar);
        pso.IniciarEnjambre(2,2,-0.1,0.1);

    PSOManager  manager(&pso,0);
                //manager.SetPorcentajes(porcentajes,10);

    pso.MostrarPSO();
    MostrarTelon();
    manager.Run();
    MostrarTelon();
    printf("%s",Random::GetSeed().GetSeedString().c_str());

    return 0;
}
