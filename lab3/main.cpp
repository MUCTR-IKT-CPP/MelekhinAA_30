// лаба (вариант 2) https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab3.md
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

struct Banknote {
    string name;  
    int value;    
    double rate;  
};

// Массив возможных номиналов банкнот
const int denominations[] = {1, 5, 10, 20, 50, 100, 1000};
const int denomSize = sizeof(denominations) / sizeof(denominations[0]);

/*
 * Генерация случайного номинала банкноты
 *
 * @return возвращает случайный номинал из массива `denominations`.
 */
int getRandomDenomination() {
    return denominations[rand() % denomSize];
}

/*
 * Генерация случайной банкноты с валютой и курсом
 *
 * @return возвращает структуру Banknote с случайными значениями
 *         валюты, номинала и курса к рублю.
 */
Banknote generateRandomBanknote() {
    // Массив пар: валюта и её курс к рублю
    pair<string, double> currencies[] = {
        {"USD", 92.87}, {"EUR", 103.39}, {"GBP", 123.84}, {"JPY", 0.64}, {"CNY", 13.}};
    int currenciesSize = sizeof(currencies) / sizeof(currencies[0]);
    int index = rand() % currenciesSize;

    Banknote bn;
    bn.name = currencies[index].first;
    bn.value = getRandomDenomination();
    bn.rate = currencies[index].second;
    return bn;
}

/*
 * Получение числа от пользователя
 *
 * @param message сообщение, которое выводится пользователю перед вводом числа.
 * @return возвращает положительное число, введенное пользователем.
 */
int getNumber(const string &message) {
    int number;
    cout << message;
    cin >> number;
    return number;
}

/*
 * Вывод содержимого кошелька
 *
 * @param wallet вектор, содержащий список банкнот.
 */
void printWallet(const vector<Banknote> &wallet) {
    cout << "Кошелек:\n";
    for (const Banknote &bn : wallet) {
        cout << "Валюта: " << bn.name << ", Номинал: " << bn.value << ", Курс к рублю: " << bn.rate << "\n";
    }
}

/*
 * Подсчет общей суммы всех банкнот в рублях
 *
 * @param wallet вектор, содержащий список банкнот.
 * @return возвращает общую сумму в рублях, рассчитанную по всем банкнотам в кошельке.
 */
double calculateRubles(const vector<Banknote> &wallet) {
    double total = 0.0;
    for (const Banknote &bn : wallet) {
        total += bn.value * bn.rate;
    }
    return total;
}

/*
 * Фильтрация банкнот по номиналу больше указанного
 *
 * @param wallet вектор, содержащий список банкнот.
 * @param minDenom минимальный номинал, для фильтрации банкнот.
 * @return возвращает карту (map), где ключ - валюта, а значение - количество банкнот с номиналом больше minDenom.
 */
map<string, int> filterByDenomination(const vector<Banknote> &wallet, int minDenom) {
    map<string, int> result;
    for (const Banknote &bn : wallet) {
        if (bn.value > minDenom) {
            result[bn.name]++;
        }
    }
    return result;
}

/*
 * Вывод отфильтрованного кошелька по минимальному номиналу
 *
 * @param filtered карта (map), содержащая количество банкнот по валютам.
 * @param minDenom минимальный номинал, используемый для фильтрации.
 */
void printFilteredWallet(const map<string, int> &filtered, int minDenom) {
    cout << "\nКоличество банкнот по валютам с номиналом больше " << minDenom << ":\n";
    for (const pair<string, int> &entry : filtered) {
        cout << entry.first << ": " << entry.second << "\n";
    }
}

/*
 * Сортировка состава кошелька по валютам и номиналу
 *
 * @param wallet вектор, содержащий список банкнот.
 * @return возвращает карту (map), где ключ - валюта, а значение - внутренняя карта
 *         с ключом в виде номинала и значением в виде количества банкнот.
 */
map<string, map<int, int>> sortWallet(const vector<Banknote> &wallet) {
    map<string, map<int, int>> sortedWallet;
    for (const Banknote &bn : wallet) {
        sortedWallet[bn.name][bn.value]++;
    }
    return sortedWallet;
}

/*
 * Вывод состава кошелька, отсортированного по валютам и номиналу
 *
 * @param sortedWallet карта (map), содержащая сортированное представление кошелька.
 */
void printSortedWallet(const map<string, map<int, int>> &sortedWallet) {
    cout << "\nОтсортированный кошелек:\n";
    for (const pair<string, map<int, int>> &currency : sortedWallet) {
        cout << currency.first << ":\n";
        for (const pair<int, int> &denom : currency.second) {
            cout << "  Номинал: " << denom.first << ", Количество: " << denom.second << "\n";
        }
    }
}

/*
 * Конвертация всех банкнот в рубли и набор их рублями с максимальным номиналом
 *
 * @param wallet вектор, содержащий список банкнот.
 */
void convertToRubles(const vector<Banknote> &wallet) {
    cout << "\nКонвертация в рубли:\n";
    double totalRubles = calculateRubles(wallet);
    cout << "Общая сумма в рублях: " << totalRubles << " руб.\n";

    // Массив рублевых номиналов для обмена
    int rubleDenominations[] = {5000, 2000, 1000, 500, 100, 200, 50, 10, 5, 2, 1};
    cout << "Сумма набирается из следующих купюр:\n";

    // Обмен общей суммы на банкноты максимального номинала
    for (int denom : rubleDenominations) {
        int count = totalRubles / denom;
        if (count > 0) {
            cout << "Номинал: " << denom << " руб, Количество: " << count << "\n";
            totalRubles -= count * denom;
        }
    }

    // Округление, если осталась сумма менее 1 рубля
    if (totalRubles > 0) {
        cout << "Номинал: 1 руб, Количество: 1 (для округления)\n";
    }
}

int main() {
    srand(time(0));
    int N = getNumber("Введите количество банкнот: ");
    vector<Banknote> wallet;
    wallet.reserve(N); // Резервируем память для N элементов

    for (int i = 0; i < N; ++i) {
        wallet.push_back(generateRandomBanknote());
    }

    printWallet(wallet);
    cout << setprecision(2);
    cout << "\nОбщая сумма в рублях: " << calculateRubles(wallet) << " руб.\n";

    int minDenom = getNumber("Введите минимальный номинал для фильтрации: ");
    map<string, int> filtered = filterByDenomination(wallet, minDenom);
    printFilteredWallet(filtered, minDenom);

    map<string, map<int, int>> sortedWallet = sortWallet(wallet);
    printSortedWallet(sortedWallet);

    convertToRubles(wallet);

    return 0;
}

