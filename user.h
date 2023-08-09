#ifndef USER_H
#define USER_H

// ARQUIVO HEADER PARA DECLARAR AS CLASSES DA PARTE 2.2 DO TRABALHO

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "parser.hpp"
#include <iomanip> // I/O MANIPULATION (DOUBLE EM 6 CASAS DECIMAIS)

using namespace std;

// CLASSE DO USER
class User
{
public:
    int user_id;
    int sofifa_id;
    double rating;

    void print_player() const
    {
        cout << "  user_id: " << user_id << endl;
        cout << "  sofifa_id: " << sofifa_id << endl;
        cout << "  rating: " << fixed << setprecision(6) << rating << endl;
    }
};

#endif /*USER_H*/