#include "ABB.h"
#include "assertdomjudge.h"
#include "iostream"

using namespace std;

ABB :: ABB(){
  this->raiz = NULL;
  this->n = 0; 
}
ABB :: ~ABB(){

}
void ABB :: insertar (int nuevoElemento){
  if(this->raiz == NULL){
    this->raiz = new Nodo();
    this->raiz->contenido = nuevoElemento;
  }else{
    Nodo* aux = this->buscarHueco(this->raiz, nuevoElemento);
    if(aux->contenido > nuevoElemento){
      aux->hijoIzquierdo = new Nodo();
      aux->hijoIzquierdo->contenido = nuevoElemento;
      aux->hijoIzquierdo->padre = aux;
      aux->hijoIzquierdo->hijoIzquierdo = NULL;
      aux->hijoIzquierdo->hijoDerecho = NULL;
    }else{
      aux->hijoDerecho = new Nodo();
      aux->hijoDerecho->contenido = nuevoElemento;
      aux->hijoDerecho->padre = aux;
      aux->hijoDerecho->hijoIzquierdo = NULL;
      aux->hijoDerecho->hijoDerecho = NULL;
    }    
  }
 
  this->n++;
}

Nodo* ABB :: buscar(int elementoABuscar){
  return buscarRecursivo(this->raiz, elementoABuscar);
}
void ABB :: eliminar (int elementoAEliminar){
  Nodo* aux = this->buscar(elementoAEliminar);
  if(aux == NULL){
    printf("ERROR\n");
  }else{
    this->eliminarNodo(aux);
  }
}
bool ABB :: esABB(){
  return this->esSubABB(this->raiz);
}
bool ABB :: esAVL(){

 if(esSubABBAvl(raiz) && esSubAVL(raiz)){
    return true;
  }
  return false;
}

bool ABB :: esSubABBAvl(Nodo *raizSubarbol){
  bool retorno = true;
  if(raizSubarbol == NULL){
    return retorno;
  }
  if(raizSubarbol->hijoIzquierdo!=NULL){
    if(raizSubarbol->hijoIzquierdo->contenido > raizSubarbol->contenido){
      return false;
    }else{
      retorno = esSubABBAvl(raizSubarbol->hijoIzquierdo);
    }
  }
  if(raizSubarbol->hijoDerecho!=NULL){
    if(raizSubarbol->hijoDerecho->contenido < raizSubarbol->contenido){
      return false;
    }else{
      retorno = esSubABBAvl(raizSubarbol->hijoDerecho);
    }  
  }
  return retorno;
}

bool ABB :: esSubABB(Nodo *raizSubarbol){

  if (raizSubarbol == NULL){
    return true;
  }
  Nodo* maxIzquierda;
  Nodo* minDerecha;
  if(raizSubarbol->hijoIzquierdo){
    maxIzquierda = buscarMaximo(raizSubarbol->hijoIzquierdo);
  }else{
    maxIzquierda = raizSubarbol;
  }
  if(raizSubarbol->hijoDerecho){
    minDerecha = buscarMinimo(raizSubarbol->hijoDerecho);
  }else{
    minDerecha = raizSubarbol;
  }
  if (maxIzquierda->contenido > raizSubarbol->contenido || minDerecha->contenido < raizSubarbol->contenido){
    return false;
  }
  
  if (esSubABB(raizSubarbol->hijoIzquierdo) && esSubABB(raizSubarbol->hijoDerecho)){
    return true;
  }
  return false;
}

bool ABB :: esSubAVL(Nodo *raizSubarbol){
  if(raizSubarbol == NULL){
    return true;
  }
  if ((maxAltura(raizSubarbol) - minAltura(raizSubarbol)) > 1) {
    return false;
  }
  if (!esSubAVL(raizSubarbol->hijoIzquierdo) || !esSubAVL(raizSubarbol->hijoDerecho)) {
    return false;
  }

  return true;
}

