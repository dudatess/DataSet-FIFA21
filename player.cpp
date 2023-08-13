
#include "player.h"

using namespace std;

// PEGA OS ARQUIVOS PLAYERS.CSV E RATINGS.CSV E COLOCA AS INFO EM UMA HASH E OS PLAYES EM UMA TRIE
void tabelaAvaliacoes(Hash_Player &hash_player, Hash_User &hash_user, Trie &trie, string players, string ratings)
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
            // Coloca na hash e na trie ao mesmo tempo
            hash_player.insert_player(stoi(row[0]), row[1], row[2]);
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
            hash_player.insert_rating(stoi(row[1]), stoi(row[2]));
            hash_user.insert_user(stoi(row[0]), stoi(row[1]), stof(row[2]));
        }
        line_count++;
    }
}

//Le o arquivo tags.csv e coloca em uma hash table
void tabelaTags(Hash_Tags &hash_tags)
{
    using namespace aria::csv;

    int line_count = 0;

    // Leitura do arquivo players.csv
    ifstream f("tags.csv");
    CsvParser parser(f);

    for (auto &row : parser)
    {
        if (line_count > 0)
        {
            hash_tags.insert(row[2], stoi(row[1]));
        }

        line_count++;
    }
   
}

