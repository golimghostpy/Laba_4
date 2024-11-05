#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <cstdint>
#include <mutex>

using namespace std;

struct Node{
    string data;
    Node* next;
    Node(string val) : data(val), next(nullptr) {}
};

struct StringList{
    int listSize;
    Node* first;
    Node* last;

    StringList() : listSize(0), first(nullptr), last(nullptr) {}

    bool is_empty();
    void push_back(string);
    Node* find(int);
    void print(string);
};

struct Car {
    string marka;
    unsigned int cost;
    unsigned int mileage;
    string bodyType;
    unsigned int year;

    Car(){}

    Car(StringList newCar) {
        marka = newCar.find(0)->data;
        cost = static_cast<unsigned int>(stoul(newCar.find(1)->data));
        mileage = static_cast<unsigned int>(stoul(newCar.find(2)->data));
        bodyType = newCar.find(3)->data;
        year = static_cast<unsigned int>(stoul(newCar.find(4)->data));
    }

    void print();
};

void is_suitable (Car, unsigned int, unsigned int, unsigned int, unsigned int, mutex& Mute);

struct CarArray {
    Car* data;
    int size;
    int capacity;

    CarArray(int initialCapacity = 10) : size(0), capacity(initialCapacity){
        data = new Car[capacity];
    }

    ~CarArray() {
        delete[] data;
    }

    void push_back(const Car&);
    Car get_at(unsigned int);
};

#endif //STRUCTURES_H
