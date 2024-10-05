// лаба (вариант 1) https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab4.md
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

const double PI = 3.14;

// Класс шестиугольника
class Hexagon {
public:
    double x, y; 
    double side; 
    double vx, vy; 

    /*
     * Конструктор класса шестиугольника.
     *
     * @param x координата центра по оси x.
     * @param y координата центра по оси y.
     * @param side длина стороны шестиугольника.
     * @param vx скорость по оси x.
     * @param vy скорость по оси y.
     */
    Hexagon(double x, double y, double side, double vx, double vy)
        : x(x), y(y), side(side), vx(vx), vy(vy) {}

    /*
     * Вычисление площади шестиугольника.
     *
     * @return площадь шестиугольника.
     */
    double area() const {
        return (3 * sqrt(3) / 2) * side * side;
    }

    /*
     * Получение радиуса описанной окружности для шестиугольника.
     *
     * @return радиус описанной окружности.
     */
    double getCircumscribedRadius() const {
        return side;
    }

    /*
     * Обновление положения шестиугольника в пространстве.
     *
     * @param timeStep шаг времени, на который нужно обновить положение.
     */
    void move(double timeStep) {
        x += vx * timeStep;
        y += vy * timeStep;
    }
};

// Класс квадрата
class Square {
public:
    double x, y; 
    double side; 
    double vx, vy; 

    /*
     * Конструктор класса квадрата.
     *
     * @param x координата центра по оси x.
     * @param y координата центра по оси y.
     * @param side длина стороны квадрата.
     * @param vx скорость по оси x.
     * @param vy скорость по оси y.
     */
    Square(double x, double y, double side, double vx, double vy)
        : x(x), y(y), side(side), vx(vx), vy(vy) {}

    /*
     * Вычисление площади квадрата.
     *
     * @return площадь квадрата.
     */
    double area() const {
        return side * side;
    }

    /*
     * Получение радиуса описанной окружности для квадрата (половина диагонали).
     *
     * @return радиус описанной окружности.
     */
    double getCircumscribedRadius() const {
        return side * sqrt(2) / 2;
    }

    /*
     * Обновление положения квадрата в пространстве.
     *
     * @param timeStep шаг времени, на который нужно обновить положение.
     */
    void move(double timeStep) {
        x += vx * timeStep;
        y += vy * timeStep;
    }
};

// Класс круга
class Circle {
public:
    double x, y; 
    double radius; 
    double vx, vy; 

    /*
     * Конструктор класса круга.
     *
     * @param x координата центра по оси x.
     * @param y координата центра по оси y.
     * @param radius радиус круга.
     * @param vx скорость по оси x.
     * @param vy скорость по оси y.
     */
    Circle(double x, double y, double radius, double vx, double vy)
        : x(x), y(y), radius(radius), vx(vx), vy(vy) {}

    /*
     * Вычисление площади круга.
     *
     * @return площадь круга.
     */
    double area() const {
        return PI * radius * radius;
    }

    /*
     * Получение радиуса описанной окружности для круга (он равен радиусу круга).
     *
     * @return радиус описанной окружности.
     */
    double getCircumscribedRadius() const {
        return radius;
    }

    /*
     * Обновление положения круга в пространстве.
     *
     * @param timeStep шаг времени, на который нужно обновить положение.
     */
    void move(double timeStep) {
        x += vx * timeStep;
        y += vy * timeStep;
    }
};

// Класс фигуры
class Figure {
public:
    void* figurePtr;
    std::string type;

    /*
     * Конструктор класса Figure.
     *
     * @param ptr указатель на объект фигуры.
     * @param type тип фигуры (Hexagon, Square, Circle).
     */
    Figure(void* ptr, const std::string& type) : figurePtr(ptr), type(type) {}

    /*
     * Вычисление площади фигуры.
     *
     * @return площадь фигуры.
     */
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

    /*
     * Получение радиуса описанной окружности для фигуры.
     *
     * @return радиус описанной окружности.
     */
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

    /*
     * Проверка пересечения данной фигуры с другой фигурой через описанные окружности.
     *
     * @param other другая фигура для проверки пересечения.
     * @return true, если фигуры пересекаются; false в противном случае.
     */
    bool intersects(const Figure& other) const {
        double dist = sqrt((getX() - other.getX()) * (getX() - other.getX()) + (getY() - other.getY()) * (getY() - other.getY()));
        return dist < (getCircumscribedRadius() + other.getCircumscribedRadius());
    }

