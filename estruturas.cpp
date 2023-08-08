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
        int line_count = 0;

        //Leitura do arquivo CSV
        std::ifstream f(nome_arq);
        CsvParser parser(f);

        //Leitura linha por linha do arquivo
        for (auto& row : parser)
        {
            if(line_count > 0)
            {//TA COM BUG NA FUNCAO STOI
            hash_table.insert(std::stoi(row[1]), std::stoi(row[2]));
            }

            line_count++;
        }

        hash_table.printTable();
    }