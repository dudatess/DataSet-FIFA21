#include "player.h"
#include "user.h"
#include "top.h"
#include "quicksort.cpp"
#include "tags.h"

using namespace std;

// 2.1
void pesquisaPlayer(string prefix, Trie_Player &trie_player, Hash_Player &hash_player)
{

    vector<int> result = trie_player.search(prefix);

    cout << "Jogadores com prefixo '" << prefix << "': " << endl;

    cout << "sofifa_id ";
    cout << "name ";
    cout << "player_positions ";
    cout << "rating " << fixed << setprecision(6);
    cout << "count " << endl;

    for (int id : result)
    {
        Player player_prefix = hash_player.search(id);
        player_prefix.print_player();
        cout << endl;
    }
}

// 2.2
void pesquisaUser(string entrada, Hash_User &hash_user, Hash_Player &hash_player)
{

    cout << "Jogadores avaliados pelo usuario '" << entrada << "': " << endl;

    int user_id = stoi(entrada);
    User user = hash_user.search(user_id);
 
    int i = 0, controle=0;

    cout << "sofifa_id ";
    cout << "name ";
    cout << "player_positions ";
    cout << "global_rating " ;
    cout << "count ";
    cout << "rating " << endl;

    quicksort_r(user.rating, user.sofifa_id, 0, user.rating.size() - 1);

    for (int id : user.sofifa_id)
    {
        Player player = hash_player.search(id);
        player.print_player();
        cout << user.rating[i] << endl;

        i++;

        controle++;
        if (controle > 20)
            break;
    }
}

// 2.3
void pesquisaTop(string entrada, Hash_Positions &hash_positions, Hash_Player &hash_player)
{
    string top;
    int numero_top;
    string posicao;

    vector<int> sofifa_ids;
    vector<Player> players_top;


    // FORMATO top<N> ‘<position>’
    size_t numStart = entrada.find_first_of("0123456789");

    if (numStart != string::npos) {
        top = entrada.substr(0, numStart);

        size_t numEnd = entrada.find_first_not_of("0123456789", numStart);
        if (numEnd != string::npos) {
            string numStr = entrada.substr(numStart, numEnd - numStart);
            istringstream(numStr) >> numero_top;

            size_t posStart = entrada.find_first_of("'\"", numEnd);
            size_t posEnd = entrada.find_first_of("'\"", posStart + 1);

            if (posStart != string::npos && posEnd != string::npos) 
                posicao = entrada.substr(posStart + 1, posEnd - posStart - 1);
        }
    }

    cout << "Top " << numero_top << " Jogadores " << posicao << " " << endl;

    sofifa_ids = hash_positions.search(posicao).sofifa_id;

    for(int id : sofifa_ids){
        Player new_player;
        new_player = hash_player.search(id);
        players_top.push_back(new_player);
    }

    int n = players_top.size();
    quickSort(players_top, 0, n - 1);
     
    int controle;
    controle = 1;

    for(Player &player: players_top){
        
        if(controle > numero_top){
            break;
        }

        if(player.count>1000)
        {
            player.print_player();
            cout<<endl;
            controle++;
        }
        
    }
    
    
}




// 2.4
void pesquisaTags(string tags_juntas, Hash_Tags &hash_tags, Hash_Player &hash_player)
{
  
    cout << "Jogadores " << tags_juntas << " :"<<endl;
    
    vector<string> tags;
    vector<Player> players;
    istringstream iss(tags_juntas);
    string tag;

    //Divide a string baseada em apostofres
    while (getline(iss, tag, '\''))
    {
        if (!tag.empty() && tag != " ") 
        {
            tags.push_back(tag);
        }
    }
    
    vector<Tag> vetor_tags;
    vector<int> sofifa_ids;

    // Para cada uma das tags
    for (string chave : tags)
    {
        // Fazer a pesquisa dos IDS na hash e guardar em um vetor
        vetor_tags.push_back(hash_tags.search(chave));
        sofifa_ids =hash_tags.search(chave).sofifa_id;

    }
    

    int i = 0, indice = 0;

    for (string chave : tags)
    {
        vector<int>::iterator it = sofifa_ids.begin();

        while (it != sofifa_ids.end())
        {

            if (!vetor_tags[indice].tem(*it))
            {
                it = sofifa_ids.erase(it);
            }
            else
            {
                ++it;
            }
        }

        indice++;
    }

    
    for(int id : sofifa_ids)
    {   

        Player new_player;
        new_player = hash_player.search(id);
        new_player.print_player();
        cout<<endl;
    }
 
}



