import matplotlib.pyplot as plt
import numpy as np

def plotar_pontos(valores_x, valores_y, nome_grafico, titulo, label_y):
    
    # Configurações do gráfico
    plt.ylabel(label_y)
    plt.title(titulo)
    #plt.legend()
    
    plt.grid(True)
    
    # Cria um gráfico de dispersão para cada ponto
    for i in range(len(valores_x)):
        plt.scatter(valores_x[i], valores_y[i], zorder=2)

    plt.savefig("./Graficos/"+nome_grafico+".png")
    plt.show()

def plotar_pontos_lucros(valores_x, valores_y, nome_grafico, titulo, label_y):
    
    # Configurações do gráfico
    plt.ylabel(label_y)
    plt.title(titulo)
    #plt.legend()
    plt.ylim([0.6, 2.0])
    plt.yticks(np.arange(0.6,2.2,0.2))
    plt.grid(True)
    
    # Cria um gráfico de dispersão para cada ponto
    for i in range(len(valores_x)):
        plt.scatter(valores_x[i], valores_y[i], zorder=2)

    plt.savefig("./Graficos/"+nome_grafico+".png")
    plt.show()

def plotar_pontos_tempos(valores_x, valores_y, nome_grafico, titulo, label_y):
    
    # Configurações do gráfico
    plt.ylabel(label_y)
    plt.title(titulo)
    #plt.legend()
    plt.ylim([-6, 500])
    plt.yticks(np.arange(0,600,100))
    plt.grid(True)
    
    # Cria um gráfico de dispersão para cada ponto
    for i in range(len(valores_x)):
        plt.scatter(valores_x[i], valores_y[i], zorder=2)

    plt.savefig("./Graficos/"+nome_grafico+".png")
    plt.show()
    
def plotar_pontos_tempos_log(valores_x, valores_y, nome_grafico, titulo, label_y):
    
    # Configurações do gráfico
    plt.ylabel(label_y)
    plt.title(titulo)
    #plt.legend()
    plt.ylim([-0.5, 3])
    plt.yticks(np.arange(-0.5,3.5,0.5))
    plt.grid(True)
    
    # Cria um gráfico de dispersão para cada ponto
    for i in range(len(valores_x)):
        plt.scatter(valores_x[i], valores_y[i], zorder=2)

    plt.savefig("./Graficos/"+nome_grafico+".png")
    plt.show()