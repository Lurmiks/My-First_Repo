#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Public_transport {
protected:
    string brand;       
    int startYear;     
    int mileage;        

public:
    Public_transport() : brand("Неизвестно"), startYear(2000), mileage(0) {}

    Public_transport(const string& b, int sy, int m) : brand(b), startYear(sy), mileage(m) {}

    virtual ~Public_transport() {}

    int getAge() const {
        return 2026 - startYear;   
    }

    string getBrand() const { return brand; }
    int getStartYear() const { return startYear; }
    int getMileage() const { return mileage; }

    virtual void show() const = 0;
};

class Bus : public Public_transport {
private:
    string driverName;   
    string busNumber;    
    int routeNumber;    

public:
    Bus() : Public_transport(), driverName("Неизвестно"), busNumber("Н000НН"), routeNumber(0) {}

    Bus(const string& brand, int sy, int m,
        const string& driver, const string& bnum, int route)
        : Public_transport(brand, sy, m), driverName(driver), busNumber(bnum), routeNumber(route) {
    }

    void show() const override {
        cout << "=== Автобус ===\n";
        cout << "Марка: " << brand << "\n";
        cout << "Год выпуска: " << startYear << "\n";
        cout << "Пробег: " << mileage << " км\n";
        cout << "Водитель: " << driverName << "\n";
        cout << "Номер автобуса: " << busNumber << "\n";
        cout << "Маршрут №" << routeNumber << "\n";
        cout << "Срок эксплуатации: " << getAge() << " лет\n\n";
    }
};

class Taxi : public Public_transport {
private:
    string taxiNumber;  
    double tariff;       
    int seats;           

public:
    Taxi() : Public_transport(), taxiNumber("Т000ТТ"), tariff(0), seats(4) {}

    Taxi(const string& brand, int sy, int m,
        const string& tnum, double tar, int s)
        : Public_transport(brand, sy, m), taxiNumber(tnum), tariff(tar), seats(s) {
    }

    double calculateFare(double distanceKm) const {
        return distanceKm * tariff;
    }

    void show() const override {
        cout << "=== Такси ===\n";
        cout << "Марка: " << brand << "\n";
        cout << "Год выпуска: " << startYear << "\n";
        cout << "Пробег: " << mileage << " км\n";
        cout << "Номер такси: " << taxiNumber << "\n";
        cout << "Тариф: " << tariff << " руб/км\n";
        cout << "Мест: " << seats << "\n";
        cout << "Срок эксплуатации: " << getAge() << " лет\n";
        cout << "Пример: поездка на 10 км будет стоить " << calculateFare(10) << " руб.\n\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Public_transport*> transports;

    transports.push_back(new Bus("ЛиАЗ-5292", 2015, 120000, "Иванов И.И.", "А123БВ", 5));
    transports.push_back(new Bus("МАЗ-103", 2010, 250000, "Петров П.П.", "В456ГД", 12));
    transports.push_back(new Bus("ПАЗ-3204", 2020, 50000, "Сидоров С.С.", "Е789ЖЗ", 7));

    transports.push_back(new Taxi("Renault Logan", 2019, 180000, "Т555КМ", 30.5, 4));
    transports.push_back(new Taxi("Kia Rio", 2022, 60000, "Т123ОР", 28.0, 4));
    transports.push_back(new Taxi("Toyota Camry", 2018, 220000, "Т777ВН", 35.0, 4));

    cout << "===== СПИСОК ТРАНСПОРТА =====\n";
    for (const auto& t : transports) {
        t->show();
    }

    for (auto& t : transports) {
        delete t;
    }

    return 0;
}