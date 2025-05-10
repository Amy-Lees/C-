#include <iostream>
#include <queue>
#include <stdexcept> // Для std::out_of_range
#include <string>

template <typename T>
class Queue {
private:
    std::queue<T> data;

public:
    void push(const T& item) {
        data.push(item);
        std::cout << "Добавлен элемент: " << item << std::endl;
    }

    T pop() {
        if (data.empty()) {
            throw std::out_of_range("Попытка удалить элемент из пустой очереди");
        }
        T item = data.front();
        data.pop();
        std::cout << "Удален элемент: " << item << std::endl;
        return item;
    }

    bool isEmpty() const {
        return data.empty();
    }
};

int main() {
    Queue<std::string> stringQueue;

    try {
        stringQueue.pop(); // Попытка удалить элемент из пустой очереди
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    stringQueue.push("Зелье");
    stringQueue.push("Карта");

    try {
        stringQueue.pop();
        stringQueue.pop();
        stringQueue.pop(); // Попытка удалить из пустой очереди после удаления всех элементов
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}