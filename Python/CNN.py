import os
import pandas as pd
import tensorflow as tf
from tensorflow import keras
import matplotlib.pyplot as plt
from tensorflow.keras import datasets, layers, models, callbacks
from tensorflow.keras.utils import to_categorical

# Load the MNIST dataset
(train_images, train_labels), (test_images, test_labels) = datasets.mnist.load_data()

# Normalize pixel values to be between 0 and 1
train_images, test_images = train_images / 255.0, test_images / 255.0

# Reshape the images to be 4D arrays (batch_size, height, width, channels)
train_images = train_images.reshape(train_images.shape[0], 28, 28, 1)
test_images = test_images.reshape(test_images.shape[0], 28, 28, 1)

# Convert integer class labels to binary matrix labels
train_labels = to_categorical(train_labels)
test_labels = to_categorical(test_labels)

# Define the CNN architecture
model = models.Sequential()
model.add(layers.Conv2D(3, (5, 5), activation='relu',use_bias=False, input_shape=(28, 28, 1)))
model.add(layers.AveragePooling2D((3, 3)))
model.add(layers.Conv2D(6, (3, 3), activation='relu',use_bias=False))
model.add(layers.AveragePooling2D((2, 2)))
model.add(layers.Flatten())
model.add(layers.Dense(10, activation='softmax'))

model.summary()

# Compile the model with categorical cross-entropy loss and Adam optimizer
model.compile(optimizer='adam',
            loss='categorical_crossentropy',
            metrics=['accuracy'])


# Callbacks function
checkpoint_callback = callbacks.ModelCheckpoint(filepath='D:/OneDrive - HKUST/Software/Workspace/Python/2312_CNN/CNN_callbacks/model.h5',
                                                save_best_only=True,
                                                save_weights_only=False,
                                                monitor='val_accuracy',
                                                mode='max',
                                                verbose=1)

    
# Train the model on the training data

#history=model.fit(train_images, train_labels, epochs=10)
history=model.fit(train_images, train_labels, epochs=20, validation_data=(test_images,test_labels), callbacks=[checkpoint_callback])


# Plot the training history
def plot_learning_curves(history):
    pd.DataFrame(history.history).plot(figsize=(8,5))
    plt.grid(True)
    plt.gca().set_ylim(0,1)
    plt.show()


# Evaluate the model on the test data
test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=0)
print('Test accuracy:', test_acc)

plot_learning_curves(history)