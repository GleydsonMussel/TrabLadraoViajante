#include <algorithm>
#include <iostream>
#include <vector>
#include "../header/Grafo.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, const char* argv[]){

    std::vector<std::string> instancias;

    std::string directory_path = "../instances/"; 
    
    std::vector<int> custosIniciais, custosFinais;

    for (const auto& entry : fs::directory_iterator(directory_path)) {
        std::cout << entry.path().filename().string() << std::endl;
        Grafo grafo("../instances/"+entry.path().filename().string());
        grafo.ACO(100,70,0.2,1,1);
    }

    return 0;

}

