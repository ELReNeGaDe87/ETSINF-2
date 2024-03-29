//Programa SumaSequencial.c
//Per a compilar teclegeu:
// gcc SumaSequencial.c -o SumaSeq -lm
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

#define DIMFILERA 1000000
#define NUMFILERES 20

typedef struct filera{
        int vector[DIMFILERA];
        long suma;
} filera;

filera matriu[NUMFILERES];

void *SumaFilera( void *ptr )
 {
   int k;
   filera *fi;
   fi=(filera *)  ptr;

   fi->suma=0;
   for(k=0;k<DIMFILERA;k++) {
     fi->suma += exp((k*(fi->vector[k])
                     +(k+1)*(fi->vector[k]))/(fi->vector[k]+2*k))/2;
   }
 }

int main()
{
  int i,j;
  long suma_total=0;
  pthread_t  fils[NUMFILERES];
  pthread_attr_t atrib;
  //s'inicialitzen a 1 tots els elements de tots els vectors
  for(i=0;i<NUMFILERES;i++) {
      for(j=0;j<DIMFILERA;j++) {
         matriu[i].vector[j]=1;
      }
  }
  //Iniciació dels atributs de fil
  //Estos atributos se pueden usar en los hilos creen
  pthread_attr_init( &atrib );
  //pthread_attr_setscope(&atrib, PTHREAD_SCOPE_SYSTEM);

int numcores = 4;//system("<< grep processor /proc/cpuinfo | wc -l");
int fila = 0;

 //EJERCICIO2.a
	for(int z=0;z<NUMFILERES; z += numcores){

		for(i=0; i < numcores; i++){
			pthread_create( &fils[i], &atrib, SumaFilera, &matriu[fila]);
			fila++;
		}
		
		for(j=0; j < numcores; j++){
			pthread_join(fils[j], NULL); 
		}
		
	}
 
 //EJERCICIO2.b

 for(i = 0; i < NUMFILERES; i++) suma_total += matriu[i].suma;
 printf(  "La suma val %ld\n",suma_total);

}

