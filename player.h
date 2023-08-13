#ifndef PLAYER_H
#define PLAYER_H

//ARQUIVO HEADER PARA DECLARAR AS CLASSES

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include "parser.hpp"
#include "user.h"
#include <iomanip> // I/O MANIPULATION (DOUBLE EM 6 CASAS DECIMAIS)

using namespace std;

// CLASSE DO PLAYER COM INFORMACOES COMPLEMENTARES
class Player
{
public:
    int sofifa_id;
    string name;
    string player_positions;
    double rating;
    double sum_ratings;
    int count;

    void print_player() const
    {
        cout << "  sofifa_id: " << sofifa_id << endl;
        cout << "  name: " << name << endl;
        cout << "  player_positions: " << player_positions << endl;
        cout << "  rating: " << fixed << setprecision(6) << rating << endl;
        cout << "  count: " << count << endl;
    }
};

// CLASSE DA HASH PARA INSERIR/EXTRAIR INFOS
class Hash_Player
{
private:
    static const int TABLE_SIZE = 20000;
    vector<list<Player>> table[TABLE_SIZE];

    // DADO UM ID RETORNA UMA POSICAO NA TABELA
    int hashFunction(int sofifa_id)
    {
        return sofifa_id % TABLE_SIZE;
    }

public:
    // DADO UM ID, NOME E POSICAO DE UM JOGADOR, INSERE NA TABELA
    void insert_player(int sofifa_id, string name, string player_positions)
    {
        int index = hashFunction(sofifa_id);

        Player new_player;
        new_player.sofifa_id = sofifa_id;
        new_player.name = name;
        new_player.player_positions = player_positions;
        new_player.rating = 0;
        new_player.sum_ratings = 0;
        new_player.count = 0;

        if (table[index].empty())
            table[index].emplace_back();

        table[index].back().push_back(new_player);
    }

    // DADO UM ID E UMA AVALIACAO, INSERE NO JOGADOR
    void insert_rating(int sofifa_id, double rating)
    {
        int index = hashFunction(sofifa_id);

        if (table[index].empty())
        {
            table[index].emplace_back();
        }

        for (auto &playerList : table[index])
        {
            for (Player &player : playerList)
            {
                if (player.sofifa_id == sofifa_id)
                {
                    player.count++;
                    player.sum_ratings += rating;
                    player.rating = player.sum_ratings / player.count;
                    return;
                }
            }
        }
    }

    // DADO UM ID RETORNA UM JOGADOR
    Player search(int sofifa_id)
    {
        int index = hashFunction(sofifa_id);

        for (auto &playerList : table[index])
        {
            for (Player &player : playerList)
            {
                if (player.sofifa_id == sofifa_id)
                {
                    return player;
                }
            }
        }

        return Player();
    }

    // IMPRIME AS INFORMACOES DE CADA JOGADOR DA TABELA
    void printTable()
    {
        for (int index = 0; index < TABLE_SIZE; ++index)
        {
            for (const list<Player> &playerList : table[index])
            {
                for (const Player &player : playerList)
                {
                    cout << "  ----------------------" << endl;
                    player.print_player();
                    cout << "  ----------------------" << endl;
                }
            }
        }
    }
};

// NODO DA TRIE
class TrieNode
{
public:
    vector<pair<char, TrieNode *>> children;
    list<int> sofifa_id;
};

// TRIE
class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string &name, int sofifa_id)
    {
        TrieNode *current = root;
        for (char c : name)
        {
            bool found = false;
            for (auto &child : current->children)
            {
                if (child.first == c)
                {
                    current = child.second;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                TrieNode *newChild = new TrieNode();
                current->children.emplace_back(c, newChild);
                current = newChild;
            }
            current->sofifa_id.push_back(sofifa_id);
        }
    }

    vector<int> search(const string &prefix)
    {
        TrieNode *current = root;
        for (char c : prefix)
        {
            bool found = false;
            for (auto &child : current->children)
            {
                if (child.first == c)
                {
                    current = child.second;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                return {};
            }
        }
        vector<int> result(current->sofifa_id.begin(), current->sofifa_id.end());
        return result;
    }
};

void tabelaAvaliacoes(Hash_Player &hash_table, Hash_User &hash_user, Trie &trie, string players, string ratings);

//DECLARACAO CLASSE HASH TABLE PARA TAGS (a chave são as tags e os dados nos buckets sao os IDS)
class Hash_Tags{

private:

    static const int TABLE_SIZE = 20000;
    std::vector<std:: list<int>> table[TABLE_SIZE];

    //Funcao de hash em que as tags sao as chaves
    int hashFunction(const std::string &tag)
    {
        //Variável hash armazena a soma dos caracteres da tag
        int hash = 0;
        for(char c : tag)
        {
            hash += c;
        }

        return hash % TABLE_SIZE;
    }

public:

    void insert(const std::string &tag, int id)
    {
        int index = hashFunction(tag);

         if (table[index].empty())
         {
            table[index].emplace_back();
         }
        
     // Encontrar a lista apropriada no bucket
    auto &id_list = table[index].back();
    
    // Verificar se o id já está presente na lista
    if (std::find(id_list.begin(), id_list.end(), id) == id_list.end())
    {
        id_list.push_back(id);
    }

    }

    std::list<int> findPlayerTag(const std::string &tag)
    {
        int index = hashFunction(tag);
        return table[index].empty() ? std::list<int>() : table[index].back();
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

void tabelaTags(Hash_Tags &hash_tags);

#endif /*PLAYER_H*/