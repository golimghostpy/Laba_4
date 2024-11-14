#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"

using namespace std;

int main()
{
    cout << "Enter task number: ";
    int choice;
    cin >> choice;

    switch(choice)
    {
    case 1: task_1(); break;
    case 2: task_2(); break;
    case 3: task_3(); break;
    default: cout << "No such a task" << endl;
    }
    return 0;
}
