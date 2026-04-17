#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Computer {
    string name;
    int ram;
    int hddCapacity;
    double price;
    string cpu;

    void display() const {
        cout << "| " << left << setw(18) << name
            << "| " << setw(6) << ram
            << "| " << setw(8) << hddCapacity
            << "| " << setw(10) << fixed << setprecision(2) << price
            << "| " << setw(18) << cpu << " |" << endl;
    }
};

void addComputer(const string& filename) {
    ofstream outFile(filename, ios::app);
    if (!outFile) {
        cout << "Помилка відкриття файлу для запису!\n";
        return;
    }

    Computer c;
    cout << "\n--- Додавання нового ПК ---\n";

    cin.ignore(cin.rdbuf()->in_avail(), '\n');

    cout << "Назва (можна з пробілами): ";
    getline(cin, c.name);

    cout << "Об'єм ОЗП (ГБ): ";
    while (!(cin >> c.ram)) {
        cout << "Помилка! Введіть число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Об'єм HDD (ГБ): ";
    while (!(cin >> c.hddCapacity)) {
        cout << "Помилка! Введіть число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Ціна (грн): ";
    while (!(cin >> c.price)) {
        cout << "Помилка! Введіть число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cin.ignore();
    cout << "Процесор: ";
    getline(cin, c.cpu);

    outFile << c.name << "|" << c.ram << "|" << c.hddCapacity << "|" << c.price << "|" << c.cpu << endl;

    outFile.close();
    cout << "Дані успішно збережено!\n";
}

void showAll(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "\nФайл не знайдено або він порожній.\n";
        return;
    }

    Computer c;
    string line;
    cout << "\n" << string(70, '-') << endl;
    cout << "| " << left << setw(18) << "Назва" << "| " << setw(6) << "RAM" << "| " << setw(8) << "HDD" << "| " << setw(10) << "Ціна" << "| " << setw(18) << "CPU" << " |" << endl;
    cout << string(70, '-') << endl;

    while (getline(inFile, c.name, '|')) {
        inFile >> c.ram;
        inFile.ignore(1, '|');
        inFile >> c.hddCapacity;
        inFile.ignore(1, '|');
        inFile >> c.price;
        inFile.ignore(1, '|');
        getline(inFile, c.cpu);

        c.display();
    }

    cout << string(70, '-') << endl;
    inFile.close();
}

void filterByPrice(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) return;

    Computer c;
    bool found = false;
    cout << "\nКомп'ютери в діапазоні 15000 - 25000 грн:\n";
    cout << string(70, '-') << endl;

    while (getline(inFile, c.name, '|')) {
        inFile >> c.ram;
        inFile.ignore(1, '|');
        inFile >> c.hddCapacity;
        inFile.ignore(1, '|');
        inFile >> c.price;
        inFile.ignore(1, '|');
        getline(inFile, c.cpu);

        if (c.price >= 15000 && c.price <= 25000) {
            c.display();
            found = true;
        }
    }

    if (!found) cout << "Об'єктів із такою ціною не знайдено.\n";
    cout << string(70, '-') << endl;
    inFile.close();
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    string filename = "computers_data.txt";
    int choice;

    while (true) {
        cout << "\n--- Головне меню ---\n";
        cout << "1. Додати новий комп'ютер\n";
        cout << "2. Переглянути повний список\n";
        cout << "3. Пошук за ціною (15000-25000 грн)\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Оберіть пункт меню (0-3).\n";
            continue;
        }

        switch (choice) {
        case 1: addComputer(filename); break;
        case 2: showAll(filename); break;
        case 3: filterByPrice(filename); break;
        case 0: return 0;
        default: cout << "Невірний вибір!\n";
        }
    }

    return 0;
}