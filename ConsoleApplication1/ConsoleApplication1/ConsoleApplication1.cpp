#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Car {
private:
    string brand;
    string model;
    string price;
public:
    Car(string brand, string model, string price) : brand(brand), model(model), price(price) {}

    string getBrand() const {
        return brand;
    }

    string getModel() const {
        return model;
    }

    string getPrice() const {
        return price;
    }
};

class CarShowroom {
private:
    string name;
    vector<Car> cars;
public:
    CarShowroom(string name) : name(name) {}

    string getName() const {
        return name;
    }

    const vector<Car>& getCars() const {
        return cars;
    }

    void addCar(const Car& car) {
        cars.push_back(car);
    }

    void removeCar(const string& brand, const string& model) {
        cars.erase(remove_if(cars.begin(), cars.end(), [&](const Car& car) {
            return (car.getBrand() == brand && car.getModel() == model);
            }), cars.end());
    }

    void displayCars() const {
        cout << "Автомобили в автосалоне " << name << ":" << endl;
        for (const auto& car : cars) {
            cout << "Марка: " << car.getBrand() << ", Модель: " << car.getModel() << ", Цена: " << car.getPrice() << "Р" << endl;
        }
    }

    Car getCheapestCar() const {
        if (cars.empty()) {
            return Car("", "", ""); 
        }
        auto cheapestCar = min_element(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return stod(a.getPrice()) < stod(b.getPrice());
            });
        return *cheapestCar;
    }


    void sellCar(const string& brand, const string& model) {
        removeCar(brand, model);
        cout << "Автомобиль " << brand << " " << model << " продан!" << endl;
    }


    void moveCar(const string& brand, const string& model, CarShowroom& destination) {
        auto it = find_if(cars.begin(), cars.end(), [&](const Car& car) {
            return (car.getBrand() == brand && car.getModel() == model);
            });

        if (it != cars.end()) {
            destination.addCar(*it);
            cars.erase(it);
            cout << "Автомобиль " << brand << " " << model << " перемещен в автосалон " << destination.getName() << "!" << endl;
        }
        else {
            cout << "Автомобиль " << brand << " " << model << " не найден в автосалоне " << name << "!" << endl;
        }
    }
};


void addCarToShowroom(vector<CarShowroom>& showrooms) {
    string showroomName, brand, model;
    string price;

    cout << "Введите название автосалона: ";
    cin >> showroomName;


    auto it = find_if(showrooms.begin(), showrooms.end(), [&](const CarShowroom& s) {
        return s.getName() == showroomName;
        });


    if (it == showrooms.end()) {
        CarShowroom newShowroom(showroomName);
        showrooms.push_back(newShowroom);
        it = showrooms.end() - 1; 
    }

    cout << "Введите марку автомобиля: ";
    cin >> brand;
    cout << "Введите модель автомобиля: ";
    cin >> model;
    cout << "Введите цену автомобиля: ";
    cin >> price;

   
    Car car(brand, model, price);
    it->addCar(car);

    cout << "Автомобиль успешно поступил в автосалон!" << endl;
}


void removeCarFromShowroom(vector<CarShowroom>& showrooms) {
    string showroomName, brand, model;

    cout << "Введите название автосалона: ";
    cin >> showroomName;

    cout << "Введите марку удаляемого автомобиля: ";
    cin >> brand;
    cout << "Введите модель удаляемого автомобиля: ";
    cin >> model;

    auto it = find_if(showrooms.begin(), showrooms.end(), [&](const CarShowroom& s) {
        return s.getName() == showroomName;
        });

    if (it != showrooms.end()) {
        it->removeCar(brand, model);
        cout << "Автомобиль успешно удален из автосалона!" << endl;
    }
    else {
        cout << "Автосалон не найден!" << endl;
    }
}

void displayAllCars(const vector<CarShowroom>& showrooms) {
    for (const auto& showroom : showrooms) {
        showroom.displayCars();
    }
}


void displayCheapestCars(const vector<CarShowroom>& showrooms) {
    for (const auto& showroom : showrooms) {
        Car cheapestCar = showroom.getCheapestCar();
        if (cheapestCar.getBrand() != "") {
            cout << "Самый дешевый автомобиль в автосалоне " << showroom.getName() << ":" << endl;
            cout << "Марка: " << cheapestCar.getBrand() << ", Модель: " << cheapestCar.getModel() << ", Цена: " << cheapestCar.getPrice() << "Р" << endl;
        }
        else {
            cout << "В автосалоне " << showroom.getName() << " нет машин!" << endl;
        }
    }
}

