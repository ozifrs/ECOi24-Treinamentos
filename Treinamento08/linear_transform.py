import cv2
import numpy as np

def imagem_negativa(imagem):
	return 255 - imagem

def limiarizar_imagem(imagem, limiar=128):
	_, img_limiarizada = cv2.threshold(cv2.cvtColor(imagem, cv2.COLOR_BGR2GRAY), limiar, 255, cv2.THRESH_BINARY)
	return img_limiarizada


img = cv2.imread('./img/Gustavo_Fring.png')

if img is not None:
	cv2.imshow('Imagem', img)

	canais = cv2.split(img)
	canais_negativos = [imagem_negativa(canal) for canal in canais]
	img_neg = cv2.merge(canais_negativos)
	img_lim = limiarizar_imagem(img)
	img_norm = img.copy()
	cv2.normalize(img, img_norm, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX)

	cv2.imshow('Imagem Negativa', img_neg)
	cv2.imshow('Imagem Limiarizada', img_lim)
	cv2.imshow('Imagem Normalizada', img_norm)
	cv2.waitKey(0)
	cv2.destroyAllWindows()
else:
	print("Erro ao carregar a imagem. Verifique o caminho do arquivo.")