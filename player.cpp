//FUNCOES PARA A PARTE 1 DO TRABALHO (CONSTRUCAO)

    #include <iostream>
    #include <string>
    #include "parser.hpp"
    #include "player.h"
    #include <cctype>

    using namespace std;

    void tabelaAvaliacoes(string nome_arq)
    {
        using namespace aria::csv;

        HashTable hash_table;
        int line_count = 0;

        //Leitura do arquivo CSV
        ifstream f(nome_arq);
        CsvParser parser(f);

        //Leitura linha por linha do arquivo
        for (auto& row : parser)
        {
            if(line_count > 0)
            {//TA COM BUG NA FUNCAO STOI
            hash_table.insert(stoi(row[1]), stoi(row[2]));
            }

            line_count++;
        }

        hash_table.printTable();
    }