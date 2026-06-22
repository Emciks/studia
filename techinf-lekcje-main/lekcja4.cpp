#include <stdio.h>

#define SIZE 10

void menu() {
    printf("\n1. Print the array.\n2. Calculate the sum of the array.\n3. Calculate the average of the array.\n4. Find the max value of the array.\n5. Find the min value of the array.\n6. Sort the array.\n7. Find the median.\n8. Input your own values.\n9. Exit.\nChoose an option: ");
}

void userInput(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("\narray[%d] = ", i);
        scanf("%d", &array[i]);
    }
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("array[%d] = %d\n", i, *(array + i));
    }
}

int calcSum(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(array + i);
    }
    return sum;
}

float calcAvg(int *array, int size) {
    return (float) calcSum(array, size) / size;
}

void sortArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 1; j <= size - i - 1; j++) {
            if (*(array + j - 1) > *(array + j)) {
                int temp = *(array + j - 1);
                *(array + j - 1) = *(array + j);
                *(array + j) = temp;
            }
        }
    }
}

void medianArray(int *array, int size) {
    sortArray(array, size);
    if (size % 2 == 0) {
        printf("Mediana to %f\n", (float) (*(array + (size / 2) - 1) + *(array + (size / 2))) / 2);
    } else {
        printf("Mediana to array[%d] = %d\n", (size / 2), *(array + (size / 2)));
    }
}

int findMax(int *array, int size) {
    int tempMax = *array;
    for (int i = 0; i < size; i++) {
        if (tempMax < *(array + i)) {
            tempMax = *(array + i);
        }
    }
    return tempMax;
}

int findMin(int *array, int size) {
    int tempMin = *array;
    for (int i = 0; i < size; i++) {
        if (tempMin > *(array + i)) {
            tempMin = *(array + i);
        }
    }
    return tempMin;
}

int main() {
    int numbers[SIZE] = {1, 2, 3, 40, -5, 6, 7, 8, 9, 10};
    int userChoice = 0;

    do {
        menu();
        scanf("%d", &userChoice);
        printf("\n");

        switch (userChoice) {
            case 1:
                printArray(numbers, SIZE);
                break;
            case 2:
                printf("Sum = %d\n", calcSum(numbers, SIZE));
                break;
            case 3:
                printf("Average = %f\n", calcAvg(numbers, SIZE));
                break;
            case 4:
                printf("Max = %d\n", findMax(numbers, SIZE));
                break;
            case 5:
                printf("Min = %d\n", findMin(numbers, SIZE));
                break;
            case 6:
                sortArray(numbers, SIZE);
                printf("Array sorted.\n");
                printArray(numbers, SIZE);
                break;
            case 7:
                medianArray(numbers, SIZE);
                break;
            case 8:
                userInput(numbers, SIZE);
                printf("\nNew array:\n");
                printArray(numbers, SIZE);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (userChoice != 9);

    return 0;
}