int ABB :: maxAltura(Nodo *raizSubarbol){
  if(raizSubarbol == NULL){
    return 0;
  }  
  if(raizSubarbol->hijoIzquierdo == NULL && raizSubarbol->hijoDerecho == NULL){
    return 1;
  }
  int izquierdo = 0;
  int derecha = 0;
  if(raizSubarbol->hijoIzquierdo != NULL){
    izquierdo = maxAltura(raizSubarbol->hijoIzquierdo);
  }
  if(raizSubarbol->hijoDerecho != NULL){
    derecha = maxAltura(raizSubarbol->hijoDerecho);
  }

  return (1 + max(izquierdo,derecha));
}
int ABB :: minAltura(Nodo *raizSubarbol){
  if(raizSubarbol == NULL){
    return 0;
  }  
  if(raizSubarbol->hijoIzquierdo == NULL || raizSubarbol->hijoDerecho == NULL){
    return 1;
  }
  int izquierdo = 0;
  int derecha = 0;
  if(raizSubarbol->hijoIzquierdo != NULL){
    izquierdo = minAltura(raizSubarbol->hijoIzquierdo);
  }
  if(raizSubarbol->hijoDerecho != NULL){
    derecha = minAltura(raizSubarbol->hijoDerecho);
  }
  return (1 + min(izquierdo,derecha) );
}


//Si el nodo sólo tiene un hijo izquierdo, se deberá buscar el máximo elemento del subárbol cuyo padre 
//es el hijo izquierdo, para ello se utilizará el método interno buscarMaximo.
Nodo* ABB :: buscarMaximo (Nodo *raizSubarbol){
  if(raizSubarbol->hijoDerecho == NULL){
    return raizSubarbol;
  }else{
    return buscarMaximo(raizSubarbol->hijoDerecho);
  }
}
// Si el nodo sólo tiene un hijo derecho, se deberá buscar el mínimo elemento del subárbol cuyo padre 
//es el hijo derecho, para ello se utilizará el método interno buscarMinimo.

Nodo* ABB :: buscarMinimo (Nodo *raizSubarbol){
  if(raizSubarbol->hijoIzquierdo == NULL){
    return raizSubarbol;
  }else{
    return this->buscarMaximo(raizSubarbol->hijoIzquierdo);
  }
}

void ABB :: eliminarNodo (Nodo *nodoParaEliminar){
  Nodo* aux = new Nodo;
  //Primero comprueba si el el nodo que va a eliminar es una hoja final
  if(nodoParaEliminar->hijoIzquierdo == NULL && nodoParaEliminar->hijoDerecho == NULL){
    aux = this->buscarRecursivo(nodoParaEliminar, nodoParaEliminar->contenido);
    if(nodoParaEliminar->padre == NULL){
      this->raiz = NULL;
    }else if(nodoParaEliminar->padre->hijoIzquierdo != NULL && nodoParaEliminar->padre->hijoIzquierdo->contenido == nodoParaEliminar->contenido){
      nodoParaEliminar->padre->hijoIzquierdo =NULL;
    }else if(nodoParaEliminar->padre->hijoDerecho != NULL && nodoParaEliminar->padre->hijoDerecho->contenido == nodoParaEliminar->contenido){
      nodoParaEliminar->padre->hijoDerecho =NULL;
    }
    this->n--;
  }else if(nodoParaEliminar->hijoIzquierdo != NULL && nodoParaEliminar->hijoDerecho == NULL){ 
    aux = this->buscarMaximo(nodoParaEliminar->hijoIzquierdo);
    if(aux->hijoIzquierdo != NULL){
      nodoParaEliminar->contenido = aux->contenido;
      aux = nodoParaEliminar->hijoIzquierdo;
      this->eliminarNodo(aux);
    }else{ 
      nodoParaEliminar->contenido = aux->contenido;
      nodoParaEliminar->hijoIzquierdo = NULL;
      this->n--;
    }
  }else if(nodoParaEliminar->hijoDerecho != NULL && nodoParaEliminar->hijoIzquierdo == NULL){
    aux = this->buscarMinimo(nodoParaEliminar->hijoDerecho);
    if(aux->hijoDerecho != NULL){
      nodoParaEliminar->contenido = aux->contenido;
      aux = nodoParaEliminar->hijoDerecho;
      this->eliminarNodo(aux);
    }else{
      if(aux->contenido < aux->padre->contenido){
        aux->hijoDerecho = aux->padre;
        aux->hijoDerecho->hijoIzquierdo = NULL;
        nodoParaEliminar->contenido = aux->contenido;
      }else{
        nodoParaEliminar->contenido = aux->contenido;
        nodoParaEliminar->hijoDerecho = NULL;
        this->n--;
      }  
    }
    
  }else if(nodoParaEliminar->hijoDerecho != NULL && nodoParaEliminar->hijoIzquierdo != NULL){ 
    if(this->alturaNodo(this->buscarMaximo(nodoParaEliminar)) > this->alturaNodo(this->buscarMinimo(nodoParaEliminar)) ){

      aux = this->buscarMinimo(nodoParaEliminar->hijoDerecho);
      if(aux->hijoDerecho != NULL){
        nodoParaEliminar->contenido = aux->contenido;
        aux = this->buscarRecursivo(nodoParaEliminar->hijoDerecho, nodoParaEliminar->contenido);
        this->eliminarNodo(aux);
      }else{
        nodoParaEliminar->contenido = aux->contenido;
        nodoParaEliminar->hijoDerecho = NULL;
        this->n--;
      }
    }else{
      aux = this->buscarMinimo(nodoParaEliminar->hijoIzquierdo);
      if(aux->hijoIzquierdo != NULL){
        nodoParaEliminar->contenido = aux->contenido;
        aux = this->buscarRecursivo(nodoParaEliminar->hijoIzquierdo, nodoParaEliminar->contenido);
        this->eliminarNodo(aux);
      }else{
        nodoParaEliminar->contenido = aux->contenido;
        nodoParaEliminar->hijoIzquierdo = NULL;
        this->n--;
      }
    }     
  }
}


