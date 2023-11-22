#include <algorithm>
#include <iostream>
#include <vector>
#include "../header/Grafo.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, const char* argv[]){

    std::vector<std::string> instancias;

    std::string directory_path = "../instances/"; // Substitua pelo caminho do seu diretório
    
    std::vector<int> custosIniciais, custosFinais;

    for (const auto& entry : fs::directory_iterator(directory_path)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
    return 0;

}

