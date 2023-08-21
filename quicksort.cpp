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