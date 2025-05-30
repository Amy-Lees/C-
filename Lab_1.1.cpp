#include <iostream>
#include <string>

class Character 
{
private:
    std::string name;
    int health;
    int attack;
    int defense;
    static const int max_health = 100; // Максимальное значение здоровья

public:
    // Конструктор класса
    Character(std::string n, int h, int a, int d) 
        : name(n), health(h), attack(a), defense(d) {}

    // Метод для получения текущего здоровья
    int getHealth() const {
        return health;
    }

    // Метод для вывода информации о персонаже
    void displayInfo() const 
    {
        std::cout << "Имя: " << name << "\nЗдоровье: " << health 
                  << "\nАтака: " << attack << "\nЗащита: " << defense << "\n";
    }

    // Метод для атаки врага
    void attackEnemy(Character& enemy) 
    {
        int damage = attack - enemy.defense;
        if (damage > 0) 
        {
            enemy.health -= damage;
            std::cout << name << " нанес " << damage << " урона " << enemy.name << "!\n";
        } 
        else 
        {
            std::cout << name << " не пробил защиту " << enemy.name << "!\n";
        }
    }
    
    // Метод для лечения
    void heal(int amount) 
    {
        if (amount > 0) 
        {
            health += amount;
            if (health > max_health) 
            {
                health = max_health;
            }
            std::cout << name << " вылечился на " << amount << " HP!" << std::endl;
        }
    }
    
    // Метод для получения урона
    void takeDamage(int amount) 
    {
        if (amount > 0) 
        {
            health -= amount;
            if (health < 0) 
            {
                health = 0;
            }
        }
    }
};

int main() 
{
    Character hero("Герой", 100, 20, 10);
    Character enemy("Враг", 80, 15, 5);

    hero.displayInfo();
    enemy.displayInfo();

    hero.attackEnemy(enemy);
    std::cout << "Здоровье врага: " << enemy.getHealth() << "\n";
    
     // Получаение урона
    hero.takeDamage(40);
    hero.displayInfo();

    // Лечение
    hero.heal(20);
    hero.displayInfo();
    
    return 0;
}