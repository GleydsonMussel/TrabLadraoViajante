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
    
    // Salvando a ordem do grafo
    this->ordem = this->nos.size();
    std::vector<double> vetor;

    // Salvando as arestas do grafo
    for(auto i = 0; i < this->ordem; ++i){
        for(auto j = 0; j < this->ordem; ++j){
          if(i==j){
            vetor.push_back(0.0);
            continue;
          }
          else{
            double pesoAresta = std::sqrt( std::pow((this->nos[i].coord.first - this->nos[j].coord.first), 2) + std::pow((this->nos[i].coord.second - this->nos[j].coord.second), 2)); 
            vetor.push_back(pesoAresta);
          }
          
        }   
        this->matrix_distancias.push_back(vetor);
        vetor.clear();
    }

    std::cout<<"Numero de nos do grafo: "<<this->ordem<<"\n";
    std::cout<<"Ordem da matrix de distancias: "<<this->matrix_distancias.size()<<"x"<<this->matrix_distancias[1].size()<<"\n";

    // Salvando dados cabecalho
    this->dimensao = std::stof(conteudos_cabecalhos[0]);
    this->numero_itens = std::stof(conteudos_cabecalhos[1]);
    this->capacidade_mochila = std::stof(conteudos_cabecalhos[2]);
    this->v_min = std::stof(conteudos_cabecalhos[3]);
    this->v_max = std::stof(conteudos_cabecalhos[4]);
    this->v_atual = this->v_max;
    this->carga_atual = 0.0;
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
  for(auto& no : this->nos){
    std::cout<<"Cidade: "<<no.id<<" apresenta os itens -> { ";
      for (auto& elemento : no.itens_to_roubar)
        std::cout<<elemento.id<<" ";
    std::cout<<"}\n";      
  }

}

double Grafo::calcDistancia_Total(std::vector<int> caminho){

  double custo = 0;
    for(auto i = 0; i < caminho.size()-1; ++i)
      custo += this->matrix_distancias[caminho[i]][caminho[i+1]];
  
  custo += this->matrix_distancias[caminho[caminho.size()-1]][caminho[0]];

  return custo;

}

std::vector<int> Grafo::ACO(int numIteracoes, int numFormigas, float taxaEvaporacao, float alpha, float beta) {
    const int numVertices = this->ordem;
    int id_formiga = 0;
    std::unordered_map<int, std::vector<int>> registro_geral_formigas;
    double custo_primeiro_caminho, custo_caminho_final;

    // Matriz de feromônios entre os vértices
    std::vector<std::vector<double>> feromonios(numVertices, std::vector<double>(numVertices, 1.0));

    std::vector<int> melhorCaminho;
    float melhorDistancia = std::numeric_limits<float>::max();

    for (int iteracao = 0; iteracao < numIteracoes; ++iteracao) {

        for (int k = 0; k < numFormigas; ++k) {

            int posicaoAtual = Random::get(0, numVertices - 1);
            std::vector<int> caminho;
            this->nos[posicaoAtual].visitado = true;
            caminho.push_back(posicaoAtual);

            for (int i = 0; i < numVertices - 1; ++i) {
                std::vector<double> probabilidades;
                double somatorio = 0.0;

                for (int j = 0; j < numVertices; ++j) {
                    if (j != posicaoAtual && !this->nos[j].visitado) {
                        // Cálculo das probabilidades para os vértices vizinhos não visitados
                        double probabilidade = std::pow(feromonios[posicaoAtual][j], alpha) * std::pow(1.0 / this->matrix_distancias[posicaoAtual][j], beta);
                        probabilidades.push_back(probabilidade);
                        somatorio += probabilidade;
                    } 
                    else {
                        probabilidades.push_back(0.0);
                    }
                }

                double probabilidadeTotal = 0.0;
                double escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
                int posicaoProvisoria = 0;
                bool achou_candidato = false;
                int j = 0;

                while (j < probabilidades.size() && !achou_candidato) {
                    
                    // Nomraliza cada valor presente no vetor de probabilidades com base no somatório, assim, só serão obtidos valores entre 0 e 1, além da soma de todos eles resultar em 1
                    probabilidades[j] = probabilidades[j]/somatorio;
                    probabilidadeTotal = probabilidadeTotal + probabilidades[j];
                    
                    // Escolhe com base na lógica da roleta
                    if (escolhaAleatoria <= probabilidadeTotal) {
                        posicaoProvisoria = j;
                        // Verifica se alguém válido
                        if (!this->nos[posicaoProvisoria].visitado) {
                            posicaoAtual = posicaoProvisoria;
                            this->nos[posicaoAtual].visitado = true;
                            achou_candidato = true;
                            break;
                        } else {
                            j = -1;
                            escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
                            probabilidadeTotal = 0;
                        }
                    }
                    ++j;
                }

                if (achou_candidato)
                    caminho.push_back(posicaoAtual);

                if (caminho.size() == numVertices) {
                    // Adicionando o primeiro vértice ao final para completar o ciclo
                    caminho.push_back(caminho[0]);
                    break;
                }
            }

            float distanciaTotal = this->calcDistancia_Total(caminho);

            if (iteracao == 0 && k == 0)
                custo_primeiro_caminho = distanciaTotal;

            if (distanciaTotal < melhorDistancia) {
                melhorDistancia = distanciaTotal;
                melhorCaminho = caminho;
            }

            for (int i = 0; i < numVertices; ++i)
                this->nos[i].visitado = false;

            registro_geral_formigas[id_formiga] = caminho;
            ++id_formiga;
        }

        for (int i = 0; i < numVertices; ++i)
            for (int j = 0; j < numVertices; ++j)
                feromonios[i][j] = feromonios[i][j]*(1.0 - taxaEvaporacao);
        /*
        std::cout<<"Matriz Feromonios Antes:\n";
        for (auto g = iteracao * numFormigas; g < registro_geral_formigas.size(); ++g) {
            for (size_t i = 0; i < registro_geral_formigas[g].size() - 1; ++i) 
                std::cout << feromonios[registro_geral_formigas[g][i]][registro_geral_formigas[g][i + 1]]<<" ";
            std::cout<<"\n";
        }
        */

        for (auto g = iteracao * numFormigas; g < registro_geral_formigas.size(); ++g){

            double feromonioDepositado;

            if(this->matrix_distancias[numVertices - 1][registro_geral_formigas[g][0]] == 0){
                feromonioDepositado = 0;
            }
            else{
                feromonioDepositado= 1.0 / this->matrix_distancias[numVertices - 1][registro_geral_formigas[g][0]];
            }
              
            for (size_t i = 0; i < registro_geral_formigas[g].size() - 1; ++i) {
                  feromonios[registro_geral_formigas[g][i]][registro_geral_formigas[g][i + 1]] += feromonioDepositado;
                  feromonios[registro_geral_formigas[g][i + 1]][registro_geral_formigas[g][i]] += feromonioDepositado;
            }
        }
        /*
        std::cout<<"\n";
        std::cout<<"Matriz Feromonios Depois:\n";
        for (auto g = iteracao* numFormigas; g < registro_geral_formigas.size(); ++g) {
            for (size_t i = 0; i < registro_geral_formigas[g].size() - 1; ++i) 
                std::cout << feromonios[registro_geral_formigas[g][i]][registro_geral_formigas[g][i + 1]]<<" ";
            std::cout<<"\n";
        }
        */
    }

    double custo_melhor_caminho = this->calcDistancia_Total(melhorCaminho);
    std::cout << "Distancia primeiro caminho: " << custo_primeiro_caminho << "\n";
    std::cout << "Distancia melhor caminho: " << custo_melhor_caminho << "\n";
    std::vector<int> melhorCaminho_Convertido_para_exibir;

    std::vector<Item> mochila;
    this->gera_mochila_light(melhorCaminho, mochila);
    std::cout<<"Mochila do Melhor caminho: ";
    for(auto& item_mochila : mochila)
      std::cout << item_mochila.id << " ";
    std::cout<<"\n";

    auto peso = 0;

    for(auto& item_mochila : mochila)
      peso+=item_mochila.peso;
    std::cout<<"Peso Mochila: "<<peso<<"\n";
    std::cout<<"Capacidade Maxima:: "<<this->capacidade_mochila;

    // Traduz a impressão do caminho
    this->traduz_caminho_interno_to_externo(melhorCaminho, melhorCaminho_Convertido_para_exibir);

    return melhorCaminho_Convertido_para_exibir;
}

