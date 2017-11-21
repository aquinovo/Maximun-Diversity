#include "funciones.cpp"

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

   //lectura de los datos
	while(cin >> origen>> destino >> valor) {
		datos[origen][destino]=valor;
	}
    //Guardar solucion en archivo csv
	ofstream ficheroSalida;
	ficheroSalida.open ("salida/recocido.csv");
	ficheroSalida << "Tiempo,Solución"<<endl; 
    
    int Tm=100; 
    vector < vector <bool>  > poblacion_inicial=poblacion(m,n,Tm);
    vector<float> heuristica=poblacion_heuristica(poblacion_inicial,datos);
    vector < vector <bool>  > seleccionados=torneo(poblacion_inicial,heuristica,0.6);
    vector<float> heuristica_seleccionados=poblacion_heuristica(seleccionados,datos);
    cout<<"hola"<<endl;
    vector < vector <bool>  > hijos=cruzamineto (seleccionados[0],seleccionados[1], m);
    for (int i = 0; i < 2; ++i){
    	cout<<"Padre: "<<i+1<<endl;
    	for (int j = 0; j < seleccionados[0].size(); ++j){
    		cout<<" "<<seleccionados[i][j];
    	}
    	cout<<endl;
    }
    for (int i = 0; i < 2; ++i){
    	cout<<"Hijo: "<<i+1<<endl;
    	for (int j = 0; j < hijos[0].size(); ++j){
    		cout<<" "<<hijos[i][j];
    	}
    	cout<<endl;
    }
	


	ficheroSalida.close();
	return 0;
}

