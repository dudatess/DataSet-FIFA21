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
    vector<int> sofifa_id;
    vector<double> rating;

    void print_user() const
    {
        cout << "  user_id: " << user_id << endl;
        for (size_t i = 0; i < sofifa_id.size(); ++i)
            cout << "  sofifa_id: " << sofifa_id[i] << "  rating: " << rating[i] << endl;
    }
};

class Hash_User
{
private:
    static const int TABLE_SIZE = 9999999;
    vector<list<User>> table[TABLE_SIZE];

    // DADO UM ID RETORNA UMA POSICAO NA TABELA
    int hashFunction(int user_id)
    {
        return user_id % TABLE_SIZE;
    }
};

#endif /*USER_H*/