    /*
     * Обновление положения фигуры.
     *
     * @param timeStep шаг времени, на который нужно обновить положение.
     */
    void move(double timeStep) {
        if (type == "Hexagon") {
            static_cast<Hexagon*>(figurePtr)->move(timeStep);
        } else if (type == "Square") {
            static_cast<Square*>(figurePtr)->move(timeStep);
        } else if (type == "Circle") {
            static_cast<Circle*>(figurePtr)->move(timeStep);
        }
    }

    /*
     * Получение координаты X центра фигуры.
     *
     * @return координата X.
     */
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

    /*
     * Получение координаты Y центра фигуры.
     *
     * @return координата Y.
     */
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

    /*
     * Получение скорости фигуры по оси X.
     *
     * @return скорость по оси X.
     */
    double getVx() const {
        if (type == "Hexagon") {
            return static_cast<Hexagon*>(figurePtr)->vx;
        } else if (type == "Square") {
            return static_cast<Square*>(figurePtr)->vx;
        } else if (type == "Circle") {
            return static_cast<Circle*>(figurePtr)->vx;
        }
        return 0;
    }

    /*
     * Получение скорости фигуры по оси Y.
     *
     * @return скорость по оси Y.
     */
    double getVy() const {
        if (type == "Hexagon") {
            return static_cast<Hexagon*>(figurePtr)->vy;
        } else if (type == "Square") {
            return static_cast<Square*>(figurePtr)->vy;
        } else if (type == "Circle") {
            return static_cast<Circle*>(figurePtr)->vy;
        }
        return 0;
    }

    /*
     * Установка новой скорости по оси X.
     *
     * @param vx новая скорость по оси X.
     */
    void setVx(double vx) {
        if (type == "Hexagon") {
            static_cast<Hexagon*>(figurePtr)->vx = vx;
        } else if (type == "Square") {
            static_cast<Square*>(figurePtr)->vx = vx;
        } else if (type == "Circle") {
            static_cast<Circle*>(figurePtr)->vx = vx;
        }
    }

    /*
     * Установка новой скорости по оси Y.
     *
     * @param vy новая скорость по оси Y.
     */
    void setVy(double vy) {
        if (type == "Hexagon") {
            static_cast<Hexagon*>(figurePtr)->vy = vy;
        } else if (type == "Square") {
            static_cast<Square*>(figurePtr)->vy = vy;
        } else if (type == "Circle") {
            static_cast<Circle*>(figurePtr)->vy = vy;
        }
    }
};

// Класс сцены
class Scene {
    double width, height; 
    std::vector<Figure> figures; 

    public:
        /*
        * Конструктор класса сцены.
        *
        * @param width ширина сцены.
        * @param height высота сцены.
        */
        Scene(double width, double height) : width(width), height(height) {}

        /*
        * Добавление случайной фигуры на сцену.
        */
        void addRandomFigure() {
            std::string type = randomFigureType();
            Figure newFigure = createRandomFigure(type);

            // Проверяем, что фигура не пересекается с другими фигурами
            bool valid = false;
            for (int attempts = 0; attempts < 100; ++attempts) {
                bool intersects = false;
                for (const auto& f : figures) {
                    if (newFigure.intersects(f)) {
                        intersects = true;
                        break;
                    }
                }

                if (!intersects && isInsideScene(newFigure)) {
                    valid = true;
                    break;
                }

                // Пробуем другую позицию
                newFigure = createRandomFigure(type);
            }

            if (valid) {
                figures.push_back(newFigure);
            } else {
                std::cout << "Не удалось разместить фигуру на сцене\n";
            }
        }

        /*
        * Вычисление суммарной площади всех фигур на сцене.
        *
        * @return суммарная площадь всех фигур.
        */
        double totalArea() const {
            double total = 0;
            for (const auto& f : figures) {
                total += f.area();
            }
            return total;
        }

        /*
        * Симуляция движения всех фигур на сцене в течение заданного времени.
        *
        * @param simulationTime общее время симуляции.
        * @param timeStep шаг времени для обновления положения фигур.
        */
        void simulateMovement(double simulationTime, double timeStep) {
            for (double currentTime = 0; currentTime <= simulationTime; currentTime += timeStep) {
                // Движение фигур
                for (size_t i = 0; i < figures.size(); ++i) {
                    auto& f = figures[i];
                    f.move(timeStep);

                    checkWallCollision(f, i + 1); // Проверка столкновения со стенками

                    // Проверка столкновений с другими фигурами
                    for (size_t j = i + 1; j < figures.size(); ++j) {
                        auto& other = figures[j];
                        if (f.intersects(other)) {
                            resolveCollision(f, other, i + 1, j + 1);  
                        }
                    }
                }

                std::cout << "Прошло: " << currentTime << " секунд:\n";
                for (size_t i = 0; i < figures.size(); ++i) {
                    const auto& f = figures[i];
                    std::cout << "Фигура #" << i + 1 << " (" << f.type << ") в (" << f.getX() << ", " << f.getY()
                            << ") с vx=" << f.getVx() << ", vy=" << f.getVy() << "\n";
                }
            }
        }

