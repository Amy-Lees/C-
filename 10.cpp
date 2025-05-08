#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// -----------------------------
// 1) Базовый класс User
// -----------------------------
class User {
private:
    std::string name_;
    int         id_;
    int         accessLevel_;
public:
    User(const std::string& name, int id, int level)
        : name_(name), id_(id), accessLevel_(level)
    {
        if (name.empty())
            throw std::invalid_argument("Ошибка: имя не может быть пустым");
        if (id < 0)
            throw std::invalid_argument("Ошибка: ID должен быть ≥0");
        if (level < 0 || level > 10)
            throw std::invalid_argument("Ошибка: уровень доступа должен быть от 0 до 10");
    }
    virtual ~User() = default;

    // Геттеры
    const std::string& getName()        const { return name_; }
    int                 getId()          const { return id_; }
    int                 getAccessLevel() const { return accessLevel_; }

    // Сеттеры с валидацией
    void setName(const std::string& n) {
        if (n.empty()) throw std::invalid_argument("Ошибка: имя не может быть пустым");
        name_ = n;
    }
    void setId(int id) {
        if (id < 0) throw std::invalid_argument("Ошибка: ID должен быть ≥0");
        id_ = id;
    }
    void setAccessLevel(int lvl) {
        if (lvl < 0 || lvl > 10)
            throw std::invalid_argument("Ошибка: уровень доступа должен быть от 0 до 10");
        accessLevel_ = lvl;
    }

    // Виртуальный метод для полиморфного вывода
    virtual void displayInfo() const {
        std::cout << "ID=" << id_
                  << " | Имя: " << name_
                  << " | Уровень доступа: " << accessLevel_;
    }

    // Тип для сериализации
    virtual std::string type() const { return "User"; }
};

// -----------------------------
// 2) Наследники User
// -----------------------------
class Student : public User {
    std::string group_;
public:
    Student(const std::string& name, int id, int lvl, const std::string& grp)
      : User(name,id,lvl), group_(grp)
    {
        if (grp.empty())
            throw std::invalid_argument("Ошибка: группа не может быть пустой");
    }
    const std::string& getGroup() const { return group_; }
    void setGroup(const std::string& g) {
        if (g.empty()) throw std::invalid_argument("Ошибка: группа не может быть пустой");
        group_ = g;
    }
    void displayInfo() const override {
        User::displayInfo();
        std::cout << " | Студент, группа: " << group_;
    }
    std::string type() const override { return "Student"; }
};

class Teacher : public User {
    std::string department_;
public:
    Teacher(const std::string& name, int id, int lvl, const std::string& dept)
      : User(name,id,lvl), department_(dept)
    {
        if (dept.empty())
            throw std::invalid_argument("Ошибка: кафедра не может быть пустой");
    }
    const std::string& getDepartment() const { return department_; }
    void setDepartment(const std::string& d) {
        if (d.empty()) throw std::invalid_argument("Ошибка: кафедра не может быть пустой");
        department_ = d;
    }
    void displayInfo() const override {
        User::displayInfo();
        std::cout << " | Преподаватель, кафедра: " << department_;
    }
    std::string type() const override { return "Teacher"; }
};

class Administrator : public User {
    std::string role_;
public:
    Administrator(const std::string& name, int id, int lvl, const std::string& role)
      : User(name,id,lvl), role_(role)
    {
        if (role.empty())
            throw std::invalid_argument("Ошибка: роль не может быть пустой");
    }
    const std::string& getRole() const { return role_; }
    void setRole(const std::string& r) {
        if (r.empty()) throw std::invalid_argument("Ошибка: роль не может быть пустой");
        role_ = r;
    }
    void displayInfo() const override {
        User::displayInfo();
        std::cout << " | Администратор, роль: " << role_;
    }
    std::string type() const override { return "Administrator"; }
};

