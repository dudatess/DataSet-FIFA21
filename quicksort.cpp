#include "player.h"
#include "top.h"

using namespace std;

// PARTICAO DO QUICKSORT
int partition(vector<Player>& players, int low, int high)
{
    double pivot = players[high].rating;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (players[j].rating >= pivot)
        {
            i++;
            swap(players[i], players[j]);
        }
    }
    swap(players[i + 1], players[high]);
    return (i + 1);
}

// QUICKSORT
void quickSort(vector<Player>& players, int low, int high)
{
    if (low < high)
    {
        int pi = partition(players, low, high);

        quickSort(players, low, pi - 1);
        quickSort(players, pi + 1, high);
    }
}

// ORDENA DECRESCENTE
void sortDescending(vector<Player>& players)
{
    int n = players.size();
    quickSort(players, 0, n - 1);
}

// MANTER ORDENACAO ESTAVEL
bool shouldSwap(int a, int b, vector<double> rating) {
    if (rating[a] != rating[b]) 
    {
        return rating[a] > rating[b];
    }

    return false;
}


//PARTICAO DE RATING
int partition_r(vector<double>& rating, vector<int>& sofifa, int low, int high) {
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (shouldSwap(j, high, rating)) {
            i++;
            swap(sofifa[i], sofifa[j]);
            swap(rating[i], rating[j]);
        }
    }

    swap(sofifa[i + 1], sofifa[high]);
    swap(rating[i + 1], rating[high]);

    return (i + 1);
}

//QUICKSORT DO RATING
void quicksort_r(vector<double>& rating, vector<int>& sofifa, int low, int high) {
    if (low < high) {
        int pi = partition_r(rating, sofifa, low, high);

        quicksort_r(rating, sofifa, low, pi - 1);
        quicksort_r(rating, sofifa, pi + 1, high);
    }
}


