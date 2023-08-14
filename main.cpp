#include "construcao.cpp"
#include "player.h"
#include "user.h"
#include "pesquisa.cpp"

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

    string input;

    while (true)
    {
        cout << endl;
        cout << "Digite: <comando> <entrada>"<< endl;
        cout << "- player"<< endl;
        cout << "- user"<< endl;
        cout << "- top10"<< endl;
        cout << "- tags"<< endl;

        getline(cin, input);

        if (input == "exit")
        {
            cout << "Encerrando o programa." << endl;
            break;
        }

        if (input.size() >= 2)
        {
            istringstream iss(input);
            string comando, entrada;

            iss >> comando;
            getline(iss, entrada);

            if (!iss.fail())
            {

                if (comando == "player")
                {
                    cout << "Player" << endl;
                    cout << "Entrada: " << entrada << endl;
                }
                else if (comando == "user")
                {
                    cout << "user" << endl;
                    cout << "Entrada: " << entrada << endl;
                }
                else if (comando == "top10")
                {
                    cout << "top10" << endl;
                    cout << "Entrada: " << entrada << endl;
                }
                else if (comando == "tags")
                {
                    cout << "tags" << endl;
                    cout << "Entrada: " << entrada << endl;
                }
            }
            else
            {
                cout << "Formato inválido. Use o formato: $ <comando> <entrada>" << endl;
            }
        }
        else
        {
            cout << "Formato inválido. Use o formato: $ <comando> <entrada>" << endl;
        }
    }

    return 0;
}
