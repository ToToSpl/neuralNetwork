#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "matrix.h"

#ifndef NEURAL_H

#define NEURAL_H


class NeuralNet{
    private:
        Matrix* inputLayer;
        Matrix* weightsZero;
        Matrix* preHidden;
        Matrix* hiddenLayer;
        Matrix* weightsOne;
        Matrix* preOutput;
        Matrix* outputLayer;
        Matrix* gammaOne;
        Matrix* gammaTwo;
        Matrix* errorZero;
        Matrix* errorOne;

    public:
        int inputs,hidden,outputs;
        NeuralNet(int input, int hidden, int outputs);
        Matrix* guess(Matrix* pInput);
        void train(Matrix** pTrainInputs, Matrix** pTrainOutputs, int trainSize, int epochs, float learningRate);
        std::string returnWeights();
        void replaceWeights(int index, Matrix* weight);
        float test(Matrix** pTestInputs, Matrix** pTestOutputs, float testSize);

};

void saveNeuralNet(std::string filePath, NeuralNet* net);
NeuralNet* loadNeuralNet(std::string filePath);

#endif