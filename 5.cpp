#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    void push(const T& item) {
        elements.push_back(item);
        std::cout << "Добавлен в инвентарь: " << item << std::endl;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("Инвентарь пуст!");
        }
        T frontItem = elements.front();
        elements.erase(elements.begin());
        std::cout << "Использован предмет: " << frontItem << std::endl;
        return frontItem;
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

int main() {
    try {
        // Очередь для квестовых предметов
        Queue<std::string> questItems;
        
        std::cout << "\n=== Квестовые предметы ===" << std::endl;
        questItems.push("Древний артефакт");
        questItems.push("Карта сокровищ");
        questItems.push("Запечатанное письмо");
        questItems.push("Руна загадочного языка");
        
        while (!questItems.empty()) {
            questItems.pop();
        }

        // Очередь для зелий
        Queue<std::string> potions;
        
        std::cout << "\n=== Аптечка ===\n";
        potions.push("Зелье здоровья (+50 HP)");
        potions.push("Зелье маны (+30 MP)");
        potions.push("Зелье невидимости");
        
        potions.pop(); // Использовали зелье здоровья
        
        // Очередь для оружия
        Queue<std::string> weapons;
        
        std::cout << "\n=== Оружейная ===" << std::endl;
        weapons.push("Стальной меч");
        weapons.push("Лук тёмного эльфа");
        weapons.push("Посох архимага");
        
        std::cout << "\nГотово! Инвентарь содержит " << weapons.size() 
                  << " единиц оружия" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "[ОШИБКА] " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}