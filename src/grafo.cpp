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
      
      if(linha == "ITEMS SECTION	(INDEX, PROFIT, WEIGHT, ASSIGNED NODE NUMBER): "){
        parteDosItens = true;
        continue;
      }
        

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
        else{

          int id_item;
          int lucro;
          int peso;
          int cidade_onde_estou;

          std::istringstream linha_manipulavel(linha);
          linha_manipulavel >> id_item >> lucro >> peso >> cidade_onde_estou;
          
          Item item;
          item.id = id_item;
          item.lucro = lucro;
          item.peso = peso;
          item.cidade_onde_estou = cidade_onde_estou;
          this->adicionaItem(cidade_onde_estou, item);

        }
      }
      
    }
    // Salvando as arestas do grafo
    for(auto noExterno : this->nos){
        for(auto noInterno : this->nos){
          float pesoAresta = std::sqrt( std::pow((noExterno.second.coord.first - noInterno.second.coord.first), 2) + std::pow((noExterno.second.coord.second - noInterno.second.coord.second), 2) ); 
          this->adicionarAresta(noExterno.first, noInterno.first, pesoAresta);
        }   
    }
    
    // Salvando a ordem do grafo
    this->ordem = this->nos.size();

    // Salvando dados cabecalho
    this->dimensao = std::stof(conteudos_cabecalhos[0]);
    this->numero_itens = std::stof(conteudos_cabecalhos[1]);
    this->capacidade_mochila = std::stof(conteudos_cabecalhos[2]);
    this->v_min = std::stof(conteudos_cabecalhos[3]);
    this->v_max = std::stof(conteudos_cabecalhos[4]);
    this->custo_aluguel = std::stof(conteudos_cabecalhos[5]);

    //this->printa_nos();
    this->printa_itens();

    /*
    Testando pegar os conteúdos do cabecalho
    for(auto& elemento_vetor:conteudos_cabecalhos)
      std::cout<<elemento_vetor<<"\n";
    std::cout<<"\n";
    */

   return;

}

void Grafo::printa_arestas() {

    for (const auto& pair : nos) {
        const Vertice& vertice = pair.second;
        std::cout << "\nArestas do Vértice " << vertice.id << ":\n";
        
        for (const Aresta& aresta : vertice.arestas) 
            std::cout << "  Destino: " << aresta.id << ", Peso: " << aresta.peso << "\n";
        
    }
}
void Grafo::adicionarAresta(int origem, int destino, float peso){

  auto noOrigem = nos.find(origem);
  auto noDestino = nos.find(destino);
  if (noOrigem == nos.end() || noDestino == nos.end())
    return;
  Aresta aresta{destino, peso};
  noOrigem->second.arestas.push_front(aresta);
  
}

void Grafo::printa_itens(){
  for(auto& [id, no] : this->nos){
    std::cout<<"Cidade: "<<id<<" apresenta os itens -> { ";
      for (auto& elemento : no.itens_to_roubar)
        std::cout<<elemento.id<<" ";
    std::cout<<"}\n";      
  }

}

std::pair<std::vector<int>, std::vector<int>> Grafo::ACO(int n_formigas, int n_geracoes, float taxa_evaporacao){
    
    // Inicializações
    std::pair<std::vector<int>, std::vector<int>> solucao;

    return solucao;

}

bool Grafo::validarSolucao(std::vector<int> solucao){
  return true;
}

int Grafo::calculaCusto(std::vector<int> solucao){
  return 0;
}