/**
* @file main.cpp
* @author Ondrej
* @brief Main function that passes dataset inputs to the perceptron to train and evaluate data
*/

#include <iostream>

#include "perceptron.hpp"

/**
* @brief Manages the program
* - Argument 1: filepath to dataset
*/

int main (int argc, char **argv)
{
  /* Not enough arguments*/
  if (argc < 2)
    return EXIT_FAILURE;
  
  // Get the dataset argument
  std::string path = argv[1];
 
  Perceptron perceptron;
  if (!perceptron.readData(path))
    return EXIT_FAILURE;
  
  // Split data into training and testing parts
  perceptron.test_train_split(0.5);
  
  // Train on the testing part
  perceptron.train();
  
  // Predict accuracy on testing dataset
  double acc = perceptron.predict();

  std::cout << "Test accuracy: " << acc << std::endl;;
  return EXIT_SUCCESS;
}
