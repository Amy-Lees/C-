#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <exception>

using namespace std;

// Исключение для отрицательного здоровья
class NegativeHealthException : public exception {
public:
    const char* what() const noexcept override {
        return "Health cannot be negative";
    }
};

// Шаблонный логгер
template<typename T>
class Logger {
    string filename;
public:
    Logger(const string& fn) : filename(fn) {}
    void log(const T& message) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << message << endl;
        }
    }
};

// Класс Inventory: хранение предметов
class Inventory {
    vector<string> items;
public:
    void addItem(const string& item) {
        items.push_back(item);
        cout << "Added to inventory: " << item << endl;
    }
    void removeItem(const string& item) {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
            cout << "Removed from inventory: " << item << endl;
        } else {
            cout << "Item not found: " << item << endl;
        }
    }
    void show() const {
        if (items.empty()) {
            cout << "Inventory is empty!" << endl;
            return;
        }
        cout << "Inventory items:" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i+1 << ". " << items[i] << endl;
        }
    }
    // Сохранение / загрузка инвентаря
    void save(ofstream& out) const {
        size_t n = items.size();
        out << n << endl;
        for (auto& it : items) out << it << endl;
    }
    void load(ifstream& in) {
        items.clear();
        size_t n;
        in >> n;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        string tmp;
        for (size_t i = 0; i < n; ++i) {
            getline(in, tmp);
            items.push_back(tmp);
        }
    }
};

// Вперёд объявление Monster
class Monster;

class Character {
    string name;
    int hp;
    int attackPower;
    int defense;
    int level;
    int experience;
    Inventory inventory;
public:
    Character(const string& n = "Hero")
        : name(n), hp(100), attackPower(10), defense(5), level(1), experience(0) {}

    // Получить урон
    void takeDamage(int dmg) {
        if (dmg < 0) dmg = 0;
        if (hp - dmg < 0) throw NegativeHealthException();
        hp -= dmg;
    }
    // Атака монстра
    void attackEnemy(Monster& target);
    // Лечение
    void heal(int amount) {
        hp += amount;
        if (hp > 100) hp = 100;
        cout << name << " heals for " << amount << " HP." << endl;
    }
    // Опыт и повышение уровня
    void gainExp(int exp) {
        experience += exp;
        cout << name << " gains " << exp << " EXP." << endl;
        if (experience >= 100) {
            level++;
            experience -= 100;
            attackPower += 2;
            defense += 1;
            cout << name << " leveled up to " << level
                 << "! Attack+" << 2 << ", Defense+" << 1 << endl;
        }
    }
    // Вывод информации
    void displayInfo() const {
        cout << "=== Character ===" << endl
             << "Name: " << name << endl
             << "HP: " << hp << endl
             << "Attack: " << attackPower << endl
             << "Defense: " << defense << endl
             << "Level: " << level << endl
             << "EXP: " << experience << endl;
    }

    // Геттеры
    const string& getName() const { return name; }
    int getHp() const { return hp; }
    int getDefense() const { return defense; }
    Inventory& getInventory() { return inventory; }

    // Сохранение/загрузка персонажа
    void save(ofstream& out) const {
        out << name << endl
            << hp << ' ' << attackPower << ' '
            << defense << ' ' << level << ' ' << experience << endl;
        inventory.save(out);
    }
    void load(ifstream& in) {
        in >> ws;
        getline(in, name);
        in >> hp >> attackPower >> defense >> level >> experience;
        inventory.load(in);
    }
};

class Monster {
protected:
    string name;
    int hp;
    int attackPower;
    int defense;
public:
    Monster(const string& n, int h, int a, int d)
        : name(n), hp(h), attackPower(a), defense(d) {}
    virtual ~Monster() = default;

    // Атака персонажа
    virtual void attackEnemy(Character& target) {
        int dmg = attackPower - target.getDefense();
        if (dmg < 0) dmg = 0;
        cout << name << " attacks " << target.getName()
             << " for " << dmg << " damage." << endl;
        target.takeDamage(dmg);
    }
    // Получить урон
    void takeDamage(int dmg) {
        if (dmg < 0) dmg = 0;
        if (hp - dmg < 0) throw NegativeHealthException();
        hp -= dmg;
    }
    int getHp() const { return hp; }
    const string& getName() const { return name; }
    void displayInfo() const {
        cout << "--- Monster ---" << endl
             << "Name: " << name << endl
             << "HP: " << hp << endl
             << "Attack: " << attackPower << endl
             << "Defense: " << defense << endl;
    }
};

