#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <iostream>
#include <stdint.h>

enum employees {DEVELOPER = 1, SALES_MANAGER = 2};


class Employee {
public:
    virtual ~Employee();
    virtual int salary() const = 0;
    virtual std::ostream& print(std::ostream& ostr) const = 0;
    virtual std::ofstream& print(std::ofstream& ofstr) const = 0;
    virtual std::istream& read(std::istream& istr) = 0;
    virtual std::ifstream& read(std::ifstream& ifstr) = 0;

    friend std::ostream& operator<<(std::ostream& ostr, const Employee& empl);
    friend std::istream& operator>>(std::istream& istr, Employee& empl);
    friend std::ofstream& operator<<(std::ofstream& ofstr, const Employee& empl);
    friend std::ifstream& operator>>(std::ifstream& ifstr, Employee& empl);

protected:
    char *_name;
    int32_t _base_salary;
};


class Developer : public Employee {
public:
    Developer();
    int salary() const {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }
    std::ostream& print(std::ostream& ostr) const;
    std::istream& read(std::istream& istr);
    std::ofstream& print(std::ofstream& ofstr) const;
    std::ifstream& read(std::ifstream& ifstr);

    friend std::istream& operator>>(std::istream& istr, Developer& dev);
    friend std::ifstream& operator>>(std::ifstream& ifstr, Developer& dev);

private:
    Developer(const Developer&);
    Developer& operator=(Developer&);
    int32_t type;
    bool _has_bonus;
};


class SalesManager : public Employee {
public:
    SalesManager();
    int salary() const {
        return _base_salary + _sold_nm * _price * 0.01;
    }
    std::ostream& print(std::ostream& ostr) const;
    std::ofstream& print(std::ofstream& ofstr) const;
    std::istream& read(std::istream& istr);
    std::ifstream& read(std::ifstream& ifstr);

    friend std::istream& operator>>(std::istream& istr, SalesManager& sm);
    friend std::ifstream& operator>>(std::ifstream& ifstr, SalesManager& sm);

private:
    SalesManager(const SalesManager&);
    SalesManager& operator=(SalesManager&);
    int32_t type;
    int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(const Employee *empl);
    int total_salary() const;

    friend std::ostream& operator<<(std::ostream& ostr, const EmployeesArray& emp_arr);
    friend std::ofstream& operator<<(std::ofstream& ofstr, const EmployeesArray& emp_arr);
    friend std::ifstream& operator>>(std::ifstream& ifstr, EmployeesArray& emp_arr);

private:
    Employee **_employees;
    int32_t _size;
    int32_t _capacity;
};


char * read_name(std::ifstream& ifstr);

#endif

