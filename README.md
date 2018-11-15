# SimpleNN
SimpleNN is a summer project that I worked on in July/August of 2018. The primary goal of the project was to gain better knowledge on how neural networks work, and the appliances of the algorithm.

*Be aware that the code is rather messy*
_______________________________________________________________________________________________
Activation functions:

Hidden layers   -   Softplus

Output layer    -   Softmax

Input to Output example:

IN  =   1, 0, 0, 0, 0, 0, 0, 0, 0, 0    (0 in decimal)

OUT =   0, 1, 0, 0, 0, 0, 0, 0, 0, 0    (1 in decimal)
_______________________________________________________________________________________________


The initial goal was to create a neural network from scratch, that could read handwritten digits from the MNIST database. However the end result became a simple counter that learned to count from 0 to 10. Neural networks are really complicated to troubleshoot, and trying to train a network to read handwritten digits demands serious computation time on a normal pc. At least with my memory inefficient code. So I had a hard time figuring out whether the problems were coming from the hyperparameters, the MNIST reader, network topology, or the code creating the network.

I first tried implementing a binary counter, but I encountered some problems with the necessary output function. To achieve wanted output from the network, I had to use an output function that delivered multiple active neurons (see in/out example below), so I choose the Sigmoid function 1/(1+e^x ). However the Sigmoid comes with several drawbacks, such as the vanishing gradient and exploding gradient problems.

IN = 0100
OUT = 0101

I could not get the network to work no matter how I changed the hyperparameters, but once I replaced the binary counter problem with a simpler counter, the network worked almost immediately. Since the simpler counter only requires one of the output neurons to be 1, I swapped Sigmoid activation with Softmax. Now all output neurons are summed to 1, called probability distribution. After reading through numerous forums online, I discovered that most people avoid using Sigmoid activation due to its flaws.

To convert my simple network to a binary counter, I simply have to add two more layers converting the binary in- and output-values to strings containing only one active neuron.

Since this neural network is both trained and tested on the same data, it can hardly be called machine learning, however this project was a great exercise to learn the concepts of Neural Networks. By using already existing api's like TensorFlow with Keras, you can easily create far superior networks. For instance I was able to create a network that could read handwritten MNIST digits by using Python with TensorFlow + Keras, with less than 30 lines of code.



