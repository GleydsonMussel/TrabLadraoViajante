#ifndef TRAB_INTELIGENCIA_COMPUTACIOANAL_HPP
#define TRAB_INTELIGENCIA_COMPUTACIOANAL_HPP

#include "No.hpp"
#include <array>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

class Grafo final {

  public:
    // Construtor
    Grafo(std::string filename);
    // Adicionadores
    void adicionarNo(int id, Vertice vertice){
      nos.emplace(id, vertice);
    }                           
    void adicionarAresta(int origem, int destino, float peso = 1.0);      
    
    void adicionaItem(int cidade, Item item){
      this->nos[cidade].itens_to_roubar.push_back(item);
    }

    void cadastraComoVisitado_No(int id){
          this->nos[id].visitado = true;
          this->ordem = this->ordem - 1;
    }
    // Printadores    
    void printa_nos(){
        for(auto& [id, no] : this->nos)
        std::cout<<id<<"\n";
    }
    void printa_arestas();   
    void printa_itens();   
    // Otimizadores                                   
    std::pair<std::vector<int>, std::vector<int>> ACO(int n_formigas, int n_geracoes, float taxa_evaporacao); 
    bool validarSolucao(std::vector<int> solucao);
    int calculaCusto(std::vector<int> solucao);
    float calculaCustoTempo(std::vector<int> solucao);

  private:
    std::unordered_map<int, Vertice> nos{};
    std::vector<std::vector<int>> floyd_interno();
    int capacidade_mochila;
    int numero_itens;
    float v_min;
    float v_max;
    float custo_aluguel;
    int ordem;
    int dimensao;

};

#endif