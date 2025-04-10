#include <iostream>
#include <string>

class Character 
{
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    // Конструктор
    Character(std::string n, int h, int a, int d) 
        : name(n), health(h), attack(a), defense(d) 
    {
        std::cout << "Создан персонаж: " << name << std::endl;
    }

    // Деструктор
    ~Character() 
    {
        std::cout << "Персонаж " << name << " уничтожен!" << std::endl;
    }

    // Метод для вывода информации
    void displayInfo() 
    {
        std::cout << "Имя: " << name << "\nЗдоровье: " << health 
                  << "\nАтака: " << attack << "\nЗащита: " << defense << "\n";
    }
};

class Monster 
{
private:
    std::string name;
    int health;
    int damage;

public:
    // Конструктор
    Monster(std::string n, int h, int dmg) 
        : name(n), health(h), damage(dmg) 
    {
        std::cout << "Появился монстр: " << name << std::endl;
    }

    // Деструктор
    ~Monster() 
    {
        std::cout << "Монстр " << name << " уничтожен!" << std::endl;
    }

    // Метод для вывода информации
    void displayInfo() 
    {
        std::cout << "Монстр: " << name << "\nЗдоровье: " << health 
                  << "\nУрон: " << damage << "\n";
    }
};

class Weapon 
{
private:
    std::string name;
    int damage;
    float weight;

public:
    // Конструктор
    Weapon(std::string n, int dmg, float w) 
        : name(n), damage(dmg), weight(w) 
    {
        std::cout << "Создано оружие: " << name << std::endl;
    }

    // Деструктор
    ~Weapon() 
    {
        std::cout << "Оружие " << name << " уничтожено!" << std::endl;
    }

    // Метод для вывода информации
    void displayInfo() 
    {
        std::cout << "Оружие: " << name << "\nУрон: " << damage 
                  << "\nВес: " << weight << " кг\n";
    }
};

int main() 
{
    // Создание объектов
    Character hero("Герой", 100, 20, 10);
    Monster orc("Дракон", 50, 15);
    Weapon sword("Меч", 25, 3.5);

    // Вывод информации
    std::cout << "\n=== Информация о персонаже ===" << std::endl;
    hero.displayInfo();

    std::cout << "\n=== Информация о монстре ===" << std::endl;
    orc.displayInfo();

    std::cout << "\n=== Информация об оружии ===" << std::endl;
    sword.displayInfo();

    return 0;
}