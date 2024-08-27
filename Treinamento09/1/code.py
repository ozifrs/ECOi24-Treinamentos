import cv2
import numpy as np
from morph import *

img = [
	[252, 46, 115, 18, 73, 203, 60, 229, 112, 183],
	[109, 31, 20, 53, 225, 58, 54, 28, 170, 94],
	[99, 73, 116, 115, 183, 146, 177, 88, 14, 141],
	[79, 176, 132, 54, 144, 148, 231, 157, 244, 187],
	[207, 28, 4, 194, 111, 122, 172, 61, 211, 71],
	[185,199,124,123,40,195,134,112,17,194],
	[26,3,168,251,12,85,98,205,174,34],
	[234,222,166,121,99,167,33,35,43,183],
	[237,102,254,45,206,234,49,144,1,70],
	[17,231,44,224,67,195,148,68,127,42]
]

img_array = np.array(img, dtype=np.uint8)
elemento_estruturante = [
	[0,0,0,1,0,0,0],
	[0,0,1,10,1,0,0],
	[0,1,10,20,10,1,0],
	[1,10,20,40,20,10,1],
	[0,1,10,20,10,1,0],
	[0,0,1,10,1,0,0],
	[0,0,0,1,0,0,0],
]

elemento_estruturante = np.array(elemento_estruturante, dtype=np.uint8)

img_erosao = np.array(erosao(img_array, elemento_estruturante), dtype=np.uint8)
img_dilata = np.array(dilatacao(img_array, elemento_estruturante), dtype=np.uint8)
img_gradie = np.array(gradiente(img_array, elemento_estruturante), dtype=np.uint8)
img_abertu = np.array(abertura(img_array, elemento_estruturante), dtype=np.uint8)
img_fecham = np.array(fechamento(img_array, elemento_estruturante), dtype=np.uint8)

cv2.imwrite("./img/erosao.png", img_erosao)
cv2.imwrite("./img/dilatacao.png", img_dilata)
cv2.imwrite("./img/gradiente.png", img_gradie)
cv2.imwrite("./img/abertura.png", img_abertu)
cv2.imwrite("./img/fechamento.png", img_fecham)
cv2.imwrite("./img/filtro.png", elemento_estruturante)