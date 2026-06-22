#include <iostream>
#define SIZE 10
int main() {

    int num[SIZE]={0,0,0,0,0,0,0,0,0,0};
    for(int i=0; i<10; i++)
    {
        printf("Podaj %d liczbe:\n ", i+1);
        scanf("%d", &num[i]);

    }
    for(int i=0; i<10; i++)
    {
        printf("num[%d]=%d\n",i,num[i]);

    }
    printf("Tablica posegregowana malejaco:\n");
    for (int i = 0; i < SIZE; i++)
    {
        int temp = 0;
        for (int j = 0; j < SIZE; j++)
        {
            if (num[j] > num[j + 1])
            {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
        printf("%d\n",temp);
    }

    int min = num[0];
    int max = num[0];
    int sum2 = 0;

    for (int i=0; i<SIZE; i++)
    {
        if(num[i]<min)
        {
            min = num[i];
        }
        if(num[i]>max)
        {
            max = num[i];
        }
        sum2=sum2+num[i];
    }

    float avg = (float) sum2/ SIZE;
    float med = (float) (num[4]+num[5])/2;
    printf("min = %d\n", min);
    printf("max = %d\n", max);
    printf("sum2 = %d\n", sum2);
    printf("avg = %f\n", avg);
    printf("med = %f\n", med);
    return 0;
}