#include "construcao.cpp"
#include "aplicacao.cpp"
#include "player.h"
#include "user.h"

using namespace std;

int main()
{
    /*PARA COMPILAR: g++ -O2 main.cpp -o main*/

    /*CONSTRUÇÃO DAS ESTRUTURAS*/

    // 2.1 OK
    Trie_Player trie_player; // Trie com os nomes dos jogadores
    Hash_Player hash_player; // Hash com as informacoes complementares de cada jogador

    // 2.2 OK
    Hash_User hash_user; // Hash com os usuarios e suas avaliacoes

    // 2.3 OK
    Hash_Positions hash_positions;

    // 2.4
    Hash_Tags hash_tags; // Hash com as tags e as ids

    cout << "COMECOU" << endl;
    tabelaPlayers(hash_player, trie_player, hash_positions, "players.csv"); // 2.1 e 2.2

    tabelaRatings(hash_user, hash_player, "rating.csv"); // 2.1 e 2.2

    tabelaTags(hash_tags); // 2.4

    cout << "AS CONSTRUCOES TERMINARAM!" << endl;

    /*user 8419*/
    /*user 118646*/
    /*user 30813*/


    /*PROCESSAMENTO DOS COMANDOS*/

    string input;

    while (true)
    {
        cout << endl;
        cout << "Comandos: " << endl;
        cout << "- player" << endl;
        cout << "- user" << endl;
        cout << "- top" << endl;
        cout << "- tags" << endl;

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
            if (!entrada.empty() && entrada[0] == ' ')
                entrada = entrada.substr(1);

            if (!iss.fail())
            {

                if (comando == "player")
                {
                    cout << endl;
                    pesquisaPlayer(entrada, trie_player, hash_player);
                }
                else if (comando == "user")
                {
                    cout << endl;
                    pesquisaUser(entrada, hash_user, hash_player);
                }
                else if (comando[1] == 'o')
                {

                    pesquisaTop(input, hash_positions, hash_player);
                }
                else if (comando == "tags")
                {
                    cout << endl;

                    pesquisaTags(entrada, hash_tags, hash_player);
                }
            }
            else
            {
                cout << "Formato invalido. Use o formato: <comando> <entrada>" << endl;
            }
        }
        else
        {
            cout << "Formato invalido. Use o formato: <comando> <entrada>" << endl;
        }
    }

    return 0;
}
