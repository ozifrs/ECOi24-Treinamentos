import cv2
import numpy as np

def grayscale(img):
  h,w = img.shape[:2]
  aux_img = np.zeros((h, w, 1), dtype=np.uint8)
  for i in range(h):
    for j in range(w):
        aux_img[i, j] = sum(img[i, j][:])/3
  return aux_img

img = cv2.imread('./img/Gustavo_Fring.png')

if img is not None:
	cv2.imshow("Image", img)
	cv2.imshow("Gray Image", grayscale(img))
	cv2.waitKey(0)
	cv2.destroyAllWindows()
else:
    print("Erro ao carregar a imagem. Verifique o caminho do arquivo.")