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

// Struct auxiliar para controlar como foi o saque na cidade
struct saque_cidade{
  std::vector<Item> itens_roubados;
  int indice_cidade;
};

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
    std::vector<int> ACO(int numIteracoes, int numFormigas, double taxaEvaporacao, double alpha, double beta);
    double calcDistancia_Total(std::vector<int> caminho);
    void traduz_caminho_interno_to_externo(std::vector<int> caminho_interno, std::vector<int>& caminho_traduzido);
    void traduz_caminho_externo_to_interno(std::vector<int> caminho_externo, std::vector<int>& caminho_traduzido);
    void gera_mochila_light(std::vector<int>& caminho, std::vector<saque_cidade>&mochila);
    void gera_vetor_velocidades(std::vector<saque_cidade>& mochila, std::vector<double>& velocidades);
    double calculador_velocidade(double velocidade_atual, double peso_item);
    void gera_vetor_tempos(std::vector<int>& caminho, std::vector<double>& velocidades, std::vector<double>& tempos);
    double gera_valores(std::vector<saque_cidade> mochila, std::vector<double>  velocidade, std::vector<int> &caminho);
    double calcula_tempo_total(std::vector<double>& tempos);
    double calcula_montante_saque(std::vector<saque_cidade>& mochila);
    double calcula_lucro(std::vector<double> &tempos,std::vector<double> velocidade, std::vector<saque_cidade> &mochila,std::vector<int> caminho);
    void print_dados_ACO(double custo_primeiro_caminho, double custo_melhor_caminho, double lucro_primeiro_caminho, double lucro_melhor_caminho, std::vector<double>& velocidades, std::vector<double>& tempos,std::vector<saque_cidade>& mochila, int peso);
    void printa_matrix_feromonios( std::vector<std::vector<double>>& feromonios, int iteracao, int numFormigas);
    void problema_mochila(std::vector<int> caminho);
    void busca_local(std::vector<Item>& itens, double& valor, int& peso, std::vector<std::pair<Item, double>>& lucroItem, int capacidade_mochila);
    double best_lucro;

  private:
    std::vector<Vertice> nos{};
    std::vector<std::vector<double>> matrix_distancias;
    std::vector<std::vector<int>> floyd_interno();
    int capacidade_mochila;
    int numero_itens;
    double v_min;
    double v_max;
    double v_atual;
    double custo_aluguel;
    double carga_atual;
    int ordem;
    int dimensao;
    std::unordered_map<int, std::vector<int>> registro_geral_formigas_caminho;
    std::unordered_map<int, std::vector<saque_cidade>> registro_geral_formigas_mochila;
    std::unordered_map<int, std::vector<double>> registro_geral_formigas_velocidades;
    std::unordered_map<int, double> registro_geral_formigas_lucros;
    
};



#endif