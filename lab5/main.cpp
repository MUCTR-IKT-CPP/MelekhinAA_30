// лаба (вариант 1) https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab5.md
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <memory>

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

/**
 * @brief Базовый класс детали станка.
 */
class Part {
public:
    std::string type;     ///< Тип детали.
    double minHealth;     ///< Минимальный уровень здоровья, при котором деталь считается сломанной.
    int replacePrice;     ///< Стоимость замены детали.
    int repairPrice;      ///< Стоимость починки детали.
    int repairTime;       ///< Время, требуемое на починку.
    double health = 100.0; ///< Текущий уровень здоровья детали (по умолчанию 100%).
    bool isBroken = false; ///< Флаг, указывающий, сломана ли деталь.

    /**
     * @brief Конструктор детали.
     * @param type Тип детали.
     * @param minHealth Минимальное здоровье детали.
     * @param replacePrice Стоимость замены.
     * @param repairPrice Стоимость починки.
     * @param repairTime Время починки.
     */
    Part(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        type(type),
        minHealth(minHealth),
        replacePrice(replacePrice),
        repairPrice(repairPrice),
        repairTime(repairTime) {}

    /**
     * @brief Проверяет, сломана ли деталь.
     * Если здоровье меньше минимального или случайное событие вызвало поломку, устанавливает флаг isBroken.
     */
    void checkBroken() {
        const int BREAK_CHANCE = 1; // Вероятность поломки
        if (health < minHealth || rand() % 100 < BREAK_CHANCE) {
            isBroken = true;
        }
    }

    /**
     * @brief Абстрактный метод работы детали.
     * Должен быть реализован в производных классах для выполнения работы детали.
     * @param intensity Интенсивность работы.
     */
    virtual void work(int intensity) = 0;
};

/**
 * @brief Класс электродвигателя, унаследованный от Part.
 */
class Engine : public Part {
public:
    /**
     * @brief Конструктор двигателя.
     * @param type Тип двигателя.
     * @param minHealth Минимальное здоровье двигателя.
     * @param replacePrice Стоимость замены.
     * @param repairPrice Стоимость починки.
     * @param repairTime Время починки.
     */
    Engine(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {}

    /**
     * @brief Работа двигателя с учетом интенсивности.
     * @param intensity Интенсивность работы.
     */
    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 1.1;
            checkBroken();
        }
    }
};

/**
 * @brief Класс вала, унаследованный от Part.
 */
class Shaft : public Part {
public:
    /**
     * @brief Конструктор вала.
     * @param type Тип вала.
     * @param minHealth Минимальное здоровье вала.
     * @param replacePrice Стоимость замены.
     * @param repairPrice Стоимость починки.
     * @param repairTime Время починки.
     */
    Shaft(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {}

    /**
     * @brief Работа вала с учетом интенсивности.
     * @param intensity Интенсивность работы.
     */
    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 0.9;
            checkBroken();
        }
    }
};

/**
 * @brief Класс панели управления, унаследованный от Part.
 */
class ControlPanel : public Part {
public:
    /**
     * @brief Конструктор панели управления.
     * @param type Тип панели.
     * @param minHealth Минимальное здоровье панели.
     * @param replacePrice Стоимость замены.
     * @param repairPrice Стоимость починки.
     * @param repairTime Время починки.
     */
    ControlPanel(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {}

    /**
     * @brief Работа панели управления с учетом интенсивности.
     * @param intensity Интенсивность работы.
     */
    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 0.7;
            checkBroken();
        }
    }
};

/**
 * @brief Класс режущей головки, унаследованный от Part.
 */
class CuttingHead : public Part {
public:
    /**
     * @brief Конструктор режущей головки.
     * @param type Тип режущей головки.
     * @param minHealth Минимальное здоровье.
     * @param replacePrice Стоимость замены.
     * @param repairPrice Стоимость починки.
     * @param repairTime Время починки.
     */
    CuttingHead(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {}

    /**
     * @brief Работа режущей головки с учетом интенсивности.
     * @param intensity Интенсивность работы.
     */
    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 1.15;
            checkBroken();
        }
    }
};

