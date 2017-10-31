#include "funciones.cpp"

vector <bool> armonica( map<int, map<int,float> > datos,int m, int n,int iteraciones, float Tm,float porcentaje){
  vector <bool>nueva_armonia;
  float valor_armonia;
  vector < vector <bool>  >memoria;
  vector<float> valores_memoria;
  int indice;

  memoria=iniciar_memoria(m,n,Tm);
  valores_memoria=iniciar_valores_memoria(memoria,datos);

  while(iteraciones--){
  	bool random = rand() % 2;

  	if(random){
      nueva_armonia=crear_solucion(m,n);
    }else{
      nueva_armonia=crear_vecino(memoria[ rand() % memoria.size()],n,porcentaje);
    }
    valor_armonia=valor_solucion(nueva_armonia,datos);
    indice=armonia_menor(valores_memoria);

    if( valor_armonia > valores_memoria[indice] ){
    	memoria[indice]=nueva_armonia;
      valores_memoria[indice]=valor_armonia;
    } 
  }
  
  return memoria[armonia_mayor(valores_memoria)];
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
   //Tamaño de memoria
int Tm[]={4,40,70};
   //porcentaje de elemetos de una armonía a modificar
float porcentaje[]={0.02,0.10,0.25}; 

ofstream ficheroSalida;
ficheroSalida.open ("salida/armonica.csv");
ficheroSalida << "Tiempo,Solución"<<endl;


for (int i = 0; i < sizeof(iteracion)/sizeof(iteracion[0]); i++){
  for (int j = 0; j < sizeof(Tm)/sizeof(Tm[0]); j++){
   for (int k = 0; k < sizeof(porcentaje)/sizeof(porcentaje[0]); k++){
    cout<<"Iteraciones: "<<iteracion[i]<<" Tamaño de la memoria: "<<Tm[j]<<"  Porcentaje: "<<porcentaje[k];
    
    //obtener el tiempo de ejecucion del algoritmo
    gettimeofday(&t_ini, NULL);
    solucion=armonica( datos, m, n,iteracion[i],Tm[j] ,porcentaje[k]); 
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

