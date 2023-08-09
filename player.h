#ifndef PLAYER_H
#define PLAYER_H

//ARQUIVO HEADER PARA DECLARAR AS CLASSES DO JOGADOR 2.1 DO TRABALHO 

#include <iostream>
#include <string>
#include <list>

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
        Player *next;

    void print_player() const
    {
        cout << "  sofifa_id: " << sofifa_id << endl;
        cout << "  player_positions: " << rating << endl;
        cout << "  rating: " << rating << endl;
        cout << "  count: " << count << endl;
    }
};


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

    // DADO UM ID E UMA AVALIACAO, RETORNA 
    void insert(int sofifa_id, double rating)
    {
        int index = hashFunction(sofifa_id);
        
        // Verifica se a posição está vazia
        if (table[index].empty()) 
        {
            // Adiciona uma nova lista à posição vazia
            table[index].emplace_back();
        }

        //Verifica se o jogador ja esta na posicao da tabela hash
        for(auto& playerList : table[index])
        {
            for(Player& player : playerList)
            {
                //Atualiza dados do jogador
                if(player.sofifa_id == sofifa_id)
                {
                    player.count++;
                    player.sum_ratings += rating;
                    player.rating = player.sum_ratings/player.count;

                    return;
                }

            }
        }

        
        //Se nao encontrou o jogador, cria uma nova posicao para ele
        Player new_player;
        new_player.sofifa_id = sofifa_id;
        new_player.sum_ratings = rating;
        new_player.rating = 0;
        new_player.count = 0;
        table[index].back().push_back(new_player);
   
        return;
    }

    Player* search(int player_id)
    {
        int index = hashFunction(player_id);

            for(auto& playerList : table[index])
        {
            for(Player& player : playerList)
            {
                if(player.sofifa_id == player_id)
                {
                    return &player;
                }

            }
        }

        return nullptr;
    }

    void printTable()
    {
        for (int index = 0; index < TABLE_SIZE; ++index)
        {
            cout << "Index " << index << ":" << endl;
            for (const list<Player>& playerList : table[index])
            {
                for (const Player& player : playerList)
                {
                    cout << "  ----------------------" << endl;
                    player.print_player();
                    cout << "  ----------------------" << endl;
                }
            }
        }
    }

};


#endif /*PLAYER_H*/