/**
 * @brief Класс станка, состоящего из нескольких деталей.
 */
class Machine {
public:
    std::vector<std::shared_ptr<Part>> parts; ///< Список деталей станка.
    const int ID;                             ///< Идентификатор станка.
    int replaceCount = 0;                     ///< Количество замен деталей.
    int repairCount = 0;                      ///< Количество починок деталей.
    int stopTime = 0;                         ///< Время простоя станка.
    int fixPrice = 0;                         ///< Стоимость всех ремонтов и замен.
    int partCount;                            ///< Количество деталей в станке.
    bool isWorking = true;                    ///< Флаг работы станка.

    /**
     * @brief Конструктор станка.
     * @param ID Идентификатор станка.
     * @param partCount Количество деталей в станке.
     */
    Machine(const int ID, int partCount) : ID(ID), partCount(partCount) {
        for (int i = 0; i < partCount; i++) {
            int type = rand() % 4;
            switch (type) {
                case 0:
                    parts.push_back(std::make_shared<Engine>(Engine("Электродвигатель", 15.0, 500, 300, 3)));
                    break;
                case 1:
                    parts.push_back(std::make_shared<Shaft>(Shaft("Вал", 10.0, 400, 150, 3)));
                    break;
                case 2:
                    parts.push_back(std::make_shared<ControlPanel>(ControlPanel("Панель управления", 5.0, 300, 100, 2)));
                    break;
                case 3:
                    parts.push_back(std::make_shared<CuttingHead>(CuttingHead("Режущая головка", 4.0, 250, 50, 1)));
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * @brief Генерация случайной интенсивности работы станка.
     * @return Интенсивность работы.
     */
    double genIntensity() {
        double intensity = 1.0 + static_cast<double>(rand()) / (RAND_MAX / (2.0 - 1.0));
        return intensity;
    }

    /**
     * @brief Печать информации о состоянии станка.
     * @param machine Экземпляр класса Machine, для которого выводится информация.
     */
    friend void printInfo(Machine machine) {
        std::cout << "Станок " << machine.ID << ":" << std::endl;
        std::cout << "Общее время простоя: " << machine.stopTime << std::endl;
        std::cout << "Итоговая стоимость обслуживания: " << machine.fixPrice << std::endl;
        std::cout << "Количество починок: " << machine.repairCount << std::endl;
        std::cout << "Количество замен: " << machine.replaceCount << std::endl << std::endl;
    }

    /**
     * @brief Основной рабочий цикл станка за год.
     */
    void work() {
        srand(time(NULL));
        const int HOURS_PER_DAY = 12;
        const int DAYS_PER_MONTH = 30;
        const int MONTHS_PER_YEAR = 12;
        const int REPLACE_TIME = 4;
        int breakTime = -1;
        int delay = 0;
        double intensity = genIntensity();

        for (int i = 1; i <= (HOURS_PER_DAY * DAYS_PER_MONTH * MONTHS_PER_YEAR); i++) {
            if (i % (HOURS_PER_DAY * DAYS_PER_MONTH) == 0) {
                intensity = genIntensity();
            }

            if (isWorking) {
                for (auto &part : parts) {
                    part->work(intensity);
                    if (part->isBroken) {
                        isWorking = false;
                        breakTime = breakTime == -1 ? i : breakTime;
                        if (part->health < part->minHealth) {
                            // деталь требует замены
                            delay += REPLACE_TIME;
                            replaceCount++;
                            fixPrice += part->replacePrice;
                        } else {
                            // деталь требует починки
                            delay += part->repairTime;
                            repairCount++;
                            fixPrice += part->repairPrice;
                        }
                        part->isBroken = false;
                        part->health = 100.0;  
                    }
                }
            } else {
                if ((i - breakTime) == delay) {
                    breakTime = -1;
                    stopTime += delay;
                    delay = 0;
                    isWorking = true;
                }
            }
        }
        printInfo(*this);
    }
};

/**
 * @brief Класс завода, содержащего несколько станков.
 */
class Factory{
public:
    std::vector<std::shared_ptr<Machine>> machines; ///< Список станков на заводе.
    int partCount;                                  ///< Количество деталей в каждом станке.
    int machineCount;                               ///< Количество станков на заводе.
    int totalStopTime = 0;                          ///< Общее время простоя всех станков.
    int totalFixPrice = 0;                          ///< Общая стоимость ремонта и замены деталей на заводе.
    int totalRepairCount = 0;                       ///< Общее количество починок всех деталей.
    int totalReplaceCount = 0;                      ///< Общее количество замен всех деталей.
    int maxStopTime = -1;                           ///< Максимальное время простоя одного станка.
    int maxRepairCount = -1;                        ///< Максимальное количество починок одного станка.
    int maxReplaceCount = -1;                       ///< Максимальное количество замен одного станка.
    int maxFixPrice = -1;                           ///< Максимальная стоимость ремонта одного станка.

    /**
     * @brief Конструктор завода.
     * @param partCount Количество деталей в каждом станке.
     * @param machineCount Количество станков на заводе.
     */
    Factory(int partCount, int machineCount) : 
        partCount(partCount),
        machineCount(machineCount){}

    /**
     * @brief Печать итоговой информации о заводе.
     * @param factory Экземпляр класса Factory, для которого выводится информация.
     */
    friend void printInfo(Factory factory) {
        std::cout << "================================Итоговая статистика работы завода за год================================" << std::endl;
        std::cout << "Общее время простоя станков: " << factory.totalStopTime << std::endl;
        std::cout << "Общее стоимость обслуживания завода: " << factory.totalFixPrice << std::endl;
        std::cout << "Общее количество починок деталей: " << factory.totalRepairCount << std::endl;
        std::cout << "Общее количество замен деталей: " << factory.totalReplaceCount << std::endl;
        std::cout << "--------------------------" << std::endl;
        std::cout << "Максимальное время простоя станка: " << factory.maxStopTime << std::endl;
        std::cout << "Максимальаня стоимость обслуживания станка: " << factory.maxFixPrice << std::endl;
        std::cout << "Максимальное количество починок деталей одного станка: " << factory.maxRepairCount << std::endl;
        std::cout << "Максимальное количество замен деталей одного станка: " << factory.maxReplaceCount << std::endl;
    }

    /**
     * @brief Поиск максимальных параметров простоя, ремонтов, замен и стоимости.
     */
    void findMaxParams(){
        for (auto &machine : machines){
            maxStopTime = (maxStopTime == -1 || maxStopTime < machine->stopTime) ? machine->stopTime : maxStopTime;
            maxRepairCount = (maxRepairCount == -1 || maxRepairCount < machine->repairCount) ? machine->repairCount : maxRepairCount;
            maxReplaceCount = (maxReplaceCount == -1 || maxReplaceCount < machine->replaceCount) ? machine->replaceCount : maxReplaceCount;
            maxFixPrice = (maxFixPrice == -1 || maxFixPrice < machine->fixPrice) ? machine->fixPrice : maxFixPrice;
        }
    }

    /**
     * @brief Подсчет общих параметров работы всех станков.
     */
    void calcTotalParams(){
        for (auto &machine : machines){
            totalStopTime += machine->stopTime;
            totalRepairCount += machine->repairCount;
            totalReplaceCount += machine->replaceCount;
            totalFixPrice += machine->fixPrice;
        }
    }

    /**
     * @brief Основной рабочий цикл завода.
     */
    void work(){
        for(int i = 0; i < machineCount; i++){
            Machine machine = Machine(i+1, partCount);
            machine.work();
            machines.push_back(std::make_shared<Machine>(machine));
        }
        calcTotalParams();
        findMaxParams();
        printInfo(*this);
    }
};

int main() {
    const int PART_COUNT = getNumber("Введите количество деталей в одном станке: ");
    const int MACHINE_COUNT = getNumber("Введите количество станков: ");
    Factory factory = Factory(PART_COUNT, MACHINE_COUNT);
    factory.work();
    return 0;
}
