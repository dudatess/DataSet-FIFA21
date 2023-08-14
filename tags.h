#ifndef TAGS_H
#define TAGS_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

// Tirei o #include <algorithm> pq nao pode.
// substitui por um loop simples para verificar a existência do ID na lista
// fique a vontade para trocar/melhorar

using namespace std;

// DECLARACAO CLASSE HASH TABLE PARA TAGS (a chave são as tags e os dados nos buckets sao os IDS)
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
        return table[index].empty() ? list<int>() : table[index].back();
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

#endif /*TAGS_H*/
