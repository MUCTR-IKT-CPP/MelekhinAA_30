// лаба (вариант 1) https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab5.md
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <memory>

int getNumber(const std::string &message) {
    int number;
    std::cout << message;
    std::cin >> number;
    return number;
}

// Базовый класс Запчасть
class Part {
public:
    std::string type;
    double minHealth;
    int replacePrice;
    int repairPrice;
    int repairTime;
    double health = 100.0;
    bool isBroken = false;

    Part(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        type(type),
        minHealth(minHealth),
        replacePrice(replacePrice),
        repairPrice(repairPrice),
        repairTime(repairTime) {};

    void checkBroken() {
        const int BREAK_CHANCE = 1; // Вероятность поломки
        if (health < minHealth || rand() % 100 < BREAK_CHANCE) {
            isBroken = true;
        }
    }

    virtual void work(int intensity) = 0;
};

class Engine : public Part {
public:
    Engine(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {};

    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 1.1;
            checkBroken();
        }
    }
};

class Shaft : public Part {
public:
    Shaft(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {};

    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 0.9;
            checkBroken();
        }
    }
};

class ControlPanel : public Part {
public:
    ControlPanel(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {};

    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 0.7;
            checkBroken();
        }
    }
};

class CuttingHead : public Part {
public:
    CuttingHead(std::string type, double minHealth, int replacePrice, int repairPrice, int repairTime) :
        Part(type, minHealth, replacePrice, repairPrice, repairTime) {};

    void work(int intensity) override {
        if (!isBroken) {
            health -= intensity * 1.15;
            checkBroken();
        }
    }
};

class Machine {
public:
    std::vector<std::shared_ptr<Part>> parts;
    const int ID;
    int replaceCount = 0;
    int repairCount = 0;
    int stopTime = 0;
    int fixPrice = 0;
    int partCount;
    bool isWorking = true;

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

    double genIntensity() {
        double intensity = 1.0 + static_cast<double>(rand()) / (RAND_MAX / (2.0 - 1.0));
        return intensity;
    }

    friend void printInfo(Machine machine) {
        std::cout << "Станок " << machine.ID << ":" << std::endl;
        std::cout << "Общее время простоя: " << machine.stopTime << std::endl;
        std::cout << "Итоговая стоимость обслуживания: " << machine.fixPrice << std::endl;
        std::cout << "Количество починок: " << machine.repairCount << std::endl;
        std::cout << "Количество замен: " << machine.replaceCount << std::endl << std::endl;
    }

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
                //std::cout << "Месяц: " << i / (HOURS_PER_DAY * DAYS_PER_MONTH) << " Интенсивность: " << intensity << std::endl;
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

class Factory{
public:
    std::vector<std::shared_ptr<Machine>> machines;
    int partCount;
    int machineCount;
    int totalStopTime = 0;
    int totalFixPrice = 0;
    int totalRepairCount = 0;
    int totalReplaceCount = 0;
    int maxStopTime = -1;
    int maxRepairCount = -1;
    int maxReplaceCount = -1;
    int maxFixPrice = -1;

    Factory(int partCount, int machineCount) : 
        partCount(partCount),
        machineCount(machineCount){}

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
    
    void findMaxParams(){
        for (auto &machine : machines){
            maxStopTime = (maxStopTime == -1 || maxStopTime < machine -> stopTime) ? machine -> stopTime : maxStopTime;
            maxRepairCount = (maxRepairCount == -1 || maxRepairCount < machine -> repairCount) ? machine -> repairCount : maxRepairCount;
            maxReplaceCount = (maxReplaceCount == -1 || maxReplaceCount < machine -> replaceCount) ? machine -> replaceCount : maxReplaceCount;
            maxFixPrice = (maxFixPrice == -1 || maxFixPrice < machine -> fixPrice) ? machine -> fixPrice : maxFixPrice;
        }
    }

    void calcTotalParams(){
        for (auto &machine : machines){
            totalStopTime += machine -> stopTime;
            totalRepairCount += machine -> repairCount;
            totalReplaceCount += machine -> replaceCount;
            totalFixPrice += machine -> fixPrice;
        }
    }

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