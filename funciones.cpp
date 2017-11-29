#include <vector>
#include <map>
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>
#include <sys/time.h>
#include <fstream>

using namespace std;

// funciones para representar el problema de máxima diversidad usados en los algoritmos de recocido, tabú y armónica
vector <bool> crear_solucion(int m,int n);
float valor_solucion(vector <bool> solucion,map<int, map<int,float> > datos);
vector <bool> crear_vecino (vector <bool> solucion,int n,float porcentaje);

// funciones usados para el algoritmo tabú
bool containsTabuElemens(queue <float>tabuListValues, float valor_vecino);
vector <bool> locateBestCandidate( vector<float> valor_vecinos,vector <vector <bool> > vecinos);

// funciones usados para el algoritmo armónico
vector < vector <bool>  > iniciar_memoria(int m,int n,int Tm);
vector<float> iniciar_valores_memoria(vector < vector <bool>  > memoria,map<int, map<int,float> > datos);
int armonia_menor(vector<float> valores_memoria);
int armonia_mayor(vector<float> valores_memoria);

// funciones usados para el algoritmo genetico
vector < vector <bool>  > poblacion_inicial(int m,int n,int Tm);
vector<float> poblacion_heuristica(vector < vector <bool>  > soluciones,map<int, map<int,float> > datos);
vector < vector <bool>  > torneo(vector < vector <bool>  > poblacion, vector<float> heuristica, float porcentaje);
vector < vector <bool>  > cruzamiento (vector <bool> padre1,vector <bool> padre2,int m);
vector <bool> eliminar_agregar_unos(vector <bool> hijo1,vector <bool> padre,int m);
int num_unos(vector <bool> hijo);
int menor(vector<float> valores_memoria);
int mayor(vector<float> valores_memoria);

//diferencia en tiempos de reloj
double timeval_diff(struct timeval *a, struct timeval *b);

//int main(){return 0;}
//Generación de soluciones aleatoriamente para m elementos tomados de n totales 
vector <bool> crear_solucion(int m,int n){
   int posicion;
   vector <bool>solucion (n);
   
   for(int i=0;i<m;i++){ 
      posicion= rand()%n; 
      while(solucion[posicion]==1)
         posicion= rand()%n; 
      solucion[posicion]=1;
   }

   return solucion;
}
//Obtener el valor de una solución dada
float valor_solucion(vector <bool> solucion,map<int, map<int,float> > datos){
   float valor=0.0;
   vector<int> soluciones;

   for (int i = 0; i < solucion.size(); i++)
      if(solucion[i]==1)
         soluciones.push_back(i);

   for (int i = 0; i < soluciones.size()-1; i++)
      for (int j = i+1; j < soluciones.size(); j++)
         valor+=datos[soluciones[i]][soluciones[j]];

	return valor;
}
//Crear vecino de una solución dado el porcentaje de elementos a modificar
vector <bool> crear_vecino (vector <bool> solucion,int n,float porcentaje){
   vector<int> soluciones;
   int num_vecinos,seleccion,cambio;

   for (int i = 0; i < solucion.size(); ++i)
      if(solucion[i]==1)
         soluciones.push_back(i);

   num_vecinos=porcentaje*n;
   
   while(num_vecinos--){
      seleccion=soluciones[rand()%soluciones.size()];
      cambio=rand()%(n);

      while(solucion[cambio]==1)
         cambio=rand()%(n);
      
      bool temp=solucion[seleccion];
      solucion[seleccion]=solucion[cambio];
      solucion[cambio]=temp;
   }

   return solucion;
}
//*********************************************************************************************//

//Verificar si un resultado ya está en la lista tabú
bool containsTabuElemens(queue <float>tabuListValues, float valor_vecino){
    queue <float> temp=tabuListValues;   

   while ( !temp.empty() ){
       if(temp.front()==valor_vecino)
         return true;
       temp.pop();
   } 

   return false;
}
//Obtener rl mejor resultado de unn conjunto de vecino
vector <bool> locateBestCandidate( vector<float> valor_vecinos,vector <vector <bool> > vecinos){
   int indice=0;
   float mayor=valor_vecinos[0];
   for (int i = 1; i < valor_vecinos.size(); ++i){
      if(valor_vecinos[i]>mayor){
         mayor=valor_vecinos[i];
         indice=i;
      }
   }
   return vecinos[indice];
}
//*********************************************************************************************//

