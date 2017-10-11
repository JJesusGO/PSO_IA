#include "Particula.h"

Particula::Particula()
{
	Xi = NULL;
	Pi = NULL;
	Vi = NULL;

	C1 = 0;
	C2 = 0;

	Vmax = 0;
	Vmin = 0;

	FitnessP = 0;
	FitnessX = 0;

	Dim = 0;
}
Particula::~Particula()
{
	delete[] Xi;
	delete[] Pi;
	delete[] Vi;
}
void Particula::IniciarParticula(float c1, float c2, float vmin, float vmax,int dim)
{
	//Inicializacion de variables de la particula
	C1 = c1;
	C2 = c2;
	Vmax = vmax;
	Vmin = vmin;
	FitnessX = 0;
	FitnessP = 0;
	Dim = dim;

	//Asignacion de memoria
	Xi = new float[dim];
	Pi = new float[dim];
	Vi = new float[dim];

	//Inicializacion de los parametros principales de la particula
	for (unsigned int i = 0;i < dim;i++)
	{
		Xi[i] = 0;
		Pi[i] = 0;
		Vi[i] = 0;
	}
}
void Particula::SetPosicion(int i, float valor)
{
	Xi[i] = valor;
}
void Particula::SetPosicion(int i, float pmin, float pmax)
{
    float aleatorio = Random::NextDouble(pmin, pmax);
	Xi[i] = aleatorio;
}
void Particula::SetMejorPosicion(int i, float valor)
{
	Pi[i] = valor;
}
void Particula::ActualizarVelocidad(Particula &Particula)
{
	//Iniciar velocidad
	float Y1, Y2;
	for (unsigned int d = 0;d < Dim;d++)
	{
		Y1 = Random::NextDouble();
		Y2 = Random::NextDouble();
		Vi[d] += C1*Y1*(Pi[d] - Xi[d]) + C2*Y2*(Particula.Pi[d] - Xi[d]);
		if (Vi[d] > Vmax){
			 Vi[d] = Vmax;
		}
		if (Vi[d] < Vmin){
			 Vi[d] = Vmin;
		}
	}
}
void Particula::ActualizarPosicion(void){
	for (unsigned int d = 0;d < Dim;d++)
	{
		Xi[d] += Vi[d];
	}
}
void Particula::SetFitnessX(float valor){
	FitnessX = valor;
}
void Particula::SetFitnessP(float valor){
	FitnessP = valor;
}
const void Particula::MostrarParticula(int n) const {
	printf("C1[%i] = %+2.4f", n, C1);
	printf("\nC2[%i] = %+2.4f", n, C2);
	printf("\nFX[%i] = %+e", n, FitnessX);
	printf("\nFP[%i] = %+e", n, FitnessP);
	printf("\n\nX[%i]: ",n);
	for (int d = 0; d < Dim;d++)
		printf("%+2.4f ", Xi[d]);
	printf("\nV[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		printf("%+2.4f ", Vi[d]);
	printf("\nP[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		printf("%+2.4f ", Pi[d]);
}
const void Particula::MostrarParticula(int n,FILE *file) const {
	fprintf(file,"C1[%i] = %+2.4f", n, C1);
	fprintf(file,"\nC2[%i] = %+2.4f", n, C2);
	fprintf(file,"\nFX[%i] = %+e", n, FitnessX);
	fprintf(file,"\nFP[%i] = %+e", n, FitnessP);
	fprintf(file,"\n\nX[%i]: ",n);
	for (int d = 0; d < Dim;d++)
		fprintf(file,"%+2.4f ", Xi[d]);
	fprintf(file,"\nV[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		fprintf(file,"%+2.4f ", Vi[d]);
	fprintf(file,"\nP[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		fprintf(file,"%+2.4f ", Pi[d]);
}