void Grafo::gera_mochila_light(std::vector<int> caminho, std::vector<Item>&mochila){
  
  int capacidade_atual = 0;

  for(int k=0; k<caminho.size()-1;++k){

      auto cidade = caminho[k];
      std::vector<double> probabilidades;
      double somaP = 0;
      bool ha_candidatos = false;
      // Calcula probabilidade e checa se há algum item possível de pegar
      for(auto item: this->nos[cidade].itens_to_roubar){
        auto prob = (double)item.lucro/item.peso;
        probabilidades.push_back(prob);
        somaP+=prob;
        if(item.peso + capacidade_atual <= this->capacidade_mochila)
          ha_candidatos = true;
      }
      // Nào é possível pegar ninguém, vai para a outra cidade
      if(!ha_candidatos)
        continue;

      // Normalizando probabilidades
      for(auto& probNaoNormalizada : probabilidades)
        probNaoNormalizada/=somaP;

      double escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
      double roleta = 0.0;

      // Roletando
      int i = 0;
      while(i<probabilidades.size()){

        roleta = roleta + probabilidades[i];
        // Escolhe com base na lógica da roleta
        
        if (escolhaAleatoria <= roleta){
          auto item = this->nos[cidade].itens_to_roubar[i];
          if(item.peso + capacidade_atual <= this->capacidade_mochila){
            mochila.push_back(item);
            capacidade_atual += item.peso;
            break;
          }
          else{
            escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
            roleta = 0;
            i = -1;
          }
        } 
        ++i;
    }
  }
}

std::vector<int> Grafo::gera_mochila(std::vector<int> rota, std::vector<int>& mochila_simples){
  std::vector<int> retorno;
  return retorno;
}

void Grafo::atualiza_velocidade(Item& item){
  this->v_atual = this->v_max - item.peso*(this->v_max-this->v_min)/this->capacidade_mochila;
}

void Grafo::traduz_caminho_interno_to_externo(std::vector<int> caminho_interno, std::vector<int>& caminho_traduzido){
  for(auto elemento : caminho_interno)
    caminho_traduzido.push_back(elemento+1);
}

/*void Grafo::traduz_caminho_interno_to_externo(std::vector<int> caminho_externo, std::vector<int>& caminho_traduzido){
  for(auto elemento : caminho_externo)
    caminho_traduzido.push_back(elemento-1);
}*/

bool Grafo::validarSolucao(std::vector<int> solucao){
  return true;
}

int Grafo::calculaCusto(std::vector<int> solucao){
  return 0;
}