//funcion que inicializa una memoria con Tm soluciones aleatorias
vector < vector <bool>  > iniciar_memoria(int m,int n,int Tm){
    vector < vector <bool> >memoria(Tm);

    for (int i = 0; i < Tm; i++){
      memoria[i]=crear_solucion(m,n);
    }

    return memoria;
}
//funcion que obtines el valor de cada solucion en la memoria
vector<float> iniciar_valores_memoria(vector < vector <bool>  > memoria,map<int, map<int,float> > datos){
   vector<float> valores_memoria(memoria.size());
    
    for (int i = 0; i < memoria.size(); i++){
      valores_memoria[i]=valor_solucion(memoria[i],datos);
    }

   return valores_memoria;
}
//funcion que determina la solucion con menor valor
int armonia_menor(vector<float> valores_memoria){
   int indice=0;
    float menor=valores_memoria[0];

    for (int i = 1; i < valores_memoria.size(); i++){
      if(valores_memoria[i]<menor){
            menor=valores_memoria[i];
            indice=i; 
      }
    }
        
   return indice;
}
//funcion que determina la solucion con mayor valor
int armonia_mayor(vector<float> valores_memoria){
   int indice=0;
    float mayor=valores_memoria[0];

    for (int i = 1; i < valores_memoria.size(); i++){
      if(valores_memoria[i] > mayor){
            mayor=valores_memoria[i];
            indice=i; 
      }
    }
        
   return indice;
}

//********************************************************************************************************

//funcion que inicializa la poblacion inicial
vector < vector <bool>  > poblacion_inicial(int m,int n,int Tm){
    vector < vector <bool> >soluciones(Tm);
    for (int i = 0; i < Tm; i++){
      soluciones[i]=crear_solucion(m,n);
    }
    return soluciones;
}
//funcion para obtener las heuristicas de la poblacion
vector<float> poblacion_heuristica(vector < vector <bool>  > soluciones,map<int, map<int,float> > datos){
   vector<float> heuristica_solucion(soluciones.size());
    for (int i = 0; i < soluciones.size(); i++){
      heuristica_solucion[i]=valor_solucion(soluciones[i],datos);
    }

   return heuristica_solucion;
}
//torneo para seleccionar a los candidatos que se cruzarán
vector < vector <bool>  > torneo(vector < vector <bool>  > poblacion, vector<float> heuristica, float porcentaje){
    int n=poblacion.size()*porcentaje;
    vector < vector <bool> >seleccionados(0);
    
    while(seleccionados.size()<n){
      int candidato1= rand() % poblacion.size();
      int candidato2= rand() % poblacion.size();

      if(heuristica[candidato1]>=heuristica[candidato2]){
        seleccionados.push_back(poblacion[candidato1]);
        poblacion.erase(poblacion.begin()+candidato1);
        heuristica.erase(heuristica.begin()+candidato1);
      }
      else{
        seleccionados.push_back(poblacion[candidato2]);
        poblacion.erase(poblacion.begin()+candidato2);
        heuristica.erase(heuristica.begin()+candidato2);
      }
    }
    return seleccionados; 
}

vector < vector <bool>  > cruzamiento (vector <bool> padre1,vector <bool> padre2,int m){
  vector < vector <bool> >hijos(2,vector<bool>(padre1.size()));
  for (int i = 0; i < padre1.size(); i++){
       if(i <= padre1.size()/2){
        hijos[0][i]=padre1[i];
        hijos[1][i]=padre2[i]; 
       }else{
        hijos[0][i]=padre2[i];
        hijos[1][i]=padre1[i]; 
       }
  }
  hijos[0]=eliminar_agregar_unos(hijos[0],padre2,m);
  hijos[1]=eliminar_agregar_unos(hijos[1],padre2,m);

  return hijos;
}

vector <bool> eliminar_agregar_unos(vector <bool> hijo,vector <bool> padre,int m){
  vector <bool> hijo_nuevo=hijo;
  int posicion;
  posicion= rand()%hijo_nuevo.size();
  while(num_unos(hijo_nuevo)>m){
    if(hijo_nuevo[posicion]==1)
      hijo_nuevo[posicion]=0;
    posicion= rand()%hijo_nuevo.size();
  }
  
  posicion=0;
  while(num_unos(hijo_nuevo)<m){
    if(padre[posicion]==1)
      hijo_nuevo[posicion]=1; 
    posicion++;
  }
  return hijo_nuevo;
}

int num_unos(vector <bool> hijo){
  int cont=0;
  for (int i = 0; i < hijo.size(); ++i){
    if(hijo[i]==1)
      cont++;
  }
  return cont;
}
//funcion que determina la solucion con menor valor
int menor(vector<float> valores_memoria){
   int indice=0;
    float menor=valores_memoria[0];

    for (int i = 1; i < valores_memoria.size(); i++){
      if(valores_memoria[i]<menor){
            menor=valores_memoria[i];
            indice=i; 
      }
    }
        
   return indice;
}
//funcion que determina la solucion con mayor valor
int mayor(vector<float> valores_memoria){
   int indice=0;
    float mayor=valores_memoria[0];

    for (int i = 1; i < valores_memoria.size(); i++){
      if(valores_memoria[i] > mayor){
            mayor=valores_memoria[i];
            indice=i; 
      }
    }
        
   return indice;
}



//***********************************************************************************************************

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b){
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}