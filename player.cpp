#include <iostream>
#include <string>
#include "parser.hpp"
#include "player.h"
#include <cctype>

using namespace std;

void tabelaAvaliacoes(HashTable hash_table, string nome_arq, string inserir)
{
    using namespace aria::csv;

    int line_count = 0;

    // Leitura do arquivo CSV
    ifstream f(nome_arq);
    CsvParser parser(f);

    if (inserir == "player")
    {
        for (auto &row : parser)
        {
            if (line_count > 0)
            {
                hash_table.insert_player(stoi(row[0]), row[1], row[2]);
            }
            line_count++;
        }
    }

    else if (inserir == "rating")
    {
        for (auto &row : parser)
        {
            if (line_count > 0)
            {
                hash_table.insert_rating(stoi(row[1]), stoi(row[2]));
            }
            line_count++;
        }
    }
}