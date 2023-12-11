import matplotlib.pyplot as plt

def plotar_pontos(labels, valores_x, valores_y, cores, nome_grafico, titulo, label_x, label_y):
    # Verifica se o número de pontos é consistente
    if len(labels) != len(valores_x) or len(labels) != len(valores_y) or len(labels) != len(cores):
        print("Erro: As listas de rótulos, valores x, valores y e cores devem ter o mesmo tamanho.")
        return
    
    # Cria um gráfico de dispersão para cada ponto
    for i in range(len(labels)):
        plt.scatter(valores_x[i], valores_y[i], label=labels[i], color=cores[i])
    
    # Configurações do gráfico
    plt.xlabel(label_x)
    plt.ylabel(label_y)
    plt.title(titulo)
    #plt.legend()
    plt.grid()
    plt.savefig("./Graficos/"+nome_grafico+".png")
    plt.show()

# Exemplo de uso
labels = ['Ponto 1', 'Ponto 2', 'Ponto 3', 'Ponto 4']
valores_x = ['A', 'B', 'C', 'D']
valores_y = [3, 5, 7, 9]
cores = ['red', 'blue', 'green', 'orange']

plotar_pontos(labels, valores_x, valores_y, cores)
