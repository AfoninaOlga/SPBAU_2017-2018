#include "employees.h"
#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;

int main() {
    EmployeesArray emp_arr;
    string command, filename;
    int32_t type;
    while (true) {
        cin >> command;
        if (command == "add") {
            cin >> type;
            if (type == DEVELOPER) {
                Developer *empl = new Developer();
                cin >> *empl;
                emp_arr.add(empl);
            } else if (type == SALES_MANAGER) {
                SalesManager *empl = new SalesManager();
                cin >> *empl;
                emp_arr.add(empl);
            }
        } else if (command == "list") {
            cout << emp_arr;
        } else if (command == "load") {
            cin >> filename;
            ifstream f;
            f.open(filename.c_str(), ios_base::binary);
            f >> emp_arr;
            f.close();
        } else if (command == "save") {
            cin >> filename;
            ofstream f;
            f.open(filename.c_str(), ios_base::binary);
            f << emp_arr;
            f.close();
        } else if (command == "exit") {
            break;
        }
    }
    return 0;
}

