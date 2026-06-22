#include <iostream>
#define SIZE 10
int main() {


    int tem1=1;
    int tem2=1;
     int* num1 = &tem1;
     int* num2 = &tem2;

    printf("Prosty kalkulator\n");

    printf("Podaj pierwsza liczbe: ");
    scanf("%d", num1);

    printf("Podaj druga liczbe: ");
    scanf("%d",num2);

    printf("%d + %d = %d\n",*num1,*num2,*num1+*num2);

    printf("%d - %d = %d\n",*num1,*num2,*num1-*num2);

    printf("%d - %d = %d\n",*num2,*num1,*num2-*num1);

    printf("%d * %d = %d\n",*num1,*num2,(*num1)*(*num2));
    float div1 = (float) (*num1)/(*num2);
    float div2 = (float) (*num2)/(*num1);
    if(num2!=0)
    {
          printf("%d / %d = %f\n",*num1,*num2,div1);
    }

    if(num1!=0)
    {
          printf("%d / %d = %f\n",*num2,*num1,div2);
    }

     int num[SIZE]={0,0,0,0,0,0,0,0,0,0};
     for(int i=0; i<SIZE; i++)
     {
           printf("Podaj %d liczbe do tablicy:\n ", i+1);
           scanf("%d", &*(num+i));

     }
     for(int i=0; i<SIZE; i++)
     {
           printf("num[%d]=%d\n",i,*(num+i));

     }
     int min = *(num+0);
     int max = *(num+0);
     int sum2 = 0;

     for (int i=0; i<SIZE; i++)
     {
           if(*(num+i)<min)
           {
                 min = *(num+i);
           }
           sum2=sum2+*(num+i);
     }
     for (int i=0; i<SIZE; i++)
     {
           if (*(num+i) > max)
           {
                 max = *(num+i);
           }
     }

     printf("Tablica posegregowana malejaco:\n");
     for (int i = 0; i < SIZE; i++)
     {

           for (int j = 0; j < SIZE-1; j++)
           {
                 if (*(num+j) > *(num+j + 1))
                 {
                       int temp = *(num+j);
                       *(num+j) = *(num+j + 1);
                       *(num+j + 1) = temp;
                 }
           }

     }
     for(int i=0; i<SIZE; i++)
     {
           printf("num[%d]=%d\n",i,*(num+i));

     }

     float avg = (float) sum2/ SIZE;
     float med = (float) (*(num+4)+*(num+5))/2;
     printf("min = %d\n", min);
     printf("max = %d\n", max);
     printf("sum2 = %d\n", sum2);
     printf("avg = %f\n", avg);
     printf("med = %f\n", med);

     return 0;
}