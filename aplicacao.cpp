#include "player.h"
#include "user.h"
#include "tags.h"

using namespace std;

// 2.1
void pesquisaPlayer(string prefix, Trie_Player &trie_player, Hash_Player &hash_player){
    
    vector<int> result = trie_player.search(prefix);

    cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    for (int id : result)
    {
        Player player_prefix = hash_player.search(id);

        cout << "  ----------------------" << endl;
        player_prefix.print_player();
        cout << "  ----------------------" << endl;
    }

}

// 2.2
void pesquisaUser(string entrada, Hash_User &hash_user){
    
    int id = stoi(entrada);
    User user = hash_user.search(id);
    user.print_user();
}


// 2.4
void pesquisaTags(string tags_juntas, Hash_Tags &hash_tags)
{
    vector<string> tags;
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
    }

    if (tags.size() == 1)
    {
        list<int> ids;
        ids = hash_tags.findPlayerTag(tags[0]);

        for (const int &num : ids)
        {
            std::cout << num << endl;
        }
    }

    /*
        vector<vector <list<int>>> lista_ids;
        //Para cada uma das tags
        for(string chave : tags)
        {
            //Fazer a pesquisa dos IDS na hash e guardar em um vetor de vetore
            lista_ids.push_back(hash_tags.findPlayerTag(chave));
        }

        //Chamar funcao que adiciona os ids dos jogadores que contem todas as tags dadas
        vector<int> ids_interseccao;

        intersecacaoIDS(ids_interseccao);
    */
}

    /*APLICAÇÃO DAS ESTRUTURAS*/



    // 2.2 (FAZER)