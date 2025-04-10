#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Entity {
protected:
    string name;
    int health;
    int attackPower;
    int defense;

public:
    Entity(const string& n, int h, int a, int d)
        : name(n), health(h), attackPower(a), defense(d) 
    {
    }

    virtual ~Entity() {}

    string getName() const { return name; }
    int getHealth() const { return health; }
    int getDefense() const { return defense; }

    void reduceHealth(int amount) { health -= amount; }

    virtual void attack(Entity& target) = 0;

    virtual void heal(int amount) 
    {
        cout << name << " cannot heal!\n";
    }

    virtual void displayInfo() const 
    {
        cout << "Имя: " << name << ", HP: " << health
            << ", Атака: " << attackPower << ", Защита: " << defense << endl;
    }
};

class Character : public Entity 
{
public:
    Character(const string& n, int h, int a, int d)
        : Entity(n, h, a, d) 
        {
    }

    void attack(Entity& target) override
    {
        int damage = attackPower - target.getDefense();
        if (damage > 0) 
        {
            if (rand() % 100 < 20) 
            { // Критический удар (20%)
                damage *= 2;
                cout << "Критический удар! ";
            }
            target.reduceHealth(damage);
            cout << name << " атакует " << target.getName() << ", нанося " << damage << " урона!\n";
        }
        else 
        {
            cout << name << " атакует " << target.getName() << ", но безрезультатно!\n";
        }
    }

    void heal(int amount) override 
    {
        health += amount;
        if (health > 100) 
        {
            health == 100;
        }
        cout << name << " получает лечение " << amount << " HP!\n";
    }

    void displayInfo() const override 
    {
        cout << "Персонаж: " << name << ", HP: " << health
            << ", Атака: " << attackPower << ", Защита: " << defense << endl;
    }
};

class Monster : public Entity 
{
public:
    Monster(const string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }

    void attack(Entity& target) override {
        int damage = attackPower - target.getDefense();
        if (damage > 0) 
        {
            if (rand() % 100 < 30) 
            {
                damage += 5;
                cout << " огненная атака! ";
            }
            target.reduceHealth(damage);
            cout << name << " атакует " << target.getName() << " нанося " << damage << " урона!\n";
        }
        else 
        {
            cout << name << " attacks " << target.getName() << ", но безрезультатно!\n";
        }
    }

    void displayInfo() const override 
    {
        cout << "Монстр: " << name << ", HP: " << health
            << ", Атака: " << attackPower << ", Защита: " << defense << endl;
    }
};

// Новый класс Boss, унаследованный от Monster
class Boss : public Monster 
{
public:
    Boss(const string& n, int h, int a, int d)
        : Monster(n, h, a, d) 
    {
    }

    void attack(Entity& target) override {
        int damage = attackPower - target.getDefense();
        if (damage > 0) 
        {
            if (rand() % 100 < 40) { // Луч болезни (40% вероятность)
                damage += 10;
                cout << "Ray of Disease! ";
            }
            target.reduceHealth(damage);
            cout << name << " обрушивает мощную атаку на " << target.getName()
                << " на " << damage << " damage!\n";
        }
        else 
        {
            cout << name << " атакует " << target.getName() << ", но безрезультатно!\n";
        }
    }

    void displayInfo() const override 
    {
        cout << "Босс: " << name << ", HP: " << health
            << ", Атака: " << attackPower << ", Защита: " << defense << endl;
    }
};

int main() 
{
    srand(static_cast<unsigned>(time(0)));

    Character hero("Hero", 100, 20, 10);
    Monster goblin("dragon", 50, 15, 5);
    Boss dragon("Necromancer", 100, 30, 15);

    Entity* entities[] = { &hero, &goblin, &dragon };

    // Вывод информации о всех сущностях
    for (auto& entity : entities) {
        entity->displayInfo();
    }

    // Бой
    hero.attack(goblin);
    goblin.attack(hero);
    dragon.attack(hero);

    // Лечение персонажа
    cout << "\nHero решил вылечиться...\n";
    hero.heal(30);

    // Вывод обновлённой информации
    cout << "\nОбновленные статы:\n";
    for (auto& entity : entities) {
        entity->displayInfo();
    }

    return 0;
}