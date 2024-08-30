import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras.datasets import mnist

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

num=0

plt.imshow(train_images[num], cmap=plt.cm.binary, extent=[0, 28, 28, 0])
plt.grid(True, which='both', color='gray', linewidth=1)
plt.xticks(np.arange(0, 28, 1), visible=False)
plt.yticks(np.arange(0, 28, 1), visible=False)
plt.tick_params(axis='both', which='both', length=0)

plt.savefig('C:/Users/eehys/Desktop/'+str(num)+'.png')

plt.show()

