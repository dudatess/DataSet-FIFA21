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
    Trie trie;

    tabelaAvaliacoes(hash_table, trie, "players.csv",  "minirating.csv");

    string prefix = "K";
    vector<int> result = trie.search(prefix);

    cout << "Jogadores com prefixo '" << prefix << "': " << endl;
    for (int id : result)
    {
        cout << id << endl;
    }

    return 0;
}
