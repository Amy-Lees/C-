#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

class Entity {
private:
    std::string name;
    int health;
    int level;

public:
    Entity(const std::string& n, int h, int l)
        : name(n), health(h), level(l) {}

    // Виртуального деструктора здесь не нужно, 
    // т. к. у нас нет наследников, но можно добавить:
    virtual ~Entity() = default;

    void displayInfo() const {
        std::cout << "Name: " << name
                  << ", Health: " << health
                  << ", Level: "  << level
                  << std::endl;
    }

    const std::string& getName()   const { return name;   }
    int               getHealth() const { return health; }
    int               getLevel()  const { return level;  }
};

template <typename T>
class Queue {
    std::vector<T> entities;
public:
    void addEntity(T entity) {
        entities.push_back(std::move(entity));
    }

    void display() const {
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
    }

    const std::vector<T>& getEntities() const {
        return entities;
    }
};

// Сохранение в файл: каждая строка — name health level
void saveToFile(const Queue<std::shared_ptr<Entity>>& queue,
                const std::string& filename)
{
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    for (const auto& e : queue.getEntities()) {
        file << e->getName()   << ' '
             << e->getHealth() << ' '
             << e->getLevel()  << '\n';
    }
}

// Загрузка из файла
void loadFromFile(Queue<std::shared_ptr<Entity>>& queue,
                  const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    std::string name;
    int hp, lvl;
    while (file >> name >> hp >> lvl) {
        queue.addEntity(std::make_shared<Entity>(name, hp, lvl));
    }
}

int main() {
    try {
        Queue<std::shared_ptr<Entity>> manager;
        manager.addEntity(std::make_shared<Entity>("Hero", 100, 5));
        manager.addEntity(std::make_shared<Entity>("Enemy", 200, 1));

        saveToFile(manager, "game_save.txt");

        Queue<std::shared_ptr<Entity>> loadedManager;
        loadFromFile(loadedManager, "game_save.txt");

        std::cout << "Loaded entities:\n";
        loadedManager.display();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}