void sellCarFromShowroom(vector<CarShowroom>& showrooms) {
    string showroomName, brand, model;

    cout << "Введите название автосалона: ";
    cin >> showroomName;

    cout << "Введите марку продаваемого автомобиля: ";
    cin >> brand;
    cout << "Введите модель продаваемого автомобиля: ";
    cin >> model;

    auto it = find_if(showrooms.begin(), showrooms.end(), [&](const CarShowroom& s) {
        return s.getName() == showroomName;
        });

    if (it != showrooms.end()) {
        it->sellCar(brand, model);
    }
    else {
        cout << "Автосалон не найден!" << endl;
    }
}

void bankruptcyOfShowroom(vector<CarShowroom>& showrooms) {
    string bankruptShowroomName;

    cout << "Введите название банкротящегося автосалона: ";
    cin >> bankruptShowroomName;

    auto bankruptIt = find_if(showrooms.begin(), showrooms.end(), [&](const CarShowroom& s) {
        return s.getName() == bankruptShowroomName;
        });

    if (bankruptIt != showrooms.end()) {
        auto nextShowroomIt = bankruptIt + 1;
        if (nextShowroomIt == showrooms.end()) {
            nextShowroomIt = showrooms.begin();
        }

        for (const auto& car : bankruptIt->getCars()) {
            nextShowroomIt->addCar(car);
        }

        showrooms.erase(bankruptIt);

        cout << "Автосалон " << bankruptShowroomName << " обанкротился. Его автомобили переданы в следующий доступный автосалон." << endl;
    }
    else {
        cout << "Автосалон не найден!" << endl;
    }
}

void moveCarBetweenShowrooms(vector<CarShowroom>& showrooms) {
    string sourceShowroomName, destinationShowroomName, brand, model;

    cout << "Введите название отправного автосалона: ";
    cin >> sourceShowroomName;
    cout << "Введите название целевого автосалона: ";
    cin >> destinationShowroomName;

    auto sourceIt = find_if(showrooms.begin(), showrooms.end(), [&](const CarShowroom& s) {
        return s.getName() == sourceShowroomName;
        });

    auto destIt = find_if(showrooms.begin(), showrooms.end(), [&](const CarShowroom& s) {
        return s.getName() == destinationShowroomName;
        });

    if (sourceIt != showrooms.end() && destIt != showrooms.end()) {
        cout << "Введите марку перемещаемого автомобиля: ";
        cin >> brand;
        cout << "Введите модель перемещаемого автомобиля: ";
        cin >> model;

        sourceIt->moveCar(brand, model, *destIt);
    }
    else {
        cout << "Один из указанных автосалонов не найден!" << endl;
    }
}

void displayMainMenu() {
    cout << " " << endl;
    cout << "Главное меню:" << endl;
    cout << "1. Добавить автомобиль в автосалон" << endl;
    cout << "2. Удалить автомобиль из автосалона" << endl;
    cout << "3. Отобразить все автомобили во всех автосалонах" << endl;
    cout << "4. Отобразить самый дешевый автомобиль в каждом автосалоне" << endl;
    cout << "5. Продать автомобиль из автосалона" << endl;
    cout << "6. Переместить автомобиль из одного автосалона в другой" << endl;
    cout << "7. Банкротство автосалона" << endl;
    cout << "8. Выйти из программы" << endl;
}

int main() {
    vector<CarShowroom> showrooms;
    setlocale(LC_ALL, "Russian");

    int choice;
    do {
        displayMainMenu();
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addCarToShowroom(showrooms);
            break;
        case 2:
            removeCarFromShowroom(showrooms);
            break;
        case 3:
            displayAllCars(showrooms);
            break;
        case 4:
            displayCheapestCars(showrooms);
            break;
        case 5:
            sellCarFromShowroom(showrooms);
            break;
        case 6:
            moveCarBetweenShowrooms(showrooms);
            break;
        case 7:
            bankruptcyOfShowroom(showrooms);
            break;
        case 8:
            cout << "До свидания!" << endl;
            break;
        default:
            cout << "Неверный выбор! Пожалуйста, выберите существующий пункт меню." << endl;
            break;
        }
    } while (choice != 8);

    return 0;
}