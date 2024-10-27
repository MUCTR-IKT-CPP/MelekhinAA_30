// лаба: https://github.com/MUCTR-IKT-CPP/cpp_course/blob/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D1%8B%D0%B5/2024/lab7.md
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Класс очереди, реализованный с использованием циклического массива.
 * @tparam T Тип элементов, хранящихся в очереди.
 */
template <typename T>
class Queue {
public:
    T* data;            // Массив для хранения данных
    size_t capacity;    // Вместимость очереди
    size_t size;        // Текущий размер очереди
    size_t front;       // Индекс начала очереди
    size_t rear;        // Индекс конца очереди

    /**
     * @brief Изменяет размер массива для хранения данных.
     * @param newCapacity Новая вместимость очереди.
     */
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[(front + i) % capacity];
        }
        delete[] data;
        data = newData;
        front = 0;
        rear = size;
        capacity = newCapacity;
    }

    // Конструктор по умолчанию
    Queue() : data(nullptr), capacity(0), size(0), front(0), rear(0) {}

    // Деструктор для очистки памяти
    ~Queue() {
        delete[] data;
    }

    /**
     * @brief Добавляет элемент в конец очереди.
     * @param value Элемент, который необходимо добавить.
     */
    void enqueue(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // Увеличение массива в два раза при необходимости
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
    }

    /**
     * @brief Получает элемент из начала очереди (без удаления).
     * @return Ссылка на первый элемент очереди.
     * @throws std::out_of_range Если очередь пуста.
     */
    T& frontElement() const {
        if (isEmpty()) {
            throw std::out_of_range("Пустая очередь!");
        }
        return data[front];
    }

    /**
     * @brief Удаляет элемент из начала очереди.
     * @throws std::out_of_range Если очередь пуста.
     */
    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Пустая очередь!");
        }
        front = (front + 1) % capacity;
        size--;
    }

    /**
     * @brief Проверяет, пуста ли очередь.
     * @return true, если очередь пуста; false в противном случае.
     */
    bool isEmpty() const {
        return size == 0;
    }

    /**
     * @brief Получает размер очереди.
     * @return Текущий размер очереди.
     */
    size_t getSize() const {
        return size;
    }

    // Итератор для обхода элементов очереди
    class Iterator {
    private:
        T* data;            // Указатель на массив данных
        size_t index;       // Текущий индекс итератора
        size_t capacity;    // Вместимость очереди
        size_t count;       // Счетчик пройденных элементов

    public:
        /**
         * @brief Конструктор итератора.
         * @param data Указатель на массив данных.
         * @param index Начальный индекс итератора.
         * @param capacity Вместимость очереди.
         * @param count Количество пройденных элементов.
         */
        Iterator(T* data, size_t index, size_t capacity, size_t count)
            : data(data), index(index), capacity(capacity), count(count) {}

        /**
         * @brief Оператор неравенства для итераторов.
         * @param other Другой итератор для сравнения.
         * @return true, если итераторы не равны; false в противном случае.
         */
        bool operator!=(const Iterator& other) const {
            return count != other.count;
        }

        /**
         * @brief Оператор разыменования итератора.
         * @return Ссылка на элемент, на который указывает итератор.
         */
        const T& operator*() const {
            return data[index];
        }

        /**
         * @brief Оператор инкремента для итератора.
         * @return Ссылку на текущий итератор после инкремента.
         */
        Iterator& operator++() {
            index = (index + 1) % capacity;
            ++count;
            return *this;
        }
    };

    /**
     * @brief Начало итератора для обхода элементов.
     * @return Итератор, указывающий на первый элемент очереди.
     */
    Iterator begin() const {
        return Iterator(data, front, capacity, 0);
    }

    /**
     * @brief Конец итератора для обхода элементов.
     * @return Итератор, указывающий на элемент, следующий за последним.
     */
    Iterator end() const {
        return Iterator(data, rear, capacity, size);
    }
};

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
 * @brief Выводит содержимое очереди на экран.
 * @param queue Очередь, которую необходимо вывести.
 */
void printQueue(const Queue<int> &queue) {
    std::cout << "Очередь содержит: ";
    for (const auto &el : queue) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));
    Queue<int> q;
    const int N = getNumber("Введите количество элементов: ");

    for (int i = 0; i < N; i++){
        q.enqueue(rand() % 100);
    }

    printQueue(q);
    q.dequeue(); 
    printQueue(q);
    std::cout << "Первый элемент: " << q.frontElement() << std::endl; 

    return 0;
}

