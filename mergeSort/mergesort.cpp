#include<iostream>
using namespace std;

void  combinar (int a[ ] , int len_a,  int b[ ] , int len_b , int c[ ]){
  /*Añadir código que permite combinar dos arrays */
  int aux =0;
  int aSeleccionadas = 0;
  int bSeleccionadas = 0;
  //Hacemos las distintas comparaciones para ver que numero es el que ocupa el primer lugar en la nueva combinacion
  for(int i = 0; i < len_a + len_b; i++){
    if(aSeleccionadas == len_a){  //Comprobamos que queden datos sin coger en el array a
      c[i] = b[bSeleccionadas];
      bSeleccionadas++;
    }else if(bSeleccionadas == len_b){  ////Comprobamos que queden datos sin coger en el array b
      c[i] = a[aSeleccionadas];
      aSeleccionadas++;
    }
    else if(a[aSeleccionadas] < b[bSeleccionadas]){ //Comprobamos si el valor de a es mayor que el de b
      c[i] = a[aSeleccionadas];
      aSeleccionadas++;
    }else if(a[aSeleccionadas] >= b[bSeleccionadas]){ //Comprobamos si el valor de b es mayor que el de a
      c[i] = b[bSeleccionadas];
      bSeleccionadas++; 
    }
  }
}


void ordenarMergeSort (int x[],int left, int right){
  int temp[(left+right)];
  if(right <= left){/*caso básico */
    return;
  } 
  else{
    /*Ordenar dos mitades */
    //Se se paran hasta quedar en parejas de forma recursiva, para que ir sacando los valores
    int mid = (left+right-1)/2;
    ordenarMergeSort(x, left, mid);
    ordenarMergeSort(x, mid+1, right);
    //Medimos los tamanos que van a tener las mitades
    int len_1 = mid-left+1;
    if(mid == left){
      len_1 = 1;
    }
    int len_2 = right-mid;
    int com1[len_1];
    int com2[len_2];
    int i = left-1;
    int posArray = 0;
    //Rellenamos los valores de las mitades que le vamos a pasar a la funcion
    do{
      com1[posArray] = x[i];
      posArray++;
      i++;
    }while(i < mid);
    posArray = 0;
    do{
      com2[posArray] = x[i];
      posArray++;
      i++;
    }while(i < right);
    /*Combinar ambas mitades y guardarlo en temp */
    combinar(com1, len_1, com2, len_2, temp);
    /*Copiar del array temporal al array resultado */
    int j = 0;
    //Vamos actualizando el valor de k en las posiciones que se han combinado, para que luego sean accesibles para la propia funcion ordenarMergeSort pero con una recursividad menos
    for (int k = left-1; k < right ; k++){
  	  x[k] = temp[j];
  	  cout<<x[k]<<" ";
      j++;
  	}
    cout<<endl;
  }
}

int main()
{
  int n;
  cin>>n;
  int *x=new int[n];
  for(int i=0;i<n;i++){
    cin>>x[i];
  }
  ordenarMergeSort(x,1,n);
}
