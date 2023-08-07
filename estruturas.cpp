//FUNCOES PARA A PARTE 1 DO TRABALHO (CONSTRUCAO)

#include <iostream>
#include <string>
#include "parser.hpp"
#include "estruturas.h"
#include <cctype>
#include <algorithm>

void tabelaAvaliacoes(std::string nome_arq)
{
    using namespace aria::csv;

    HashTable hash_table;

    //Leitura do arquivo CSV
    std::ifstream f(nome_arq);
    CsvParser parser(f);

    //Leitura linha por linha do arquivo
    for (auto& row : parser)
    {
        //TA COM BUG NA FUNCAO STOI
        hash_table.insert(std::stoi(row[1]), std::stoi(row[2]));
    }

    hash_table.printTable();
}