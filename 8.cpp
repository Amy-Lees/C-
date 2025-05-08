#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int         age;
    std::string email;
    std::string address;

public:
    // Геттеры
    const std::string& getName()    const { return name;    }
    int                 getAge()     const { return age;     }
    const std::string& getEmail()   const { return email;   }
    const std::string& getAddress() const { return address; }

    // Сеттеры
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            std::cerr << "Error: Name cannot be empty!\n";
        }
    }

    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 120) {
            age = newAge;
        } else {
            std::cerr << "Error: Age must be between 0 and 120!\n";
        }
    }

    void setEmail(const std::string& newEmail) {
        if (newEmail.find('@') != std::string::npos) {
            email = newEmail;
        } else {
            std::cerr << "Error: Invalid email format!\n";
        }
    }

    void setAddress(const std::string& newAddress) {
        if (!newAddress.empty()) {
            address = newAddress;
        } else {
            std::cerr << "Error: Address cannot be empty!\n";
        }
    }

    // Вывод информации
    void displayInfo() const {
        std::cout
            << "Name:    " << name    << "\n"
            << "Age:     " << age     << "\n"
            << "Email:   " << email   << "\n"
            << "Address: " << address << "\n";
    }
};

int main() {
    Person p;

    // 1) Устанавливаем корректные значения
    p.setName("Ivan Petrov");
    p.setAge(25);
    p.setEmail("ivan.petrov@example.com");
    p.setAddress("Rostov-on-Don, pl.Gagarina, 1");

    // 2) Выводим через геттеры
    std::cout << "Name:    " << p.getName()    << "\n";
    std::cout << "Age:     " << p.getAge()     << "\n";
    std::cout << "Email:   " << p.getEmail()   << "\n";
    std::cout << "Address: " << p.getAddress() << "\n\n";

    // 3) Пытаемся установить некорректные данные
    p.setName("");                 // Ошибка: имя не пустое
    p.setAge(150);                 // Ошибка: возраст 0–120
    p.setEmail("invalid-email");   // Ошибка: нет '@'
    p.setAddress("");              // Ошибка: адрес не пустой

    // 4) Финальный вывод
    std::cout << "\nFinal info:\n";
    p.displayInfo();

    return 0;
}