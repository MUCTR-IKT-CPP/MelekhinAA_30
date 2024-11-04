#include <iostream>
#include <complex>
#include <optional>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <set>  // Добавляем для использования std::set

// Компаратор для комплексных чисел
struct ComplexComparator {
    bool operator()(const std::complex<int>& a, const std::complex<int>& b) const {
        if (std::abs(a) < std::abs(b)) {
            return true;
        } else if (std::abs(a) > std::abs(b)) {
            return false;
        }
        // Если модули равны, сравниваем по действительной части
        return a.real() < b.real();
    }
};

class QuadraticEquation {
private:
    std::complex<int> a, b, c;  // Коэффициенты уравнения (целые комплексные числа)
    std::optional<std::complex<int>> root1, root2;  // Корни уравнения, могут быть пустыми

public:
    // Конструктор принимает коэффициенты и сразу находит корни
    QuadraticEquation(std::complex<int> a, std::complex<int> b, std::complex<int> c) 
        : a(a), b(b), c(c) {
        
        // Обработка различных случаев в зависимости от значений a, b и c
        if (a != std::complex<int>(0, 0)) {
            // Квадратное уравнение: решаем через дискриминант
            std::complex<int> discriminant = b * b - std::complex<int>(4) * a * c;
            root1 = (-b + std::sqrt(discriminant)) / (std::complex<int>(2) * a);
            root2 = (-b - std::sqrt(discriminant)) / (std::complex<int>(2) * a);
        } else if (b != std::complex<int>(0, 0)) {
            // Линейное уравнение: bx + c = 0
            root1 = -c / b;
            root2 = std::nullopt;  // Только один корень
        } else {
            // Уравнение превращается в c = 0
            if (c == std::complex<int>(0, 0)) {
                std::cout << "Уравнение имеет бесконечное множество решений." << std::endl;
            } else {
                std::cout << "Уравнение не имеет решений." << std::endl;
            }
        }
    }

    // Перегрузка оператора вывода для отдельного объекта
    friend std::ostream& operator<<(std::ostream& os, const QuadraticEquation& eq) {
        os << "Уравнение: (" << eq.a << ")x^2 + (" << eq.b << ")x + (" << eq.c << ") = 0\n";
        
        if (eq.root1 && eq.root2) {
            os << "Корни уравнения: x1 = " << *eq.root1 << ", x2 = " << *eq.root2;
        } else if (eq.root1) {
            os << "Корень уравнения: x = " << *eq.root1;
        } else {
            os << "Нет действительных корней";
        }
        os << std::endl;
        return os;
    }

    // Метод для проверки наличия корня
    bool containsRoot(const std::complex<int>& number) const {
        return (root1 && *root1 == number) || (root2 && *root2 == number);
    }

    // Статический метод для поиска корня среди вектора уравнений
    static bool hasRoot(const std::vector<QuadraticEquation>& equations, const std::complex<int>& number) {
        return std::any_of(equations.begin(), equations.end(), [&](const QuadraticEquation& eq) {
            return eq.containsRoot(number);
        });
    }

    // Статический метод для подсчета количества корней, меньших заданного числа
    static int countRootsLessThan(const std::vector<QuadraticEquation>& equations, const std::complex<int>& number) {
        return std::count_if(equations.begin(), equations.end(), [&](const QuadraticEquation& eq) {
            return (eq.root1 && std::abs(*eq.root1) < std::abs(number)) +
                   (eq.root2 && std::abs(*eq.root2) < std::abs(number));
        });
    }

    // Новый статический метод для получения уникальных корней
    static std::vector<std::complex<int>> uniqueRoots(const std::vector<QuadraticEquation>& equations) {
        std::set<std::complex<int>, ComplexComparator> uniqueRootsSet;  // Используем компаратор

        for (const auto& eq : equations) {
            if (eq.root1) {
                uniqueRootsSet.insert(*eq.root1); // Добавляем первый корень
            }
            if (eq.root2) {
                uniqueRootsSet.insert(*eq.root2); // Добавляем второй корень
            }
        }

        return std::vector<std::complex<int>>(uniqueRootsSet.begin(), uniqueRootsSet.end());
    }
};

// Функция для генерации случайных целых комплексных чисел
std::complex<int> generateRandomComplex() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(-10, 10);
    return {dis(gen), dis(gen)};
}

int getNumber(const std::string &message) {
    int number;
    std::cout << message;
    std::cin >> number;
    return number;
}

int main() {
    int N = getNumber("Введите количество уравнений: ");
    std::vector<QuadraticEquation> equations;

    // Генерируем N объектов и добавляем их в контейнер
    for (int i = 0; i < N; ++i) {
        std::complex<int> a = generateRandomComplex();
        std::complex<int> b = generateRandomComplex();
        std::complex<int> c = generateRandomComplex();
        equations.emplace_back(a, b, c);
    }

    // Выводим все уравнения из контейнера
    std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

    // Запрашиваем у пользователя число для проверки наличия корня
    std::cout << "Введите комплексное число для поиска корня (формат: a + bi):" << std::endl;
    int realPart = getNumber("Введите вещественную часть: "); 
    int imaginaryPart = getNumber("Введите мнимую часть: ");
    std::complex<int> userInput(realPart, imaginaryPart);

    // Проверка, есть ли уравнения с данным корнем
    if (QuadraticEquation::hasRoot(equations, userInput)) {
        std::cout << "Данное комплексное число является корнем хотя бы одного уравнения." << std::endl;
    } else {
        std::cout << "Данное комплексное число не является корнем ни одного уравнения." << std::endl;
    }

    // Запрашиваем у пользователя число для подсчета корней меньше этого числа
    std::cout << "Введите комплексное число для сравнения корней (формат: a + bi):" << std::endl;
    realPart = getNumber("Введите вещественную часть: ");
    imaginaryPart = getNumber("Введите мнимую часть: "); 
    std::complex<int> threshold(realPart, imaginaryPart);

    // Подсчет количества корней, меньших заданного числа
    int count = QuadraticEquation::countRootsLessThan(equations, threshold);
    std::cout << "Количество корней, модуль которых меньше заданного числа: " << count << std::endl;

    // Получение уникальных корней
    std::vector<std::complex<int>> uniqueRoots = QuadraticEquation::uniqueRoots(equations);
    std::cout << "Уникальные корни уравнений:" << std::endl;
    for (const auto& root : uniqueRoots) {
        std::cout << root << std::endl;
    }

    return 0;
}
