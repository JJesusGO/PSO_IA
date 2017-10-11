#include "PSO.h"

PSO::PSO(int particulas,float *rmin,float *rmax,int dimensiones,int iteraciones){

    this->cantidad = particulas;
    this->dimensiones = dimensiones;
    this->iteraciones = iteraciones;

    this->rmin = new float[dimensiones];
    this->rmax = new float[dimensiones];

    for(unsigned int i=0;i<dimensiones;i++){
        this->rmin[i] = rmin[i];
        this->rmax[i] = rmax[i];
    }

    mejorparticula = 0;

    evaluar     = NULL;
    actualizar  = NULL;
    seleccionar = NULL;

    CrearEnjambre();
}
PSO::~PSO(){

    delete [] particulas;
    delete [] rmin;
    delete [] rmax;

}
void PSO::CrearEnjambre(){
    particulas = new Particula[GetCantidadParticulas()];
}

void PSO::IniciarEnjambre(float c1,float c2,float vmin,float vmax){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
        particulas[i].IniciarParticula(c1,c2,vmin,vmax,GetDimensiones());
        for(unsigned int j=0;j<GetDimensiones();j++)
            particulas[i].SetPosicion(j,GetRangoMinimo(j),GetRangoMaximo(j));

    }

    EvaluarEnjambre();
    ForzarEnjambre();
    SeleccionEnjambre();
}
void PSO::EvaluarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++)
        particulas[i].SetFitnessX(evaluar(particulas[i]));
}
void PSO::ActualizarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++)
        if(actualizar(particulas[i])){
            particulas[i].SetFitnessP(particulas[i].GetFitnessX());
            for(unsigned int j=0;j<GetDimensiones();j++)
                particulas[i].SetMejorPosicion(j,particulas[i].GetPosicion(j));
        }

}
void PSO::ForzarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
            particulas[i].SetFitnessP(particulas[i].GetFitnessX());
            for(unsigned int j=0;j<GetDimensiones();j++)
                particulas[i].SetMejorPosicion(j,particulas[i].GetPosicion(j));
    }
}
void PSO::SeleccionEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++)
        if(seleccionar(particulas[i],particulas[mejorparticula]))
            mejorparticula = i;
}
void PSO::MovimientoEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
        particulas[i].ActualizarVelocidad(particulas[mejorparticula]);
        particulas[i].ActualizarPosicion();
    }
}

void PSO::NextIteracion(){

    MovimientoEnjambre();
    EvaluarEnjambre();
    ActualizarEnjambre();
    SeleccionEnjambre();

}

void PSO::MostrarPSO(){
    printf("PARTICULAS : %d\n",GetCantidadParticulas());
    printf("DIMENSIONES : %d\n",GetDimensiones());
    printf("ITERACIONES : %d\n",GetIteraciones());
    printf("MEJOR PARTICULA : \n\n");
    MostrarMejorParticula();
}
void PSO::MostrarPSO(FILE *file){
    fprintf(file,"PARTICULAS : %d\n",GetCantidadParticulas());
    fprintf(file,"DIMENSIONES : %d\n",GetDimensiones());
    fprintf(file,"ITERACIONES : %d\n",GetIteraciones());
    fprintf(file,"MEJOR PARTICULA : \n\n");
    MostrarMejorParticula(file);
}
void PSO::MostrarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
        particulas[i].MostrarParticula(i);
        printf("\n\n");
    }
}
void PSO::MostrarMejorParticula(){
    GetMejorParticula().MostrarParticula(GetMejorParticulaIndex());
}
void PSO::MostrarMejorParticula(FILE *file){
    GetMejorParticula().MostrarParticula(GetMejorParticulaIndex(),file);
}

void PSO::SetFunciones(float (*evaluar)(Particula &particula),
                          int (*actualizar)(Particula &particula),
                          int (*seleccionar)(Particula &particula,Particula &mejor)){

    this->evaluar = evaluar;
    this->actualizar = actualizar;
    this->seleccionar = seleccionar;

}
