#ifndef NO_HPP
#define NO_HPP

#include <forward_list>
#include <vector>

struct Aresta {
  int id{};
  float peso{ 1.0 };
};

struct Item{
  int id = -1;
  int lucro;
  int peso; 
  int cidade_onde_estou;
};

struct Vertice{
    int id = -1;
    bool visitado = false;
    std::forward_list<Aresta> arestas{};
    std::pair<float,float> coord;
    std::vector<Item> itens_to_roubar;
};


#endif