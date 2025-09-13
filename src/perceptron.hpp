/**
 * @file perceptron.hpp
 * @author Ondrej
 * @brief Perceptron Class
*/

#include <string>
#include <vector>

struct dataPoint
{
  int label;
  std::vector<int> features;
};

class Perceptron
{
  public:
    /** Reads data from csv file*/
    bool readData(std::string path);
    
    /** Displays data point in grayscale format */
    bool displayDatapoint(const dataPoint & datapoint);
    
    /** Splits data randomly into test and train, train_ratio range is (0 - 1.0) */
    void test_train_split(double train_ratio, int seed = 42);
    
    /** Trains data using perceptron learning algorithm - ONLY WORKS FOR LINEARLY SEPARABLE DATA!!!
        Algorithm explanation in README file
    */
    void train(void);
    

    /** Predicts target value for test dataset and returns accuracy on the test dataframe */
    double predict(void);

  private:

    std::vector<dataPoint> m_dataframe;
    std::vector<dataPoint> m_train;
    std::vector<dataPoint> m_test;
    
    /* Weights for label (index 0) and for all features (indices 1 - n) */
    std::vector<double> m_weights;
};
