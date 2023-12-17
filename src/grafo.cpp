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

Grafo::Grafo(std::string filename)
{

  std::ifstream arquivo(filename);
  std::string linha;
  std::vector<std::string> conteudos_cabecalhos;

  int dimensao, n_itens, capacidade_mochila;
  std::vector<std::pair<double, double>> coordenadas_nos;
  std::vector<int> pesos;

  int contLinha = 0;
  bool parteDosItens = false;

  while (std::getline(arquivo, linha))
  {

    if (linha == "ITEMS SECTION	(INDEX, PROFIT, WEIGHT, ASSIGNED NODE NUMBER): ")
    {
      parteDosItens = true;
      continue;
    }

    // Somente pegando dados do cabeçalho
    if (contLinha < 10)
    {

      std::istringstream linha_manipulavel(linha);
      std::string elemento;
      int cont_colunas = 0, colunaAlvo;
      switch (contLinha)
      {

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
      while (linha_manipulavel >> elemento)
      {
        if (cont_colunas == colunaAlvo)
          conteudos_cabecalhos.push_back(elemento);
        cont_colunas++;
      }

      contLinha++;
    }
    else
    {

      if (!parteDosItens)
      {

        std::istringstream linha_manipulavel(linha);

        int contCol = 0;

        int id;
        double coord_x;
        double coord_y;

        linha_manipulavel >> id >> coord_x >> coord_y;

        Vertice novoNo;
        novoNo.id = id;
        novoNo.coord = {coord_x, coord_y};
        this->adicionarNo(id, novoNo);
      }
      else
      {

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
  for (auto i = 0; i < this->ordem; ++i)
  {
    for (auto j = 0; j < this->ordem; ++j)
    {
      if (i == j)
      {
        vetor.push_back(0.0);
        continue;
      }
      else
      {
        double pesoAresta = std::sqrt(std::pow((this->nos[i].coord.first - this->nos[j].coord.first), 2) + std::pow((this->nos[i].coord.second - this->nos[j].coord.second), 2));
        vetor.push_back(pesoAresta);
      }
    }
    this->matrix_distancias.push_back(vetor);
    vetor.clear();
  }

  // std::cout << "Numero de nos do grafo: " << this->ordem << "\n";
  // std::cout << "Ordem da matrix de distancias: " << this->matrix_distancias.size() << "x" << this->matrix_distancias[1].size() << "\n";

  // Salvando dados cabecalho
  this->dimensao = std::stof(conteudos_cabecalhos[0]);
  this->numero_itens = std::stof(conteudos_cabecalhos[1]);
  this->capacidade_mochila = std::stof(conteudos_cabecalhos[2]);
  this->v_min = std::stof(conteudos_cabecalhos[3]);
  this->v_max = std::stof(conteudos_cabecalhos[4]);
  this->v_atual = this->v_max;
  this->carga_atual = 0.0;
  this->custo_aluguel = std::stof(conteudos_cabecalhos[5]);

  // this->printa_nos();
  this->printa_itens();

  /*
  Testando pegar os conteúdos do cabecalho
  for(auto& elemento_vetor:conteudos_cabecalhos)
    std::cout<<elemento_vetor<<"\n";
  std::cout<<"\n";
  */

  return;
}

void Grafo::printa_itens()
{
  // for(auto& no : this->nos){
  //   std::cout<<"Cidade: "<<no.id<<" apresenta os itens -> { ";
  //     for (auto& elemento : no.itens_to_roubar)
  //       std::cout<<elemento.id<<" ";
  //   std::cout<<"}\n";
  // }
}

double Grafo::calcDistancia_Total(std::vector<int> caminho){

  double custo = 0;
  for (auto i = 0; i < caminho.size() - 1; ++i)
    custo += this->matrix_distancias[caminho[i]][caminho[i + 1]];

  custo += this->matrix_distancias[caminho[caminho.size() - 1]][caminho[0]];

  return custo;
}

std::vector<int> Grafo::ACO(int numIteracoes, int numFormigas, double taxaEvaporacao, double alpha, double beta){

  const int numVertices = this->ordem;
  int id_formiga = 0, id_melhor_formiga;
  double custo_primeiro_caminho, custo_caminho_final, lucro_primeiro_caminho, lucro_melhor_caminho;

  // Matriz de feromônios entre os vértices
  std::vector<std::vector<double>> feromonios(numVertices, std::vector<double>(numVertices, 1.0));

  std::vector<int> melhorCaminho;
  double melhorDistancia = std::numeric_limits<double>::max();
  double melhor_lucro_formiga = std::numeric_limits<double>::max();

  for (int iteracao = 0; iteracao < numIteracoes; ++iteracao){

    for (int k = 0; k < numFormigas; ++k){

      int posicaoAtual = Random::get(0, numVertices - 1);
      std::vector<int> caminho;
      std::vector<saque_cidade> mochila;
      std::vector<double> velocidades;
      std::vector<double> tempos;

      this->nos[posicaoAtual].visitado = true;
      caminho.push_back(posicaoAtual);

      for (int i = 0; i < numVertices - 1; ++i){
        std::vector<double> probabilidades;
        double somatorio = 0.0;

        for (int j = 0; j < numVertices; ++j){
          if (j != posicaoAtual && !this->nos[j].visitado){
            // Cálculo das probabilidades para os vértices vizinhos não visitados
            double probabilidade = std::pow(feromonios[posicaoAtual][j], alpha) * std::pow(1.0 / this->matrix_distancias[posicaoAtual][j], beta);
            probabilidades.push_back(probabilidade);
            somatorio += probabilidade;
          }
          else
            probabilidades.push_back(0.0);
          
        }

        double probabilidadeTotal = 0.0;
        double escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
        int posicaoProvisoria = 0;
        bool achou_candidato = false;
        int j = 0;

        while (j < probabilidades.size() && !achou_candidato){

          // Calcula a probabilidade normalizada
          probabilidadeTotal = probabilidadeTotal + probabilidades[j] / somatorio;

          // Escolhe com base na lógica da roleta
          if (escolhaAleatoria <= probabilidadeTotal){
            posicaoProvisoria = j;
            // Verifica se alguém válido
            if (!this->nos[posicaoProvisoria].visitado){
              posicaoAtual = posicaoProvisoria;
              this->nos[posicaoAtual].visitado = true;
              achou_candidato = true;
              break;
            }
            else{
              j = -1;
              escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
              probabilidadeTotal = 0;
            }
          }
          ++j;
        }

        if (achou_candidato)
          caminho.push_back(posicaoAtual);

        if (caminho.size() == numVertices){
          // Adicionando o primeiro vértice ao final para completar o ciclo
          caminho.push_back(caminho[0]);
          break;
        }
      }

      // Reseta o estado de todos os vértices para não visitado
      for (int i = 0; i < numVertices; ++i)
        this->nos[i].visitado = false;

      // Contabiliza pontos relevantes sobre cada formiga
      registro_geral_formigas_caminho[id_formiga] = caminho;
      this->gera_mochila_light(caminho, mochila);
      registro_geral_formigas_mochila[id_formiga] = mochila;
      this->gera_vetor_velocidades(mochila, velocidades);
      registro_geral_formigas_velocidades[id_formiga] = velocidades;
      this->gera_vetor_tempos(caminho, velocidades, tempos);

      double distanciaTotal = this->calcDistancia_Total(caminho);
      auto lucro_formiga = this->calcula_lucro(tempos, velocidades, mochila, caminho);

      if (iteracao == 0 && k == 0){
        custo_primeiro_caminho = distanciaTotal;
        lucro_primeiro_caminho = lucro_formiga;
        lucro_melhor_caminho = lucro_formiga;
      }
      if (lucro_formiga > lucro_melhor_caminho){
        // std::cout << "lucro da formiga " << lucro_formiga << std::endl;
        melhorDistancia = distanciaTotal;
        melhorCaminho = caminho;
        lucro_melhor_caminho = lucro_formiga;
        id_melhor_formiga = id_formiga;
      }
      registro_geral_formigas_lucros[id_formiga] = lucro_formiga;
      ++id_formiga;
    }

    for (int i = 0; i < numVertices; ++i)
      for (int j = 0; j < numVertices; ++j)
        feromonios[i][j] = feromonios[i][j] * (1.0 - taxaEvaporacao);

    // Pega o índice do menor e do maior lucro
    int indice_menor_lucro = iteracao * numFormigas;
    int indice_maior_lucro = iteracao * numFormigas;
    double menor_lucro = registro_geral_formigas_lucros[iteracao * numFormigas];
    double maior_lucro = registro_geral_formigas_lucros[iteracao * numFormigas];
    for (auto g = (iteracao * numFormigas) + 1; g < registro_geral_formigas_lucros.size(); ++g){
      if (registro_geral_formigas_lucros[g] < menor_lucro){
        menor_lucro = registro_geral_formigas_lucros[g];
        indice_menor_lucro = g;
      }
      if (registro_geral_formigas_lucros[g] > maior_lucro){
        maior_lucro = registro_geral_formigas_lucros[g];
        indice_maior_lucro = g;
      }
    }

    for (auto g = iteracao * numFormigas; g < registro_geral_formigas_caminho.size(); ++g){

      double feromonioDepositado;
    
      // Normaliza o lucro obtido pela solução com base no maior e menor lucro, também vai influenciar a deposição de feromônio
      auto influencia_mochila = (registro_geral_formigas_lucros[g] + std::abs(menor_lucro)) / (maior_lucro + std::abs(menor_lucro));
      feromonioDepositado = (1.0 / this->calcDistancia_Total(registro_geral_formigas_caminho[g])) + influencia_mochila;
      
      for (int i = 0; i < registro_geral_formigas_caminho[g].size() - 1; ++i){
        feromonios[registro_geral_formigas_caminho[g][i]][registro_geral_formigas_caminho[g][i + 1]] += feromonioDepositado;
        feromonios[registro_geral_formigas_caminho[g][i + 1]][registro_geral_formigas_caminho[g][i]] += feromonioDepositado;
      }
    }
  }

  double custo_melhor_caminho = this->calcDistancia_Total(melhorCaminho);

  std::vector<saque_cidade> mochila = registro_geral_formigas_mochila[id_melhor_formiga];

  auto peso = 0;

  for (auto &[itens_mochila, indice_cidade] : mochila)
    for (auto &item_roubado : itens_mochila)
      peso += item_roubado.peso;

  // Vetores de velocidade e tempos
  std::vector<double> velocidades;
  std::vector<double> tempos;
  this->gera_vetor_velocidades(mochila, velocidades);
  this->gera_vetor_tempos(melhorCaminho, velocidades, tempos);
  // Printa vários dados relativos às soluções obtidas no ACO
  this->print_dados_ACO(custo_primeiro_caminho, custo_melhor_caminho, lucro_primeiro_caminho, lucro_melhor_caminho, velocidades, tempos, mochila, peso);
  this->best_lucro = custo_melhor_caminho;

  return melhorCaminho;
}

double Grafo::calculador_velocidade(double velocidade_atual, double peso_item)
{
  double velocidade = velocidade_atual - peso_item * ((this->v_max - this->v_min) / this->capacidade_mochila);
  return velocidade >= this->v_min ? velocidade : this->v_min;
}

void Grafo::gera_vetor_velocidades(std::vector<saque_cidade> &mochila, std::vector<double> &velocidades)
{

  for (int i = 0; i < mochila.size(); ++i)
  {
    double peso_acumulado_cidade = 0.0;
    // Contabilizo o peso dos itens roubados em uma cidade
    for (auto &item_roubado : mochila[i].itens_roubados)
      peso_acumulado_cidade += item_roubado.peso;
    if (i == 0)
      velocidades.push_back(this->calculador_velocidade(this->v_max, peso_acumulado_cidade));
    else
      velocidades.push_back(this->calculador_velocidade(velocidades[velocidades.size() - 1], peso_acumulado_cidade));
  }
}

void Grafo::gera_vetor_tempos(std::vector<int> &caminho, std::vector<double> &velocidades, std::vector<double> &tempos)
{
  for (int i = 0; i < caminho.size() - 1; ++i)
    tempos.push_back(this->matrix_distancias[caminho[i]][caminho[i + 1]] / velocidades[i]);
}

double Grafo::gera_valores(std::vector<saque_cidade> mochila, std::vector<double> velocidades, std::vector<int> &caminho)
{
  double valores;
  double veloOld = 0;
  ;
  double velocidade = 0;
  ;
  int j = 0;
  double peso_acumulado_cidade = 0.0;
  for (auto item : mochila)
  {

    for (auto it : item.itens_roubados)
    {
      peso_acumulado_cidade += it.peso;
      double camin = 0;

      for (int i = it.id; i < caminho.size() - 1; ++i)
      {
        camin += this->matrix_distancias[caminho[i]][caminho[i + 1]];
      }

      if (j == 0)
      {
        velocidade = this->calculador_velocidade(this->v_max, peso_acumulado_cidade);
      }
      else
      {
        veloOld = velocidade;
        velocidade = this->calculador_velocidade(veloOld, peso_acumulado_cidade);
      }
      // std::cout << "velocidades: " << velocidade[it.id] << std::endl;
      valores += (((camin * this->custo_aluguel) / (velocidade - (it.peso * (this->v_max - this->v_min) / this->capacidade_mochila))) - ((camin * this->custo_aluguel) / (velocidade)));
    }
    j++;
  }
  return valores;
}

void Grafo::gera_mochila_light(std::vector<int> &caminho, std::vector<saque_cidade> &mochila)
{

  int capacidade_atual = 0;

  for (int k = 0; k < caminho.size() - 1; ++k)
  {

    auto cidade = caminho[k];
    std::vector<double> probabilidades;
    double somaP = 0;
    bool ha_candidatos = false;
    saque_cidade saque;

    // Calcula probabilidade e checa se há algum item possível de pegar
    for (auto item : this->nos[cidade].itens_to_roubar)
    {
      auto prob = (double)item.lucro / item.peso;
      probabilidades.push_back(prob);
      somaP += prob;
      if (item.peso + capacidade_atual <= this->capacidade_mochila)
        ha_candidatos = true;
    }
    // Nào é possível pegar ninguém, vai para a outra cidade, o push back é para só contabilizar na mochila que foi na cidade, mas não pegou ninguém
    if (!ha_candidatos)
    {
      mochila.push_back(saque);
      continue;
    }

    // Normalizando probabilidades
    for (auto &probNaoNormalizada : probabilidades)
      probNaoNormalizada /= somaP;

    double escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
    double roleta = 0.0;

    // Roletando
    int i = 0;
    while (i < probabilidades.size())
    {

      roleta = roleta + probabilidades[i];
      // Escolhe com base na lógica da roleta

      if (escolhaAleatoria <= roleta)
      {
        auto item = this->nos[cidade].itens_to_roubar[i];
        if (item.peso + capacidade_atual <= this->capacidade_mochila)
        {
          saque.itens_roubados.push_back(item);
          saque.indice_cidade = i;
          mochila.push_back(saque);
          capacidade_atual += item.peso;
          break;
        }
        else
        {
          escolhaAleatoria = static_cast<double>(std::rand()) / RAND_MAX;
          roleta = 0;
          i = -1;
        }
      }
      ++i;
    }
  }
}

void Grafo::traduz_caminho_interno_to_externo(std::vector<int> caminho_interno, std::vector<int> &caminho_traduzido)
{
  for (auto elemento : caminho_interno)
    caminho_traduzido.push_back(elemento + 1);
}

double Grafo::calcula_tempo_total(std::vector<double> &tempos)
{
  double tempoTotal = 0;
  for (auto &tempo : tempos)
    tempoTotal += tempo;
  return tempoTotal;
}
double Grafo::calcula_montante_saque(std::vector<saque_cidade> &mochila)
{
  double monstante_total = 0.0;
  for (auto &[itens_roubados, _] : mochila)
    for (auto &item : itens_roubados)
      monstante_total += item.lucro;
  return monstante_total;
}

double Grafo::calcula_lucro(std::vector<double> &tempos, std::vector<double> velocidade, std::vector<saque_cidade> &mochila, std::vector<int> caminho)
{
  double valor = this->gera_valores(mochila, velocidade, caminho);
  // std::cout << "valor do saque:" << this->calcula_montante_saque(mochila) << std::endl;
  // std::cout << "perda: " <<  valor << std::endl;
  return this->calcula_montante_saque(mochila) - valor;
}


void Grafo::busca_local(std::vector<Item>& itens, double& valor, int& peso, std::vector<std::pair<Item, double>>& lucroItem, int capacidade_mochila)
{
    for (size_t i = 0; i < itens.size(); ++i)
    {
        for (size_t j = i + 1; j < itens.size(); ++j)
        {
            // Tenta trocar os itens i e j
            if (peso - itens[i].peso + itens[j].peso <= capacidade_mochila &&
                peso - itens[j].peso + itens[i].peso <= capacidade_mochila)
            {
                double novoValor = valor - lucroItem[i].second * itens[i].peso - lucroItem[j].second * itens[j].peso +
                                   lucroItem[i].second * itens[j].peso + lucroItem[j].second * itens[i].peso;

                // Se a troca melhora o valor, realiza a troca
                if (novoValor > valor)
                {
                    valor = novoValor;
                    peso = peso - itens[i].peso + itens[j].peso;
                    std::swap(itens[i], itens[j]);
                }
            }
        }
    }
}
// void trocar_itens(std::vector<Item> &itens, double &valor, int &peso, std::vector<std::pair<Item, double>> &lucroItem, int capacidade_mochila)
// {
//     for (size_t i = 0; i < itens.size(); ++i)
//     {
//         for (size_t j = i + 1; j < itens.size(); ++j)
//         {
//             // Tenta trocar os itens i e j
//             const int pesoOriginalI = itens[i].peso;
//             const int pesoOriginalJ = itens[j].peso;

//             if (peso - pesoOriginalI + pesoOriginalJ <= capacidade_mochila &&
//                 peso - pesoOriginalJ + pesoOriginalI <= capacidade_mochila)
//             {
//                 double novoValor = valor - lucroItem[i].second * pesoOriginalI - lucroItem[j].second * pesoOriginalJ;
//                 int novoPeso = peso - pesoOriginalI - pesoOriginalJ;

//                 // Calcula o novo valor após a troca
//                 for (const auto& lucro : lucroItem)
//                 {
//                     const int pesoTroca = (lucro.first.peso == pesoOriginalI) ? pesoOriginalJ : ((lucro.first.peso == pesoOriginalJ) ? pesoOriginalI : lucro.first.peso);

//                     if (novoPeso + pesoTroca <= capacidade_mochila)
//                     {
//                         novoValor += lucro.second * pesoTroca;
//                         novoPeso += pesoTroca;
//                     }
//                 }

//                 // Se a troca melhora o valor, realiza a troca
//                 if (novoValor > valor)
//                 {
//                     valor = novoValor;
//                     peso = novoPeso + pesoOriginalI + pesoOriginalJ;
//                     std::swap(itens[i], itens[j]);
//                 }
//             }
//         }
//     }
// }


void Grafo::remove_insert(std::vector<Item> &itens, double &valor, int &peso, std::vector<std::pair<Item, double>> &lucroItem, int capacidade_mochila)
{
    for (size_t i = 0; i < itens.size(); ++i)
    {
        for (size_t j = i + 1; j < itens.size(); ++j)
        {
            // Tenta trocar os itens i e j
            const int pesoOriginalI = itens[i].peso;
            const int pesoOriginalJ = itens[j].peso;

            if (peso - pesoOriginalI + pesoOriginalJ <= capacidade_mochila &&
                peso - pesoOriginalJ + pesoOriginalI <= capacidade_mochila)
            {
                double novoValor = valor - lucroItem[i].second * pesoOriginalI - lucroItem[j].second * pesoOriginalJ;
                int novoPeso = peso - pesoOriginalI - pesoOriginalJ;

                // Calcula o novo valor após a troca
                for (const auto& lucro : lucroItem)
                {
                    const int pesoTroca = (lucro.first.peso == pesoOriginalI) ? pesoOriginalJ : ((lucro.first.peso == pesoOriginalJ) ? pesoOriginalI : lucro.first.peso);

                    if (novoPeso + pesoTroca <= capacidade_mochila)
                    {
                        novoValor += lucro.second * pesoTroca;
                        novoPeso += pesoTroca;
                    }
                }

                // Se a troca melhora o valor, realiza a troca
                if (novoValor > valor)
                {
                    valor = novoValor;
                    peso = novoPeso + pesoOriginalI + pesoOriginalJ;
                    std::swap(itens[i], itens[j]);
                }
            }
        }
    }
}

void Grafo::problema_mochila(std::vector<int> caminho)
{
  std::vector<std::pair<Item, int>> itens;
  std::vector<std::pair<Item, double>> lucroItem;
  int peso = 0;
  std::vector<Item> itensFinais;
  double valorFinal = 0.0;

  for (int no : caminho)
  {
    for (auto item : nos[no].itens_to_roubar)
    {
      itens.push_back(std::make_pair(item, no));
    }
  }

  for (auto item : itens)
  {
    double camin = 0;
    for (int i = item.second; i < caminho.size() - 1; ++i)
    {
      camin += this->matrix_distancias[caminho[i]][caminho[i + 1]];
    }

    double velo = this->calculador_velocidade(this->v_max, item.first.peso);

    lucroItem.push_back(std::make_pair(item.first, (((camin * this->custo_aluguel) / (velo - (item.first.peso * (this->v_max - this->v_min) / this->capacidade_mochila))) - ((camin * this->custo_aluguel) / (velo))) / item.first.peso));
  }

  std::sort(lucroItem.begin(), lucroItem.end(), [](const std::pair<Item, double> &a, const std::pair<Item, double> &b)
            { return a.second > b.second; });

  for (auto lucro : lucroItem)
  {
    if (this->capacidade_mochila >= (peso + lucro.first.peso))
    {
      itensFinais.push_back(lucro.first);
      peso += lucro.first.peso;
      valorFinal += lucro.second * lucro.first.peso;
    }
  }
  //std::cout << "valor final: " << valorFinal << std::endl;
  //busca_local(itensFinais, valorFinal, peso, lucroItem, this->capacidade_mochila);
  //remove_insert(itensFinais, valorFinal, peso, lucroItem, this->capacidade_mochila);
  if(best_lucro < valorFinal){
    best_lucro = valorFinal;
  }
}

void Grafo::printa_matrix_feromonios(std::vector<std::vector<double>> &feromonios, int iteracao, int numFormigas)
{
  for (auto g = iteracao * numFormigas; g < registro_geral_formigas_caminho.size(); ++g)
  {
    //   for (size_t i = 0; i < registro_geral_formigas_caminho[g].size() - 1; ++i)
    // std::cout << feromonios[registro_geral_formigas_caminho[g][i]][registro_geral_formigas_caminho[g][i + 1]]<<" ";
    // std::cout<<"\n";
  }
}

void Grafo::print_dados_ACO(double custo_primeiro_caminho, double custo_melhor_caminho, double lucro_primeiro_caminho, double lucro_melhor_caminho, std::vector<double> &velocidades, std::vector<double> &tempos, std::vector<saque_cidade> &mochila, int peso)
{
//   //std::cout << "Distancia primeiro caminho: " << custo_primeiro_caminho << "\n";
//   //std::cout << "Distancia melhor caminho: " << custo_melhor_caminho << "\n";

//   //std::cout << "Mochila do Melhor caminho: ";
//   for (auto &[itens_mochila, indice_cidade] : mochila)
//     for (auto &item_roubado : itens_mochila)
//       //std::cout << item_roubado.id << " ";
//   //std::cout << "\n";

//   //std::cout << "Peso Mochila: " << peso << "\n";
//   //std::cout << "Capacidade Maxima:: " << this->capacidade_mochila << "\n";

//   //std::cout << "Vetor velocidade: [";
//   // for (auto &velocidade : velocidades)
//   //   //std::cout << velocidade << " ";
//   // //std::cout << "]\n";
//   // //std::cout << "Vetor tempos: [";
//   // for (auto &tempo : tempos)
//   //   std::cout << tempo << " ";
//   // std::cout << "]\n";
//   // std::cout << "Tempo Total: " << this->calcula_tempo_total(tempos) << "\n";
//   // std::cout << "Lucro Primeiro Caminho: " << lucro_primeiro_caminho << "\n";
//   // std::cout << "Lucro Ultimo Caminho: " << lucro_melhor_caminho << "\n";
// }
}
/*void Grafo::traduz_caminho_interno_to_externo(std::vector<int> caminho_externo, std::vector<int>& caminho_traduzido){
  for(auto elemento : caminho_externo)
    caminho_traduzido.push_back(elemento-1);
}*/
