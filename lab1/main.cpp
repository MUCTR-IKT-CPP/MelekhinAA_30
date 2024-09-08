#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

/*
 * Генерация случайной строки
 *
 * @param lenth длина строки.
 * @return возвращает сгенерированноую строку.
 */
string makeString(int lenth){
    string str = "";
    srand(time(0));
    for(int i = 0; i < lenth; i++){
        str += 'a' + rand() % 26;
    }
    return str;
}


/*
 * Подчёт символов в строке и вывод количства символов
 *
 * @param string строка.
 * @param lenth длина исследуемой строки.
 * @return возвращает мапу символов
 */
map<char, int> countRandomChars(string str, int lenth){
    map<char, int> charsCount;
    for(int i = 0; i < lenth; i++){
        if(charsCount.find(str[i]) != charsCount.end()){
            charsCount[str[i]] += 1;
        }else{
            charsCount[str[i]] = 1;
        }
    }
    return charsCount;
}

/*
 * Вывод информации о символах
 *
 * @param charsCount выводимая мапа символов
 */
void printMap(map<char, int> charsCount){
    for(const auto& pair : charsCount){
        std::cout << "символ " << pair.first << ": " << pair.second << std::endl;
    }
}

int main(){
    const int LENTH = 10000;
    string str = makeString(LENTH);
    cout << "Случайная строка: " << str << endl;
    map<char, int> charsCount = countRandomChars(str, LENTH);
    printMap(charsCount);
    return 0;
}
