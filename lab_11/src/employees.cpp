#include "employees.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdint.h>

using namespace std;

char * read_name(ifstream& ifstr) {
    string name;
    while (true) {
        char letter;
        ifstr.read(&letter, sizeof(letter));
        if (!letter)
            break;
        name += letter;
    }
    char *_name = new char[name.size() + 1];
    strcpy(_name, name.c_str());
    return _name;
}

ostream & operator<<(ostream& ostr, const Employee& empl) {
    empl.print(ostr);
    return ostr;
}

ofstream& operator<<(ofstream& ofstr, const Employee& empl) {
    empl.print(ofstr);
    return ofstr;
}

istream& operator>>(istream& istr, Employee& empl) {
    empl.read(istr);
    return istr;
}

ifstream& operator>>(ifstream& ifstr, Employee& empl) {
    empl.read(ifstr);
    return ifstr;
}

Employee::~Employee() {
    delete[] _name;
}

Developer::Developer() {
    type = DEVELOPER;
    _name = NULL;
}

ostream& Developer::print(ostream& ostr) const {
    ostr << "Developer\n";
    ostr << "Name: " << _name << '\n';
    ostr << "Base Salary: " << _base_salary << '\n';
    ostr << "Has bonus: " << (_has_bonus? "+" : "-") << '\n';
    return ostr;
}

istream& Developer::read(istream& istr) {
    istr >> *this;
    return istr;
}

ofstream& Developer::print(ofstream& ofstr) const {
    ofstr.write((const char *)&type, sizeof(type));
    ofstr.write((const char *)_name, strlen(_name) + 1);
    ofstr.write((const char *)&_base_salary, sizeof(_base_salary));
    ofstr.write((const char *)&_has_bonus, sizeof(_has_bonus));
    return ofstr;
}

ifstream& Developer::read(ifstream& ifstr) {
    ifstr >> *this;
    return ifstr;
}

SalesManager::SalesManager() {
    type = SALES_MANAGER;
    _name = NULL;
}

ostream & SalesManager::print(ostream &ostr) const {
    ostr << "Sales Manager\n";
    ostr << "Name: " << _name << '\n';
    ostr << "Base Salary: " << _base_salary << '\n';
    ostr << "Sold items: " << _sold_nm << '\n';
    ostr << "Item price: " << _price << '\n';
    return ostr;
}

ifstream& SalesManager::read(ifstream& ifstr) {
    ifstr >> *this;
    return ifstr;
}

ofstream& SalesManager::print(ofstream& ofstr) const {
    ofstr.write((const char *)&type, sizeof(type));
    ofstr.write((const char *)_name, strlen(_name) + 1);
    ofstr.write((const char *)&_base_salary, sizeof(_base_salary));
    ofstr.write((const char *)&_sold_nm, sizeof(_sold_nm));
    ofstr.write((const char *)&_price, sizeof(_price));
    return ofstr;
}

istream& SalesManager::read(istream& istr) {
    istr >> *this;
    return istr;
}

istream& operator>>(istream& istr, Developer& dev) {
    string name;
    istr >> name >> dev._base_salary >> dev._has_bonus;
    delete[] dev._name;
    dev._name = new char [name.length() + 1];
    strcpy(dev._name, name.c_str());
    return istr;
}

ifstream& operator>>(ifstream& ifs, Developer& dev) {
    delete[] dev._name;
    dev._name = read_name(ifs);
    ifs.read((char *)&dev._base_salary, sizeof(dev._base_salary));
    ifs.read((char *)&dev._has_bonus, sizeof(dev._has_bonus));
    return ifs;
}

istream& operator>>(istream& istr, SalesManager& sm) {
    string name;
    istr >> name >> sm._base_salary >> sm._sold_nm >> sm._price;
    delete[] sm._name;
    sm._name = new char [name.length() + 1];
    strcpy(sm._name, name.c_str());
    return istr;
}

ifstream& operator>>(ifstream& ifstr, SalesManager& sm) {
    delete[] sm._name;
    sm._name = read_name(ifstr);
    ifstr.read((char *)&sm._base_salary, sizeof(sm._base_salary));
    ifstr.read((char *)&sm._sold_nm, sizeof(sm._sold_nm));
    ifstr.read((char *)&sm._price, sizeof(sm._price));
    return ifstr;
}

ostream& operator<<(ostream& ostr, const EmployeesArray& emp_arr) {
    for (int i = 0; i < emp_arr._size; i++) {
        ostr << i + 1 << ". ";
        emp_arr._employees[i]->print(ostr);
    }
    ostr << "== Total salary: " << emp_arr.total_salary() << "\n\n";
    return ostr;
}

ofstream& operator<<(ofstream& ofstr, const EmployeesArray& emp_arr) {
    ofstr.write((const char *)&emp_arr._size, sizeof(int32_t));
    for (int i = 0; i < emp_arr._size; i++) {
        emp_arr._employees[i]->print(ofstr);
    }
    return ofstr;
}

ifstream& operator>>(ifstream& ifstr, EmployeesArray& emp_arr) {
    int32_t count;
    ifstr.read((char *)&count, sizeof(count));
    int32_t type;
    while(count--) {
        ifstr.read((char *)&type, sizeof(type));
        if (type == DEVELOPER) {
            Developer * worker = new Developer();
            ifstr >> *worker;
            emp_arr.add(worker);
        }
        else if (type == SALES_MANAGER) {
            SalesManager * worker = new SalesManager();
            ifstr >> *worker;
            emp_arr.add(worker);
        }
    }
    return ifstr;
}

EmployeesArray::EmployeesArray() : _size(0), _capacity(2) {
    _employees = new Employee * [_capacity];
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++) {
        delete _employees[i];
    }
    delete[] _employees;
}

void EmployeesArray::add(const Employee *empl) {
    if (_size == _capacity) {
        _capacity *= 2;
        Employee ** tmp = new Employee * [_capacity];
        memcpy(tmp, _employees, _size * sizeof(*tmp));
        delete[] _employees;
        _employees = tmp;
    }
    _employees[_size++] = (Employee *) empl;
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (int i = 0; i < _size; i++) {
        total += _employees[i]->salary();
    }
    return total;
}

