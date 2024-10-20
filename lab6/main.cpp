// лаба: https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab6.md
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <math.h>
#include <memory>
#include <iomanip>

/**
 * @brief Запрашивает у пользователя ввод числа с сообщением.
 * @param message Сообщение для пользователя.
 * @return Введенное пользователем число.
 */
int getNumber(const std::string &message) {
    int number;
    std::cout << message;
    std::cin >> number;
    return number;
}

class Target {
public:
    std::string type;         ///< Тип мишени.
    double damage = 0.0;     ///< Урон, нанесенный мишени.
    int distance;             ///< Расстояние до мишени.
    const int ID;            ///< Уникальный идентификатор мишени.
    double side;             ///< Длина стороны (для квадратной мишени) или радиус (для круглой).
    double size = 0;         ///< Размер мишени.
    int hitsToDestroy;       ///< Количество попаданий, необходимых для уничтожения мишени.
    int hits = 0;            ///< Общее количество попаданий по мишени.
    double visibility = 1.0; ///< Видимость мишени.
    bool isGleams;           ///< Индикатор, блестит ли мишень.
    bool isMoving;           ///< Индикатор, движется ли мишень.
    bool isAvailable = true; ///< Индикатор, доступна ли мишень для стрельбы.

    /**
     * @brief Конструктор класса Target.
     * @param type Тип мишени.
     * @param ID Уникальный идентификатор мишени.
     * @param distance Расстояние до мишени.
     * @param side Длина стороны (для квадратной мишени) или радиус (для круглой).
     * @param hitsToDestroy Количество попаданий, необходимых для уничтожения мишени.
     * @param isGleams Индикатор, блестит ли мишень.
     * @param isMoving Индикатор, движется ли мишень.
     */
    Target(std::string type, const int ID, int distance, double side, int hitsToDestroy, bool isGleams, bool isMoving):
        ID(ID),
        type(type),
        side(side),
        hitsToDestroy(hitsToDestroy),
        isGleams(isGleams),
        isMoving(isMoving) {
            if (isGleams) this->visibility -= 0.1;
            if (isMoving) this->visibility -= 0.2;
            if (distance >= 12) this->visibility -= 0.2; 
        }

    /**
     * @brief Обрабатывает попадания по мишени.
     * @param hitsCount Количество попаданий.
     */
    void Damage(int hitsCount) {
        hits += hitsCount;
        damage += hitsCount * 10.0; 
        std::cout << "Попадания по мишени №" << ID << ": " << hits << " из " << hitsToDestroy << std::endl;
        if (hits >= hitsToDestroy) {
            isAvailable = false;
            std::cout << "Мишень №" << ID << " уничтожена!" << std::endl;
        }
    }

    /**
     * @brief Проверяет доступность мишени.
     * @return true, если мишень доступна, иначе false.
     */
    bool getAvailability() {
        return isAvailable;
    }

    /**
     * @brief Чисто виртуальная функция для получения шанса попадания.
     * @return Вероятность попадания по мишени.
     */
    virtual double getChance() = 0;
};

class TargetSquare : public Target {
public:
    /**
     * @brief Конструктор класса TargetSquare.
     * @param type Тип мишени.
     * @param ID Уникальный идентификатор мишени.
     * @param distance Расстояние до мишени.
     * @param side Длина стороны мишени.
     * @param hitsToDestroy Количество попаданий, необходимых для уничтожения мишени.
     * @param isGleams Индикатор, блестит ли мишень.
     * @param isMoving Индикатор, движется ли мишень.
     */
    TargetSquare(std::string type, const int ID, int distance, double side, int hitsToDestroy, bool isGleams, bool isMoving) : 
        Target(type, ID, distance, side, hitsToDestroy, isGleams, isMoving) {
        this->size = side * side;
    }

    /**
     * @brief Получает шанс попадания по квадратной мишени.
     * @return Вероятность попадания.
     */
    double getChance() {
        double chance = static_cast<double>(rand()) / RAND_MAX;
        chance =  0.5 + chance * 0.5; 
        if (size <= 25) {
            chance += 0.2;
        } else {
            chance -= 0.1;
        }
        chance -= 0.1; // влияние типы фигуры на вероятность попадания
        return chance;
    }
};

class TargetCircular : public Target {
public:
    /**
     * @brief Конструктор класса TargetCircular.
     * @param type Тип мишени.
     * @param ID Уникальный идентификатор мишени.
     * @param distance Расстояние до мишени.
     * @param side Радиус мишени.
     * @param hitsToDestroy Количество попаданий, необходимых для уничтожения мишени.
     * @param isGleams Индикатор, блестит ли мишень.
     * @param isMoving Индикатор, движется ли мишень.
     */
    TargetCircular(std::string type, const int ID, int distance, double side, int hitsToDestroy, bool isGleams, bool isMoving) : 
        Target(type, ID, distance, side, hitsToDestroy, isGleams, isMoving) {
        this->size = 3.14 * side * side;
    }

