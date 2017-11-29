#include "funciones.cpp"

vector <bool> genetico( map<int, map<int,float> > datos,int m, int n,int num_poblacion,float porcentaje_seleccion,float prob_cruzamiento, float prob_mutacion, float porcentaje_gen_mutar,int numero_generaciones){
	vector <bool> solucion;
	vector < vector <bool>  > poblacion,seleccionados,nueva_poblacion,hijos(2);
    vector<float> heuristica,heuristica_nueva;

    poblacion=poblacion_inicial(m,n,num_poblacion);
    heuristica=poblacion_heuristica(poblacion,datos);
    cout<<"Nueva ejecución"<<endl; 
    for (int i = 0; i < numero_generaciones; i++){
        heuristica=poblacion_heuristica(poblacion,datos); 	
        seleccionados=torneo(poblacion,heuristica,porcentaje_seleccion);
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


    //numero de poblacion 
    int num_poblacion[]={100,150,300};
    //porcentaje de poblacion
    float porcentaje_seleccion[]={0.6,0.7,0.8};
    //probabilidad de cruzamiento
    float prob_cruzamiento[]={0.6,0.7,0.8};
    //probabilidad de mutacion
    float prob_mutacion[]={0.1,0.2,0.3};
    //porcentajes de genes a mutar
    float porcentaje_gen_mutar[]={0.1,0.15,0.20};
    //porcentaje de elementos a modificar para determinar un vecino
    int numero_generaciones[] = {200,500,1000};
    

    for (int i = 0; i < sizeof(num_poblacion)/sizeof(num_poblacion[0]); i++){
     
     for (int j = 0; j < sizeof(porcentaje_seleccion)/sizeof(porcentaje_seleccion[0]); j++){
        
        for (int k = 0; k < sizeof(prob_cruzamiento)/sizeof(prob_cruzamiento[0]); k++){
            
            for (int l = 0; l < sizeof(prob_mutacion)/sizeof(prob_mutacion[0]); l++){
                
                for (int p = 0; p < sizeof(porcentaje_gen_mutar)/sizeof(porcentaje_gen_mutar[0]); p++){
                
                    for (int q = 0; q < sizeof(numero_generaciones)/sizeof(numero_generaciones[0]); q++){
                      
                        for (int o = 0; o<5; o++){
                           
                            cout<<"Parametros : ( "<<num_poblacion[i]<<" , "<<porcentaje_seleccion[j]<<" , "<<prob_cruzamiento[k]<<" , "<<prob_mutacion[l]<<" , "<<porcentaje_gen_mutar[p]<<" , "<<numero_generaciones[q]<<" ) ";

                            //obtener el tiempo de ejecucion del algoritmo
                            gettimeofday(&t_ini, NULL);
                            solucion=genetico(datos,m,n,num_poblacion[i], porcentaje_seleccion[j],prob_cruzamiento[k],prob_mutacion[l],porcentaje_gen_mutar[p],numero_generaciones[q]);
                            gettimeofday(&t_fin, NULL); secs = timeval_diff(&t_fin, &t_ini);

                            //obtener y guardar los resultados
                            float valorsolucion=valor_solucion(solucion,datos);
                            cout<<endl;cout<<"Tiempo: "<<secs<<" Valor de la solucion: "<<valorsolucion;
                            ficheroSalida <<secs<<","<<valorsolucion<<endl; 
                            cout<<endl;cout<<endl;

                        }
                    }
                }
            }
        }            
    }
}
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
