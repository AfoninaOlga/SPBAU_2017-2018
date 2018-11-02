#include "circle.h"
#include <cstdio>
#include <cstring>

Circle::~Circle() {
    delete [] _label;
}

Circle::Circle(int id, int x, int y, int radius, const char* label): Figure(id, x, y) {
    _radius = radius;
    _label = new char[strlen(label) + 1];
    strcpy(_label, label);
}

void Circle::print() const {
    printf("Circle %i: x = %i y = %i radius = %i label = %s\n", _id, _x, _y, _radius, _label);
}

bool Circle::is_inside(int x, int y) const {
    return (x - _x) * (x - _x) + (y - _y) * (y - _y) <= _radius * _radius;
}

void Circle::zoom(int factor) {
    _radius *= factor;
}

