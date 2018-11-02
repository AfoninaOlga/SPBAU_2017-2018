#include <iostream>
#include <cstring>
#include "my_vector.h"
#include "test_my_vector.h"

class Product {
public:
    Product(const char* name = NULL, int quantity = 0, double price = 0) : quantity_(quantity), price_(price) {
        if (name) {
            name_ = new char [strlen(name) + 1];
            strcpy(name_, name);
        } else
            name_ = NULL;
    }

    Product(const Product &p) : quantity_(p.quantity()), price_(p.price()) {
        if (p.name()) {
            name_ = new char [strlen(p.name()) + 1];
            strcpy(name_, p.name());
        } else
            name_ = NULL;
    }

    Product& operator=(const Product &other) {
        if (this != &other) {
            delete[] name_;
            if (other.name()) {
                name_ = new char [strlen(other.name()) + 1];
                strcpy(name_, other.name());
            } else
                name_ = NULL;
            quantity_ = other.quantity();
            price_ = other.price();
        }
        return *this;
    }

    ~Product() {
        delete[] name_;
    }

    const char* name() const {
        return name_;
    }

    int quantity() const {
        return quantity_;
    }

    double price() const {
        return price_;
    }

    bool operator==(const Product &p) const {
        return (!strcmp(name_, p.name())) && (quantity_ == p.quantity()) && (price_ == p.price());
    }
    
    bool operator!=(const Product &p) const {
        return (!(*this == p));
    }

private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream &ostr, const Product& p) {
    ostr << std::string(p.name()) << " " << p.quantity() << " " << p.price();
    return ostr;
}

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}