    private:
        /*
        * Генерация случайного типа фигуры.
        *
        * @return строка с типом фигуры (Hexagon, Square, Circle).
        */
        std::string randomFigureType() {
            int r = rand() % 3;
            if (r == 0) return "Hexagon";
            if (r == 1) return "Square";
            return "Circle";
        }

        /*
        * Генерация случайной фигуры с случайными параметрами положения и скорости.
        *
        * @param type тип фигуры (Hexagon, Square, Circle).
        * @return объект Figure, содержащий случайно сгенерированную фигуру.
        */
        Figure createRandomFigure(const std::string& type) {
            double x = rand() % static_cast<int>(width);
            double y = rand() % static_cast<int>(height);
            double vx = (rand() % 200 - 100) / 100.0; // скорость от -1 до 1
            double vy = (rand() % 200 - 100) / 100.0;

            if (type == "Hexagon") {
                return Figure(new Hexagon(x, y, rand() % 10 + 1, vx, vy), "Hexagon");
            } else if (type == "Square") {
                return Figure(new Square(x, y, rand() % 10 + 1, vx, vy), "Square");
            } else if (type == "Circle") {
                return Figure(new Circle(x, y, rand() % 10 + 1, vx, vy), "Circle");
            }
            return Figure(nullptr, "Unknown"); // Невозможный тип фигуры
        }

        /*
        * Проверка, находится ли фигура внутри границ сцены.
        *
        * @param figure фигура для проверки.
        * @return true, если фигура находится внутри границ сцены, иначе false.
        */
        bool isInsideScene(const Figure& figure) {
            double radius = figure.getCircumscribedRadius();
            return (figure.getX() - radius >= 0 && figure.getX() + radius <= width &&
                    figure.getY() - radius >= 0 && figure.getY() + radius <= height);
        }

        /*
        * Проверка на столкновение фигуры со стенками сцены.
        *
        * @param figure фигура для проверки.
        * @param figureNumber номер фигуры в списке.
        */
        void checkWallCollision(Figure& figure, int figureNumber) {
            double radius = figure.getCircumscribedRadius();

            if (figure.getX() - radius < 0 || figure.getX() + radius > width) {
                std::cout << "Фигура #" << figureNumber << " (" << figure.type << ") столкнулась со стенкой по оси X\n";
                figure.setVx(-figure.getVx()); // Инвертируем скорость по x
            }
            if (figure.getY() - radius < 0 || figure.getY() + radius > height) {
                std::cout << "Фигура #" << figureNumber << " (" << figure.type << ") столкнулась со стенкой по оси Y\n";
                figure.setVy(-figure.getVy()); // Инвертируем скорость по y
            }
        }

    /*
     * Разрешение столкновения между двумя фигурами.
     *
     * @param f1 первая фигура.
     * @param f2 вторая фигура.
     * @param f1Number номер первой фигуры.
     * @param f2Number номер второй фигуры.
     */
    void resolveCollision(Figure& f1, Figure& f2, int f1Number, int f2Number) {
        std::cout << "Фигура #" << f1Number << " (" << f1.type << ") столкнулась с фигурой #" << f2Number << " (" << f2.type << ")\n";
        // Меняем направление движения обеих фигур при столкновении
        f1.setVx(-f1.getVx());
        f1.setVy(-f1.getVy());

        f2.setVx(-f2.getVx());
        f2.setVy(-f2.getVy());
    }
};

int main() {
    srand(time(NULL));

    const double SCENE_WIDTH = 100;
    const double SCENE_HEIGHT = 100;
    const double TIME_STEP = 0.5;  
    const double SIMULATION_TIME = 20.0; 

    Scene scene(SCENE_WIDTH, SCENE_HEIGHT);
    
    int N;
    std::cout << "Введите количество фигур для добавления: ";
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        scene.addRandomFigure();
    }
    
    std::cout << "Суммарная площадь всех фигур: " << scene.totalArea() << std::endl;
    scene.simulateMovement(SIMULATION_TIME, TIME_STEP);

    return 0;
}

