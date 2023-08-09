#include "player.cpp"
#include "player.h"
#include "user.h"

using namespace std;

int main()
{

    // 2.1 CONSTRUCAO

    Trie trie;            // Trie com os nomes dos jogadores
    Hash_Player hash_player; // Hash com as informacoes complementares de cada jogador
    
    // 2.2 CONSTRUCAO
    Hash_User hash_user;

    tabelaAvaliacoes(hash_player, hash_user, trie, "players.csv", "minirating.csv"); // Construcao 2.1 e 2.2

    // // 2.1 APLICACAO (FIQUEI SEM CRIATIVIDADE)
    // string prefix = "Fer";
    // vector<int> result = trie.search(prefix);

    // cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    // for (int id : result)
    // {
    //     Player player_prefix = hash_table.search(id);

    //     cout << "  ----------------------" << endl;
    //     player_prefix.print_player();
    //     cout << "  ----------------------" << endl;
    // }

    // 2.2 APLICACAO (FAZER)



    return 0;
}
