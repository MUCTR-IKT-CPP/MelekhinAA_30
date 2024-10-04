// лаба (вариант 1) https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab4.md
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

const double PI = 3.14159265359;

// Класс для шестиугольника
class Hexagon {
public:
    double x, y; // центр
    double side; // длина стороны

    Hexagon(double x, double y, double side) : x(x), y(y), side(side) {}

    double area() const {
        return (3 * sqrt(3) / 2) * side * side;
    }

    // Радиус описанной окружности (для правильного шестиугольника)
    double getCircumscribedRadius() const {
        return side;
    }
};

// Класс для квадрата
class Square {
public:
    double x, y; // центр
    double side; // длина стороны

    Square(double x, double y, double side) : x(x), y(y), side(side) {}

    double area() const {
        return side * side;
    }

    // Радиус описанной окружности (половина диагонали)
    double getCircumscribedRadius() const {
        return side * sqrt(2) / 2;
    }
};

// Класс для круга
class Circle {
public:
    double x, y; // центр
    double radius; // радиус

    Circle(double x, double y, double radius) : x(x), y(y), radius(radius) {}

    double area() const {
        return PI * radius * radius;
    }

    // Радиус описанной окружности равен радиусу круга
    double getCircumscribedRadius() const {
        return radius;
    }
};

// Класс, хранящий указатель на фигуру и её тип в виде строки
class Figure {
public:
    void* figurePtr;
    std::string type;

    Figure(void* ptr, const std::string& type) : figurePtr(ptr), type(type) {}

    double area() const {
        if (type == "Hexagon") {
            return static_cast<Hexagon*>(figurePtr)->area();
        } else if (type == "Square") {
            return static_cast<Square*>(figurePtr)->area();
        } else if (type == "Circle") {
            return static_cast<Circle*>(figurePtr)->area();
        }
        return 0;
    }

    // Получаем радиус описанной окружности
    double getCircumscribedRadius() const {
        if (type == "Hexagon") {
            return static_cast<Hexagon*>(figurePtr)->getCircumscribedRadius();
        } else if (type == "Square") {
            return static_cast<Square*>(figurePtr)->getCircumscribedRadius();
        } else if (type == "Circle") {
            return static_cast<Circle*>(figurePtr)->getCircumscribedRadius();
        }
        return 0;
    }

    // Проверка на пересечение через описанные окружности
    bool intersects(const Figure& other) const {
        double dist = sqrt((getX() - other.getX()) * (getX() - other.getX()) + (getY() - other.getY()) * (getY() - other.getY()));
        return dist < (getCircumscribedRadius() + other.getCircumscribedRadius());
    }

    double getX() const {
        if (type == "Hexagon") {
            return static_cast<Hexagon*>(figurePtr)->x;
        } else if (type == "Square") {
            return static_cast<Square*>(figurePtr)->x;
        } else if (type == "Circle") {
            return static_cast<Circle*>(figurePtr)->x;
        }
        return 0;
    }

    double getY() const {
        if (type == "Hexagon") {
            return static_cast<Hexagon*>(figurePtr)->y;
        } else if (type == "Square") {
            return static_cast<Square*>(figurePtr)->y;
        } else if (type == "Circle") {
            return static_cast<Circle*>(figurePtr)->y;
        }
        return 0;
    }
};

// Класс сцены
class Scene {
public:
    double width, height; // размеры сцены
    std::vector<Figure> figures;

    Scene(double w, double h) : width(w), height(h) {}

    // Добавление случайной фигуры с проверкой на пересечения и выход за границы
    void addRandomFigure() {
        int attempts = 0;
        while (attempts < 100) {
            std::string type = randomFigureType();
            Figure figure = createRandomFigure(type);

            // Проверяем, чтобы фигура находилась внутри границ сцены
            if (!isInsideScene(figure)) {
                attempts++;
                continue;
            }

            // Проверяем пересечения с уже существующими фигурами
            bool intersects = false;
            for (const auto& f : figures) {
                if (figure.intersects(f)) {
                    intersects = true;
                    break;
                }
            }

            // Если пересечений нет, добавляем фигуру
            if (!intersects) {
                figures.push_back(figure);
                return;
            }

            attempts++;
        }

        std::cout << "Не удалось добавить фигуру. Превышено количество попыток.\n";
    }

    // Вычисление общей площади всех фигур на сцене
    double totalArea() const {
        double total = 0;
        for (const auto& f : figures) {
            total += f.area();
        }
        return total;
    }

private:
    // Метод для генерации случайного типа фигуры
    std::string randomFigureType() {
        int r = rand() % 3;
        if (r == 0) return "Hexagon";
        if (r == 1) return "Square";
        return "Circle";
    }

    // Метод для генерации случайной фигуры
    Figure createRandomFigure(const std::string& type) {
        double x = rand() % static_cast<int>(width);
        double y = rand() % static_cast<int>(height);
        if (type == "Hexagon") {
            return Figure(new Hexagon(x, y, rand() % 10 + 1), "Hexagon");
        } else if (type == "Square") {
            return Figure(new Square(x, y, rand() % 10 + 1), "Square");
        } else if (type == "Circle") {
            return Figure(new Circle(x, y, rand() % 10 + 1), "Circle");
        }
        return Figure(nullptr, "Unknown"); // Невозможный тип фигуры
    }

    // Проверка, что фигура находится внутри границ сцены
    bool isInsideScene(const Figure& figure) {
        double radius = figure.getCircumscribedRadius();
        return (figure.getX() - radius >= 0 && figure.getX() + radius <= width &&
                figure.getY() - radius >= 0 && figure.getY() + radius <= height);
    }
};

int main() {
    srand(time(nullptr));

    const double SCENE_WIDTH = 100;
    const double SCENE_HEIGHT = 100;

    Scene scene(SCENE_WIDTH, SCENE_HEIGHT);
    
    int n;
    std::cout << "Введите количество фигур для добавления: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        scene.addRandomFigure();
    }

    std::cout << "Суммарная площадь фигур на сцене: " << scene.totalArea() << std::endl;

    return 0;
}

