#include <iostream>
#include <string>
#include "parser.hpp"
#include "player.h"
#include <cctype>
#include <tuple>

using namespace std;

void tabelaAvaliacoes(HashTable &hash_table, Trie &trie, string players, string ratings)
{
    using namespace aria::csv;

    int line_count = 0;

    // Leitura do arquivo players.csv
    ifstream f(players);
    CsvParser parser(f);
        
    for (auto &row : parser)
    {
        if (line_count > 0)
        {
            hash_table.insert_player(stoi(row[0]), row[1], row[2]);
            trie.insert(row[1], stoi(row[0]));

        }
        line_count++;
    }

    line_count = 0;

    // Leitura do arquivo ratings.csv
    ifstream file(ratings);
    CsvParser new_parser(file);

    for (auto &row : new_parser)
    {
        if (line_count > 0)
        {
            hash_table.insert_rating(stoi(row[1]), stoi(row[2]));
        }
        line_count++;
    }

}