#ifndef TASK1_H
#define TASK1_H

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <semaphore.h>
#include <barrier>
#include <atomic>
#include <condition_variable>

using namespace std;

struct SpinLock{ // пока процесс не закончится, другие потоки будут бескоенчно ождать и "крутиться"
    SpinLock() : flag(ATOMIC_FLAG_INIT) {}

    void lock() {
        while (flag.test_and_set(memory_order_acquire)){

        }
    }

    void unlock() {
        flag.clear(memory_order_release);
    }
private:
    atomic_flag flag;
};

struct SpinWait{
    void wait() {
        while (flag.test_and_set(memory_order_acquire)){
            this_thread::yield(); // дает другим потокам выполняться, не нагружая CPU
        }
    }

    void reset(){
        flag.clear(memory_order_release);
    }

private:
    atomic_flag flag = ATOMIC_FLAG_INIT;
};

struct Monitor {
    void wait() { // ошжидание освобождения блока кода
        unique_lock<mutex> lock(muter);
        while (!is_cond) {
            cv.wait(lock);
        }
        is_cond = false;
    }

    void notify() { // "уведомление" о том, что блок был освобожден
        lock_guard<mutex> lock(muter);
        is_cond = true;
        cv.notify_one();
    }

private:
    mutex muter;
    condition_variable cv;
    bool is_cond = true;
};

struct SemaphoreSlim { // в отличии от обычного Semaphore не может работать с несколькими процессами
    int cntr; // не будем создавать переменную maxCnt, потому в данном задании максимальное число потоков всегда - 1

    explicit SemaphoreSlim(int initCnt) : cntr(initCnt) {}

    void wait() {
        unique_lock<mutex> lock(muter);
        cv.wait(lock, [this]{ return cntr > 0; });
        --cntr;
    }

    void release() {
        lock_guard<mutex> lock(muter);
        ++cntr;
        cv.notify_one();
    }
private:
    mutex muter;
    condition_variable cv;
};

void race_simulation(const unsigned int&, const unsigned int&, const string&);
void use_primitives(const unsigned int&, const unsigned int&);
void task_1();

#endif //TASK1_H
