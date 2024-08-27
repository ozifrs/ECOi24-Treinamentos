import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt


def compute_fshift(image):
    f_transform = np.fft.fft2(image)
    return np.fft.fftshift(f_transform)


def generate_responses(image, fshift, D0=10, n=1):
    height, width = image.shape[:2]

    ideal_filter = create_ideal_filter(height, width, D0)
    butterworth_filter = create_butterworth_filter(height, width, D0, n)
    gaussian_filter = create_gaussian_filter(height, width, D0)

    response_ideal = np.abs(np.fft.ifft2(np.fft.ifftshift(fshift * ideal_filter)))
    response_butterworth = np.abs(
        np.fft.ifft2(np.fft.ifftshift(fshift * butterworth_filter))
    )
    response_gaussian = np.abs(np.fft.ifft2(np.fft.ifftshift(fshift * gaussian_filter)))

    display_responses(response_ideal, response_butterworth, response_gaussian)


def create_ideal_filter(height, width, D0):
    filter_array = np.zeros((height, width), dtype=np.float32)

    for h in range(height):
        for w in range(width):
            D = np.sqrt((h - height / 2) ** 2 + (w - width / 2) ** 2)
            if D <= D0:
                filter_array[h, w] = 1

    return filter_array


def create_butterworth_filter(height, width, D0, n):
    filter_array = np.zeros((height, width), dtype=np.float32)

    for h in range(height):
        for w in range(width):
            D = np.sqrt((h - height / 2) ** 2 + (w - width / 2) ** 2)
            filter_array[h, w] = 1 / (1 + (D / D0) ** (2 * n))

    return filter_array


def create_gaussian_filter(height, width, D0):
    filter_array = np.zeros((height, width), dtype=np.float32)

    for h in range(height):
        for w in range(width):
            D = np.sqrt((h - height / 2) ** 2 + (w - width / 2) ** 2)
            filter_array[h, w] = np.exp(-(D**2) / (2 * D0**2))

    return filter_array


def display_responses(response_ideal, response_butterworth, response_gaussian):
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.imshow(response_ideal, cmap="gray")
    plt.title("Ideal Filter")
    plt.xticks([])
    plt.yticks([])

    plt.subplot(2, 2, 2)
    plt.imshow(response_butterworth, cmap="gray")
    plt.title("Butterworth Filter")
    plt.xticks([])
    plt.yticks([])

    plt.subplot(2, 2, 4)
    plt.imshow(response_gaussian, cmap="gray")
    plt.title("Gaussian Filter")
    plt.xticks([])
    plt.yticks([])

    plt.show()


if __name__ == "__main__":
    image = cv.imread("./gus.png", cv.IMREAD_GRAYSCALE)

    if image is None:
        print("Unable to read the image.")
    else:
        fshift = compute_fshift(image)
        generate_responses(image, fshift, D0=10, n=1)
