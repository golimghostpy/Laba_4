#include "task2.h"

unsigned int MAX_THREADS;

StringList split(const string& str, const string& delimiter) { // разбиение строки в односвязный список
    StringList result;
    string currentPart;
    int delimiterLength = delimiter.size();

    for (auto i = 0; i < str.size(); ++i) {
        int j = 0;
        while (j < delimiterLength && i + j < str.size() && str[i + j] == delimiter[j]) {
            ++j;
        }

        if (j == delimiterLength) {
            if (currentPart != "") {
                result.push_back(currentPart);
                currentPart = "";
            }
            i += delimiterLength - 1;
        } else {
            currentPart += str[i];
        }
    }

    if (!currentPart.empty()) {
        result.push_back(currentPart);
    }

    return result;
}

// проверка без многопотока
void no_threads(CarArray& carShowroom, unsigned int minCost, unsigned int maxCost, unsigned int maxMileage, uint8_t minYear){
    mutex Mute; // заглушка для проверяющей функции
    for (unsigned int i = 0; i < carShowroom.size; ++i){
        is_suitable(carShowroom.get_at(i), minCost, maxCost, maxMileage, minYear, Mute);
    }
}

void worker(CarArray& carShowroom, unsigned int minCost, unsigned int maxCost, unsigned int maxMileage, unsigned int minYear, unsigned int& checkedCars, mutex& Mute) {
    while (true) {
        if (checkedCars >= carShowroom.size) {
            break;
        }

        is_suitable(carShowroom.get_at(checkedCars++), minCost, maxCost, maxMileage, minYear, Mute);
    }
}

// проверка с многопотоком
void with_threads(CarArray& carShowroom, unsigned int minCost, unsigned int maxCost, unsigned int maxMileage, uint8_t minYear){
    thread allThreads[MAX_THREADS];
    unsigned int checkedCars = 0; // общий счетчик для потоков
    mutex Mute;

    for (auto i = 0; i < MAX_THREADS; ++i) {
        allThreads[i] = thread(worker, ref(carShowroom), minCost, maxCost, maxMileage, minYear, ref(checkedCars), ref(Mute));
    }

    for (auto i = 0; i < MAX_THREADS; ++i) {
        if (allThreads[i].joinable()) {
            allThreads[i].join();
        }
    }
}

void task_2()
{
    cout << "Enter size of array: ";
    size_t arrSize;
    cin >> arrSize;

    cout << "Enter count of threads: ";
    cin >> MAX_THREADS;
    ++MAX_THREADS;

    cout << "Enter minimum cost: ";
    unsigned int minCost;
    cin >> minCost;

    cout << "Enter maximum cost: ";
    unsigned int maxCost;
    cin >> maxCost;

    cout << "Enter maximum mileage: ";
    unsigned int maxMileage;
    cin >> maxMileage;

    cout << "Enter minimum year of manufacture: ";
    unsigned int minYear;
    cin >> minYear;

    CarArray carShowroom(arrSize);

    cout << "How do you want to input cars? 1 - manualy, 2 - automaticly: ";
    int inputChoice;
    cin >> inputChoice;

    if (inputChoice == 1){ // ручной ввод автомобилей
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter " << arrSize << " strings according to the template" << endl;
        cout << "<marka> <cost> <mileage> <body type> <year of manufacture>" << endl;
        for (auto i = 0; i < arrSize; ++i){
            string temp;
            getline(cin, temp);
            carShowroom.push_back(split(temp, " "));
        }
    }
    else if (inputChoice == 2){ // выборка данных из файла
        ifstream sourceFile("data.txt");
        if (!sourceFile.is_open()){
            cout << "No such a file" << endl;
            return;
        }
        for (auto i = 0; i < arrSize; ++i){
            string temp;
            getline(sourceFile, temp);
            carShowroom.push_back(split(temp, " "));
        }
    }
    else {
        cout << "No such a choice!" << endl;
        return;
    }
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Result with no threads:" << endl;
    auto startNoThreads = chrono::high_resolution_clock::now();
    no_threads(carShowroom, minCost, maxCost, maxMileage, minYear);
    auto endNoThreads = chrono::high_resolution_clock::now();
    chrono::duration<double> durationNoThreads = endNoThreads - startNoThreads;
    cout << endl << "Lead time with no threads: " << durationNoThreads.count() * 1000 << " ms." << endl;

    cout << "-----------------------------------------------------------------" << endl;
    cout << "Result with threads:" << endl;
    auto startWithThreads = chrono::high_resolution_clock::now();
    with_threads(carShowroom, minCost, maxCost, maxMileage, minYear);
    auto endWithThreads = chrono::high_resolution_clock::now();
    chrono::duration<double> durationWithThreads = endWithThreads - startWithThreads;
    cout << endl << "Lead time with threads: " << durationWithThreads.count() * 1000 << " ms." << endl;
}