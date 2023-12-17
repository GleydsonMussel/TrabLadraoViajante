import numpy as np
import plota_grafico

# (s) Vetores de tempos

# Instâncias Pequenas/Médias
tempos_eil51 = []
tempos_berlin52 = []
tempos_st70 = []
tempos_eil76 = []
tempos_eil101 = []
# Instâncias Grandes
tempos_pr76 = []
tempos_pr124 = []
tempos_rat195 = []
tempos_gil262 = []
tempos_rd400 = []
tempos_d657 = []
tempos_pr1002 = []
tempos_d1291 = []
tempos_fl1577 = []
tempos_d2103 = []

dic_tempos = {}
dic_tempos["berlin52"] = tempos_berlin52
dic_tempos["d1291"] = tempos_d1291
dic_tempos["fl1577"] = tempos_fl1577
dic_tempos["gil262"] = tempos_gil262
dic_tempos["pr1002"] = tempos_pr1002
dic_tempos["pr124"] = tempos_pr124
dic_tempos["pr76"] = tempos_pr76
dic_tempos["rat195"] = tempos_rat195
dic_tempos["rd400"] = tempos_rd400
dic_tempos["st70"] = tempos_st70

# Vetores de lucro

# Instâncias Pequenas/Médias
lucros_eil51 = []
lucros_berlin52 = []
lucros_st70 = []
lucros_eil76 = []
lucros_eil101 = []

# Instâncias Grandes
lucros_pr76 = []
lucros_pr124 = []
lucros_rat195 = []
lucros_gil262 = []
lucros_rd400 = []
lucros_d657 = []
lucros_pr1002 = []
lucros_d1291 = []
lucros_fl1577 = []
lucros_d2103 = []

dic_lucros = {}
dic_lucros["berlin52"] = lucros_berlin52
dic_lucros["d1291"] = lucros_d1291
dic_lucros["fl1577"] = lucros_fl1577
dic_lucros["gil262"] = lucros_gil262
dic_lucros["pr1002"] = lucros_pr1002
dic_lucros["pr124"] = lucros_pr124
dic_lucros["pr76"] = lucros_pr76
dic_lucros["rat195"] = lucros_rat195
dic_lucros["rd400"] = lucros_rd400
dic_lucros["st70"] = lucros_st70

with open("./outputs/resultado_copia.txt", "r") as arquivo:
    cont_linha = 0
    linhas = arquivo.readlines()
    
    for linha in linhas: 
        if linha != "FIM\n":
    
            if cont_linha == 3:
                cont_linha = 0
                
            if cont_linha == 0:
                elementos_linha = linha.split('_')
                instancia = elementos_linha[0]
                cont_linha += 1
                continue
            
            match cont_linha:
                case 1:
                    linha = linha.replace('\n', '')
                    tata = float(linha)
                    if tata >= 1000000:
                        cont_linha+=1
                        continue
                    dic_lucros[instancia].append(tata)
                case 2:
                    linha = linha.replace('\n', '')
                    dic_tempos[instancia].append(float(linha))
            
            cont_linha +=1
        else:
            break
        
dic_media_MELHOR_lucros_literatura = {}
dic_media_MELHOR_lucros_literatura["berlin52"] = 9426.68
dic_media_MELHOR_lucros_literatura["d1291"] = 120777.76
dic_media_MELHOR_lucros_literatura["fl1577"] = 131462.38
dic_media_MELHOR_lucros_literatura["gil262"] = 28999.08
dic_media_MELHOR_lucros_literatura["pr1002"] = 80070.34
dic_media_MELHOR_lucros_literatura["pr124"] = 19683.23
dic_media_MELHOR_lucros_literatura["pr76"] = 15812.60
dic_media_MELHOR_lucros_literatura["rat195"] = 27550.47
dic_media_MELHOR_lucros_literatura["rd400"] = 34008.34
dic_media_MELHOR_lucros_literatura["st70"] = 11920.99

dic_media_lucros_home_made = {}
tempos = []

for instancia in dic_lucros:
    dic_media_lucros_home_made[instancia] = np.mean(dic_lucros[instancia])
    tempos.append(np.mean(dic_tempos[instancia]))
    print(instancia, end=" ")
    # Printa Tempos
    print(np.mean(dic_tempos[instancia]))

tempos_log = [np.log10(elemento) for elemento in tempos]

nomes_instancias = ["berlin52", "d1291", "fl1577", "gil262", "pr1002", "pr124", "pr76", "rat195", "rd400", "st70"]
# Normaliza os lucros obtidos com base nos valores da literatura
lucros_normalizados = [(dic_media_lucros_home_made[instancia]/6)/dic_media_MELHOR_lucros_literatura[instancia] for instancia in dic_media_lucros_home_made]

#lucros_normalizados = [i for i in range(len(nomes_instancias))]
#plota_grafico.plotar_pontos_lucros(nomes_instancias, lucros_normalizados, "Lucros_Nomalizado", "Lucros Normalizados com a Literatura", "Lucro Normalizado")
#plota_grafico.plotar_pontos_tempos(nomes_instancias, tempos, "Tempos_Nomalizado", "Tempo de Execução", "Tempo Médio para uma Instância (s)")
plota_grafico.plotar_pontos_tempos_log(nomes_instancias, tempos_log, "Tempos_Log", "Comparativo de Tempos de Execução", " Log(Tempo Médio)")
alal = 0
    