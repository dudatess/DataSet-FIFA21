#ifndef TAGS_H
#define TAGS_H

// HASH DAS TAGS

#include "player.h"

using namespace std;

class Hash_Tags
{
    private:

        static const int TABLE_SIZE = 20000;
        list<int> table[TABLE_SIZE];

    // Funcao de hash em que as tags sao as chaves
    int hashFunction(const string &tag)
    {
        //Funcao hash polinomial, utilizado propriedade aritmetica modular 
        int hash = 0;

        for(int i = 0; i < tag.length(); i++)
        {
            hash = (31 * hash + tag[i]) % TABLE_SIZE;
        }

        return hash;
    }

    public:

        void insert(const string &tag, int id)
        {
            int index = hashFunction(tag);

            // Verificar se o id já está presente na lista
            bool found = false;
            for (int existing_id : table[index])
            {
                if (existing_id == id)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                table[index].push_back(id);
            }
        }

        list<int> findPlayerTag(const string &tag)
        {
            int index = hashFunction(tag);
        
            
            if (!table[index].empty())
            {
                return table[index];
            } 
            else 
            {
                return list<int>();
            }

        }

        void printTable()
        {
                for (const list<int> &ids : table)
                {
                    for (const int id : ids)
                    {
                        cout << "  ----------------------" << endl;
                        cout << id << endl;
                        cout << "  ----------------------" << endl;
                    }
                }
            
        }
};

//Declaracao de funcoes para pesquisa de tags
void interseccaoIDS(vector<int> &ids_interseccao, const vector<list<int>> lista_ids);

#endif /*TAGS_H*/


// DECLARACAO CLASSE HASH TABLE PARA TAGS (a chave são as tags e os dados nos buckets sao os IDS)

/*
class Hash_Tags
{

private:
    static const int TABLE_SIZE = 20000;
    vector<list<int>> table[TABLE_SIZE];

    // Funcao de hash em que as tags sao as chaves
    int hashFunction(const string &tag)
    {
        // Variável hash armazena a soma dos caracteres da tag
        int hash = 0;
        for (char c : tag)
        {
            hash += c;
        }

        return hash % TABLE_SIZE;
    }

public:
    void insert(const string &tag, int id)
    {
        int index = hashFunction(tag);

        if (table[index].empty())
        {
            table[index].emplace_back();
        }

        // Encontrar a lista apropriada no bucket
        auto &id_list = table[index].back();

        // Verificar se o id já está presente na lista
        bool found = false;
        for (int existing_id : id_list)
        {
            if (existing_id == id)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            id_list.push_back(id);
        }
    }

    list<int> findPlayerTag(const string &tag)
    {
            int index = hashFunction(tag);
    
        if (!table[index].empty()) {
        return table[index].back();
         } else {
        return list<int>();
        }
        int index = hashFunction(tag);
        return table[index].empty() ? table[index];
    }

    void printTable()
    {
        for (int index = 0; index < TABLE_SIZE; ++index)
        {
            for (const list<int> &ids : table[index])
            {
                for (const int id : ids)
                {
                    cout << "  ----------------------" << endl;
                    cout << id << endl;
                    cout << "  ----------------------" << endl;
                }
            }
        }
    }
};
*/