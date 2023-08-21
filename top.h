#ifndef TOP_H
#define TOP_H

// HASH DAS POSICOES

#include "player.h"

using namespace std;


// HASH TABLE EM QUE AS CHAVES SAO AS POSICOES
class Hash_Positions{
    
private:

    static const int TABLE_SIZE = 200;
    vector<int> table[TABLE_SIZE];

    // Funcao de hash em que as posicoes sao as chaves
    int hashFunction(const string &positions)
    {
        //Funcao hash polinomial, utilizado propriedade aritmetica modular 
        int hash = 0;
        
        int len = positions.length();

        for(int i = 0; i < len ; i++)
        {
            hash = (31 * hash + positions[i]) % TABLE_SIZE;
        }

        return hash;
    }


public:

    void insert(const string &positions, int id)
    {
        vector<string> positions_jogador;
        istringstream iss(positions);
        string position;
        int index = 0;

        //Separar as posicoes dos jogadores tirando as apostrofes
        while (iss >> position)
        {
            // Tire as apostrofes da tag
            if (position.front() == '\'' && position.back() == '\'')
            {
                position = position.substr(1, position.length() - 2);
            }
            // Guarda as tags em um vector
            positions_jogador.push_back(position);

        }

        //Inserir cada posicao do vetor na tabela hash 
        for(const auto& p : positions_jogador)
        {
            index = hashFunction(p);
            table[index].push_back(id);
        }
        
    }

    vector<int> findPosition(const string &position)
    {
        int index = hashFunction(position);
    
        if (!table[index].empty())
        {
            return table[index];
        } 
        else 
        {
            return vector<int>();
        }

    }

    void printTable()
    {
            for(const vector<int> &ids : table)
            {
                cout << "  ----------------------" << endl;

                for(const int id : ids)
                {
                    cout << id << endl;
                }

                cout << "  ----------------------" << endl;
            }
        
    }

};

void tabelaPosicoes(Hash_Positions &hash_positions);


#endif /*TOP_H*/