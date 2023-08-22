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








void swapTwo(vector<int>& vec1, vector<double>& vec2, int index1, int index2)
{
    swap(vec1[index1], vec1[index2]);
    swap(vec2[index1], vec2[index2]);
}


int partition_r(vector<double>& arr, vector<int>& sofifa, int low, int high)
{
    double pivot = arr[high]; 
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        
        if (arr[j] >= pivot)
        {
            i++;
            swapTwo(sofifa, arr, i, j);
        }
    }
    swapTwo(sofifa, arr, i + 1, high);
    return (i + 1);
}


void quicksort_r(vector<double>& arr, vector<int>& sofifa, int low, int high)
{
    if (low < high)
    {
        int pi = partition_r(arr, sofifa, low, high);

        quicksort_r(arr, sofifa, low, pi - 1);
        quicksort_r(arr, sofifa, pi + 1, high);
    }
}