// -----------------------------
// 4) Класс Resource
// -----------------------------
class Resource {
private:
    std::string name_;
    int         requiredLevel_;
public:
    Resource(const std::string& name, int lvl)
      : name_(name), requiredLevel_(lvl)
    {
        if (name.empty())
            throw std::invalid_argument("Ошибка: название ресурса не может быть пустым");
        if (lvl < 0 || lvl > 10)
            throw std::invalid_argument("Ошибка: уровень доступа ресурса должен быть 0–10");
    }
    const std::string& getName() const       { return name_; }
    int                 getRequiredLevel() const { return requiredLevel_; }

    void displayInfo() const {
        std::cout << "Ресурс: " << name_
                  << " | Требуемый уровень: " << requiredLevel_;
    }

    bool checkAccess(const User& u) const {
        return u.getAccessLevel() >= requiredLevel_;
    }
};

// -----------------------------
// 5) Система контроля доступа
// -----------------------------
class AccessControlSystem {
    std::vector<std::shared_ptr<User>>     users_;
    std::vector<std::shared_ptr<Resource>> resources_;

    // Вспомогательная: разбить строку по разделителю
    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> parts;
        std::istringstream       ss(s);
        std::string              item;
        while (std::getline(ss, item, delim))
            parts.push_back(item);
        return parts;
    }

public:
    // Добавление пользователей и ресурсов
    void addUser(const std::shared_ptr<User>& u)         { users_.push_back(u); }
    void addResource(const std::shared_ptr<Resource>& r) { resources_.push_back(r); }

    // Вывод списков
    void listUsers() const {
        std::cout << "\n=== Список пользователей ===\n";
        for (auto& u : users_) {
            u->displayInfo();
            std::cout << "\n";
        }
    }
    void listResources() const {
        std::cout << "\n=== Список ресурсов ===\n";
        for (auto& r : resources_) {
            r->displayInfo();
            std::cout << "\n";
        }
    }

    // Проверка доступа по ID пользователя и имени ресурса
    void checkAccess(int userId, const std::string& resName) const {
        auto itU = std::find_if(users_.begin(), users_.end(),
            [&](const auto& u){ return u->getId() == userId; });
        auto itR = std::find_if(resources_.begin(), resources_.end(),
            [&](const auto& r){ return r->getName() == resName; });
        if (itU == users_.end()) {
            std::cout << "Пользователь с ID=" << userId << " не найден\n";
            return;
        }
        if (itR == resources_.end()) {
            std::cout << "Ресурс \"" << resName << "\" не найден\n";
            return;
        }
        bool ok = (*itR)->checkAccess(**itU);
        std::cout << "Пользователь \"" << (*itU)->getName()
                  << (ok ? "\" ИМЕЕТ доступ к \"" : "\" НЕ ИМЕЕТ доступ к \"")
                  << resName << "\"\n";
    }

    // Поиск пользователя
    std::shared_ptr<User> findUserByName(const std::string& name) const {
        for (auto& u : users_)
            if (u->getName() == name) return u;
        return nullptr;
    }
    std::shared_ptr<User> findUserById(int id) const {
        for (auto& u : users_)
            if (u->getId() == id) return u;
        return nullptr;
    }

    // Сохранение в файлы
    void saveToFile(const std::string& usersFile,
                    const std::string& resFile) const
    {
        std::ofstream uout(usersFile);
        if (!uout) throw std::runtime_error("Не удалось открыть файл пользователей");
        for (auto& u : users_) {
            uout << u->type()  << ';'
                 << u->getName() << ';'
                 << u->getId()   << ';'
                 << u->getAccessLevel();
            if (u->type() == "Student") {
                auto p = std::dynamic_pointer_cast<Student>(u);
                uout << ';' << p->getGroup();
            }
            else if (u->type() == "Teacher") {
                auto p = std::dynamic_pointer_cast<Teacher>(u);
                uout << ';' << p->getDepartment();
            }
            else if (u->type() == "Administrator") {
                auto p = std::dynamic_pointer_cast<Administrator>(u);
                uout << ';' << p->getRole();
            }
            uout << "\n";
        }

        std::ofstream rout(resFile);
        if (!rout) throw std::runtime_error("Не удалось открыть файл ресурсов");
        for (auto& r : resources_) {
            rout << r->getName() << ';' << r->getRequiredLevel() << "\n";
        }
    }

    // Загрузка из файлов
    void loadFromFile(const std::string& usersFile,
                      const std::string& resFile)
    {
        users_.clear();
        resources_.clear();
        // Пользователи
        std::ifstream uin(usersFile);
        if (!uin) throw std::runtime_error("Не удалось открыть файл пользователей");
        std::string line;
        while (std::getline(uin, line)) {
            if (line.empty()) continue;
            auto parts = split(line, ';');
            if (parts[0] == "Student") {
                users_.push_back(std::make_shared<Student>(
                    parts[1], std::stoi(parts[2]), std::stoi(parts[3]), parts[4]));
            }
            else if (parts[0] == "Teacher") {
                users_.push_back(std::make_shared<Teacher>(
                    parts[1], std::stoi(parts[2]), std::stoi(parts[3]), parts[4]));
            }
            else if (parts[0] == "Administrator") {
                users_.push_back(std::make_shared<Administrator>(
                    parts[1], std::stoi(parts[2]), std::stoi(parts[3]), parts[4]));
            }
            else {
                users_.push_back(std::make_shared<User>(
                    parts[1], std::stoi(parts[2]), std::stoi(parts[3])));
            }
        }
        // Ресурсы
        std::ifstream rin(resFile);
        if (!rin) throw std::runtime_error("Не удалось открыть файл ресурсов");
        while (std::getline(rin, line)) {
            if (line.empty()) continue;
            auto parts = split(line, ';');
            resources_.push_back(std::make_shared<Resource>(
                parts[0], std::stoi(parts[1])));
        }
    }
};

