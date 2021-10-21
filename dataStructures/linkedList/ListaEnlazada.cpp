#include"ListaEnlazada.h"
#include<iostream>
using namespace std;
ListaEnlazada :: ListaEnlazada(){
	this->n = 0;
	this->lista = NULL;
}

void ListaEnlazada::~ListaEnlazada(){
	for(int i =n; i > 0; i++){
		free(this->getNodo(i));
	}
}

Nodo* ListaEnlazada :: getNodo (int posicion){
	Nodo* aux = new Nodo;
	aux = this->lista;
	while(posicion > 0){
		aux = aux->siguienteNodo;
		posicion--;
	}
	return aux;
}

int ListaEnlazada :: getValor(int pos){
	if(n > pos){
		return this->getNodo(pos)->elemento;
	}else{
		cout<<"ERROR"<<endl;
		exit(0);
	}
}

void ListaEnlazada :: setValor(int pos, int val){
	if(n > pos){
		this->getNodo(pos)->elemento = val;
	}else{
		cout<<"ERROR"<<endl;
		exit(0);
	}
}

int ListaEnlazada :: getN(){
	return this->n;
}

void ListaEnlazada :: insertar(int pos, int val){
	if(pos <= n && pos >= 0){
		this->n++;
		Nodo* insertado = new Nodo;
		insertado->elemento = val;
		insertado->siguienteNodo = NULL;
		if(pos == 0){
			insertado->siguienteNodo = this->lista;
			this->lista = insertado;
		}else if(pos == this->n-1){
			Nodo* aux = this->getNodo(pos-1)->siguienteNodo;
			this->getNodo(pos-1)->siguienteNodo = insertado;
			this->getNodo(pos)->siguienteNodo = aux;
			free(aux);

		}else{
			this->getNodo(n)->siguienteNodo = insertado;
		}
	}else{
		cout<<"ERROR"<<endl;
		exit(0);
	}
	
}
void ListaEnlazada :: eliminar(int pos){
	if(pos < n && pos >= 0){
		n--;
		if(pos == 0){
			this->lista = this->getNodo(pos)->siguienteNodo;
		}else if(pos == this->n){
			this->getNodo(pos)->siguienteNodo=NULL;
		}else{
			this->getNodo(pos-1)->siguienteNodo = this->getNodo(pos+1);
		}
	}else{
		cout<<"ERROR"<<endl;
		exit(0);
	}
}

void ListaEnlazada :: concatenar(ListaEnlazada *lista){
	
	int x = n;
	for(int i =0; i < lista->n; i++){
		this->insertar(x+i,lista->getNodo(i)->elemento);
	}
	
}

int ListaEnlazada :: buscar(int num){
	int retorno = -1;
	Nodo* aux = this->lista;
	for(int i =0; i < n; i++){
		if(aux->elemento == num){
			retorno = i;
			break;
		}
		aux = aux->siguienteNodo;
	}
	return retorno;
}