// MAIN DA PARTE 1 DO TRABALHO (CONSTRUCAO)

#include <iostream>
#include "parser.hpp"
#include "player.cpp"
#include "player.h"

using namespace std;

int main()
{
    HashTable hash_table;

    tabelaAvaliacoes(hash_table, "players.csv", "player");
    tabelaAvaliacoes(hash_table, "minirating.csv", "rating");

    hash_table.printTable();

    return 0;
}
