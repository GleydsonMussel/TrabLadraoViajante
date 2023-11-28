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
      this->nos.push_back(vertice);
    }                              
    
    void adicionaItem(int cidade, Item item){
      cidade--;
      this->nos[cidade].itens_to_roubar.push_back(item);
    }

    void cadastraComoVisitado_No(int id){
          this->nos[id].visitado = true;
          this->ordem = this->ordem - 1;
    }
    // Printadores    
    void printa_nos(){
        for(auto& no : this->nos)
        std::cout<<no.id<<"\n";
    }  
    void printa_itens();   
    // Otimizadores                                   
    std::vector<int> ACO(int numIteracoes, int numFormigas, float taxaEvaporacao, float alpha, float beta);
    bool validarSolucao(std::vector<int> solucao);
    int calculaCusto(std::vector<int> solucao);
    float calculaCustoTempo(std::vector<int> solucao);
    double calcDistancia_Total(std::vector<int> caminho);
    void traduz_caminho_interno_to_externo(std::vector<int> caminho_interno, std::vector<int>& caminho_traduzido);
    void traduz_caminho_externo_to_interno(std::vector<int> caminho_externo, std::vector<int>& caminho_traduzido);
    std::vector<int> gera_mochila(std::vector<int> rota, std::vector<int>& mochila_simples);
    void atualiza_velocidade(Item& item);

  private:
    std::vector<Vertice> nos{};
    std::vector<std::vector<double>> matrix_distancias;
    std::vector<std::vector<int>> floyd_interno();
    int capacidade_mochila;
    int numero_itens;
    float v_min;
    float v_max;
    float v_atual;
    float custo_aluguel;
    float carga_atual;
    int ordem;
    int dimensao;
    
};

#endif