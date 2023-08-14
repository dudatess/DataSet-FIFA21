#include "construcao.cpp"
#include "player.h"
#include "user.h"
#include "pesquisa.cpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{

    /*CONSTRUÇÃO DAS ESTRUTURAS*/

    // 2.1
    Trie_Player trie_player; // Trie com os nomes dos jogadores
    Hash_Player hash_player; // Hash com as informacoes complementares de cada jogador

    // 2.2
    Hash_User hash_user; // Hash com os usuarios e suas avaliacoes

    // 2.4
    Hash_Tags hash_tags; // Hash com as tags e as ids

    tabelaPlayers(hash_player, trie_player, "players.csv");  // 2.1 e 2.2
    tabelaRatings(hash_user, hash_player, "minirating.csv"); // 2.1 e 2.2
    tabelaTags(hash_tags);                                   // 2.4

    cout << "AS CONSTRUCOES TERMINARAM!" << endl;

    /*PROCESSAMENTO DOS COMANDOS*/

    while (true)
    {
        string input;
        cout << "Insira uma opcao:" << endl;
        getline(cin, input);

        if (input == "sair")
        {
            break; // Encerra o loop se o usuario escolhe sair
        }
        else if (input.substr(0, 6) == "player")
        {
            // Sepera comando de pesquida do jogador
            string player_name = input.substr(7);
        }
        else if (input.substr(0, 4) == "user")
        {
            // Separa o userID do input
            // int user_id = stoi(input.substr(5));
        }
        else if (input.substr(0, 5) == "top10")
        {
            // Separa a posicao do joagdor
            string top = input.substr(6);
        }
        else if (input.substr(0, 4) == "tags")
        {
            // Separa as tags
            string tags = input.substr(5);

            // Chama funcao para fazer a pesquisa das tags
            pesquisaTags(tags, hash_tags);
        }
        else
        {
            cout << "Comando invalido." << endl;
        }
    }

    /*APLICAÇÃO DAS ESTRUTURAS*/

    // 2.1
    //  string prefix = "Fer";
    //  vector<int> result = trie_player.search(prefix);

    // cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    // for (int id : result)
    // {
    //     Player player_prefix = hash_player.search(id);

    //     cout << "  ----------------------" << endl;
    //     player_prefix.print_player();
    //     cout << "  ----------------------" << endl;
    // }

    // 2.2 (FAZER)

    return 0;
}
