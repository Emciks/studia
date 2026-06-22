#include <iostream>
#include <stdio.h>

#define SIZE 10

void printarray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("num[%d]=%d\n", i, *(array + i));
    }
}

int calculatemin(int *array, int size) {
    int min = *array;
    for (int i = 1; i < size; i++) {
        if (*(array + i) < min) {
            min = *(array + i);
        }
    }
    return min;
}

int calculatemax(int *array, int size) {
    int max = *array;
    for (int i = 1; i < size; i++) {
        if (*(array + i) > max) {
            max = *(array + i);
        }
    }
    return max;
}

int calculatesum(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(array + i);
    }
    return sum;
}

float calculateavg(int *array, int size) {
    return (float)calculatesum(array, size) / size;
}

void segregacja(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (*(array + j) < *(array + j + 1)) {
                int temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
            }
        }
    }
}

float calculatemedian(int *array, int size) {
    segregacja(array, size);
    if (size % 2 == 0) {
        return (float)(*(array + (size / 2) - 1) + *(array + (size / 2))) / 2.0;
    } else {
        return (float)*(array + (size / 2));
    }
}

void prostyKalkulator() {
    int tem1 = 0, tem2 = 0;
    int *num1 = &tem1;
    int *num2 = &tem2;

    printf("\n--- Prosty kalkulator ---\n");
    printf("Podaj pierwsza liczbe: ");
    scanf("%d", num1);
    printf("Podaj druga liczbe: ");
    scanf("%d", num2);

    printf("%d + %d = %d\n", *num1, *num2, *num1 + *num2);
    printf("%d - %d = %d\n", *num1, *num2, *num1 - *num2);
    printf("%d - %d = %d\n", *num2, *num1, *num2 - *num1);
    printf("%d * %d = %d\n", *num1, *num2, (*num1) * (*num2));

    if (*num2 != 0) {
        printf("%d / %d = %f\n", *num1, *num2, (float)*num1 / *num2);
    } else {
        printf("Nie mozna dzielic przez zero (%d / %d)\n", *num1, *num2);
    }

    if (*num1 != 0) {
        printf("%d / %d = %f\n", *num2, *num1, (float)*num2 / *num1);
    } else {
        printf("Nie mozna dzielic przez zero (%d / %d)\n", *num2, *num1);
    }
}


int main() {
    int num[SIZE];
    int choice;

    printf("uzupelnij tablice %d liczbami:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("Podaj %d liczbe: ", i + 1);
        scanf("%d", &num[i]);
    }

    do {
        printf("\n======= MENU =======\n");
        printf("1. Wyswietl tablice\n");
        printf("2. Sortuj tablice malejaco\n");
        printf("3. Statystyki (Min, Max, Suma, Srednia)\n");
        printf("4. Oblicz mediane\n");
        printf("5. URUCHOM PROSTY KALKULATOR\n");
        printf("0. Wyjscie\n");
        printf("Wybor: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printarray(num, SIZE);
                break;
            case 2:
                segregacja(num, SIZE);
                printf("Tablica zostala posortowana.\n");
                break;
            case 3:
                printf("Min: %d | Max: %d\n", calculatemin(num, SIZE), calculatemax(num, SIZE));
                printf("Suma: %d | Srednia: %.2f\n", calculatesum(num, SIZE), calculateavg(num, SIZE));
                break;
            case 4:
                printf("Mediana wynosi: %.2f\n", calculatemedian(num, SIZE));
                break;
            case 5:
                prostyKalkulator();
                break;
            case 0:
                printf("Zamykanie programu...\n");
                break;
            default:
                printf("Niepoprawny wybor!\n");
        }
    } while (choice != 0);

    return 0;
}