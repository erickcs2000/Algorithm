#include<stdio.h>
#include <stdlib.h>
 
void Quicksort(int lista[], int limit_izq, int limit_der){
	int izq = limit_izq;
	int der = limit_der;
	int Aux;
	int Pos = lista[((limit_der + limit_izq)/2)];
	
	do{
		while(lista[izq] < Pos && izq < limit_der){	//Recorre la lista hasta encontar un numero menor a pos
			izq++;
		}
		while(lista[der] > Pos && der > limit_izq){	//Recorrela lista hasta encontarr un numero mayor a pos
			der--;
		}
		if (izq <= der){	// como no ponemos como limite la posicion central el array recorrera todas las posiciones
			Aux = lista[der];
			lista[der] = lista[izq];
			lista[izq] = Aux;
			der--;
			izq++;
		}
		
	}while(izq <= der);
	
	//Hacemos que la funcion se llame a si misma mientras que no recorra todos los numeros
	
	if(der > limit_izq){
		Quicksort(lista,limit_izq,der);
	}
	if( izq < limit_der){
		Quicksort(lista,izq,limit_der);
	}
}



int main(){
	int lista[] = {1,-20,5,7,-3,6,-32,100,50};
	int size = sizeof(lista)/sizeof(int);
	printf("Lista desordenada");
	
	for (int i = 0; i < size; i++){
			printf("%d",lista[i]);
			
			if(i < size-1){
				printf(",");
			}
			
	}
	printf("\nLista ordenada");
	int aux = 0;
	Quicksort(lista, 0, size-1);
	for (int i = 0; i < size; i++){
			printf("%d",lista[i]);
			
			if(i < size-1){
				printf(",");
			}
			
	}

}
