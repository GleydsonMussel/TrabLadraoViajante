#ifndef TRAB_INTELIGENCIA_COMPUTACIOANAL_HPP
#define TRAB_INTELIGENCIA_COMPUTACIOANAL_HPP

#include "No.hpp"
#include <iostream>
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
    void printa_itens();   
    // Otimizadores                                   
    std::vector<int> ACO(int numIteracoes, int numFormigas, float taxaEvaporacao, float alpha, float beta);
    bool validarSolucao(std::vector<int> solucao);
    int calculaCusto(std::vector<int> solucao);
    float calculaCustoTempo(std::vector<int> solucao);
    double calcDistancia_Total(std::vector<int> caminho);

  private:
    std::unordered_map<int, Vertice> nos{};
    std::unordered_map<int, std::unordered_map<int, double>> matrix_distancias;
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