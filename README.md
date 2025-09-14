# Simple perceptron implementation for binary classification

## How to use
Use `make` and `make run ARGS="path_to_dataset` where dataset is expected to be csv file, where every row contains one datapoint. First column is label (target variable) and other columns are features. I specifically used mnist digits dataset from here (https://github.com/phoebetronic/mnist). 

## Algorithm explanation
Perceptron can be used for binary classification for linearly separable data (which mnist digits dataset is). In this case, the training algorithm will always finish in finite time. For my program, I split dataset into two parts, training and testing, for obvious reason. Let's call the size of training dataset $N$. The training process it self goes as follows:\
Let us denote the i-th point $x_i$ of the training dataset $\tilde{x}_i = (1, x\_{i;1}, \dots, x\_{i;p})^T$ of $p$ features with 1 being placeholder for bias, and weights $\tilde{w} = (w_0, w_1, \dots, w_p)^T$ ($w_0$ for bias). We will then count the prediction as correct, if $(2 \cdot Y_i - 1) \, \tilde{\mathbf{x}}_i^\top \tilde{\mathbf{w}} > 0$ where $Y_i$ is the correct label of the i-th point. In the start of training we set $w^0 = (0, \dots, 0)$. We iteratively construct sequence of weight vectors $w^1, w^2, \dots$ such that in (k + 1)-th step we update the weights $\tilde{w}^{k+1} = \tilde{w}^k + (2Y\_{i(k)} - 1) \tilde{x}\_{i(k)}$ if prediction was not correct and $\tilde{w}^{k+1} = \tilde{w}^{k+1}$ if prediction was correct where $i(k)$ is the index of the point in the training dataset, that we used in the (k + 1)th step of training. Points are repeating in the training, so $i(k) = (k \mod N) + 1$. We can end the training if there was no error in prediction after $N$ steps. If the training dataset is linearly separable, this algorithm will always end, meaning that all training datapoints will be predicted correcly. The final prediction on new points is $\tilde{Y} = g(\xi) = g(w \cdot x + w_0)$ \
where $g (\xi) = 1$ if $\xi \ge 0$ and $g (\xi) = 0$ if $\xi \lt 0$














