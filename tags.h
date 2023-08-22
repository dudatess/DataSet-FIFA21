#ifndef TAGS_H
#define TAGS_H

// HASH DAS TAGS

#include "player.h"

using namespace std;


// CLASSE DAS TAGS
class Tag
{
public:
    string tag;
    vector<int> sofifa_id;

    void print_tag() const
    {
        cout << "tag: " << tag << endl;
        int i=0;
        for(int id: sofifa_id)
        {
            cout << id << " ";
            i++;
        }

    }

    // DADO UM SOFIFA DIZ SE TEM NA TAG
    bool tem(int i)
    {
        for (int id : sofifa_id)
        {
            if (id == i)
                return true;
        }

        return false; 
    }


};


class Hash_Tags
{
    private:

        static const int TABLE_SIZE = 20000;
        list<Tag> table[TABLE_SIZE];

        int hashFunction(const string &tag)
        {
            int hash = 5381; // Um número primo

            for (char c : tag)
            {
                hash += static_cast<unsigned char>(c);
            }

            return hash % TABLE_SIZE;
        }

    public:

        // VERIFICA SE UM NUMERO ESTA NA LISTA
        bool find(vector<int> &vetor, int numero)
        {
            for (int num : vetor)
            {
                if (num == numero)
                {
                    return true;
                }
            }
            return false;
        }

        // DADO UMA TAG E UM SOFIFA_ID INSERE NA TABELA
        void insert_tag(const string &tag, int sofifa_id)
        {
            int index = hashFunction(tag);
            
            if (table[index].empty())
            {
                Tag new_tag;
                new_tag.tag = tag;
                new_tag.sofifa_id.push_back(sofifa_id);
                table[index].push_back(new_tag);
            }

            else
            {
                for (Tag &t : table[index])
                {
                    if (t.tag == tag)
                    {
                        if(!find(t.sofifa_id, sofifa_id))
                        {
                            t.sofifa_id.push_back(sofifa_id);
                        }
                    }
                }
            }

        }

        // DADO UMA TAG RETORNA UMA Tag
        Tag search(string tag)
        {
            int index = hashFunction(tag);

                for (Tag &t : table[index])
                {
                    if (t.tag == tag)
                        return t;

                }

            return Tag();
        }





        // IMPRIME AS INFORMACOES DE CADA TAG DA TABELA
        void printTable()
        {
            for (int index = 0; index < TABLE_SIZE; ++index)
            {
                for (Tag t : table[index])
                {   
                    cout << "  ----------------------" << endl;
                    t.print_tag();
                    cout <<  "\n  ----------------------" << endl;

                }
            }
            
        }




};

//Declaracao de funcoes para pesquisa de tags
void pesquisaTags(string tags_juntas, Hash_Tags &hash_tags, Hash_Player &hash_player);

#endif /*TAGS_H*/