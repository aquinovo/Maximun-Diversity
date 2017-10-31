#include "funciones.cpp"

vector <bool> recocido_simulado( map<int, map<int,float> > datos,int m, int n,float Ti,int num_vecinos ,float porcentaje){
	int k=1;
	float Tk=Ti,Tf=(15039.1 - 15038.8)/30 ,e=2.71827,valor_solucion_actual, valor_vecino,alfa,delta_e;
	vector <bool>vecino(n),vecino_temp(n); vector <bool>solucion_actual=crear_solucion(m,n);

	while(Tk>Tf){
		vecino=crear_vecino(solucion_actual,n,porcentaje);
		valor_vecino=valor_solucion(vecino,datos);
		for (int i = 0; i < num_vecinos-1; i++){
			vecino_temp=crear_vecino(solucion_actual,n,porcentaje);
			float valor_temp=valor_solucion(vecino_temp,datos);
			if(valor_vecino<valor_temp){
				valor_vecino=valor_temp;
				vecino=vecino_temp; 
			}
		} 

		valor_solucion_actual=valor_solucion(solucion_actual,datos); 

		delta_e=valor_solucion_actual-valor_vecino;
		alfa=(rand()%(20));
		alfa=(alfa+80)/100;

		if(delta_e<=0){
			solucion_actual=vecino;
		}else{         
			if( alfa <= 1 / pow(e,delta_e/Tk) )
				solucion_actual=vecino;
		}     

		Tk=alfa*Tk; k++;
	}

	return solucion_actual;

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

   //Temperatura inicial
	float Ti[]={5.0,50.0,300.0};
   //número de vecinos a considerar 
	int num_vecinos[]={2,8,25};
   //porcentaje de elementos a modificar para determinar un vecino
	float porcentajes[] = {0.02,0.10,0.25};

    //Guardar solucion en archivo csv
	ofstream ficheroSalida;
	ficheroSalida.open ("salida/recocido.csv");
	ficheroSalida << "Tiempo,Solución"<<endl;

	for (int i = 0; i < sizeof(Ti)/sizeof(Ti[0]); i++){
		for (int j = 0; j < sizeof(num_vecinos)/sizeof(num_vecinos[0]); j++){
			for (int k = 0; k < sizeof(porcentajes)/sizeof(porcentajes[0]); k++){
				cout<<"Temperatura inicial: "<<Ti[i]<<"  Numero de Vecinos: "<<num_vecinos[j]<<"  Porcentaje: "<<porcentajes[k];
				
				//obtener el tiempo de ejecucion del algoritmo
				gettimeofday(&t_ini, NULL);
				solucion=recocido_simulado( datos, m, n,Ti[i],num_vecinos[j] ,porcentajes[k]); 
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

