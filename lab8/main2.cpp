// лаба: https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab8.md
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <random>
#include <chrono>
#include <thread>

// Класс "Патрон"
class Cartridge {
    std::string type; // Тип патрона в виде строки

public:
    /**
     * Конструктор класса Cartridge
     * @param type - тип патрона ("Subsonic", "Supersonic", или "Tracer")
     */
    Cartridge(const std::string& type) : type(type) {}

    /**
     * Отображает эффект выстрела патрона в консоль
     */
    void displayEffect() const {
        if (type == "Subsonic") {
            std::cout << "Тихий звук выстрела (дозвуковой)\n";
        } else if (type == "Supersonic") {
            std::cout << "Стандартный звук выстрела (обычный)\n";
        } else if (type == "Tracer") {
            std::cout << "Стандартный звук и подсветка траектории (трассирующий)\n";
        }
    }

    /**
     * Возвращает тип патрона
     * @return тип патрона как строка
     */
    const std::string& getType() const { return type; }
};

// Класс "Магазин"
class Magazine {
    std::stack<Cartridge> cartridges;
    const int capacity = 30;

public:
    /**
     * Проверяет, пуст ли магазин
     * @return true, если магазин пуст, иначе false
     */
    bool isEmpty() const { return cartridges.empty(); }

    /**
     * Проверяет, полон ли магазин
     * @return true, если магазин полон, иначе false
     */
    bool isFull() const { return cartridges.size() == capacity; }

    /**
     * Заряжает патрон в магазин, если он не полон
     * @param cartridge - патрон для добавления
     * @param loadTime - счетчик времени на зарядку (увеличивается на 2 за каждый патрон)
     */
    void loadCartridge(const Cartridge& cartridge, int& loadTime) {
        if (!isFull()) {
            cartridges.push(cartridge);
            loadTime += 2;  // Время на зарядку одного патрона (2 ед. времени)
        }
    }

    /**
     * Извлекает патрон из магазина
     * @param unloadTime - счетчик времени на извлечение (увеличивается на 1 за каждый патрон)
     * @return извлеченный патрон
     */
    Cartridge unloadCartridge(int& unloadTime) {
        if (!isEmpty()) {
            Cartridge cartridge = cartridges.top();
            cartridges.pop();
            unloadTime += 1;  // Время на изъятие патрона (1 ед. времени)
            return cartridge;
        }
        throw std::runtime_error("Магазин пуст");
    }
};

// Класс "Оружие"
class Weapon {
    Magazine* magazine = nullptr;

public:
    /**
     * Вставляет магазин в оружие
     * @param mag - указатель на объект магазина
     */
    void insertMagazine(Magazine* mag) { magazine = mag; }

    /**
     * Удаляет магазин из оружия
     */
    void removeMagazine() { magazine = nullptr; }

    /**
     * Проверяет, можно ли произвести выстрел
     * @return true, если магазин вставлен и не пуст, иначе false
     */
    bool canShoot() const { return magazine && !magazine->isEmpty(); }

    /**
     * Выполняет выстрел, если это возможно
     * @param shootTime - общее время на стрельбу (увеличивается на 1 за каждый выстрел)
     * @param shotsFired - счетчик произведенных выстрелов
     * @param subsonicCount - количество отстрелянных дозвуковых патронов
     * @param supersonicCount - количество отстрелянных обычных патронов
     * @param tracerCount - количество отстрелянных трассирующих патронов
     */
    void shoot(int& shootTime, int& shotsFired, int& subsonicCount, int& supersonicCount, int& tracerCount) {
        if (canShoot()) {
            Cartridge cartridge = magazine->unloadCartridge(shootTime); // Извлекаем патрон
            shootTime += 1;  // Время на выстрел (1 ед. времени)
            cartridge.displayEffect(); // Показать эффект
            shotsFired++;

            // Обновление статистики по типам патронов
            if (cartridge.getType() == "Subsonic") subsonicCount++;
            else if (cartridge.getType() == "Supersonic") supersonicCount++;
            else if (cartridge.getType() == "Tracer") tracerCount++;
        } else {
            std::cout << "Магазин пуст!\n";
        }
    }
};

/**
 * Запрашивает у пользователя целое число с сообщением
 * @param message - сообщение для запроса у пользователя
 * @return введенное пользователем целое число
 */
int getNumber(const std::string &message) {
    int number;
    std::cout << message;
    std::cin >> number;
    return number;
}

/**
 * Генерирует набор патронов заданного размера
 * @param totalCartridges - общее количество патронов для генерации
 * @return вектор патронов
 */
std::vector<Cartridge> generateCartridgeBox(int totalCartridges) {
    std::vector<Cartridge> box;

    std::string cartridgeTypes[] = {"Subsonic", "Supersonic", "Tracer"};
    for (int i = 0; i < totalCartridges; ++i) {
        std::string type = cartridgeTypes[std::rand() % 3];
        box.emplace_back(type);
    }
    return box;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализация генератора случайных чисел

    // Получаем общее количество патронов от пользователя
    int totalCartridges = getNumber("Введите общее количество патронов: ");
    
    Weapon weapon;
    int totalShots = 0;
    int totalLoadTime = 0;
    int totalShootTime = 0;
    int subsonicCount = 0;
    int supersonicCount = 0;
    int tracerCount = 0;

    // Генерируем коробку патронов
    std::vector<Cartridge> cartridgeBox = generateCartridgeBox(totalCartridges);

    // Стрельба пока есть патроны
    while (!cartridgeBox.empty()) {
        Magazine magazine;

        // Заряжаем магазин из коробки патронов
        for (int j = 0; j < 30 && !cartridgeBox.empty(); ++j) {
            magazine.loadCartridge(cartridgeBox.back(), totalLoadTime);
            cartridgeBox.pop_back();
        }

        // Вставляем магазин в оружие
        weapon.insertMagazine(&magazine);

        // Стрельба из магазина
        while (weapon.canShoot()) {
            weapon.shoot(totalShootTime, totalShots, subsonicCount, supersonicCount, tracerCount);
        }

        // Убираем пустой магазин
        weapon.removeMagazine();
    }

    // Выводим статистику
    std::cout << "\n--- Статистика ---\n";
    std::cout << "Суммарное количество отстрелянных патронов: " << totalShots << "\n";
    std::cout << "Суммарное количество заряженных магазинов: " << (totalShots + 29) / 30 << "\n"; // Округление вверх
    std::cout << "Суммарное время на зарядку патронов: " << totalLoadTime << " ед.\n";
    std::cout << "Суммарное время стрельбы: " << totalShootTime << " ед.\n";
    std::cout << "Количество дозвуковых патронов: " << subsonicCount << "\n";
    std::cout << "Количество обычных патронов: " << supersonicCount << "\n";
    std::cout << "Количество трассирующих патронов: " << tracerCount << "\n";

    return 0;
}
