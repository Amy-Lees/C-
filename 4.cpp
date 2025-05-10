#include <iostream>
#include <memory>
#include <string>

class Inventory {
private:
    std::unique_ptr<std::string[]> items_;  // динамический массив строк
    size_t size_ = 0;       // текущее число предметов
    size_t capacity_ = 0;   // ёмкость массива

    // увеличить capacity (обычно в 2 раза)
    void grow() {
        size_t newCap = capacity_ == 0 ? 4 : capacity_ * 2;
        // выделяем новый массив
        auto newItems = std::make_unique<std::string[]>(newCap);
        // копируем старые строки
        for (size_t i = 0; i < size_; ++i) {
            newItems[i] = std::move(items_[i]);
        }
        // перекидываем указатель и обновляем capacity
        items_    = std::move(newItems);
        capacity_ = newCap;
    }

public:
    Inventory() = default;

    // добавить предмет
    void addItem(const std::string& item) {
        if (size_ >= capacity_) {
            grow();
        }
        items_[size_++] = item;
    }

    // вывести весь инвентарь
    void displayInventory() const {
        std::cout << "=== Инвентарь (" << size_ << " предметов) ===\n";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << " " << (i+1) << ") " << items_[i] << "\n";
        }
        if (size_ == 0) {
            std::cout << " <пусто>\n";
        }
    }
};

int main() {
    try {
        Inventory inv;

        inv.displayInventory();  // пока пусто

        inv.addItem("Меч");
        inv.addItem("Щит");
        inv.addItem("Зелье лечения");
        inv.addItem("Лук");
        inv.addItem("Стрелы x20");

        inv.displayInventory();

        // добавим ещё
        inv.addItem("Руна силы");
        inv.displayInventory();
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}