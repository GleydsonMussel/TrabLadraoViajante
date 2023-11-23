#ifndef NO_HPP
#define NO_HPP

#include <forward_list>
#include <vector>

struct Aresta {
  int id{};
  float peso{ 1.0 };
};

struct Item{
  int id;
  int lucro;
  int peso; 
  int onde_esta;
};

struct Vertice{
    int id;
    bool visitado = false;
    std::forward_list<Aresta> arestas{};
    std::pair<float,float> coord;
};


#endif