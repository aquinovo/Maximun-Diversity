#include "funciones.cpp"

vector <bool> genetico( map<int, map<int,float> > datos,int m, int n,int num_poblacion,float porcentaje_seleccion,float prob_cruzamiento, float prob_mutacion, float porcentaje_gen_mutar,int numero_generaciones){
	vector <bool> solucion;
	vector < vector <bool>  > poblacion,seleccionados,nueva_poblacion,hijos(2);
    vector<float> heuristica,heuristica_nueva;
    
    poblacion=poblacion_inicial(m,n,num_poblacion);
    heuristica=poblacion_heuristica(poblacion,datos);
    for (int i = 0; i < numero_generaciones; i++){
		heuristica=poblacion_heuristica(poblacion,datos); 	
        seleccionados=torneo(poblacion,heuristica,porcentaje_seleccion);
        cout<<valor_solucion(poblacion[mayor(heuristica)],datos)<<endl;
        while(nueva_poblacion.size()<num_poblacion ){ 
        	int seleccion1= rand() % seleccionados.size();
        	int seleccion2= rand() % seleccionados.size();
        	if(rand() % 100 < prob_cruzamiento*100 ){
        	    hijos=cruzamiento (seleccionados[seleccion1],seleccionados[seleccion2], m);
        	    nueva_poblacion.push_back(hijos[0]); 
        		nueva_poblacion.push_back(hijos[1]); 

        	}       	
        }

        for (int j = 0; j < nueva_poblacion.size(); j++){
            if(rand() % 100 < prob_mutacion*100){
                hijos[0]=crear_vecino(nueva_poblacion[j],n,porcentaje_gen_mutar);   
                nueva_poblacion[j]=hijos[0];
            }
        }
        cout<<"Geracion"<<i+1<<endl;
        int pos_mejor=mayor(heuristica);
        heuristica_nueva=poblacion_heuristica(nueva_poblacion,datos);  
        
        int pos_peor=menor(heuristica_nueva);
        nueva_poblacion[pos_peor]=poblacion[pos_mejor];
        
        poblacion=nueva_poblacion;
        nueva_poblacion.clear();
    }
    heuristica=poblacion_heuristica(poblacion,datos); 
	return poblacion[mayor(heuristica)];
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

   //lectura de los datos
	while(cin >> origen>> destino >> valor) {
		datos[origen][destino]=valor;
	}
	vector <bool>solucion (n);
    //Guardar solucion en archivo csv
	ofstream ficheroSalida;
	ficheroSalida.open ("salida/genetico.csv");
	ficheroSalida << "Tiempo,Solución"<<endl; 
    
    int num_poblacion=100; 
    float porcentaje_seleccion=0.6;
    float prob_cruzamiento=0.75;
    float prob_mutacion=0.28;
    float porcentaje_gen_mutar=0.15;
    int numero_generaciones=100;
 
  
    solucion=genetico(datos,m,n,num_poblacion, porcentaje_seleccion,prob_cruzamiento,prob_mutacion,porcentaje_gen_mutar,numero_generaciones);
	float valorsolucion=valor_solucion(solucion,datos);
	cout<<" Valor de la solucion: "<<valorsolucion<<endl<<endl;

    for (int i = 0; i < solucion.size(); ++i){
     	cout<<solucion[i]<<" ";
     } 
     cout<<endl<<endl;
	ficheroSalida.close();
	return 0;
}

/*int Tm=100; 
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
}*/
