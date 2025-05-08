#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

// Класс персонажа и монстра — полностью взаимозаменяемый
class Fighter {
    std::string name_;
    int health_;
    int attack_;
public:
    Fighter(const std::string& n, int hp, int att)
      : name_(n), health_(hp), attack_(att) {}

    // Поток будет читать/писать health_, поэтому доступ синхронизируется снаружи
    void takeDamage(int dmg) { health_ -= dmg; }
    bool isAlive() const    { return health_ > 0; }

    int  getAttack() const  { return attack_; }
    int  getHealth() const  { return health_; }
    const std::string& getName() const { return name_; }

    void displayInfo() const {
        std::cout << name_ 
                  << "  HP=" << health_ 
                  << "  ATK=" << attack_ 
                  << "\n";
    }
};

// Общий мьютекс для боя
std::mutex fightMutex;

// Функция, имитирующая бой до смерти одного из бойцов
void simulateBattle(Fighter& hero, Fighter& monster) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Открываем «критическую секцию» на время обмена ударами
        std::lock_guard<std::mutex> lock(fightMutex);

        if (!hero.isAlive() || !monster.isAlive())
            break;

        // Герой бьёт первым
        monster.takeDamage(hero.getAttack());
        std::cout << hero.getName() << " hits " 
                  << monster.getName() 
                  << " for " << hero.getAttack() << " dmg.  [" 
                  << monster.getName() << " HP=" 
                  << monster.getHealth() << "]\n";

        if (!monster.isAlive())
            break;

        // Монстр отвечает
        hero.takeDamage(monster.getAttack());
        std::cout << monster.getName() << " hits " 
                  << hero.getName() 
                  << " for " << monster.getAttack() << " dmg.  [" 
                  << hero.getName() << " HP=" 
                  << hero.getHealth() << "]\n";
    }

    // Кто победил?
    if (hero.isAlive())
        std::cout << "\n*** " << hero.getName() 
                  << " wins! ***\n";
    else
        std::cout << "\n*** " << monster.getName() 
                  << " wins! ***\n";
}

int main() {
    // 1) Создаём персонажа и монстра
    Fighter hero("Hero",    100, 20);
    Fighter monster("Orc",   80,  15);

    // 2) Запускаем поток боя
    std::thread battleThread(simulateBattle, 
                             std::ref(hero), 
                             std::ref(monster));

    // 3) Ждём, пока бой закончится
    battleThread.join();

    // 4) Выводим финальное состояние (может быть избыточно)
    std::cout << "\nFinal status:\n";
    hero.   displayInfo();
    monster.displayInfo();

    return 0;
}