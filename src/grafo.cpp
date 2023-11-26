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
#include <unordered_map>

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
          double pesoAresta = std::sqrt( std::pow((noExterno.second.coord.first - noInterno.second.coord.first), 2) + std::pow((noExterno.second.coord.second - noInterno.second.coord.second), 2) ); 
          this->matrix_distancias[noExterno.second.id][noInterno.second.id] = pesoAresta;
        }   
    }
    
    // Salvando a ordem do grafo
    this->ordem = this->nos.size();

    std::cout<<"Numero de nos do grafo: "<<this->ordem<<"\n";
    std::cout<<"Ordem da matrix de distancias: "<<this->matrix_distancias.size()<<"x"<<this->matrix_distancias[1].size()<<"\n";

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

void Grafo::printa_itens(){
  for(auto& [id, no] : this->nos){
    std::cout<<"Cidade: "<<id<<" apresenta os itens -> { ";
      for (auto& elemento : no.itens_to_roubar)
        std::cout<<elemento.id<<" ";
    std::cout<<"}\n";      
  }

}

double Grafo::calcDistancia_Total(std::vector<int> caminho){

  double custo = 0;
    for(auto i = 0; i < caminho.size()-1; ++i)
      custo += this->matrix_distancias[i][i+1];
  
  custo += this->matrix_distancias[caminho[caminho.size()-1]][caminho[0]];

  return custo;

}

std::vector<int> Grafo::ACO(int numIteracoes, int numFormigas, float taxaEvaporacao, float alpha, float beta){
    
    const int numVertices = this->ordem;
    int id_formiga = 0;
    std::unordered_map<int, std::vector<int>> registro_geral_formigas;
    double custo_primeiro_caminho, custo_caminho_final;
    // Matriz de feromônios entre os vértices
    std::vector<std::vector<float>> feromonios(numVertices, std::vector<float>(numVertices, 1.0));

    std::vector<int> melhorCaminho;
    float melhorDistancia = std::numeric_limits<float>::max();

    // Loop principal do ACO
    for (int iteracao = 0; iteracao < numIteracoes; ++iteracao){

        for (int k = 0; k < numFormigas; ++k) {
            // Inicialização de uma formiga em um vértice aleatório
            int posicaoAtual = std::rand() % numVertices;
            std::vector<int> caminho;
            caminho.push_back(posicaoAtual);

            // Construção do caminho da formiga
            for (int i = 0; i < numVertices - 1; ++i) {
                std::vector<float> probabilidades;
                float somatorio = 0.0f;

                // Cálculo das probabilidades para os vértices vizinhos não visitados
                for (int j = 0; j < numVertices; ++j) {
                    if (j != posicaoAtual && !this->nos[j].visitado) {
                        float probabilidade = std::pow(feromonios[posicaoAtual][j], alpha) * std::pow(1.0 / this->matrix_distancias[posicaoAtual][j], beta);
                        probabilidades.push_back(probabilidade);
                        somatorio += probabilidade;
                    } else {
                        probabilidades.push_back(0.0f);
                    }
                }

                // Escolha do próximo vértice baseado nas probabilidades
                float probabilidadeTotal = 0.0f;
                float escolhaAleatoria = static_cast<float>(std::rand()) / RAND_MAX;
                for (size_t j = 0; j < probabilidades.size(); ++j) {
                    probabilidades[j] /= somatorio;
                    probabilidadeTotal += probabilidades[j];
                    if (escolhaAleatoria <= probabilidadeTotal) {
                        posicaoAtual = j;
                        break;
                    }
                }

                caminho.push_back(posicaoAtual);
                this->nos[posicaoAtual].visitado = true;
            }

            // Verificação se o caminho atual é o melhor encontrado
            float distanciaTotal = 0.0f;

            // Salvo o custo do primeiro caminho
            if(iteracao==0 && k==0)
              custo_primeiro_caminho = this->calcDistancia_Total(caminho);

            for (size_t i = 0; i < caminho.size() - 1; ++i) 
                distanciaTotal += this->matrix_distancias[caminho[i]][caminho[i+1]];

            if (distanciaTotal < melhorDistancia) {
                melhorDistancia = distanciaTotal;
                melhorCaminho = caminho;
            }

            // Resetar os vértices visitados para a próxima iteração
            for (int i = 0; i < numVertices; ++i) 
                this->nos[i].visitado = false;

            // Salvo o caminho feito pela formiga
            registro_geral_formigas[id_formiga] = caminho;
            ++id_formiga;
        }

        // Evaporação de feromônios
        for (int i = 0; i < numVertices; ++i)
          for (int j = 0; j < numVertices; ++j)
            feromonios[i][j] *= (1.0 - taxaEvaporacao);

        // Atualização dos feromônios no caminho percorrido pela formiga
        for(auto g=iteracao*numFormigas; g < registro_geral_formigas.size(); ++g){
          float feromonioDepositado = 1.0 / this->matrix_distancias[numVertices - 1][registro_geral_formigas[g][0]];
          for (size_t i = 0; i < registro_geral_formigas[g].size() - 1; ++i){
            feromonios[registro_geral_formigas[g][i]][registro_geral_formigas[g][i + 1]] += feromonioDepositado;
            feromonios[registro_geral_formigas[g][i + 1]][registro_geral_formigas[g][i]] += feromonioDepositado;
          }
        }
    }
    
    double custo_melhor_caminho = this->calcDistancia_Total(melhorCaminho);
    std::cout<<"Distancia primeiro caminho: "<<custo_primeiro_caminho<<"\n";
    std::cout<<"Distancia melhor caminho: "<<custo_melhor_caminho<<"\n";

    return melhorCaminho;

}

bool Grafo::validarSolucao(std::vector<int> solucao){
  return true;
}

int Grafo::calculaCusto(std::vector<int> solucao){
  return 0;
}