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
dic_tempos["d2103"] = tempos_d2103
dic_tempos["d657"] = tempos_d657
dic_tempos["eil101"] = tempos_eil101
dic_tempos["eil51"] = tempos_eil51
dic_tempos["eil76"] = tempos_eil76
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
dic_lucros["d2103"] = lucros_d2103
dic_lucros["d657"] = lucros_d657
dic_lucros["eil101"] = lucros_eil101
dic_lucros["eil51"] = lucros_eil51
dic_lucros["eil76"] = lucros_eil76
dic_lucros["fl1577"] = lucros_fl1577
dic_lucros["gil262"] = lucros_gil262
dic_lucros["pr1002"] = lucros_pr1002
dic_lucros["pr124"] = lucros_pr124
dic_lucros["pr76"] = lucros_pr76
dic_lucros["rat195"] = lucros_rat195
dic_lucros["rd400"] = lucros_rd400
dic_lucros["st70"] = lucros_st70
"""
with open("./outputs/resultado.txt", "r") as arquivo:
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
                    dic_lucros[instancia].append(float(linha))
                case 2:
                    linha = linha.replace('\n', '')
                    dic_tempos[instancia].append(float(linha))
            
            cont_linha +=1
        else:
            break
        
dic_media_MELHOR_lucros_literatura = {}
dic_media_MELHOR_lucros_literatura["berlin52"] = lucros_berlin52
dic_media_MELHOR_lucros_literatura["d1291"] = lucros_d1291
dic_media_MELHOR_lucros_literatura["d2103"] = lucros_d2103
dic_media_MELHOR_lucros_literatura["d657"] = lucros_d657
dic_media_MELHOR_lucros_literatura["eil101"] = lucros_eil101
dic_media_MELHOR_lucros_literatura["eil51"] = lucros_eil51
dic_media_MELHOR_lucros_literatura["eil76"] = lucros_eil76
dic_media_MELHOR_lucros_literatura["fl1577"] = lucros_fl1577
dic_media_MELHOR_lucros_literatura["gil262"] = lucros_gil262
dic_media_MELHOR_lucros_literatura["pr1002"] = lucros_pr1002
dic_media_MELHOR_lucros_literatura["pr124"] = lucros_pr124
dic_media_MELHOR_lucros_literatura["pr76"] = lucros_pr76
dic_media_MELHOR_lucros_literatura["rat195"] = lucros_rat195
dic_media_MELHOR_lucros_literatura["rd400"] = lucros_rd400
dic_media_MELHOR_lucros_literatura["st70"] = lucros_st70

dic_media_lucros_home_made = {}

for instancia in dic_lucros:
    dic_media_lucros_home_made[instancia] = np.mean(dic_lucros[instancia])
"""
nomes_instancias = ["berlin52", "d1291", "d2103","d657", "eil101", "eil51", "eil76", "fl1577", "gil262", "pr1002", "pr124", "pr76", "rat195", "rd400", "st70"]
# Normaliza os lucros obtidos com base nos valores da literatura
#lucros_normalizados = [dic_media_lucros_home_made[instancia]/dic_media_MELHOR_lucros_literatura[instancia] for instancia in dic_media_lucros_home_made]
lucros_normalizados = [i for i in range(len(nomes_instancias))]
plota_grafico.plotar_pontos(nomes_instancias, lucros_normalizados, "Lucros_Nomalizado", "Lucros Normalizados com a Literatura", "Lucro Normalizado")
alal = 0
    