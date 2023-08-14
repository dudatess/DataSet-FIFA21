#ifndef USER_H
#define USER_H

// TIPO USER
// HASH DOS USERS

#include "player.h"

using namespace std;

// CLASSE DO USER
class User
{
public:
    int user_id;
    vector<int> sofifa_id;
    vector<double> rating;

    void print_user() const
    {
        cout << "  user_id: " << user_id << endl;
        for (size_t i = 0; i < sofifa_id.size(); ++i)
            cout << "  sofifa_id: " << sofifa_id[i] << "  rating: " << rating[i] << endl;
    }
};

// HASH DO USER
class Hash_User
{
private:
    static const int TABLE_SIZE = 20000;
    vector<list<User>> table[TABLE_SIZE];

    // DADO UM ID RETORNA UMA POSICAO NA TABELA
    int hashFunction(int user_id)
    {
        return user_id % TABLE_SIZE;
    }

public:
    // DADO UM USER ID, SOFIFA_ID E UM RATING INSERE NA TABELA
    void insert_user(int user_id, int sofifa_id, double rating)
    {
        int index = hashFunction(sofifa_id);

        if (table[index].empty())
        {
            User new_user;
            new_user.user_id = user_id;
            new_user.sofifa_id.push_back(sofifa_id);
            new_user.rating.push_back(rating);
            table[index].emplace_back();
            table[index].back().push_back(new_user);
        }

        for (auto &userList : table[index])
        {
            for (User &user : userList)
            {
                if (user.user_id == user_id)
                {
                    user.sofifa_id.push_back(sofifa_id);
                    user.rating.push_back(rating);
                    // ORDEM DECRESCENTE
                    for (size_t i = user.rating.size() - 1; i > 0 && user.rating[i] > user.rating[i - 1]; --i)
                    {
                        swap(user.rating[i], user.rating[i - 1]);
                        swap(user.sofifa_id[i], user.sofifa_id[i - 1]);
                    }
                    return;
                }
            }
        }
    }

    // IMPRIME AS INFORMACOES DE CADA USER DA TABELA
    void printTable()
    {
        for (int index = 0; index < TABLE_SIZE; ++index)
        {
            for (const list<User> &userList : table[index])
            {
                for (const User &user : userList)
                {
                    cout << "  ----------------------" << endl;
                    user.print_user();
                    cout << "  ----------------------" << endl;
                }
            }
        }
    }
};

void tabelaRatings(Hash_User &hash_user, Hash_Player &hash_player, string ratings);

#endif /*USER_H*/