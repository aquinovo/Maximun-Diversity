#include "funciones.cpp"

vector <bool> tabu( map<int, map<int,float> > datos,int m, int n,int iteracion,int Tm,int num_vecinos ,float porcentaje){

  vector <bool>s=crear_solucion(m,n);
  vector <bool> sBest=s,vecino;
  queue< float > tabuListValues;
  queue< vector <bool> > tabuList;
  vector <vector <bool> >candidateList;
  vector <float>valuesCandidateList;

  while(iteracion--){
    vector <bool> sCandidate;
    float sCandidateValue;
    for (int i = 0; i < num_vecinos; i++){
      sCandidate=crear_vecino(sBest,n,porcentaje);
      sCandidateValue=valor_solucion(sCandidate,datos);
      if(!containsTabuElemens(tabuListValues,sCandidateValue)){
        candidateList.push_back(sCandidate);
        valuesCandidateList.push_back(sCandidateValue);
      }
    }
    sCandidate=locateBestCandidate(valuesCandidateList,candidateList);	 
    s=sCandidate;

    if( valor_solucion(sCandidate,datos) > valor_solucion(sBest,datos) ){
      tabuList.push(sCandidate);
      tabuListValues.push(valor_solucion(sCandidate,datos));
      sBest=sCandidate;
      while(tabuList.size()>Tm){
        tabuList.pop();
        tabuListValues.pop();
      }
    }
  }

  return sBest;

}

int main() {
   // Inicializacion de variables
   // n número total de elementos, m número de elementos para cada subconjunto
   /* Para cada tupla tenemos lo siguiente:
         origen: elemto incial
         destino: elemento a comparar
         valor: distancia entre los elementos   
   */ 
   int n, m, origen, destino; float valor;
     //Mapa para respaldar los datos
   map<int, map<int,float> > datos;
     //Inicializacion de semilla para generacion de numeros aleatorios
   srand (time(NULL));

     // variables para medir el tiempo de ejecución del algoritmo
   struct timeval t_ini, t_fin;
   double secs;

   cin >> n >>m;

     //Definicion del vector solucion con n elementos
   vector <bool>solucion (n);

     //lectura de los datos
   while(cin >> origen>> destino >> valor) {
    datos[origen][destino]=valor;
   }

     //numero de iteraciones
  int iteracion[]={100,1000,3500};
     //tamaño de la memoria 
  int Tm[]={5,40,80}; 
     //número de vecinos a considerar
  int num_vecinos[]={2,8,25}; 
     //porcentaje de elementos a modificar para determinar un vecino 
  float porcentaje=0.04; 

     //Guardar solucion en archivo csv
  ofstream ficheroSalida;
  ficheroSalida.open ("salida/tabu.csv");
  ficheroSalida << "Tiempo,Solución"<<endl;

  for (int i = 0; i < sizeof(iteracion)/sizeof(iteracion[0]); i++){
      for (int j = 0; j < sizeof(Tm)/sizeof(Tm[0]); j++){
        for (int k = 0; k < sizeof(num_vecinos)/sizeof(num_vecinos[0]); k++){
          cout<<"Iteraciones: "<<iteracion[i]<<" Tamaño de la memoria: "<<Tm[j]<<"  Numero de vecinos: "<<num_vecinos[k];
      
          //obtener el tiempo de ejecucion del algoritmo
          gettimeofday(&t_ini, NULL);
          solucion=tabu( datos, m, n,iteracion[i],Tm[j] ,num_vecinos[k],porcentaje); 
          gettimeofday(&t_fin, NULL); secs = timeval_diff(&t_fin, &t_ini);
      

          //obtener y guardar los resultados
          float valorsolucion=valor_solucion(solucion,datos);
          cout<<endl;cout<<"Tiempo: "<<secs<<" Valor de la solucion: "<<valorsolucion;
          ficheroSalida <<secs<<","<<valorsolucion<<endl; 
          cout<<endl;cout<<endl;
        }
      }
  }
  ficheroSalida.close();
  return 0;
}

