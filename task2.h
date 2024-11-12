#ifndef TASK2_H
#define TASK2_H

#include <thread>
#include "structures.h"
#include <fstream>

StringList split(const string&, const string&);
void no_threads(CarArray&, unsigned int, unsigned int, unsigned int, uint8_t);
void worker(CarArray&, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int&, mutex&);
void with_threads(CarArray&, unsigned int, unsigned int, unsigned int, uint8_t);
void task_2();

#endif //TASK2_H
