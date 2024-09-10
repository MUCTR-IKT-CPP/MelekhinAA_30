// Лаба: https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2023/lab2.md
#include <iostream>

using namespace std;

int getNumber(){
    int n;
    cout << "Введите число: ";
    cin >> n;
    return n;
}

int makeArray(int n){
    int** array=new int*[n];
    for(int s=0; s<n; s++){
        array[s]=new int [1];
    }
    return **array;
}
int main(){
    int n = getNumber();
    cout << "Введённое число: " << n << endl;
    int array=makeArray(n);
    *array[0][0] = 1;
    cout << array[0][0]+1;
    return 0;
}
