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
    Grafo(std::string filename);
    void adicionarNo(int id, Vertice vertice);                            // b
    void adicionarAresta(int origem, int destino, float peso = 1.0);      // b
    bool removerNo(int id);
    void removerAresta(int origem, int destino);                          // b
    bool verificarNoRemovidoOuArestaApontaPara(int id);
    Vertice& no(int id);                                      // m
    std::vector<int> geraSolucao(float alpha, int instancia); 
    void printa_arestas();   
    bool validarSolucao(std::vector<int> solucao);
    int calculaCusto(std::vector<int> solucao);
    int quantidadeNos();
    float calculaCustoTempo(std::vector<int> solucao);
    std::unordered_map<int, Vertice> copiarNos() {
      return nos;
    }

  private:
    std::unordered_map<int, Vertice> nos{};
    std::vector<std::vector<int>> floyd_interno();
    int capacidade_mochila;
    int numero_itens;
    float min_velocidade;
    float max_velocidade;
    float custo_aluguel;
    int ordem;

};

#endif