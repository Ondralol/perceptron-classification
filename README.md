# Simple perceptron implementation for binary classification

## How to use
Use `make` and `make run ARGS="path_to_dataset` where dataset is expected to be csv file, where every row contains one datapoint. First column is label (target variable) and other columns are features. I specifically used mnist digits dataset from here (https://github.com/phoebetronic/mnist). 

## Algorithm explanation
Perceptron can be used for binary classification for linearly separable data (which mnist digits dataset is). In this case, the training algorithm will always finish in finite time. For my program, I split dataset into two parts, training and testing for obvious reason. The training process it self goes as followed: \
Let us denote the i-th point $x_i$ of the training dataset $\tilde{x}_i = (1, x_{i;1},...,x_{i;p})$


=
