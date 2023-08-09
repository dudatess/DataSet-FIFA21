//ARQUIVO HEADER PARA DECLARAR AS CLASSES E AS ESTRUTURAS UTILIZADAS NA PARTE 1 DO TRABALHO (CONSTRUCAO)

#include <iostream>
#include "parser.hpp"
#include <string>
#include <list>

void tabelaAvaliacoes(std::string nome_arq);

struct PlayerData
{
    int player_id;
    double avarage_rating;
    double sum_ratings;
    int total_ratings;

};

class HashTable
{
    private:

    static const int TABLE_SIZE = 20000;
    std::vector<std::list<PlayerData>> table[TABLE_SIZE];

    int hashFunction(int player_id)
    {  
        return player_id % TABLE_SIZE;
    }

    public:

    void insert(int player_id, double rating)
    {
        int index = hashFunction(player_id);
        
            // Verifica se a posição está vazia
    if (table[index].empty()) {
        // Adiciona uma nova lista à posição vazia
        table[index].emplace_back();
    }

        //Verifica se o jogador ja esta na posicao da tabela hash
        for(auto& playerList : table[index])
        {
            for(PlayerData& player : playerList)
            {
                //Atualiza dados do jogador
                if(player.player_id == player_id)
                {
                    player.total_ratings++;
                    player.sum_ratings += rating;
                    player.avarage_rating = player.sum_ratings/player.total_ratings;

                    return;
                }

            }
        }

        
        //Se nao encontrou o jogador, cria uma nova posicao para ele
        PlayerData new_player;
        new_player.player_id = player_id;
        new_player.sum_ratings = rating;
        new_player.avarage_rating = 0;
        new_player.total_ratings = 0;
        table[index].back().push_back(new_player);
   
        return;
    }

    PlayerData* search(int player_id)
    {
        int index = hashFunction(player_id);

            for(auto& playerList : table[index])
        {
            for(PlayerData& player : playerList)
            {
                if(player.player_id == player_id)
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
        std::cout << "Index " << index << ":" << std::endl;
        for (const std::list<PlayerData>& playerList : table[index])
        {
            for (const PlayerData& player : playerList)
            {
                std::cout << "  Player ID: " << player.player_id << std::endl;
                std::cout << "  Average Rating: " << player.avarage_rating << std::endl;
                std::cout << "  Total Ratings: " << player.total_ratings << std::endl;
                std::cout << "  Sum Ratings: " << player.sum_ratings << std::endl;
                std::cout << "  ----------------------" << std::endl;
            }
        }
    }
}

};