    /**
     * @brief Получает шанс попадания по круглой мишени.
     * @return Вероятность попадания.
     */
    double getChance() {
        double chance = static_cast<double>(rand()) / RAND_MAX;
        chance =  0.5 + chance * 0.5; 
        if (size <= 25) {
            chance += 0.2;
        } else {
            chance -= 0.1;
        }
        chance += 0.2; // влияние типы фигуры на вероятность попадания
        return chance;
    }
};

class TargetHexagon : public Target {
public:
    /**
     * @brief Конструктор класса TargetHexagon.
     * @param type Тип мишени.
     * @param ID Уникальный идентификатор мишени.
     * @param distance Расстояние до мишени.
     * @param side Длина стороны мишени.
     * @param hitsToDestroy Количество попаданий, необходимых для уничтожения мишени.
     * @param isGleams Индикатор, блестит ли мишень.
     * @param isMoving Индикатор, движется ли мишень.
     */
    TargetHexagon(std::string type, const int ID, int distance, double side, int hitsToDestroy, bool isGleams, bool isMoving) : 
        Target(type, ID, distance, side, hitsToDestroy, isGleams, isMoving) {
        this->size = ((3.0 * sqrt(3)) / 2.0) * side * side;
    }

    /**
     * @brief Получает шанс попадания по шестиугольной мишени.
     * @return Вероятность попадания.
     */
    double getChance() {
        double chance = static_cast<double>(rand()) / RAND_MAX;
        chance =  0.5 + chance * 0.5; 
        if (size <= 25) {
            chance += 0.2;
        } else {
            chance -= 0.1;
        }
        chance -= 0.2; // влияние типы фигуры на вероятность попадания
        return chance;
    }
};

class Gun {
public:
    int magazineCount;             ///< Количество магазинов.
    const int MAGAZINE_CAPACITY;  ///< Вместимость магазина.
    int currentBullets;            ///< Текущее количество патронов.
    int shootingType;              ///< Тип стрельбы.
    bool hasBullets = true;        ///< Индикатор наличия патронов.

    /**
     * @brief Конструктор класса Gun.
     * @param magazineCount Количество магазинов.
     * @param MAGAZINE_CAPACITY Вместимость магазина.
     * @param shootingType Тип стрельбы.
     */
    Gun(int magazineCount, const int MAGAZINE_CAPACITY, int shootingType) :
        magazineCount(magazineCount),
        MAGAZINE_CAPACITY(MAGAZINE_CAPACITY),
        shootingType(shootingType) {
            this->currentBullets = MAGAZINE_CAPACITY;
        }

    /**
     * @brief Проверяет наличие патронов и обновляет их количество.
     */
    void checkBullets() {
        if (currentBullets == 0 && magazineCount != 0) {
            currentBullets = MAGAZINE_CAPACITY;
            magazineCount--;
        } else if (currentBullets == 0 && magazineCount == 0) {
            hasBullets = false;
        }
    }
};

class ShootingRange {
public:
    std::vector<std::shared_ptr<Target>> targets; ///< Вектор мишеней.
    Gun gun;                                        ///< Объект оружия.
    const int TARGET_COUNT;                         ///< Общее количество мишеней.
    int availableTargetsCount;                      ///< Количество доступных мишеней.
    int destroyedCount = 0;                         ///< Количество уничтоженных мишеней.
    double avgDamage;                               ///< Средний урон.

    /**
     * @brief Конструктор класса ShootingRange.
     * @param gun Объект оружия.
     * @param TARGET_COUNT Общее количество мишеней.
     */
    ShootingRange(Gun gun, const int TARGET_COUNT) :
        gun(gun),
        TARGET_COUNT(TARGET_COUNT),
        availableTargetsCount(TARGET_COUNT) {
            for (int i = 0; i < TARGET_COUNT; i++) {
                int type = genNumber(0, 2);
                int distance = genNumber(5, 20);
                int side = genNumber(2, 10);
                bool isGleams = static_cast<bool>(genNumber(0, 1));
                bool isMoving = static_cast<bool>(genNumber(0, 1));

                switch (type) {
                    case 0:
                        targets.push_back(std::make_shared<TargetSquare>(TargetSquare("Квадрат", i + 1, distance, side, 10, isGleams, isMoving)));
                        break;
                    case 1:
                        targets.push_back(std::make_shared<TargetCircular>(TargetCircular("Круг", i + 1, distance, side, 8, isGleams, isMoving)));
                        break;
                    case 2:
                        targets.push_back(std::make_shared<TargetHexagon>(TargetHexagon("Шестиугольник", i + 1, distance, side, 13, isGleams, isMoving)));
                        break;
                    default:
                        break;
                }
            }
        }

