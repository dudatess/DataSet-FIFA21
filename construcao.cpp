
#include "player.h"
#include "user.h"
#include "tags.h"
#include "top.h"

using namespace std;

// LE O ARQUIVO PLAYERS.CSV E COLOCA EM DUAS HASH (DO PLAYER E DAS POSICOES), E EM UMA TRIE DE PLAYER
void tabelaPlayers(Hash_Player &hash_player, Trie_Player &trie, Hash_Positions &hash_positions, string players)
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
            // Coloca nas duas hash e na trie ao mesmo tempo
            hash_player.insert_player(stoi(row[0]), row[1], row[2]);
            trie.insert(row[1], stoi(row[0]));
            hash_positions.insert_position(row[2], stoi(row[0]));
        }
        line_count++;
    }
}

// LE O ARQUIVO RATINGS.CSV E COLOCA EM UMA HASH DE USER E COMPLEMENTA A HASH DO PLAYER
void tabelaRatings(Hash_User &hash_user, Hash_Player &hash_player, string ratings)
{
    using namespace aria::csv;

    int line_count = 0;

    // Leitura do arquivo ratings.csv
    ifstream file(ratings);
    CsvParser new_parser(file);

    for (auto &row : new_parser)
    {
        if (line_count > 0)
        {
            // coloca nas duas hash, de player e user, ao mesmo tempo
            hash_player.insert_rating(stoi(row[1]), stod(row[2])); // string to double
            hash_user.insert_user(stoi(row[0]), stoi(row[1]), stod(row[2]));  // string to double
        }
        line_count++;
    }
}


// LE O ARQUIVO TAGS.CSV E COLOCA EM UMA HASH
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
            hash_tags.insert_tag(row[2], stoi(row[1]));
        }

        line_count++;
    }
}