// Реализация атаки персонажа
void Character::attackEnemy(Monster& target) {
    int dmg = attackPower - target.defense;
    if (dmg < 0) dmg = 0;
    cout << name << " attacks " << target.getName()
         << " for " << dmg << " damage." << endl;
    target.takeDamage(dmg);
}

// Конкретные монстры
class Goblin : public Monster {
public:
    Goblin() : Monster("Goblin", 30, 6, 2) {}
};
class Dragon : public Monster {
public:
    Dragon() : Monster("Dragon", 120, 20, 8) {}
};
class Skeleton : public Monster {
public:
    Skeleton() : Monster("Skeleton", 50, 8, 4) {}
};

// Игровой класс
class Game {
    Character* hero;
    vector<Monster*> monsters;
    Logger<string> logger;
public:
    Game() : hero(nullptr), logger("game.log") {
        // наполняем перечень монстров
        monsters.push_back(new Goblin());
        monsters.push_back(new Skeleton());
        monsters.push_back(new Dragon());
    }
    ~Game() {
        delete hero;
        for (auto m : monsters) delete m;
    }

    void start() {
        srand(static_cast<unsigned int>(time(nullptr)));
        cout << "=== Welcome to Text RPG ===" << endl;
        hero = new Character();
        cout << "Enter your name: ";
        string nm; getline(cin, nm);
        if (!nm.empty()) *hero = Character(nm);

        mainLoop();
    }

private:
    void mainLoop() {
        while (true) {
            cout << "\n1) Show Status\n"
                 << "2) Fight Monster\n"
                 << "3) Inventory\n"
                 << "4) Save Game\n"
                 << "5) Load Game\n"
                 << "6) Exit\n"
                 << "Choose: ";
            int choice; cin >> choice;
            try {
                switch (choice) {
                case 1: hero->displayInfo(); break;
                case 2: fight(); break;
                case 3: manageInventory(); break;
                case 4: saveGame(); break;
                case 5: loadGame(); break;
                case 6: return;
                default: cout << "Invalid choice\n";
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }

    void fight() {
        Monster* m = monsters[rand() % monsters.size()];
        cout << "\nA wild " << m->getName() << " appears!\n";
        m->displayInfo();

        while (hero->getHp() > 0 && m->getHp() > 0) {
            // ход героя
            hero->attackEnemy(*m);
            logger.log("Hero attacked " + m->getName());
            if (m->getHp() <= 0) {
                cout << m->getName() << " is defeated!\n";
                hero->gainExp(50);
                hero->getInventory().addItem("Gold");
                break;
            }
            // ход монстра
            m->attackEnemy(*hero);
            logger.log(m->getName() + " attacked Hero");
            if (hero->getHp() <= 0) {
                cout << "You died...\n";
                break;
            }
            cout << "Hero HP: " << hero->getHp()
                 << " | " << m->getName() << " HP: " << m->getHp() << endl;
        }
    }

    void manageInventory() {
        hero->getInventory().show();
        cout << "1) Add Potion  2) Remove Item  3) Back\nChoose: ";
        int c; cin >> c;
        string itm;
        switch (c) {
        case 1:
            itm = "Potion";
            hero->getInventory().addItem(itm);
            break;
        case 2:
            cout << "Enter item name to remove: ";
            cin >> ws;
            getline(cin, itm);
            hero->getInventory().removeItem(itm);
            break;
        case 3: return;
        default: cout << "Invalid\n";
        }
    }

    void saveGame() {
        ofstream out("savegame.txt");
        if (!out) {
            cerr << "Cannot open save file!\n";
            return;
        }
        hero->save(out);
        cout << "Game saved.\n";
    }

    void loadGame() {
        ifstream in("savegame.txt");
        if (!in) {
            cerr << "Cannot open save file!\n";
            return;
        }
        hero->load(in);
        cout << "Game loaded.\n";
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}