#include <iostream>
#include <string>

// Базовый класс
class Entity 
{
protected:
    std::string name;
    int health;

public:
    Entity(std::string n, int h) : name(n), health(h) {}

    void displayInfo() 
    {
        std::cout << "Имя: " << name << "\nЗдоровье: " << health << std::endl;
    }
};

// Производный класс Игрока
class Player : public Entity 
{
private:
    int level;

public:
    Player(std::string n, int h, int lvl) : Entity(n, h), level(lvl) {}

    void displayInfo() 
    {
        Entity::displayInfo(); // Вызов метода родителя
        std::cout << "Уровень: " << level << std::endl;
    }
};

// Производный класс Врага
class Enemy : public Entity 
{
private:
    int damage;

public:
    Enemy(std::string n, int h, int dmg) : Entity(n, h), damage(dmg) {}

    void displayInfo() 
    {
        Entity::displayInfo();
        std::cout << "Урон: " << damage << std::endl;
    }
};

class Boss : public Enemy 
{
private:
    std::string specialAbility;

public:
    Boss(std::string n, int h, int dmg, std::string ability) 
        : Enemy(n, h, dmg), specialAbility(ability) {}

    virtual void displayInfo() 
    {
        Enemy::displayInfo();
        std::cout << "Способность: " << specialAbility << std::endl;
    }
};

int main() 
{
    Player hero("Герой", 100, 5);

    Boss dragon("Дракон", 200, 30, "Огненное дыхание");
    std::cout << "----------------\n";
    dragon.displayInfo();

    return 0;
}