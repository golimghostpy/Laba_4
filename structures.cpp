#include "structures.h"

bool  StringList::is_empty(){
    return first == nullptr;
}

void  StringList::push_back(string data){
    ++listSize;
    Node* newElem = new Node(data);
    if (is_empty()){
        first = newElem;
        last = newElem;
        return;
    }
    last->next = newElem;
    last = newElem;
}

Node* StringList::find(int index){
    if (index >= listSize || index < 0) cout << index << endl;

    int counter = 0;
    Node* current = first;
    while (counter < index){
        current = current->next;
        ++counter;
    }
    return current;
}

void StringList::print(string delimiter){
    for (auto i = first; i != nullptr; i = i->next){
        cout << i->data << delimiter;
    }
    cout << endl;
}

void is_suitable (Car car, unsigned int from, unsigned int to, unsigned int maxMileage, unsigned int minYear, mutex& Mute){
    if (car.cost >= from && car.cost <= to && car.mileage <= maxMileage && car.year >= minYear)
    {
        {
            lock_guard<mutex> locker(Mute);
            cout << car.marka << " " << car.cost << " " << car.mileage << " " << car.bodyType << " " << car.year << endl;
        }
    }
}

void Car::print(){
    cout << marka << " " << cost << " " << mileage << " " << bodyType << " " << year;
}

void CarArray::push_back(const Car& element) {
    if (size == capacity) {
        capacity *= 2;
        Car* newData = new Car[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = element;
}

Car CarArray::get_at(unsigned int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }
    return data[index];
}