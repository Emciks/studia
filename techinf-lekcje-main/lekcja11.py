SIZE = 10

def find_min(arr):
    return min(arr)

def find_max(arr):
    return max(arr)

def average(arr):
    return sum(arr) / len(arr)

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def enter_array(arr, size):
    for i in range(size):
        while True:
            try:
                val = int(input(f"Enter element {i}: "))
                arr[i] = val
                break
            except ValueError:
                print("Błąd: Wprowadź liczbę całkowitą.")

def print_array(arr, size):
    for i in range(size):
        print(f"array[{i}] = {arr[i]}")

def menu():
    print("1. podaj wartosci")
    print("2. wypisz")
    print("3. minimalna")
    print("4. maximum")
    print("5. mediana")
    print("6. Bubble")
    print("0. EXIT")
    print("wybierz opcje:")

def main():
    array = [0] * SIZE
    array_sorted = [0] * SIZE
    option = -1

    print("ARRAY\n")

    while option != 0:
        menu()
       
        try:
            option = int(input())
        except ValueError:
            print("wybierz dobra  opcje1...\n")
            continue

        if option == 0:
            break
        elif option == 1:
            print("wpisywanie\n")
            enter_array(array, SIZE)
        elif option == 2:
            print_array(array, SIZE)
        elif option == 3:
            print("minimume\n")
            print(f"Minimum value: {find_min(array)}\n")
        elif option == 4:
            print("maximume\n")
            print(f"Maximum value: {find_max(array)}\n")
        elif option == 5:
            print("mediana\n")
            print(f"Average value: {average(array):.6f}\n")
        elif option == 6:
            print("Bubble ")
            array_sorted = array.copy()
            bubble_sort(array_sorted)
            print("Array sorted, printing..")
            print_array(array_sorted, SIZE)
        else:
            print("wybierz dobra  opcje1...\n")

    print("koniec")

if __name__ == "__main__":
    main()