# Simple perceptron implementation for binary classification

## How to use
Use `make` and `make run ARGS="path_to_dataset"` where dataset is expected to be csv file, where every row contains one datapoint. First column is label (target variable) and other columns are features. I specifically used mnist digits dataset from here (https://github.com/phoebetronic/mnist). 

## Algorithm Explanation

This project uses the **Perceptron algorithm** for binary classification. The Perceptron is an ideal choice for **linearly separable data**, which applies to our simplified binary classification task on the MNIST digits dataset. A key advantage of this algorithm is that when the data is linearly separable, the training process is guaranteed to converge in a finite amount of time.

### Training the Model

The training process involves splitting the dataset into training and testing sets. For our purposes, we'll focus on the training set, which has a size of **N**.

1.  **Define the Vectors**:
    * Each data point, **x**, is augmented with a bias placeholder. We represent this as a feature vector **x̃** = (1, x₁, ..., xₚ)ᵀ. The `1` in the first position is for the bias term.
    * The corresponding weight vector is **w̃** = (w₀, w₁, ..., wₚ)ᵀ, where w₀ is the bias weight.

2.  **Prediction and Evaluation**:
    * A prediction is considered correct if the sign of the dot product is positive. The condition for a correct prediction is:
        $$(2Y_i - 1) \cdot \tilde{\mathbf{x}}_i^\top \tilde{\mathbf{w}} > 0$$
    * In this expression, $Y_i$ is the correct label (either 0 or 1).

3.  **Iterative Training**:
    * We start with an initial weight vector, typically all zeros: **w̃**⁰ = (0, ..., 0)ᵀ.
    * The algorithm then iterates through the training data, updating the weights whenever a prediction is incorrect. At each step **k+1**, we use a data point with index **i(k)**.
    * The weight update rule is:
        $$\tilde{\mathbf{w}}^{k+1} = \tilde{\mathbf{w}}^k + (2Y_{i(k)} - 1) \tilde{\mathbf{x}}_{i(k)}$$ if the prediction was incorrect.
    * The weights remain the same if the prediction was correct. Points are repeated in the training, with the index being determined by **i(k) = (k mod N) + 1**.

### Convergence and Final Prediction

The algorithm continues updating weights until it correctly classifies **all** training data points in one full pass. Because the dataset is linearly separable, this convergence is guaranteed.

Once training is complete, the final prediction for a new point **x** is determined by a simple step function:

$$\tilde{Y} = g(\xi) = g(\tilde{\mathbf{w}}^\top \tilde{\mathbf{x}})$$
where the step function $g(\xi)$ is defined as:

$$g(\xi) = 1 \text{ if } \xi \ge 0$$
$$g(\xi) = 0 \text{ if } \xi < 0$$



