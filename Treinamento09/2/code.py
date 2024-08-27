import cv2
import numpy as np
from filters import *

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

img_baixa = np.array(passa_baixa(img_array), dtype=np.uint8)
img_gauss = np.array(gaussiano(img_array), dtype=np.uint8)
img_lapla = np.array(laplaciano(img_array), dtype=np.uint8)
img_horiz = np.array(realce_bordas_horizontais(img_array), dtype=np.uint8)
img_verti = np.array(realce_bordas_verticais(img_array), dtype=np.uint8)
img_opeor = np.array(bordas_or(img_horiz, img_verti), dtype=np.uint8)
img_euler = np.array(bordas_eu(img_horiz, img_verti), dtype=np.uint8)

cv2.imwrite("./img/imagem.png", img_array)
cv2.imwrite("./img/passa_baixa.png", img_baixa)
cv2.imwrite("./img/gaussiana.png", img_gauss)
cv2.imwrite("./img/laplaciana.png", img_lapla)
cv2.imwrite("./img/horizontal.png", img_horiz)
cv2.imwrite("./img/vertical.png", img_verti)
cv2.imwrite("./img/opertion_or.png", img_opeor)
cv2.imwrite("./img/euclidian_dist.png", img_opeor)