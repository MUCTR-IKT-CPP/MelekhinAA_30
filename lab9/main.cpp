#include <iostream>
#include <complex>
#include <optional>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <set>
#include <cmath>

struct ComplexComparator {
    bool operator()(const std::complex<double>& a, const std::complex<double>& b) const {
        return std::abs(a) < std::abs(b);
    }
};

std::complex<double> roundComplex(const std::complex<double>& number) {
    double realPart = std::round(number.real() * 100.0) / 100.0;
    double imagPart = std::round(number.imag() * 100.0) / 100.0;
    return {realPart, imagPart};
}

class QuadraticEquation {
private:
    std::complex<double> a, b, c;
    std::optional<std::complex<double>> root1, root2;

public:
    QuadraticEquation(std::complex<double> a, std::complex<double> b, std::complex<double> c)
        : a(roundComplex(a)), b(roundComplex(b)), c(roundComplex(c)) {

        if (a != std::complex<double>(0.0, 0.0)) {
            std::complex<double> discriminant = b * b - std::complex<double>(4.0) * a * c;
            root1 = roundComplex((-b + std::sqrt(discriminant)) / (std::complex<double>(2.0) * a));
            root2 = roundComplex((-b - std::sqrt(discriminant)) / (std::complex<double>(2.0) * a));
        } else if (b != std::complex<double>(0.0, 0.0)) {
            root1 = roundComplex(-c / b);
            root2 = std::nullopt;
        } else {
            if (c == std::complex<double>(0.0, 0.0)) {
                std::cout << "Уравнение имеет бесконечное множество решений." << std::endl;
            } else {
                std::cout << "Уравнение не имеет решений." << std::endl;
            }
        }
    }

    std::optional<std::complex<double>> getRoot1() const { return root1; }
    std::optional<std::complex<double>> getRoot2() const { return root2; }

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

    bool containsRoot(const std::complex<double>& number) const {
        return (root1 && *root1 == number) || (root2 && *root2 == number);
    }

    std::optional<std::complex<double>> sumOfRoots() const {
        if (root1 && root2) {
            return *root1 + *root2;
        } else if (root1) {
            return *root1;
        } else if (root2){
            return *root2;
        }
        return std::nullopt;
    }
};

bool hasRoot(const std::vector<QuadraticEquation>& equations, const std::complex<double>& number) {
    return std::any_of(equations.begin(), equations.end(), [&](const QuadraticEquation& eq) {
        return eq.containsRoot(number);
    });
}

int countRoots(const std::vector<QuadraticEquation>& equations, const std::complex<double>& number) {
    return std::count_if(equations.begin(), equations.end(), [&](const QuadraticEquation& eq) {
        int count = 0;
        if (eq.getRoot1() && std::abs(*eq.getRoot1()) < std::abs(number)) count++;
        if (eq.getRoot2() && std::abs(*eq.getRoot2()) < std::abs(number)) count++;
        return count;
    });
}

std::vector<std::complex<double>> uniqueRoots(const std::vector<QuadraticEquation>& equations) {
    std::set<std::complex<double>, ComplexComparator> uniqueRootsSet;

    for (const QuadraticEquation& eq : equations) {
        if (eq.getRoot1()) {
            uniqueRootsSet.insert(*eq.getRoot1());
        }
        if (eq.getRoot2()) {
            uniqueRootsSet.insert(*eq.getRoot2());
        }
    }

    return std::vector<std::complex<double>>(uniqueRootsSet.begin(), uniqueRootsSet.end());
}

void sortRoots(std::vector<QuadraticEquation>& equations) {
    std::sort(equations.begin(), equations.end(), [](const QuadraticEquation& eq1, const QuadraticEquation& eq2) {
        std::optional<std::complex<double>> sum1 = eq1.sumOfRoots();
        std::optional<std::complex<double>> sum2 = eq2.sumOfRoots();

        if (!sum1) return false;
        if (!sum2) return true;

        return std::abs(*sum1) < std::abs(*sum2);
    });
}

// Функция для генерации случайных дробных комплексных чисел
std::complex<double> generateRandomComplex() {
    double realPart = ((static_cast<double>(rand()) / RAND_MAX) * 20.0) - 10.0;
    double imagPart = ((static_cast<double>(rand()) / RAND_MAX) * 20.0) - 10.0;
    return roundComplex({realPart, imagPart});
}

double getDouble(const std::string &message) {
    double number;
    std::cout << message;
    std::cin >> number;
    return number;
}

int main() {
    srand((time(NULL)));
    int N;
    std::cout << "Введите количество уравнений: ";
    std::cin >> N;
    
    std::vector<QuadraticEquation> equations;

    for (int i = 0; i < N; ++i) {
        std::complex<double> a = generateRandomComplex();
        std::complex<double> b = generateRandomComplex();
        std::complex<double> c = generateRandomComplex();
        equations.emplace_back(a, b, c);
    }

    std::cout << "\nСписок уравнений до сортировки:\n";
    std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

    std::cout << "\nВведите комплексное число для поиска корня (формат: a + bi):" << std::endl;
    double realPart = getDouble("Введите вещественную часть: "); 
    double imaginaryPart = getDouble("Введите мнимую часть: ");
    std::complex<double> userInput(realPart, imaginaryPart);

    if (hasRoot(equations, userInput)) {
        std::cout << "Данное комплексное число является корнем хотя бы одного уравнения." << std::endl;
    } else {
        std::cout << "Данное комплексное число не является корнем ни одного уравнения." << std::endl;
    }

    std::cout << "\nВведите комплексное число для сравнения корней (формат: a + bi):" << std::endl;
    realPart = getDouble("Введите вещественную часть: ");
    imaginaryPart = getDouble("Введите мнимую часть: "); 
    std::complex<double> threshold(realPart, imaginaryPart);

    int count = countRoots(equations, threshold);
    std::cout << "Количество корней, модуль которых меньше заданного числа: " << count << std::endl;

    std::vector<std::complex<double>> uniqueRootsList = uniqueRoots(equations);
    std::cout << "\nУникальные корни уравнений:" << std::endl;
    for (const std::complex<double>& root : uniqueRootsList) {
        std::cout << root << std::endl;
    }
    
    sortRoots(equations);
    std::cout << "\nСписок уравнений после сортировки по возрастанию суммы корней:\n";
    std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

    return 0;
}
