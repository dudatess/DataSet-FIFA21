#include <iostream>
#include "parser.hpp"
#include "player.cpp"
#include "player.h"

using namespace std;

int main()
{

    // 2.1 CONSTRUCAO

    Trie trie;            // Trie com os nomes dos jogadores
    HashTable hash_table; // Hash com as informacoes complementares de cada jogador

    tabelaAvaliacoes(hash_table, trie, "players.csv", "minirating.csv"); // Construcao

    // 2.1 APLICACAO (FIQUEI SEM CRIATIVIDADE)
    string prefix = "Fer";
    vector<int> result = trie.search(prefix);

    cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    for (int id : result)
    {
        Player player_prefix = hash_table.search(id);

        cout << "  ----------------------" << endl;
        player_prefix.print_player();
        cout << "  ----------------------" << endl;
    }

    // 2.2 CONSTRUCAO
    // 20 maiores avaliações do usuario

    return 0;
}
