#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>

#include "matrix.h"

using namespace std;

int main(int, char **) {
    map<string, Matrix> regs;
    std::string cmd, reg1, reg2, filename;
    int rows, cols, val, row_ind, col_ind;
    fstream file;

    while (1) {
        cin >> cmd;
        try {
            if (cmd == "exit") {
                break;
            } else if (cmd == "load") {
                cin >> reg1 >> filename;
                file.open(filename, fstream::in);
                file >> rows >> cols;
                Matrix tmp(rows, cols);
                regs[reg1] = tmp;
                for (int i = 0; i < rows; ++i)
                    for (int j = 0; j < cols; ++j) {
                        file >> val;
                        regs[reg1].set(i, j, val);
                    }
                file.close();
            } else if (cmd == "elem") {
                cin >> reg1 >> row_ind >> col_ind;
                cout << regs[reg1].get(row_ind, col_ind) << '\n';
            } else if (cmd == "print") {
                cin >> reg1;
                for (size_t i = 0; i < regs[reg1].rows(); ++i) {
                    for (size_t j = 0; j < regs[reg1].cols(); ++j)
                        cout << regs[reg1].get(i, j) << " ";
                    cout << '\n';
                }
            } else if (cmd == "add") {
                cin >> reg1 >> reg2;
                regs[reg1] += regs[reg2];
            } else if (cmd == "mul") {
                cin >> reg1 >> reg2;
                regs[reg1] *= regs[reg2];
            }
        }
        catch (MatrixException &e) {
            cout << e.what() << '\n';
        }
    }

    return 0;
}