int ABB :: alturaNodo(Nodo *raizSubarbol){


  Nodo* aux = raizSubarbol;
  int altura = 0;
  
  if(aux == NULL){
    return 0;
  }
  while(aux->padre != NULL){
    aux = aux->padre;
    altura++;
  }
  return altura;
}

Nodo* ABB :: buscarHueco(Nodo *raizSubarbol, int elementoAInsertar){
  if(raizSubarbol == NULL || raizSubarbol->hijoIzquierdo == NULL && raizSubarbol->hijoDerecho == NULL){
    return raizSubarbol;
  }else{
    if(raizSubarbol->contenido < elementoAInsertar){
      if(raizSubarbol->hijoDerecho == NULL){
        return raizSubarbol;
      }else{
        return buscarHueco(raizSubarbol->hijoDerecho, elementoAInsertar);
      }
      
    }else{
      if(raizSubarbol->hijoIzquierdo == NULL){
        return raizSubarbol;
      }else{
        return buscarHueco(raizSubarbol->hijoIzquierdo, elementoAInsertar);
      }
    }
  }  
}

Nodo* ABB :: buscarRecursivo (Nodo *raizSubarbol, int elementoABuscar){
    if(!raizSubarbol){
      return NULL;
    }
    if(raizSubarbol->contenido ==elementoABuscar){
      return raizSubarbol;
    }else if(raizSubarbol->contenido > elementoABuscar){

      return buscarRecursivo(raizSubarbol->hijoIzquierdo,elementoABuscar);
    }else if(raizSubarbol->contenido < elementoABuscar){

     return buscarRecursivo(raizSubarbol->hijoDerecho,elementoABuscar);   
    }
    return NULL;
}

void ABB::imprimir()
{
  if(raiz==NULL)
    cout<<"VACIO"<<endl;
  else   
      imprimirRecorrido(raiz);    
}

void ABB::imprimirRecorrido(Nodo *raizSubarbol)
{
  cout<<raizSubarbol->contenido<<endl;
  if(raizSubarbol->hijoIzquierdo!=NULL)
    {
      cout<<"I";
      imprimirRecorrido(raizSubarbol->hijoIzquierdo);
      cout<<endl;
    }
  if(raizSubarbol->hijoDerecho!=NULL)
    {
      cout<<"D";
      imprimirRecorrido(raizSubarbol->hijoDerecho);
      cout<<endl;
    }
}

void ABB::leerArbol()
{
  raiz=leerSubarbol(NULL);
}

Nodo * ABB::leerSubarbol(Nodo *padre)
{
  int contenido;
  cin>>contenido;
  if(contenido>=0)
    {
      Nodo *arbol=new Nodo;
      arbol->contenido=contenido;
      arbol->hijoIzquierdo=leerSubarbol(arbol);
      arbol->hijoDerecho=leerSubarbol(arbol);
      arbol->padre=padre;
      return arbol;
    }
  else
    {
      return NULL;
    }
}


