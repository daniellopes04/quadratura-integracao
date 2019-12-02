import sys

# variaveis globais
nThreads = 0
totalLeitores = 0
totalEscritores = 0
leitores = 0
escritores = 0
recurso = -1

arquivoAux = open("temp.txt", "r")
arquivo = open(arquivoAux.readline(), "r")

threadsExecutadas = []

def iniciaVerificacao(nLeitores, nEscritores, leituras, escritas):
    global totalLeitores, totalEscritores
    global nThreads

    totalLeitores = nLeitores
    totalEscritores = nEscritores
    nThreads = nLeitores + nEscritores


def entraLeitura(idThread):
    global leitores, escritores
    leitores += 1

    if(escritores > 0):
        erro(idThread, 1, 2)

def saiLeitura (idThread, valorLido):
    global leitores

    if(recurso != valorLido):
        erro(idThread, 1, 5)

    leitores -= 1

    if idThread not in threadsExecutadas:
        threadsExecutadas.append(idThread)

def entraEscrita(idThread):
    global leitores, escritores
    escritores += 1

    if(escritores > 1):
        erro(idThread, 2, 1)

    if(leitores > 0):
        erro(idThread, 2, 2)

def saiEscrita(idThread):
    global escritores, recurso

    recurso = idThread
    escritores -= 1

    if idThread not in threadsExecutadas:
        threadsExecutadas.append(idThread)

def leituraBloqueada(idThread):
    global escritores

    if(escritores == 0):
        erro(idThread, 1, 3)

def escritaBloqueada(idThread):
    global leitores

    if(leitores == 0 and escritores == 0):
        erro(idThread, 2, 4)

def erro(t_id, tipoThread, codErro):
    if(tipoThread == 1):
        print("Thread leitora ", t_id, " executou com erro:")
    elif(tipoThread == 2):
        print("Thread escritora ", t_id, " executou com erro:")

    if(codErro == 1):
        print("Mais de um escritor escrevendo ao mesmo tempo")
    elif(codErro == 2):
        print("Leitura e escrita acontecendo simultaneamente")
    elif(codErro == 3):
        print("Leitura bloqueada sem que haja escritores executando")
    elif(codErro == 4):
        print("Escrita bloqueada sem que haja leitores/escritores executando")
    elif(codErro == 5):
        print("Valor lido do recurso diferente do esperado")
    elif(codErro == 6):
        print("Inanicao")

    sys.exit()

# Executa as linhas do arquivo
for linha in arquivo:
    exec(linha)

for i in range(0, nThreads):
    if i not in threadsExecutadas:
        erro(i, 0, 6)

print("\nExecucao finalizada sem erros!\n")