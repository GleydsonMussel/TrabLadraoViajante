#include "../header/Grafo.hpp"
#include "../header/random.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <execution>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <queue>
#include <random>
#include <stack>
#include <utility>
#include <vector>
#include <cstddef>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>

Grafo::Grafo(std::string filename){

    std::ifstream arquivo(filename);
    std::string linha;
    std::vector<std::string> conteudos_cabecalhos;

    int dimensao, n_itens, capacidade_mochila;
    std::vector<std::pair<float, float>> coordenadas_nos;
    std::vector<int> pesos;

    int contLinha = 0;
    bool parteDosItens = false;

    while(std::getline(arquivo, linha)){
      
      if(linha == "ITEMS SECTION	(INDEX, PROFIT, WEIGHT, ASSIGNED NODE NUMBER): ")
        parteDosItens = true;

      // Somente pegando dados do cabeçalho
      if(contLinha<10){
        
        std::istringstream linha_manipulavel(linha);
        std::string elemento;
        int cont_colunas = 0, colunaAlvo;
        switch (contLinha){
          
          case 0:
            contLinha++;
            continue;
          break;

          case 1:
            contLinha++;
            continue;
          break;

          case 2:
            colunaAlvo = 1;
          break;

          case 3:
            colunaAlvo = 3;
          break;

          case 4:
            colunaAlvo = 3;
          break;

          case 5:
            colunaAlvo = 2;
          break;

          case 6:
            colunaAlvo = 2;
          break;

          case 7:
            colunaAlvo = 2;
          break;

          case 8:
            contLinha++;
            continue;
          break;

          case 9:
            contLinha++;
            continue;
          break;

          default:
          break;
        }
        
        // Percorro os espaçoes em branco
        while(linha_manipulavel >> elemento){
          if (cont_colunas==colunaAlvo)
            conteudos_cabecalhos.push_back(elemento);
          cont_colunas++;
        }

        contLinha++;

      }
      else{

        if(!parteDosItens){

            std::istringstream linha_manipulavel(linha);
            std::string elemento;

            int contCol = 0;

            int id;
            float coord_x;
            float coord_y;

            linha_manipulavel >> id >> coord_x >> coord_y;

            Vertice novoNo;
            novoNo.id = id;
            novoNo.coord = {coord_x, coord_y};
            this->adicionarNo(id, novoNo);

        }
      }
    }

    // Salvando dados cabecalho
    this->dimensao = std::stof(conteudos_cabecalhos[0]);
    this->numero_itens = std::stof(conteudos_cabecalhos[1]);
    this->capacidade_mochila = std::stof(conteudos_cabecalhos[2]);
    this->v_min = std::stof(conteudos_cabecalhos[3]);
    this->v_max = std::stof(conteudos_cabecalhos[4]);
    this->custo_aluguel = std::stof(conteudos_cabecalhos[5]);
    
    /*
    Testando pegar os conteúdos do cabecalho
    for(auto& elemento_vetor:conteudos_cabecalhos)
      std::cout<<elemento_vetor<<"\n";
    */

    std::cout<<"\n";

    // TESTES
    /*
      // Printando hotel
      for(int i=0; i<this->nos.size(); i++){

        std::cout << "\nNo: "<<this->nos[i].id<< " Custo para o hotel mais proximo: "<<this->nos[i].cost_nearest_hotel;
        // std::cout<<"\nCaminho para o hotel mais proximo:\n";

        //for(auto& elemento_caminho : elemento.second.path_nearest_hotel)
          //std::cout<<elemento_caminho << "->";

      }
      
      for(auto& elemento : this->ids_hoteis)
        std::cout<<"\nId hotel: "<<elemento;

      //std::cout<<"\nNumero de nos: "<< this->ordem;
      ids_hoteis
      //this->printa_arestas();
    */

   return;

}

void Grafo::adicionarNo(int id, Vertice vertice)
{
  nos.emplace(id, vertice);
}

void Grafo::printa_arestas() {
    for (const auto& pair : nos) {
        const Vertice& vertice = pair.second;
        std::cout << "\nArestas do Vértice " << vertice.id << ":\n";
        
        for (const Aresta& aresta : vertice.arestas) {
            std::cout << "  Destino: " << aresta.id << ", Peso: " << aresta.peso << "\n";
        }
    }
}


void Grafo::adicionarAresta(int origem, int destino, float peso)
{
  auto noOrigem = nos.find(origem);
  auto noDestino = nos.find(destino);
  if (noOrigem == nos.end() || noDestino == nos.end()) {
    return;
  }
  Aresta aresta{ destino, peso};
  noOrigem->second.arestas.push_front(aresta);
  
}

bool Grafo::removerNo(int id) {

      // Crie uma função lambda que verifica se a aresta deve ser removida
      auto shouldRemoveAresta = [id](const Aresta& aresta) { return aresta.id == id; };

      // Itera sobre todos os nós do grafo
      for (auto& [_, no] : nos) {
          // Use a função std::remove_if seguida de no.arestas.erase para remover as arestas que atendem à condição
          no.arestas.remove_if(shouldRemoveAresta);
      }
  

    nos.erase(id);

    this->ordem = this->ordem - 1;

    return true;
}

void Grafo::removerAresta(int origem, int destino){
  auto noOrigem = nos.find(origem);
  auto noDestino = nos.find(destino);
  if (noOrigem == nos.end() || noDestino == nos.end()) {
    return;
  }

  auto& arestas = noOrigem->second.arestas;
  auto numRemovidos = std::count_if(arestas.begin(), arestas.end(), [destino](const Aresta& aresta) { return aresta.id == destino; });

  if (numRemovidos == 0)
    return;
  
  noDestino->second.arestas.remove_if([origem](const Aresta& aresta) { return aresta.id == origem; });
  
}

  Vertice& Grafo::no(int id){
  return nos.at(id);
}

std::vector<int> Grafo::geraSolucao(float alpha, int instancia){
    
    // Inicializações
    std::vector<int> solucao;

    return solucao;

}

bool Grafo::verificarNoRemovidoOuArestaApontaPara(int id) {
    // Verifica se o nó com o ID fornecido ainda existe no grafo

    // Verifica se alguma aresta aponta para o nó com o ID fornecido
    for (auto& par : nos) {
        Vertice& vertice = par.second;
        for (const Aresta& aresta : vertice.arestas) {
            if (aresta.id == id) {
                return true; // Existe uma aresta que aponta para o nó
            }
        }
    }

    // Se o nó não foi encontrado e nenhuma aresta aponta para ele, ele não está mais no grafo
    return false;
}

bool Grafo::validarSolucao(std::vector<int> solucao){
  return true;
}

int Grafo::calculaCusto(std::vector<int> solucao){
  return 0;
}