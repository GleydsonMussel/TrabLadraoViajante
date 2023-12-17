import matplotlib.pyplot as plt

def plotar_pontos(valores_x, valores_y, nome_grafico, titulo, label_y):
    
    # Cria um gráfico de dispersão para cada ponto
    for i in range(len(valores_x)):
        plt.scatter(valores_x[i], valores_y[i])
    
    # Configurações do gráfico
    plt.ylabel(label_y)
    plt.title(titulo)
    #plt.legend()
    plt.grid()
    plt.savefig("./Graficos/"+nome_grafico+".png")
    plt.show()

 