// -----------------------------
// 6) Демонстрация в main()
// -----------------------------
int main() {
    AccessControlSystem acs;
    try {
        // Создаём пользователей
        acs.addUser(std::make_shared<Student>("Ксения", 1, 2,  "ИСТЭМ21"));
        acs.addUser(std::make_shared<Teacher>("Борис", 2, 5,  "Физика"));
        acs.addUser(std::make_shared<Administrator>("Галина", 3, 10, "Root"));

        // Создаём ресурсы
        acs.addResource(std::make_shared<Resource>("Аудитория 202", 1));
        acs.addResource(std::make_shared<Resource>("Лаборатория",   3));
        acs.addResource(std::make_shared<Resource>("Библиотека",     0));

        // Выводим всех пользователей и ресурсы
        acs.listUsers();
        acs.listResources();

        // Проверяем доступ
        std::cout << "\n=== Проверка доступа ===\n";
        acs.checkAccess(1, "Аудитория 202");
        acs.checkAccess(1, "Лаборатория");
        acs.checkAccess(3, "Лаборатория");

        // Поиск пользователя
        std::cout << "\n=== Поиск пользователя по имени ===\n";
        auto u = acs.findUserByName("Борис");
        if (u) {
            std::cout << "Найден: ";
            u->displayInfo();
            std::cout << "\n";
        }

        // Сохраняем в файлы
        acs.saveToFile("users.txt", "resources.txt");
        std::cout << "\nДанные успешно сохранены в users.txt и resources.txt\n";

        // Загружаем в новую систему и показываем
        AccessControlSystem acs2;
        acs2.loadFromFile("users.txt", "resources.txt");
        std::cout << "\n=== Данные после загрузки ===\n";
        acs2.listUsers();
        acs2.listResources();
    }
    catch (const std::exception& ex) {
        std::cerr << "\nФатальная ошибка: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}