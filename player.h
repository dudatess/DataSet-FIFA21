#ifndef PLAYER_H
#define PLAYER_H

// CLASSE DO PLAYER
// HASH DOS PLAYERS
// TRIE DOS PLAYERS

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip> // I/O MANIPULATION (DOUBLE EM 6 CASAS DECIMAIS)
#include <algorithm>
#include "parser.hpp"

using namespace std;

// CLASSE DO PLAYER
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
        cout << sofifa_id << " ";
        cout << name << " ";
        cout << player_positions << " ";
        cout << fixed << setprecision(6) << rating << " ";
        cout << count << " ";
    }
};

// HASH DO PLAYER
class Hash_Player
{
private:
    static const int TABLE_SIZE = 20000;
    list<Player> table[TABLE_SIZE];

    // Funcao de hash em que as sofifa_id sao as chaves
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

        table[index].push_back(new_player);
    }

    // DADO UM ID E UMA AVALIACAO, INSERE NO JOGADOR
    void insert_rating(int sofifa_id, double rating)
    {
        int index = hashFunction(sofifa_id);

        for (Player &player : table[index])
        {
            if (player.sofifa_id == sofifa_id)
            {
                player.count++;
                player.sum_ratings += rating;
                player.rating = player.sum_ratings / player.count;
                return;
            }
        }

        // Se o jogador não foi encontrado, insere um novo jogador na lista
        Player newPlayer;
        newPlayer.sofifa_id = sofifa_id;
        newPlayer.count = 1;
        newPlayer.sum_ratings = rating;
        newPlayer.rating = rating;

        table[index].push_back(newPlayer);
    }

    // DADO UM ID RETORNA UM JOGADOR
    Player search(int sofifa_id)
    {
        int index = hashFunction(sofifa_id);

        for (Player &player : table[index])
        {
            if (player.sofifa_id == sofifa_id)
                return player;
        }

        return Player();
    }

    // IMPRIME AS INFORMACOES DE CADA JOGADOR DA TABELA
    void printTable()
    {

        cout << "  sofifa_id: ";
        cout << "  name: ";
        cout << "  player_positions: ";
        cout << "  global rating: " << fixed << setprecision(6);
        cout << "  count: ";
        cout << "  ----------------------" << endl;
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            for (const Player &player : table[i])
            {
                player.print_player();
            }
        }
        cout << "  ----------------------" << endl;
    }
};

// NODO DA TRIE
class TrieNode
{
public:
    vector<pair<char, TrieNode *>> children;
    list<int> sofifa_id;
};

// TRIE DO PLAYER
class Trie_Player
{
private:
    TrieNode *root;

public:
    Trie_Player()
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

void tabelaPlayers(Hash_Player &hash_player, Trie_Player &trie, string players);

#endif /*PLAYER_H*/