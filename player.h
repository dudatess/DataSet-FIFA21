#ifndef PLAYER_H
#define PLAYER_H

// ARQUIVO HEADER PARA DECLARAR AS CLASSES DO JOGADOR 2.1 DO TRABALHO

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

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
        cout << "  rating: " << rating << endl;
        cout << "  count: " << count << endl;
    }
};

// CLASSE DA HASH PARA INSERIR/EXTRAIR INFOS
class HashTable
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
class TrieNode{
public:
    unordered_map<char, TrieNode*> children;
    vector<int> sofifa_id;
};

// TRIE
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& name, int sofifa_id) {
        TrieNode* current = root;
        for (char c : name) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
            current->sofifa_id.push_back(sofifa_id);
        }
    }

    vector<int> search(const string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return {};
            }
            current = current->children[c];
        }
        return current->sofifa_id;
    }
};


// ASSINATURA DAS FUNCOES EM PLAYER.CPP
void tabelaAvaliacoes(HashTable &hash_table, Trie &trie, string players, string ratings);

#endif /*PLAYER_H*/