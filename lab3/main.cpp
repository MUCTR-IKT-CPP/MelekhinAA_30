// лаба (вариант 2) https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab3.md
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

// Структура Банкнота
struct Banknote {
    string name;  // Валюта
    int value;    // Номинал
    double rate;  // Курс к рублю
};

// Массив номиналов
const int denominations[] = { 1, 5, 10, 20, 50, 100, 1000 };
const int denomSize = sizeof(denominations) / sizeof(denominations[0]);

/**
 * @brief Функция для генерации случайного номинала банкноты.
 * 
 * @return int Случайный номинал из массива denominations.
 */
int getRandomDenomination() {
    return denominations[rand() % denomSize];
}

/**
 * @brief Функция для генерации случайной банкноты с валютой и курсом.
 * 
 * @return Banknote Случайно сгенерированная банкнота с валютой, номиналом и курсом.
 */
Banknote generateRandomBanknote() {
    // Вектор пар валют и их курсов к рублю
    vector<pair<string, double>> currencies = {
        {"USD", 95.0}, {"EUR", 100.0}, {"GBP", 115.0}, {"JPY", 0.7}, {"CNY", 13.5}
    };
    // Выбор случайной валюты
    int index = rand() % currencies.size();
    Banknote bn;
    bn.name = currencies[index].first;
    bn.value = getRandomDenomination();
    bn.rate = currencies[index].second;
    return bn;
}

/**
 * @brief Функция для подсчета общей суммы всех банкнот в рублях.
 * 
 * @param wallet Вектор банкнот, хранящийся в кошельке.
 * @return double Общая сумма в рублях всех банкнот в кошельке.
 */
double calculateTotalInRubles(const vector<Banknote>& wallet) {
    double total = 0.0;
    for (const auto& bn : wallet) {
        total += bn.value * bn.rate;
    }
    return total;
}

/**
 * @brief Функция для формирования среза банкнот с номиналом больше указанного пользователем.
 * 
 * @param wallet Вектор банкнот, хранящийся в кошельке.
 * @param minDenom Минимальный номинал для фильтрации банкнот.
 * @return map<string, int> Словарь, где ключ - валюта, значение - количество банкнот с номиналом больше minDenom.
 */
map<string, int> filterByDenomination(const vector<Banknote>& wallet, int minDenom) {
    map<string, int> result;
    for (const auto& bn : wallet) {
        if (bn.value > minDenom) {
            result[bn.name]++;
        }
    }
    return result;
}

/**
 * @brief Функция для вывода состава кошелька, отсортированного по валютам и номиналу с количеством каждой банкноты.
 * 
 * @param wallet Вектор банкнот, хранящийся в кошельке.
 */
void printSortedWallet(const vector<Banknote>& wallet) {
    // Словарь, хранящий количество банкнот для каждой валюты и номинала
    map<string, map<int, int>> sortedWallet;
    for (const auto& bn : wallet) {
        sortedWallet[bn.name][bn.value]++;
    }
    // Вывод отсортированного кошелька
    for (const auto& currency : sortedWallet) {
        cout << currency.first << ":\n";
        for (const auto& denom : currency.second) {
            cout << "  Номинал: " << denom.first << ", Количество: " << denom.second << "\n";
        }
    }
}

/**
 * @brief Функция для конвертации всех банкнот в рубли и набора их рублями с максимальным номиналом.
 * 
 * @param wallet Вектор банкнот, хранящийся в кошельке.
 */
void convertToRubles(const vector<Banknote>& wallet) {
    double totalRubles = calculateTotalInRubles(wallet);
    cout << "Общая сумма в рублях: " << totalRubles << " руб.\n";
    
    // Массив рублевых номиналов для обмена
    int rubleDenominations[] = { 1000, 100, 50, 20, 10, 5, 1 };
    cout << "Сумма набирается:\n";
    
    // Обмен общей суммы на банкноты максимального номинала
    for (int denom : rubleDenominations) {
        int count = static_cast<int>(totalRubles) / denom;
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
    srand(static_cast<unsigned>(time(0)));

    cout << "Введите количество банкнот: ";
    int N;
    cin >> N;

    vector<Banknote> wallet;
    for (int i = 0; i < N; ++i) {
        wallet.push_back(generateRandomBanknote());
    }

    cout << "Кошелек:\n";
    for (const auto& bn : wallet) {
        cout << "Валюта: " << bn.name << ", Номинал: " << bn.value << ", Курс к рублю: " << bn.rate << "\n";
    }

    // Устанавливаем точность вывода до 2-х знаков после запятой
    cout << fixed << setprecision(2);
    
    cout << "\nОбщая сумма в рублях: " << calculateTotalInRubles(wallet) << " руб.\n";

    cout << "\nВведите минимальный номинал для фильтрации: ";
    int minDenom;
    cin >> minDenom;

    auto filtered = filterByDenomination(wallet, minDenom);
    cout << "\nКоличество банкнот по валютам с номиналом больше " << minDenom << ":\n";
    for (const auto& entry : filtered) {
        cout << entry.first << ": " << entry.second << "\n";
    }

    cout << "\nОтсортированный кошелек:\n";
    printSortedWallet(wallet);

    cout << "\nКонвертация в рубли:\n";
    convertToRubles(wallet);

    return 0;
}