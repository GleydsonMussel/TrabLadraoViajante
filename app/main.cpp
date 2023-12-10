#include <algorithm>
#include <iostream>
#include <vector>
#include "../header/Grafo.hpp"
#include <fstream>
#include <filesystem>
#include <fstream>
#include "../header/timer.hpp"

namespace fs = std::filesystem;

int main(int argc, const char* argv[]){

    std::vector<std::string> instancias;

    std::string directory_path = "../instances/"; 
    
    std::vector<int> custosIniciais, custosFinais;
    
    std::ofstream arquivo("../outputs/resultado.txt");
    
    if(arquivo.is_open()){

        auto acumulador_tempos = 0.0;

        for (const auto& entry : fs::directory_iterator(directory_path)) {

            // Inicializa o tempo
            auto timer = Timer{};
            
            Grafo grafo("../instances/"+entry.path().filename().string());
            //grafo.ACO(100,70,0.2,1,1);
            
            // Pega o tempo decorrido em segundos
            auto tempo = timer.elapsed();
            acumulador_tempos += tempo;
        
            grafo.best_lucro = 20;

            auto instancia_rodada = entry.path().filename().string();
            
            arquivo << instancia_rodada << "\n";
            arquivo << grafo.best_lucro << "\n";
            arquivo << tempo << "\n"; 
            std::cout<<"Li o arquivo: "<<instancia_rodada<<"\n";
        }

        arquivo << "\nTempo Total(s): " << acumulador_tempos;

        arquivo.close();

    }
    
    return 0;

}

