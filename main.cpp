#include <iostream>
#include "parser.hpp"
#include "player.cpp"
#include "player.h"

using namespace std;

int main()
{

    // 2.1 
    // TABELA HASH COM AS INFORMACOES COMPLEMENTARES DE CADA JOGADOR
    HashTable hash_table;

    hash_table = tabelaAvaliacoes(hash_table, "players.csv",  "minirating.csv");
    
    hash_table.printTable();


    return 0;
}
