#include "matrix.h"
#include "neural.h"

NeuralNet::NeuralNet(int _inputs, int _hidden, int _outputs){
    inputs = _inputs;
    hidden = _hidden;
    outputs = _outputs;
    //creating matrices for layers
    inputLayer = new Matrix(inputs+1,1);
    inputLayer->writeValue(1,inputs,0);

    weightsZero = new Matrix(hidden+1,inputs+1);
    weightsZero->fillRand();
    for(int i = 0; i < inputs; i++){
        weightsZero->writeValue(0,hidden,i);
    }
    weightsZero->writeValue(1,hidden,inputs);

    preHidden = new Matrix(hidden+1,1);
    hiddenLayer = new Matrix(hidden+1,1);

    weightsOne = new Matrix(outputs,hidden+1);
    weightsOne->fillRand();

    preOutput = new Matrix(outputs,1);
    outputLayer = new Matrix(outputs,1);
    
}

Matrix* NeuralNet::guess(Matrix* pInput){
    for(int i = 0; i < inputs; i++){
        inputLayer->writeValue(pInput->returnValue(i,0),i,0);
    }

    preHidden = weightsZero->matMult(inputLayer);
    //hiddenLayer = preHidden->applyReLu();
    hiddenLayer = preHidden->applySigmoid();

    preOutput = weightsOne->matMult(hiddenLayer);
    //outputLayer = preOutput->applyReLu();
    outputLayer = preOutput->applySigmoid();

    return outputLayer;
}

void NeuralNet::train(Matrix** pTrainInputs, Matrix** pTrainOutputs, int trainSize, int epochs, float learningRate){
    for(int i = 0; i < epochs; i++){
        for(int sampleNum = 0; sampleNum < trainSize; sampleNum++){
            //first make a guess based on train input
            guess(pTrainInputs[sampleNum]);

            //calculate gammaOne and gammaTwo

            //ReLu application
            //gammaOne = ((pTrainOutputs[sampleNum]->subtract(outputLayer))->scalarMult(-1))->simpleMult(preOutput->applyDerReLu());
            //gammaTwo = ((weightsOne->transpose())->matMult(gammaOne))->simpleMult(preHidden->applyDerReLu());

            //Sigmoid application
            gammaOne = ((pTrainOutputs[sampleNum]->subtract(outputLayer))->scalarMult(-1))->simpleMult(preOutput->applyDerSigmoid());
            gammaTwo = ((weightsOne->transpose())->matMult(gammaOne))->simpleMult(preHidden->applyDerSigmoid());

            //calculate gradient of error for weights
            errorZero = gammaTwo->matMult(inputLayer->transpose());
            errorOne = gammaOne->matMult(hiddenLayer->transpose());

            //update weights
            weightsZero = weightsZero->subtract(errorZero->scalarMult(learningRate));
            weightsOne = weightsOne->subtract(errorOne->scalarMult(learningRate));

            delete errorOne;
            delete errorZero;
            delete gammaOne;
            delete gammaTwo;
        }
    }
}

float NeuralNet::test(Matrix** pTestInputs, Matrix** pTestOutputs, float testSize){
    float correctAnswer = 0;
    
    for(int sampleNum = 0; sampleNum < testSize; sampleNum++){
        if(pTestOutputs[sampleNum]->returnBiggest() == guess(pTestInputs[sampleNum])->returnBiggest())
            correctAnswer++;
    }
    return correctAnswer/testSize;
}

std::string NeuralNet::returnWeights(){
    std::string temp;
    temp.append(weightsZero->splitOutMatrix());
    temp.append(weightsOne->splitOutMatrix());
    return temp;
}

void NeuralNet::replaceWeights(int index, Matrix* weight){
    if(index == 0) weightsZero = weight;
    else if(index == 1) weightsOne = weight;
}

void saveNeuralNet(std::string filePath, NeuralNet* net){
    std::ofstream netFile;
    netFile.open(filePath);
    netFile << net->inputs << ' ' << net->hidden << ' ' << net->outputs << '\n';
    netFile << net->returnWeights();
    netFile.close();
}

NeuralNet* loadNeuralNet(std::string filePath){

    NeuralNet* tempNet;
    Matrix* tempWeightsZero;
    Matrix* tempWeightsOne;

    std::ifstream netFile;
    netFile.open(filePath);

    std::string firstLine;
    std::getline(netFile, firstLine);
    int inputs,hidden,outputs;

    std::istringstream in(firstLine);
    in >> inputs >> hidden >> outputs;

    tempNet = new NeuralNet(inputs,hidden,outputs);

    tempWeightsZero = new Matrix(hidden+1,inputs+1);
    tempWeightsOne = new Matrix(outputs,hidden+1);

    int index = 0;
    int sizeZero = (hidden+1)*(inputs+1);
    for(std::string line; std::getline(netFile, line); ){
        std::istringstream in(line);

        float value;
        in >> value;

        if(index < sizeZero) tempWeightsZero->write1Dvalue(value,index);
        else tempWeightsOne->write1Dvalue(value,index-sizeZero);
        index++;
    }

    tempNet->replaceWeights(0,tempWeightsZero);
    tempNet->replaceWeights(1,tempWeightsOne);

    return tempNet;
}