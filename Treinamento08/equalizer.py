import cv2
import numpy as np
import matplotlib.pyplot as plt

def equalizar_histograma(imagem):
	hist = cv2.calcHist([imagem], [0], None, [256], [0,256])

	hist_acumulado = np.cumsum(hist)
	hist_acumulado = (hist_acumulado / hist_acumulado.max()) * 255

	imagem_equalizada = hist_acumulado[imagem]

	hist_equalizado = cv2.calcHist([imagem_equalizada], [0], None, [256], [0,256])

	return imagem_equalizada, hist_equalizado, hist_acumulado

def exibir_histograma(hist):
	plt.plot(hist)
	plt.title('Histograma Equalizado')
	plt.xlabel('Níveis de Cinza')
	plt.ylabel('Número de Pixels')
	plt.show()


caminho_imagem = 'caminho/para/sua/imagem.jpg'
img = cv2.imread('./img/Gustavo_Fring.png', cv2.IMREAD_GRAYSCALE)

if img is not None:
	imagem_equalizada, hist_equalizado, hist_acumulado = equalizar_histograma(img)

	cv2.imshow('Imagem Equalizada', imagem_equalizada)

	exibir_histograma(hist_equalizado)

	cv2.waitKey(0)
	cv2.destroyAllWindows()
else:
	print("Erro ao carregar a imagem. Verifique o caminho do arquivo.")