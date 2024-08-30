import tensorflow as tf
from tensorflow.keras.models import load_model

# Load the saved model from the h5 file
model = tf.keras.models.load_model('D:/OneDrive - HKUST/Software/Workspace/Python/2312_CNN/CNN_callbacks/model.h5'.encode('utf-8').decode('utf-8'))

# Loop through each layer in the model and print the kernel and weight parameters
for layer in model.layers:
    #if hasattr(layer, 'kernel'):
    #    print(layer.kernel)
    if hasattr(layer, 'weights'):
        print(layer.weights)