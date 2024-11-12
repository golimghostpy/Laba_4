#include "task1.h"

mutex muter;
counting_semaphore cntSem(1);
barrier<>* bar = nullptr;

void race_simulation(const unsigned int& cntSymbols, const unsigned int& threadId, const string& primitive)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribution(65, 122);

    string raceRes;
    for (auto i = 0; i < cntSymbols; ++i)
    {
        raceRes += static_cast<char>(distribution(gen));
    }

    if (primitive == "noprimitive")
    {
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
    }
    else if (primitive == "mutexes")
    {
        lock_guard<mutex> lock(muter);
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
    }
    else if (primitive == "semaphore")
    {
        cntSem.acquire();
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
        cntSem.release();
    }
    else if (primitive == "semaphoreslim")
    {
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
    }
    else if (primitive == "barrier")
    {
        bar->arrive_and_wait();
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
        bar->arrive_and_wait();
    }
    else if (primitive == "spinlock")
    {
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
    }
    else if (primitive == "spinwait")
    {
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
    }
    else
    {
        cout << "Thread " << threadId << " race result: " << raceRes << endl;
    }
}

void use_primitives(const unsigned int& cntThreads, const unsigned int& cntSymbols)
{
    vector<string> primitives = {"noprimitive", "mutexes", "semaphore", "semaphoreslim", "barrier", "spinlock", "spinwait", "monitor"};
    for (auto i: primitives)
    {
        cout << "Primitive - " << i << endl;
        thread allThreads[cntThreads];

        auto start = chrono::high_resolution_clock::now();

        for (unsigned int j = 0; j < cntThreads; ++j)
        {
            allThreads[i] = thread(race_simulation, ref(cntSymbols), ref(j), ref(i));
        }

        for (auto& i: allThreads)
        {
            if (i.joinable())
            {
                i.join();
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << endl << "Lead time with " << i << ": " << duration.count() * 1000 << " ms." << endl;
        cout << "------------------------------------------------" << endl;
    }
}

void task_1()
{
    cout << "Enter count of threads: ";
    unsigned int cntThreads;
    cin >> cntThreads;

    cout << "Enter count of symbols in race: ";
    unsigned int cntSymbols;
    cin >> cntSymbols;

    use_primitives(cntThreads, cntSymbols);
}