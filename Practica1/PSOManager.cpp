#include "PSOManager.h"

PSOManager::PSOManager(PSO *pso,float valor,float error){
    this->porcentajes = NULL;
    this->error = error;
    this->erroractual = 0;
    this->valor = valor;
    this->pso = pso;
    this->n = 0;
}
PSOManager::~PSOManager(){
    if(this->porcentajes!=NULL)
        delete []this->porcentajes;
}
void PSOManager::Run(){

    int *iteraciones = NULL;
    if(this->n!=0)
        iteraciones = new int[this->n];
    for(int i=0;i<n;i++)
        iteraciones[i] = static_cast<int>((porcentajes[i]/100)*(pso->GetIteraciones()));
    int t = 0;
    printf("CALCULANDO...\n\n");

    FILE *file = fopen("log.txt","w");
    FILE *data = fopen("log_data.txt","w");
    if(file){
        fprintf(file,"SEED: %s\n",Random::GetSeed().GetSeedString().c_str());
        pso->MostrarPSO(file);
        fprintf(file,"\n\n\n");
    }

    while(pso->IsNextIteracion(valor,error,t)){
        pso->NextIteracion();
        bool impreso = false;
        for(int i=0;i<n;i++)
            if(t == iteraciones[i]){
                printf("-> %2.2f \% - (%i / %i)\n\n",porcentajes[i],t,pso->GetIteraciones());
                pso->MostrarMejorParticula();
                printf("\n\n");
                if(file){
                    fprintf(file,"-> %2.2f \% - (%i / %i)\n\n",porcentajes[i],t,pso->GetIteraciones());
                    pso->MostrarMejorParticula(file);
                    fprintf(file,"\n\n");
                }
                impreso = true;
            }
        if(pso->GetErrorAbs(valor) != erroractual && !impreso){
                erroractual  = pso->GetErrorAbs(valor);
                printf("-> %2.2f \% - (%i / %i)\n\n",(float)t/pso->GetIteraciones()*100.0f,t,pso->GetIteraciones());
                pso->MostrarMejorParticula();
                printf("\n\n");
                if(file){
                    fprintf(file,"-> %2.2f \% - (%i / %i)\n\n",(float)t/pso->GetIteraciones()*100.0f,t,pso->GetIteraciones());
                    pso->MostrarMejorParticula(file);
                    fprintf(file,"\n\n");
                }
                if(data)
                    fprintf(data,"%2.6e\t%d\n",pso->GetErrorAbs(valor),t);
            }
        t++;
    }

    printf("-> 100.00 \% - (%i / %i)\n\n",pso->GetIteraciones(),pso->GetIteraciones());
    pso->MostrarMejorParticula();
    printf("\n");

    if(file){
        fprintf(file,"-> 100.00 \% - (%i / %i)\n\n",pso->GetIteraciones(),pso->GetIteraciones());
        pso->MostrarMejorParticula(file);
        fprintf(file,"\n");
        fclose(file);
    }
    if(data){
        fprintf(data,"%2.6e\t%d\n",pso->GetErrorAbs(valor),t);
        fclose(data);
    }

}
void PSOManager::SetPorcentajes(float *porcentajes,int n){
    if(this->porcentajes!=NULL)
        delete []this->porcentajes;
    this->porcentajes = new float[n];
    for(int i=0;i<n;i++)
        this->porcentajes[i] = porcentajes[i];
        this->n = n;
}
