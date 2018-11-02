#include "scheme.h"

Scheme::Scheme(int capacity) {
    _capacity = capacity;
    _size = 0;
    figures_ = new Figure*[capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < _size; ++i)
        delete figures_[i];
    delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
    if (_size < _capacity)
        figures_[_size++] = fg;
}

void Scheme::remove_figure(int id) {
    for (int i = 0; i < _size; ++i)
        if (figures_[i]->get_id() == id) {
            delete figures_[i];
            for (++i; i < _size; ++i)
                figures_[i - 1] = figures_[i];
            --_size;
        }
}

void Scheme::print_all_figures() {
    for (int i = 0; i < _size; ++i)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    for (int i = 0; i < _size; ++i)
        if (figures_[i]->get_id() == id)
            figures_[i]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < _size; ++i)
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    return figures_[0];
}

void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < _size; ++i)
        if (figures_[i]->get_id() == id)
            figures_[i]->move(new_x, new_y);
}

