#include "player.h"
#include "user.h"
#include "tags.h"
#include "top.h"
#include "merge.cpp"

using namespace std;

// 2.1
void pesquisaPlayer(string prefix, Trie_Player &trie_player, Hash_Player &hash_player){
    
    vector<int> result = trie_player.search(prefix);

    cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    cout << "sofifa_id ";
    cout << "name ";
    cout << "player_positions ";
    cout << "global rating " << fixed << setprecision(6);
    cout << "count "<<endl;

    for (int id : result)
    {
        Player player_prefix = hash_player.search(id);
        player_prefix.print_player();
        cout<<endl;
    }

}

// 2.2
void pesquisaUser(string entrada, Hash_User &hash_user, Hash_Player &hash_player){
    
    int user_id = stoi(entrada);
    User user = hash_user.search(user_id );

    int controle =0, i=0;


    cout << "sofifa_id ";
    cout << "name ";
    cout << "player_positions ";
    cout << "global rating " << fixed << setprecision(6);
    cout << "count ";
    cout << "rating "<<endl;
    
    for(int id: user.sofifa_id)
    {
        Player player = hash_player.search(id);
        player.print_player();
        cout << user.rating[i] << endl;
        
        i++;
        controle ++;
        if(controle>20)
            break;
    }
        


}

// 2.3
void pesquisaTop(string entrada, Hash_Positions &hash_positions, Hash_Player &hash_player)
{
    
    int numero_top = 0;
    string posicao;
    vector<int> ids_jogadores;
    vector<Player> topJogadores;

    //Separar string de entrada em quantidade de top jogadores
    //e posicao

    istringstream stream(entrada);
    stream >> numero_top;
    stream.ignore();
    stream >> posicao;

    if (posicao.front() == '\'' && posicao.back() == '\'')
    {
        posicao = posicao.substr(1, posicao.length() - 2);
    }

    //Fazer pesquisa na tabela hash "hash positions" com a posicao desejada
    ids_jogadores = hash_positions.findPosition(posicao);


    //Ordena os IDS de acordo com as suas avaliacoes 
    mergeSort(ids_jogadores, hash_player, 0, ids_jogadores.size() - 1);


    //Pegar os primeiros numero_top jogadores
    for(int i = 0; i < numero_top && i < ids_jogadores.size(); ++i)
    {
        if(hash_player.search(ids_jogadores[i]).count >= 1)
        {
            topJogadores.push_back(hash_player.search(ids_jogadores[i]));        
        }
    }

    for(const Player& player : topJogadores)
    {
        player.print_player();
    }

}

// 2.4
void pesquisaTags(string tags_juntas, Hash_Tags &hash_tags, Hash_Player &hash_player)
{
    vector<string> tags;
    vector<Player> players;
    istringstream iss(tags_juntas);
    string tag;

    // Percorre a string e divide em palavras baseadas nos espacos
    while (iss >> tag)
    {
        // Tire as apostrofes da tag
        if (tag.front() == '\'' && tag.back() == '\'')
        {
            tag = tag.substr(1, tag.length() - 2);
        }
        // Guarda as tags em um vector
        tags.push_back(tag);

        cout << tag << endl;
    }


    if(tags.size() == 1)
    {
        //Se tiver apenas uma tag, efetuar uma pesquisa simples
        //(nao precisa fazer interseccao)

        list<int> ids;
        
        ids = hash_tags.findPlayerTag(tags[0]);

        //Para cada player, pesquisar seus dados na hash player
        for (const int &num : ids)
        {
    
            players.push_back(hash_player.search(num));
        }

        //Imprimir informações de cada player
        for(const Player &player : players)
        {
            player.print_player();
        }
    }
    else
    {
            
        vector<list<int>> lista_ids;
       
        //Para cada uma das tags
        for(string chave : tags)
        {
            //Fazer a pesquisa dos IDS na hash e guardar em um vetor
            lista_ids.push_back(hash_tags.findPlayerTag(chave));
        }

        //Chamar funcao que adiciona os ids dos jogadores que contem todas as tags dadas
        vector<int> ids_interseccao;

         interseccaoIDS(ids_interseccao, lista_ids);

        //Para cada player, pesquisar seus dados na hash player
        for (const int &num : ids_interseccao)
        {
            players.push_back(hash_player.search(num));
        }

        //Imprimir informações de cada player
        for(const Player &player : players)
        {
            player.print_player();
        }
    

    }
 
}


//2.4
void interseccaoIDS(vector<int> &ids_interseccao, const vector<list<int>> lista_ids)
{
    //Se ha uma lista vazia, retorna vazio 
    for(const auto& lst : lista_ids)
    {
        if(lst.empty())
        {
            cout << "Nao ha nenhum jogador com estas tags." << endl;
            return;
        }
    }

    for(const auto& num : lista_ids[0])
    {
        bool elemento_comum = true;

        for(size_t i = 1; i < lista_ids.size(); ++i)
        {
            if(find(lista_ids[i].begin(), lista_ids[i].end(), num) == lista_ids[i].end())
            {
                elemento_comum = false;
                break;
            }
        }

        //Se elemento for comum a todas as listas, ineserir no vetor
        if(elemento_comum)
        {
            ids_interseccao.push_back(num);
        }
    }

}



    // 2.2 (FAZER)