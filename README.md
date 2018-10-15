# SimpleNN
SimpleNN was a summer project that I worked on in July/August of 2018. The primary goal of the project was to gain better knowledge of how neural networks work, and the appliances of the technology.

_______________________________________________________________________________________________
Activation functions:
Hidden layers   -   Softplus
Output layer    -   Softmax

Input to Output example:

IN  =   1, 0, 0, 0, 0, 0, 0, 0, 0, 0    (0 in decimal)

OUT =   0, 1, 0, 0, 0, 0, 0, 0, 0, 0    (1 in decimal)
_______________________________________________________________________________________________


The initial technological goal was to create a neural network from scratch, that could read handwritten digits from the MNIST database. However the end result became a simple counter that learned to count from 0 to 10. Neural networks are really complicated to troubleshoot, and trying to train a network to read handwritten digits demands serious computation time on a normal pc. So I had a hard time figuring out whether the problems were coming from the hyperparameters, the MNIST reader, or the network itself.

I first tried implementing a binary counter, but I encountered some problems with the necessary output function. To achieve wanted output from the network, I had to use an output function that delivered multiple active neurons, so I choose the Sigmoid function 1/(1+e^x ). However the Sigmoid comes with several drawbacks, such as the vanishing gradient and exploding gradient problems.

I could not get the network to work no matter how I changed the hyperparameters, but once I replaced the binary counter problem with a simpler counter, the network worked almost immediately. Since the simpler counter only requires one of the output neurons to be 1, I swapped Sigmoid activation with Softmax. Now all output neurons are summed to 1, called probability distribution.

In retrospect, I think two extra layers could easily convert my simple counter to a binary counter. It would work by converting binary numbers to longer binary strings consisting only of one active bit, or neuron, and feeding the converted number on the input. Whereas a long string of neurons coming from the output would be converted to a binary value.
