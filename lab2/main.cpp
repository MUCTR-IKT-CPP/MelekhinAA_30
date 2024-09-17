// Лаба: https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab2.md
#include <iostream>
#include <iomanip> 
#include <cstdlib> 
#include <ctime>    

using namespace std;

/*
 * Получение числа от пользователя.
 *
 * @return введённое пользователем число.
 */
int getNumber(){
    int n;
    cout << "Введите число: ";
    cin >> n;
    return n;
}

/*
 * Заполняет все элементы двумерного массива значением 0.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void clearArray(int** array, const int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            array[i][j] = 0;     
        }
    }
}

/*
 * Выделяет память для двумерного массива размером N x N.
 *
 * @param N размер массива (количество строк и столбцов).
 * @return указатель на созданный двумерный массив.
 */
int** createArray(const int N) {
    int** array = new int*[N];   
    for (int i = 0; i < N; i++) {
        array[i] = new int[N];   
    }
    clearArray(array, N);
    return array;
}

/*
 * Вывод двумерного массива на экран.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void printArray(int** array, const int N) {
    cout << "\nМассив:" << endl;
    const int WIDTH = 2; 

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "|" << setw(WIDTH) << array[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

/*
 * Освобождает память, выделенную для двумерного массива.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void deleteArray(int** array, const int N) {
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    }
    delete[] array;
}

/*
 * Заполняет массив случайными значениями таким образом, чтобы он был симметричен относительно главной диагонали.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void fillMain(int** array, const int N) {
    clearArray(array, N);

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            array[i][j] = rand() % 10; 
            array[j][i] = array[i][j]; 
        }
    }
}

/*
 * Заполняет массив случайными значениями таким образом, чтобы он был симметричен относительно побочной диагонали.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void fillSecond(int** array, const int N) {
    clearArray(array, N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N - i - 1; j++) {
            array[i][j] = rand() % 10; 
            array[N - j - 1][N - i - 1] = array[i][j]; 
        }
    }
}

/*
 * Заполнение массива треугольником Паскаля.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void pascalArray(int** array, int N) {
    clearArray(array, N);

    for (int i = 0; i < N; i++) {
        array[i][0] = 1;  
        for (int j = 1; j <= i; j++) {
            array[i][j] = array[i-1][j-1] + array[i-1][j];
        }
    }
}

/*
 * Заполнение массива минами для игры в сапёра.
 *
 * @param array указатель на двумерный массив.
 * @param N размер массива (количество строк и столбцов).
 */
void saperArray(int** array, const int N) {
    clearArray(array, N);  
    const int MINES = N + 2;
    int minesPlaced = 0;

    while (minesPlaced < MINES) {
        int row = rand() % N;
        int col = rand() % N;

        if (array[row][col] != -1) {
            array[row][col] = -1; // Устанавка мины
            minesPlaced++;

            // Проход по всем соседним ячейкам
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    int newRow = row + x;
                    int newCol = col + y;
                    if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N && array[newRow][newCol] != -1) {
                        array[newRow][newCol]++;
                    }
                }
            }
        }
    }
}
int main(){
    const int N = getNumber();
    int** array = createArray(N);
    printArray(array, N);
    int choice;
    srand(time(0));

    do {
        cout << "Меню:\n";
        cout << "-1 - Закончить работу\n";
        cout << "0 - Очистить массив и заполнить его 0\n";
        cout << "1 - Провести заполнение массива так, что бы он обладал свойством симметричности относительно главной диагонали\n";
        cout << "2 - Провести заполнение массива так, что бы он обладал свойством симметричности относительно побочной диагонали\n";
        cout << "3 - Провести заполнения массива так, что бы он являлся треугольником Паскаля\n";
        cout << "4 - Провести заполнения массива для игры в сапера\n\n";
        choice = getNumber();

        switch (choice) {
            case -1:
                cout << "\nЗавершение работы программы...\n\n";
                deleteArray(array, N);
                break;

            case 0:
                clearArray(array, N);
                printArray(array, N);
                break;

            case 1:
                fillMain(array, N);
                printArray(array, N);
                break;

            case 2:
                fillSecond(array, N);
                printArray(array, N);
                break;

            case 3:
                pascalArray(array, N);
                printArray(array, N);
                break;
            
            case 4:
                saperArray(array, N);
                printArray(array, N);
                break;

            default:
                cout << "\nНеверная команда. Попробуйте снова.\n\n";
                break;
        }
    } while (choice != -1);

    return 0;
}