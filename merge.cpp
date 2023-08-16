#include "player.h"
#include "top.h"

using namespace std;

// Função de merge
void merge(vector<int>& playerIds, Hash_Player playerData, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> leftIds(n1);
    vector<int> rightIds(n2);

    // Copia os dados para os vetores temporários
    for (int i = 0; i < n1; i++) {
        leftIds[i] = playerIds[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightIds[i] = playerIds[middle + 1 + i];
    }

    // Merge dos dois vetores temporários
    int i = 0; // Índice para o vetor esquerdo
    int j = 0; // Índice para o vetor direito
    int k = left; // Índice para o vetor original

    while (i < n1 && j < n2) {
        int id1 = leftIds[i];
        int id2 = rightIds[j];

        Player playerData1 = playerData.search(id1);
        Player playerData2 = playerData.search(id2);

        // Verifica se ambos os jogadores têm mais de 1000 avaliações
        if (playerData1.count >= 1 && playerData2.count >= 1) {
            // Compara as avaliações dos jogadores
            if (playerData1.rating >= playerData2.rating) {
                playerIds[k] = id1;
                i++;
            } else {
                playerIds[k] = id2;
                j++;
            }
            k++;
        } else if (playerData1.count >= 1) {
            playerIds[k] = id1;
            i++;
            k++;
        } else {
            playerIds[k] = id2;
            j++;
            k++;
        }
    }

    // Copia os elementos restantes, se houver
    while (i < n1) {
        playerIds[k] = leftIds[i];
        i++;
        k++;
    }

    while (j < n2) {
        playerIds[k] = rightIds[j];
        j++;
        k++;
    }
}

// Função de merge sort
void mergeSort(vector<int>& playerIds, Hash_Player playerData, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(playerIds, playerData, left, middle);
        mergeSort(playerIds, playerData, middle + 1, right);

        merge(playerIds, playerData, left, middle, right);
    }
}
