// Модель библиотечной системы.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
private:
    std::string title;
    std::string author;
    bool isAvailable;

public:
    Book(std::string t, std::string a) : title(t), author(a), isAvailable(true) {}

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    bool available() const {
        return isAvailable;
    }

    void borrow() {
        if (isAvailable) {
            isAvailable = false;
            std::cout << "Книга '" << title << "' была успешно взята." << std::endl;
        }
        else {
            std::cout << "Книга '" << title << "' недоступна." << std::endl;
        }
    }

    void returnBook() {
        isAvailable = true;
        std::cout << "Книга '" << title << "' была возвращена." << std::endl;
    }
};

class User {
private:
    std::string name;

public:
    User(std::string n) : name(n) {}

    std::string getName() const {
        return name;
    }
};

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Книга '" << book.getTitle() << "' добавлена в библиотеку." << std::endl;
    }

    void addUser(const User& user) {
        users.push_back(user);
        std::cout << "Пользователь '" << user.getName() << "' добавлен в библиотеку." << std::endl;
    }

    void listBooks() const {
        std::cout << "Доступные книги:" << std::endl;
        for (const auto& book : books) {
            if (book.available()) {
                std::cout << "- " << book.getTitle() << " автор: " << book.getAuthor() << std::endl;
            }
        }
    }

    void borrowBook(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.borrow();
                return;
            }
        }
        std::cout << "Книга с названием '" << title << "' не найдена." << std::endl;
    }

    void returnBook(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                book.returnBook();
                return;
            }
        }
        std::cout << "Книга с названием '" << title << "' не найдена." << std::endl;
    }
};

int main() {
    Library library;

    // Добавляем книги
    library.addBook(Book("1984", "Джордж Оруэлл"));
    library.addBook(Book("Война и мир", "Лев Толстой"));
    library.addBook(Book("Преступление и наказание", "Федор Достоевский"));

    // Добавляем пользователей
    library.addUser(User("Алексей"));
    library.addUser(User("Мария"));

    // Список доступных книг
    library.listBooks();

    // Пользователь берет книгу
    library.borrowBook("1984");

    // Список доступных книг после взятия
    library.listBooks();

    // Пользователь возвращает книгу
    library.returnBook("1984");

    // Список доступных книг после возврата
    library.listBooks();

    return 0;
}