    /**
     * @brief Генерирует случайное число в диапазоне [A, B].
     * @param A Нижняя граница диапазона.
     * @param B Верхняя граница диапазона.
     * @return Случайное число в диапазоне [A, B].
     */
    int genNumber(const int A, const int B) {
        return A + rand() % (B - A + 1);
    }

    /**
     * @brief Получает индекс доступной мишени.
     * @return Индекс доступной мишени или -1, если нет доступных мишеней.
     */
    int getIndex() {
        if (availableTargetsCount != 0) {
            bool Availability = false;
            std::shared_ptr<Target> target;
            int index;
            while (!Availability) {
                index = genNumber(0, targets.size() - 1);
                target = targets[index];
                if (target->getAvailability()) {
                    Availability = true;
                    return index;
                }
            }
        }
        return -1; 
    }

    /**
     * @brief Вычисляет средний урон по мишеням.
     */
    void calcDamage() {
        double totalDamage = 0;
        int damagedTargetsCount = 0;  

        for (auto &target : targets) {
            totalDamage += target->damage;
            if (target->damage > 0) {  // Учитываем только те мишени, которые получили урон
                damagedTargetsCount++;
            }
        }

        if (damagedTargetsCount > 0) {
            avgDamage = totalDamage / damagedTargetsCount;
        } else {
            avgDamage = 0;
        }
    }

    /**
     * @brief Выполняет выстрел по мишени.
     * @param index Индекс мишени в векторе.
     */
    void shoot(int index) {
        if (index == -1 || !gun.hasBullets) return;
        double chance = static_cast<double>(rand()) / RAND_MAX; 
        int shootCount = 1;  
        int hits = 0;

        if (gun.shootingType == 1) {
            shootCount = std::min(3, gun.currentBullets);  
        }

        for (int i = 0; i < shootCount; i++) {   
            double difficult = targets[index]->getChance();  

            if (chance * targets[index]->visibility > difficult) {
                hits++;  
            }

            gun.currentBullets--;
            gun.checkBullets();
            if (!gun.hasBullets) break;  
        }

        targets[index]->Damage(hits);
        if (!targets[index]->isAvailable) {
            destroyedCount++;
            availableTargetsCount--;
        }
    }

    /**
     * @brief Симулирует стрельбу по мишеням.
     */
    void simulate() {
        while (gun.hasBullets && availableTargetsCount != 0) {
            int index = getIndex();
            if (index == -1) {
                break;  
            }
            shoot(index);
        }
        calcDamage();
        printInfo(*this);
    }

    /**
     * @brief Выводит информацию о результатах стрельбы.
     * @param shootingRange Объект ShootingRange для вывода информации.
     */
    friend void printInfo(ShootingRange shootingRange) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Результаты стрельбы: " << std::endl;
        std::cout << "Уничтожено мишеней: " << shootingRange.destroyedCount << std::endl;
        std::cout << "Осталось мишеней: " << shootingRange.availableTargetsCount << std::endl;
        std::cout << "Средний урон по мишеням: " << shootingRange.avgDamage << std::endl;
    }
};

int main() {
    srand(time(NULL));
    int check = 0;
    const int MAGAZINE_COUNT = getNumber("Введите количество магазинов: ");
    const int MAGAZINE_CAPACITY = getNumber("Введите количество патронов в магазине: ");
    const int TARGET_COUNT = getNumber("Введите количество мишеней: ");
    int shootingType;
    do {
        shootingType = getNumber("0 - одиночный режим\n1 - режим очередями\n2 - выбрать случайный\nВыберите режим стрельбы: ");
        if (shootingType >= 0 && shootingType <= 2) {
            check = 1;
            if (shootingType == 2){
                shootingType = rand() % 2;
                std::cout << "Выбран режим стрельбы: " << shootingType << std::endl;
            }
        } else{
            std::cout << "Выбран неверный режим стрельбы" << std::endl;
        }
    } while(check == 0);
    ShootingRange shootingRange = ShootingRange(Gun(MAGAZINE_COUNT - 1, MAGAZINE_CAPACITY, shootingType), TARGET_COUNT);
    shootingRange.simulate();
    return 0;
}
