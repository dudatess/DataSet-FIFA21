#ifndef TOP_H
#define TOP_H

// HASH DAS POSICOES

#include "player.h"

using namespace std;

// CLASSE DAS POSICOES
class Position
{
public:
    string position;
    vector<int> sofifa_id;

    void print_position() const
    {
        cout << "position: " << position << endl;
        int i=0;
        for(int id: sofifa_id)
        {
            cout << id << " ";
            i++;
        }

    }
};



// HASH TABLE EM QUE AS CHAVES SAO AS POSICOES
class Hash_Positions{
    
private:

    static const int TABLE_SIZE = 2000;
    list<Position> table[TABLE_SIZE];

    int hashFunction(const string& positions)
    {
        unsigned long hash = 5381; // Um número primo recomendado como valor inicial

        for (char c : positions)
        {
            // Atualize o hash usando uma combinação de multiplicação e adição
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
        }

        return hash % TABLE_SIZE;
    }


public:

    // DADO AS POSITIONS E UM SOFIFA_ID INSERE NA TABELA
    void insert_position(string positions, int sofifa_id)
    {
        vector<string> positions_jogador;
        istringstream iss(positions);
        string position;
        int index = 0;

        //Separar as posicoes dos jogadores usando vírgulas como delimitador
        while (getline(iss, position, ','))
        {
            // Remova espaços em branco extras ao redor da posição
            position.erase(0, position.find_first_not_of(" "));
            position.erase(position.find_last_not_of(" ") + 1);

            // Tire as aspas da posição, se presentes
            if (!position.empty() && position.front() == '\'' && position.back() == '\'')
            {
                position = position.substr(1, position.length() - 2);
            }

            // Se a posição não estiver vazia, adicione-a ao vetor
            if (!position.empty())
            {
                positions_jogador.push_back(position);
            }
        }

        //Inserir cada posicao do vetor na tabela hash 
        for(const auto& p : positions_jogador)
        {
            index = hashFunction(p);

            if (table[index].empty())
            {
                Position new_pos;
                new_pos.position = p;
                new_pos.sofifa_id.push_back(sofifa_id);
                table[index].push_back(new_pos);
            }

            else
            {
                for (Position &pos : table[index])
                {
                    if (pos.position == p)
                    {
                        pos.sofifa_id.push_back(sofifa_id);
                        return;
                    }
                }
            }





        }
        
    }

    // DADO UMA POS RETORNA UM POSITION
    Position search(string pos)
    {
        int index = hashFunction(pos);

            for (Position &p : table[index])
            {
                if (p.position == pos)
                    return p;

            }

        return Position();
    }

    // IMPRIME AS INFORMACOES DE CADA POSITION DA TABELA
    void printTable()
    {
        for (int index = 0; index < TABLE_SIZE; ++index)
        {
            for (Position pos : table[index])
            {   

                cout << "  ----------------------" << endl;
                pos.print_position();
                cout <<  "\n  ----------------------" << endl;

            }
        }
        
    }
};




#endif /*TOP_H*/