import numpy as np

def dilatacao(imagem, elemento_estruturante):
    linhas, colunas = imagem.shape
    tamanho_elemento_estruturante = elemento_estruturante.shape[0]

    imagem_dilatada = np.zeros((linhas, colunas), dtype=np.uint8)

    for i in range(linhas - tamanho_elemento_estruturante + 1):
        for j in range(colunas - tamanho_elemento_estruturante + 1):
            submatriz = imagem[i:i+tamanho_elemento_estruturante, j:j+tamanho_elemento_estruturante]

            valor_dilatado = np.sum(submatriz * elemento_estruturante)

            imagem_dilatada[i + tamanho_elemento_estruturante // 2, j + tamanho_elemento_estruturante // 2] = valor_dilatado

    return imagem_dilatada

def erosao(imagem, elemento_estruturante):
    linhas, colunas = imagem.shape
    tamanho_elemento_estruturante = elemento_estruturante.shape[0]

    # Inicializar imagem erodida com o valor máximo representável
    imagem_erodida = np.full((linhas, colunas), fill_value=255, dtype=np.uint8)

    for i in range(linhas - tamanho_elemento_estruturante + 1):
        for j in range(colunas - tamanho_elemento_estruturante + 1):
            submatriz = imagem[i:i+tamanho_elemento_estruturante, j:j+tamanho_elemento_estruturante]

            # Aplicar erosão (atribuir mínimo ao pixel central)
            valor_erodido = np.min(submatriz * elemento_estruturante)
            imagem_erodida[i + tamanho_elemento_estruturante // 2, j + tamanho_elemento_estruturante // 2] = valor_erodido

    return imagem_erodida

def gradiente(imagem, elemento_estruturante):
    return dilatacao(imagem, elemento_estruturante) - erosao(imagem, elemento_estruturante)

def abertura(imagem, elemento_estruturante):
    return dilatacao(erosao(imagem, elemento_estruturante), elemento_estruturante)

def fechamento(imagem, elemento_estruturante):
    return erosao(dilatacao(imagem, elemento_estruturante), elemento_estruturante)