#include "player.h"
#include "user.h"
#include "tags.h"
#include "top.h"
#include "quicksort.cpp"
#include <algorithm> // TEM QUE TIRAR ESSE ALGORITHM

using namespace std;

// 2.1
void pesquisaPlayer(string prefix, Trie_Player &trie_player, Hash_Player &hash_player)
{

    vector<int> result = trie_player.search(prefix);

    cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    cout << "sofifa_id ";
    cout << "name ";
    cout << "player_positions ";
    cout << "rating " << fixed << setprecision(6);
    cout << "count " << endl;

    for (int id : result)
    {
        Player player_prefix = hash_player.search(id);
        player_prefix.print_player();
        cout << endl;
    }
}

// 2.2
void pesquisaUser(string entrada, Hash_User &hash_user, Hash_Player &hash_player)
{

    int user_id = stoi(entrada);
    User user = hash_user.search(user_id);

    int controle = 0, i = 0;

    cout << "sofifa_id ";
    cout << "name ";
    cout << "player_positions ";
    cout << "global_rating " << fixed << setprecision(6);
    cout << "count ";
    cout << "rating " << endl;

    for (int id : user.sofifa_id)
    {
        Player player = hash_player.search(id);
        player.print_player();
        cout << user.rating[i] << endl;

        i++;
        controle++;
        if (controle > 20)
            break;
    }
}

// 2.3
void pesquisaTop(string entrada, Hash_Positions &hash_positions, Hash_Player &hash_player)
{
    string top;
    int numero_top;
    string posicao;

    vector<int> sofifa_ids;
    vector<Player> players_top;


    // FORMATO top<N> ‘<position>’
    size_t numStart = entrada.find_first_of("0123456789");

    if (numStart != string::npos) {
        top = entrada.substr(0, numStart);

        size_t numEnd = entrada.find_first_not_of("0123456789", numStart);
        if (numEnd != string::npos) {
            string numStr = entrada.substr(numStart, numEnd - numStart);
            istringstream(numStr) >> numero_top;

            size_t posStart = entrada.find_first_of("'\"", numEnd);
            size_t posEnd = entrada.find_first_of("'\"", posStart + 1);

            if (posStart != string::npos && posEnd != string::npos) 
                posicao = entrada.substr(posStart + 1, posEnd - posStart - 1);
        }
    }

    sofifa_ids = hash_positions.search(posicao).sofifa_id;

    for(int id : sofifa_ids){
        Player new_player;
        new_player = hash_player.search(id);
        players_top.push_back(new_player);
    }

    int n = players_top.size();
    quickSort(players_top, 0, n - 1);
     
    int controle;
    controle = 1;

    for(Player &player: players_top){
        
        if(controle > numero_top){
            break;
        }

        if(player.count>1000)
        {
            player.print_player();
            cout<<endl;
            controle++;
        }
        
    }
    
    
}

// 2.4
void pesquisaTags(string tags_juntas, Hash_Tags &hash_tags, Hash_Player &hash_player)
{
    vector<string> tags;
    vector<Player> players;
    istringstream iss(tags_juntas);
    string tag;

    //Divide a string baseada em apostofres
    while (getline(iss, tag, '\''))
    {
        if (!tag.empty() && tag != " ") 
        {
            tags.push_back(tag);
        }
    }

    if (tags.size() == 1)
    {
        // Se tiver apenas uma tag, efetuar uma pesquisa simples
        //(nao precisa fazer interseccao)

        list<int> ids;

        ids = hash_tags.findPlayerTag(tags[0]);

        // Para cada player, pesquisar seus dados na hash player
        for (const int &num : ids)
        {

            players.push_back(hash_player.search(num));
        }

        // Imprimir informações de cada player
        for (const Player &player : players)
        {
            player.print_player();
            cout<<endl;
        }
    }
    else
    {

        vector<list<int>> lista_ids;

        // Para cada uma das tags
        for (string chave : tags)
        {
            // Fazer a pesquisa dos IDS na hash e guardar em um vetor
            lista_ids.push_back(hash_tags.findPlayerTag(chave));
        }

        // Chamar funcao que adiciona os ids dos jogadores que contem todas as tags dadas
        vector<int> ids_interseccao;

        interseccaoIDS(ids_interseccao, lista_ids);

        // Para cada player, pesquisar seus dados na hash player
        for (const int &num : ids_interseccao)
        {
            players.push_back(hash_player.search(num));
        }

        // Imprimir informações de cada player
        for (const Player &player : players)
        {
            player.print_player();
            cout<<endl;
        }
    }
}

// 2.4
void interseccaoIDS(vector<int> &ids_interseccao, const vector<list<int>> lista_ids)
{
    // Se ha uma lista vazia, retorna vazio
    for (const auto &lst : lista_ids)
    {
        if (lst.empty())
        {
            cout << "Nao ha nenhum jogador com estas tags." << endl;
            return;
        }
    }

    for (const auto &num : lista_ids[0])
    {
        bool elemento_comum = true;

        for (size_t i = 1; i < lista_ids.size(); ++i)
        {
            if (find(lista_ids[i].begin(), lista_ids[i].end(), num) == lista_ids[i].end()) // NAO PODE ESSE FIND
            {
                elemento_comum = false;
                break;
            }
        }

        // Se elemento for comum a todas as listas, ineserir no vetor
        if (elemento_comum)
        {
            ids_interseccao.push_back(num);
        }
    }
}

