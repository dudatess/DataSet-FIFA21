#include "tags.h"

using namespace std;

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