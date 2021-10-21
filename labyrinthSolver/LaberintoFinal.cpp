#include<iostream>
using namespace std;

// Esta funcion recibe el ultimo movimiento que ha hecho y devuelve a la posicion que tenia antes de moverse
void recular(int* x, int* y, int movimiento){
	if(movimiento == 1){
		*x = *x+1;
	}else if(movimiento == 2){
		*y = *y-1;
	}
	else if(movimiento == 3){
		*x = *x-1;
	}
	else if(movimiento == 4){
		*y = *y+1;
	}
}

void recorrerLaberinto(char laberinto[10][10], int* x, int* y, bool* end, int* finalX, int* finalY, int movimiento){
	//Estas funciones con lados comprueban que el laberinto pueda moverse por esos lados, que haya un punto o el tesoro, y que el movimiento anterior no haya sido el inverso para no entrar en bucle
	// En caaso de que este el tesoro pon una x en su posicion, dice el bucle se ha acabado (end =true) recula a la posicion anterior y termina la funcion, por lo que de ahi en adelante el programa solo pone X y "recula"
	// En caso de que aun no este delante del tesoro, solo se llama asi misma para poder seguir recorriendo el bucle
	
	//Arriba
	if(*end == false && *x-1 > 0 && (laberinto[*x-1][*y] == '.' || laberinto[*x-1][*y] == 'T') && movimiento !=3){
		if(laberinto[*x-1][*y] == 'T'){
			
			laberinto[*x][*y] = 'X';
			*finalX= *x-1;
			*finalY = *y;
			*end = true;
			recular(x,y, movimiento);
			return;
		}else{
			*x = *x-1;
			recorrerLaberinto(laberinto,x,y, end, finalX, finalY, 1);
			if(*end ==false){
				*x = *x+1;
			}else{
				laberinto[*x][*y] = 'X';
				recular(x,y, movimiento);
				return;
			}
		}
	}
	//Derecha
	if(*end == false && (*y+1 < 10 )&& (laberinto[*x][*y+1] == '.' || laberinto[*x][*y+1] == 'T') && movimiento !=4){
		if(laberinto[*x][*y+1] == 'T'){
			laberinto[*x][*y] = 'X';
			*finalX= *x;
			*finalY = *y+1;
			*end = true;
			recular(x,y, movimiento);
			return;
		}else{
			*y = *y+1;
			recorrerLaberinto(laberinto,x,y, end, finalX, finalY, 2);
			if(*end ==false){
				*y = *y-1;
			}else{
				laberinto[*x][*y] = 'X';
				recular(x,y, movimiento);
				return;
			}
		}
	}
	//Abajo
	if(*end == false && *x+1 < 10 && (laberinto[*x+1][*y] == '.' || laberinto[*x+1][*y] == 'T' ) && movimiento !=1){
		if(laberinto[*x+1][*y] == 'T'){
			
			laberinto[*x][*y] = 'X';
			*finalX= *x+1;
			*finalY = *y;
			*end = true;
			recular(x,y, movimiento);
			return;
		}else{
			*x = *x+1;
			recorrerLaberinto(laberinto,x,y, end, finalX, finalY, 3);
			if(*end ==false){
				*x = *x-1;
			}else{
				laberinto[*x][*y] = 'X';
				recular(x,y, movimiento);
				return;
			}
			
		}
	}
	//Izquierda
	if(*end == false && (*y-1 >= 0 )&& (laberinto[*x][*y-1] == '.' || laberinto[*x][*y-1] == 'T') && movimiento !=2){
		if(laberinto[*x][*y-1] == 'T'){
			
			laberinto[*x][*y] = 'X';
			*finalX= *x;
			*finalY = *y-1;
			*end = true;
			recular(x,y, movimiento);
			return;
		}else{
			*y = *y-1;
			recorrerLaberinto(laberinto,x,y, end, finalX, finalY, 4);
			if(*end ==false){
				*y = *y+1;
			}else{
				laberinto[*x][*y] = 'X';
				recular(x,y, movimiento);
				return;
			}
		}
	}
}



int main(){
	char laberinto[10][10];
	bool final = false;
	bool *end = &final;
	int x = 0;
	int y = 0;
	int* puntX = &x;
	int* puntY = &y;
	for(int i =0; i < 10; i ++){
		for(int j =0; j < 10; j++){
			cin>>laberinto[i][j];
		}
	}
	printf("\n\n\n");
	int finalX, finalY;
	int *endX = &finalX;
	int *endY = &finalY;
	recorrerLaberinto(laberinto, puntX, puntY, end, endX, endY, 0);


	if(*end == true){
		for(int i =0; i < 10; i ++){
			for(int j =0; j < 10; j++){
				cout<<laberinto[i][j];
			}
			cout<<"\n";
		}
		cout<< "ENCONTRADO "<< finalX << " " << finalY <<endl;
	}else{
		cout<<"INALCANZABLE"<<endl;
	}
}
/*
..********
*.*......*
*.*.****.*
*.*.*..*.*
*.*.*T.*.*
*.*.**.*.*
*.*....*.*
*.******.*
*........*
**********
*/