#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

     int zakres;
     int number;
     int *tab;
     srand(time(NULL));
     printf("ile liczb: ");
     if(scanf("%d",&number)!=1||number<=0)
     {
           printf("Podaj pprawna wartosc");
           return 1;
     }
     printf("Podaj zakres: ");
     scanf("%d",&zakres);
     tab = (int *)malloc(number*sizeof(int));
     if(tab==NULL){}
     for(int i=0; i<number; i++)
     {
           tab[i]=rand()%zakres;
           printf("tab[%d] = %d\n",i,tab[i]);
     }
     free(tab);
     return 0;
}