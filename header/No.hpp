#ifndef NO_HPP
#define NO_HPP

#include <forward_list>
#include <vector>

struct Item{
  int id = -1;
  int lucro;
  int peso; 
  int cidade_onde_estou;
};

struct Vertice{
    int id = -1;
    bool visitado = false;
    std::pair<float,float> coord;
    std::vector<Item> itens_to_roubar;
};


#endif