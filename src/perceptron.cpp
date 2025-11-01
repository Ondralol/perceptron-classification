/**
 * @file main.cpp
 * @author Ondrej
 * @brief Perceptron class
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "perceptron.hpp"
#include <algorithm>
#include <random>

/** Defines which two numbers you want to use binary classification for. 
    In dataset that is currently used numbers 0 - 9 are viable       */
#define NUMBER_ONE 0
#define NUMBER_TWO 1


/** Maximum iteration count is useful when the data is not linearly separable, otherwise your algorithm
    will never end                                                                                     */
#define MAX_ITERATIONS 10'000

/** Parse data from csv, 1 column is label, other columns are features (in our case pixels) */
bool Perceptron::readData(std::string path)
{
  std::ifstream file (path);
  if (!file.is_open())
  {
    std::cout << "Failed to open dataset file with path: " << path << std::endl;
    return false;
  }

  std::string line;

  // Parse all rows
  while (std::getline(file, line))
  {
    std::stringstream stream(line);
    std::string cell;
    
    int index = 0;
    dataPoint datapoint;
    bool success = true;

    // Parse singular row
    while(std::getline(stream, cell, ','))
    {
      int value;
      std::istringstream(cell) >> value;
      
      // First index is the label
      if (index++ == 0)
      {
        // If the label is something else than the 2 labels that we wanna use the binary classification for
        if (value != NUMBER_ONE && value != NUMBER_TWO)
        {
          success = false;
          break;
        }
        // Save the label
        datapoint.label = value;
      }
      // Save the feature
      else
        datapoint.features.push_back(value);
    }
    if (success)
      m_dataframe.push_back(datapoint);
  }

  file.close();
  
  std::cout << "Number of points: " << m_dataframe.size() << std::endl;
  
  return true; 
}


/** Displays data point in grayscale */
bool Perceptron::displayDatapoint(const dataPoint & datapoint)
{

  std::cout << "LABEL: " << datapoint.label << std::endl;

  const std::vector<std::string> shades = {" ", "░", "▒", "▓", "█"};
  int counter = 0;
  for (const auto & pixel: datapoint.features)
  {
    int shade = (pixel * 4) / 255;
    std::cout << shades[shade];
    if (counter++ % 28 == 0)
      std::cout << std::endl;
  }
  std::cout << std::endl;

  return true;
}

/** Splits data randomly into test and train, train_ratio range is (0 - 1.0) */
void Perceptron::test_train_split(double train_ratio, int seed)
{
  std::mt19937 rng(seed);
  std::shuffle(m_dataframe.begin(), m_dataframe.end(), rng);
  
  int train_size = static_cast<int>(m_dataframe.size() * train_ratio);

  m_train.assign(m_dataframe.begin(), m_dataframe.begin() + train_size);
  m_test.assign(m_dataframe.begin() + train_size, m_dataframe.end());
  
  std::cout << "Train size: " << m_train.size() << std::endl;
  std::cout << "Test size: " << m_test.size() << std::endl;
}

/** Trains data using perceptron learning algorithm - ONLY WORKS FOR LINEARLY SEPARABLE DATA!!! */
void Perceptron::train(void)
{
  // Initialize weights to 0 in the beginning
  for (int i = 0; i < m_train[0].features.size() + 1; i++)
    m_weights.push_back(0.0);
  
  // Keep track of how many correct predictions were correct in row
  int correct_in_row = 0;
  bool break_flag = false;

  // Keep iterating over the whole dataset until every datapoint in train dataframe is predicted correctly 
  for (int iteration = 0; iteration < MAX_ITERATIONS; iteration ++)
  {
    if (break_flag)
      break;

    for (const auto & datapoint: m_train)
    {
      
      std::cout <<"\r Correctly predicted in row: " << correct_in_row << std::flush;
      
      // Calculate for bias
      double mult = m_weights[0] * 1.0;
      
      // Calculate for weights
      for (size_t i = 0; i < datapoint.features.size(); i ++)
      {
        mult += m_weights[i+1] * datapoint.features[i];
      }

      // Check if predition is correct
      double prediction = (2.0 * datapoint.label - 1)  * mult;
      
      // If prediction is correct
      if (prediction > 0)
      {
        correct_in_row ++;
      }
      // If prediction is not correct, update the bias/weights
      else
      {
        correct_in_row = 0;
        for (size_t i = 0; i < m_weights.size(); i ++)
        { 
          // Update bias
          if (i == 0)
             m_weights[i] = m_weights[i] + (2.0 * datapoint.label - 1) * 1.0;
          // Update weights
          else
             m_weights[i] = m_weights[i] + (2.0 * datapoint.label - 1) * datapoint.features[i-1];
        }
        
      }

      // If all train points in train dataframe were predicted correctly
      if (correct_in_row >= m_train.size())
      {
        std::cout << "All datapoints in the training dataset predicted correctly! Took #"
                  << iteration << " iterations." << std::endl;
        break_flag = true;
        break;
      }
    }
  }
}

/** Predicts target value for test dataset and returns accuracy on the test dataframe */
double Perceptron::predict(void)
{
  // Total amount of accurately predicted data points on the test dataset
  int accurate_count = 0;

  for (const auto & datapoint: m_test)
  {
    // Calculate for bias
    double prediction = m_weights[0] * 1.0;
    
    // Calculate for weights
    for (size_t i = 0; i < datapoint.features.size(); i ++)
    {
      prediction += m_weights[i+1] * datapoint.features[i];
    }
    
    // Check if predition is correct
    if ((2 * datapoint.label - 1) * prediction >= 0)
    {
      accurate_count ++;
    }
    // Display wrongly predicted datapoint
    else
    {
      this -> displayDatapoint(datapoint);
    }
  }

  // Return test accuracy
  return 1.0 * accurate_count / m_test.size();
}
