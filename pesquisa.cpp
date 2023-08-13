#include "player.h"

using namespace std;

void pesquisaTags(string tags_juntas, Hash_Tags &hash_tags)
{
    vector<string> tags;
    istringstream iss(tags_juntas);
    string tag;

    //Percorre a string e divide em palavras baseadas nos espacos
    while(iss >> tag)
    {
        //Tire as apostrofes da tag
        if (tag.front() == '\'' && tag.back() == '\'')
        {
            tag = tag.substr(1, tag.length() - 2);
        }
        //Guarda as tags em um vector
        tags.push_back(tag);

    }
/*
    //Para cada uma das tags
    for(string chave : tags)
    {   
        //Fazer a pesquisa dos IDS na hash


    }
*/

}