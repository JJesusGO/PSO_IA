#include "Random.h"

Seed Random::seed;

void Random::SetRandom(){
    srand(time(NULL));
}
void Random::SetRandomSeed(){
    srand(seed.GetSeedValor());
}

void Random::SetSeed(const Seed &s){
    seed = s;
    SetRandomSeed();
}

int Random::Next(){
    return rand();
}
int Random::Next(int mn,int mx){
    return (mn + (rand() % (mx-mn+1)));
}
int Random::Next(int mx){
    Next(0,mx);
}

double Random::NextDouble(){
    return static_cast<double>(rand())/RAND_MAX;
}
double Random::NextDouble(double mn,double mx){
    return  NextDouble()*(mx-mn) + mn;
}
double Random::NextDouble(double mx){
    return NextDouble(0,mx);
}

Seed::Seed(){
    this->seedi = 0;
    this->seeds = "DESCONOCIDA";
}
Seed::Seed(const std::string palabra){
    CrearSeed(palabra);
}
Seed::Seed(const unsigned int n){

   std::string palabra;
   int  caracter;

   for(int i=0;i<n;i++){

        do{caracter = (int)('0')+(rand() % (int)'Z');}
        while( !(
                  ((caracter >= (int)'0') && (caracter <= (int)'9')) ||
                  ((caracter >= (int)'A') && (caracter <= (int)'Z'))
                 )
              );
        palabra += static_cast<char>(caracter);

   }
   CrearSeed(palabra);

}

void Seed::CrearSeed(std::string palabra){

    int resultado = 1;

   for(int i=0;i<palabra.size();i++){
     if(isalpha(palabra[i]))
       palabra[i] = (char)toupper((int)palabra[i]);
       resultado += (int)(palabra[i])*12345*i;
   }

   this->seedi = resultado;
   this->seeds = palabra;

}



