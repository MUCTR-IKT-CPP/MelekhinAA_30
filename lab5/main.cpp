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
    double minHealth;
    int breakTime = -1;
    int replacePrice;
    int repairPrice;
    int repairTime;
    double health = 100.0;
    bool isBroken = false;

    Part(double minHealth, int replacePrice, int repairPrice, int repairTime):
        minHealth(minHealth),
        replacePrice(replacePrice), 
        repairPrice(repairPrice),
        repairTime(repairTime) {};
    
    void checkBroken(){
        const int BREAKE_CHANCE = 5; // Вероятность поломки
        if (health >= minHealth || rand() % 100 < BREAKE_CHANCE) {  
            isBroken = true;
        }
    }

    virtual void work(int intensity) = 0;

};

class Engine : public Part {
public:
    Engine(double minHealth, int replacePrice, int repairPrice, int repairTime):         
        Part(minHealth, replacePrice, repairPrice, repairTime) {};
        
    void work(int intensity) override{
        if (!isBroken){
            health -= intensity * 1.1;
            checkBroken();
        }
    }
};

class Shaft : public Part {
public:
    Shaft(double minHealth, int replacePrice, int repairPrice, int repairTime):         
        Part(minHealth, replacePrice, repairPrice, repairTime) {};
    
    void work(int intensity) override {
        if (!isBroken){
            health -= intensity * 0.9;
            checkBroken();
        }
    }
};

class ControlPanel : public Part {
public:
    ControlPanel(double minHealth, int replacePrice, int repairPrice, int repairTime):         
        Part(minHealth, replacePrice, repairPrice, repairTime) {};
    
    void work(int intensity) override {
        if (!isBroken){
            health -= intensity * 0.7;
            checkBroken();
        }
    }
};

class CuttingHead : public Part {
public:
    CuttingHead(double minHealth, int replacePrice, int repairPrice, int repairTime):         
        Part(minHealth, replacePrice, repairPrice, repairTime) {};        
    

    void work(int intensity) override {
        if (!isBroken){
            health -= intensity * 1.15;
            checkBroken();
        }
    }
};

class Machine{
public:
    std::vector<std::shared_ptr<Part>> parts;
    int replaceCount = 0;
    int repairCount = 0;
    int stopTime = 0;
    int fixPrice = 0;
    int partCount;
    bool isWorking = true;
    const int REPLACE_TIME = 4;


    Machine(int partCount) : partCount(partCount) {
        for (int i = 0; i < partCount; i++){
            int type = rand() % 4;
            switch (type){
                case 0:
                    parts.push_back(std::make_shared<Engine>(Engine(25.0, 500, 300, 3)));
                    break;
                case 1:
                    parts.push_back(std::make_shared<Shaft>(Shaft(15.0, 400, 150, 3)));
                    break;
                case 2:
                    parts.push_back(std::make_shared<ControlPanel>(ControlPanel(5.0, 300, 100, 2)));
                    break;
                case 3:
                    parts.push_back(std::make_shared<CuttingHead>(CuttingHead(20.0, 250, 50, 1)));
                    break;
                default:
                    break;
            }
        } 
    }

    double genIntensity(){
        double intesity = 10.0 + static_cast<double>(rand()) / (RAND_MAX / (20.0 - 10.0));
        return intesity;
    }

    void work(){
        /*
        const int HOURS_PER_DAY = 12;
        const int DAYS_PER_MOUNTH = 30;
        const int MOUNTHS_PER_YEAR = 12;
        double intensity = genIntensity();
        for (int i = 0; i < (HOURS_PER_DAY * DAYS_PER_MOUNTH * MOUNTHS_PER_YEAR); i++){
            if (i % (HOURS_PER_DAY * DAYS_PER_MOUNTH))
            {
                double intensity = genIntensity();
            }
            for(auto& part : parts){
                part->work(intensity);
            }
        }*/
       for(auto& part : parts){
            std::cout << typeid(*part).name() << " " << genIntensity() << std::endl;
       }
    }
};

int main() {
    srand(time(NULL));

    const int PART_COUNT = getNumber("Введите количество деталей в одном станке: ");
    const int MACHINE_COUNT = getNumber("Введите количество станков: ");
    Machine machine = Machine(PART_COUNT);
    machine.work();
    return 0;
}