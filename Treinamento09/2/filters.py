import cv2
import numpy as np

def passa_baixa(imagem):
    kernel = np.ones((3, 3), np.float32) / 9
    imagem_suavizada = cv2.filter2D(imagem, -1, kernel)
    return imagem_suavizada

def gaussiano(imagem):
    kernel = np.array([[1, 2, 1],
                       [2, 4, 2],
                       [1, 2, 1]], dtype=np.float32) / 16

    imagem_suavizada = cv2.filter2D(imagem, -1, kernel)
    return imagem_suavizada

def laplaciano(imagem):
    kernel = np.array([[0, 1, 0],
                       [1, -4, 1],
                       [0, 1, 0]], dtype=np.float32)

    imagem_realcada = cv2.filter2D(imagem, -1, kernel)
    return imagem_realcada

def realce_bordas_horizontais(imagem):
    kernel = np.array([[-1, -2, -1],
                       [0, 0, 0],
                       [1, 2, 1]], dtype=np.float32)

    bordas_horizontais = cv2.filter2D(imagem, -1, kernel)
    return bordas_horizontais

def realce_bordas_verticais(imagem):
    kernel = np.array([[-1, 0, 1],
                       [-2, 0, 2],
                       [-1, 0, 1]], dtype=np.float32)

    bordas_verticais = cv2.filter2D(imagem, -1, kernel)
    return bordas_verticais

def bordas_or(bordas_horizontais, bordas_verticais):
    return np.bitwise_or(bordas_horizontais, bordas_verticais)

def bordas_eu(bordas_horizontais, bordas_verticais):
    return np.sqrt((bordas_horizontais.astype(np.float32) ** 2) + (bordas_verticais.astype(np.float32) ** 2))