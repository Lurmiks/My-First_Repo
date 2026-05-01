#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define PRIVATE_FIELDS

class Bus {
private:
    static int count;     
    int id;                

#ifdef PRIVATE_FIELDS
    std::string driverName;
    std::string busNumber;
    int routeNumber;
    std::string brand;
    int startYear;
    int mileage;
public:
    void setDriverName(const std::string& s) { driverName = s; }
    void setBusNumber(const std::string& s) { busNumber = s; }
    void setRouteNumber(int n) { routeNumber = n; }
    void setBrand(const std::string& s) { brand = s; }
    void setStartYear(int y) { startYear = y; }
    void setMileage(int m) { mileage = m; }

    std::string getDriverName() const { return driverName; }
    std::string getBusNumber() const { return busNumber; }
    int getRouteNumber() const { return routeNumber; }
    std::string getBrand() const { return brand; }
    int getStartYear() const { return startYear; }
    int getMileage() const { return mileage; }
#else
public:
    std::string driverName;
    std::string busNumber;
    int routeNumber;
    std::string brand;
    int startYear;
    int mileage;
#endif

public:
    Bus() : id(++count) {
#ifdef PRIVATE_FIELDS
        driverName = "Неизвестно";
        busNumber = "Н000НН";
        routeNumber = 0;
        brand = "Неизвестно";
        startYear = 2000;
        mileage = 0;
#else
        driverName = "Неизвестно";
        busNumber = "Н000НН";
        routeNumber = 0;
        brand = "Неизвестно";
        startYear = 2000;
        mileage = 0;
#endif
        std::cout << "Создан объект #" << id << " (всего: " << count << ")\n";
    }
    Bus(const std::string& dn, const std::string& bn, int rn,
        const std::string& br, int sy, int m) : id(++count) {
#ifdef PRIVATE_FIELDS
        driverName = dn;
        busNumber = bn;
        routeNumber = rn;
        brand = br;
        startYear = sy;
        mileage = m;
#else
        driverName = dn;
        busNumber = bn;
        routeNumber = rn;
        brand = br;
        startYear = sy;
        mileage = m;
#endif
        std::cout << "Создан объект #" << id << " (всего: " << count << ")\n";
    }

    Bus(const Bus& other) : id(++count) {
#ifdef PRIVATE_FIELDS
        driverName = other.driverName;
        busNumber = other.busNumber;
        routeNumber = other.routeNumber;
        brand = other.brand;
        startYear = other.startYear;
        mileage = other.mileage;
#else
        driverName = other.driverName;
        busNumber = other.busNumber;
        routeNumber = other.routeNumber;
        brand = other.brand;
        startYear = other.startYear;
        mileage = other.mileage;
#endif
        std::cout << "Скопирован объект #" << id << " (всего: " << count << ")\n";
    }

    ~Bus() {
        std::cout << "Удалён объект #" << id << " (осталось: " << count - 1 << ")\n";
        --count;
    }

    int getAge() const {
        return 2026 - startYear;
    }

    void show() const {
        std::cout << "ID: " << id << "\n"
            << "  Водитель       : " <<
#ifdef PRIVATE_FIELDS
            driverName << "\n"
            << "  Номер автобуса : " << busNumber << "\n"
            << "  Маршрут        : " << routeNumber << "\n"
            << "  Марка          : " << brand << "\n"
            << "  Год выпуска    : " << startYear << "\n"
            << "  Пробег         : " << mileage << " км\n"
            << "  Срок службы    : " << getAge() << " лет\n\n";
#else
            driverName << "\n"
            << "  Номер автобуса : " << busNumber << "\n"
            << "  Маршрут        : " << routeNumber << "\n"
            << "  Марка          : " << brand << "\n"
            << "  Год выпуска    : " << startYear << "\n"
            << "  Пробег         : " << mileage << " км\n"
            << "  Срок службы    : " << getAge() << " лет\n\n";
#endif
    }

    static int getCount() { return count; }
};

int Bus::count = 0;

void modify_object(Bus& bus) {
#ifdef PRIVATE_FIELDS
    bus.setMileage(bus.getMileage() + 5000);
    bus.setBrand("Модифицирован");
#else
    bus.mileage += 5000;
    bus.brand = "Модифицирован";
#endif
}

void try_to_modify_object(Bus bus) {
#ifdef PRIVATE_FIELDS
    bus.setMileage(bus.getMileage() + 5000);
    bus.setBrand("Модифицирован");
#else
    bus.mileage += 5000;
    bus.brand = "Модифицирован";
#endif
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== Классическое создание объектов ===\n";
    Bus b1;
    Bus b2("Иванов И.И.", "А123БВ", 5, "ЛиАЗ-5292", 2015, 120000);
    Bus b3 = b2;

    b1.show();
    b2.show();
    b3.show();

    std::cout << ">>> Вызов try_to_modify_object(b1):\n";
    try_to_modify_object(b1);
    std::cout << "b1 после try_to_modify (не изменился):\n";
    b1.show();

    std::cout << ">>> Вызов modify_object(b1):\n";
    modify_object(b1);
    std::cout << "b1 после modify (изменился):\n";
    b1.show();

    std::cout << "=== Динамическое создание через new ===\n";
    Bus* p1 = new Bus("Петров П.П.", "В456ГД", 12, "МАЗ-103", 2010, 250000);
    Bus* p2 = new Bus("Сидоров С.С.", "Е789ЖЗ", 7, "ПАЗ-3204", 2020, 50000);
    std::cout << "Счётчик объектов: " << Bus::getCount() << "\n";

    p1->show();
    p2->show();

    delete p1;
    delete p2;

    std::cout << "\n=== Загрузка из файла buses.txt ===\n";
    std::vector<Bus> buses;
    std::ifstream file("buses.txt");
    if (!file) {
        std::cout << "Файл не найден. Создайте buses.txt со строками:\n";
        std::cout << "Фамилия;Номер;Маршрут;Марка;Год;Пробег\n";
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::istringstream ss(line);
            std::string d, nb, br;
            int rt, yr, ml;
            std::getline(ss, d, ';');
            std::getline(ss, nb, ';');
            ss >> rt; ss.ignore(1);
            std::getline(ss, br, ';');
            ss >> yr; ss.ignore(1);
            ss >> ml;
            if (ss) buses.emplace_back(d, nb, rt, br, yr, ml);
        }
        file.close();
        std::cout << "Загружено " << buses.size() << " записей.\n\n";

        int targetRoute;
        std::cout << "Введите номер маршрута: ";
        std::cin >> targetRoute;
        std::cout << "\nАвтобусы маршрута " << targetRoute << ":\n";
        for (const auto& b : buses) {
#ifdef PRIVATE_FIELDS
            if (b.getRouteNumber() == targetRoute)
#else
            if (b.routeNumber == targetRoute)
#endif
                b.show();
        }

        std::cout << "\nАвтобусы со сроком службы > 10 лет:\n";
        for (const auto& b : buses) {
            if (b.getAge() > 10) b.show();
        }

        std::cout << "\nАвтобусы с пробегом > 10000 км:\n";
        for (const auto& b : buses) {
#ifdef PRIVATE_FIELDS
            if (b.getMileage() > 10000)
#else
            if (b.mileage > 10000)
#endif
                b.show();
        }
    }

    std::cout << "Счётчик объектов перед выходом: " << Bus::getCount() << "\n";
    return 0;
}
