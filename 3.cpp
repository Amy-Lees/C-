#include <iostream>
#include <string>

// Класс Weapon
class Weapon {
private:
    std::string name;
    int damage;
public:
    Weapon(const std::string& name, int damage)
        : name(name), damage(damage)
    {
        if (name.empty())
            throw std::invalid_argument("Имя оружия не может быть пустым");
        if (damage < 0)
            throw std::invalid_argument("Урон не может быть отрицательным");
    }

    int getDamage() const { return damage; }
    const std::string& getName() const { return name; }

    // 1) Перегрузка оператора +
    Weapon operator+(const Weapon& other) const {
        // новое имя — имя1 + "+" + имя2
        return Weapon(name + "+" + other.name, damage + other.damage);
    }

    // 2) Перегрузка оператора >
    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    // Перегрузка вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Weapon& w) {
        os << w.name << " (Урон: " << w.damage << ")";
        return os;
    }
};

int main() {
    try {
        Weapon sword("Меч",  50);
        Weapon bow(  "Лук",  30);

        // Демонстрация оператора +
        Weapon combo = sword + bow;
        std::cout << "Комбинированное оружие: " << combo << "\n";
        // Ожидаем урон = 80, имя = "Меч+Лук"

        // Демонстрация оператора >
        if (sword > bow) {
            std::cout << sword.getName() << " сильнее, чем " << bow.getName() << "\n";
        } else {
            std::cout << bow.getName() << " сильнее, чем " << sword.getName() << "\n";
        }

        // Дополнительная проверка
        Weapon axe("Топор", 80);
        std::cout << "Сравним топор и комбинированное оружие:\n";
        std::cout << axe << (axe > combo ? " сильнее " : " слабее ")
                  << combo << "\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}