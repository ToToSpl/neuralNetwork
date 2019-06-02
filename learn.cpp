#include <stdlib.h>
#include <iostream>
#include <string>

#include "matrix.h"
#include "neural.h"


using namespace std;

#define DATASIZE 60000
#define BATCHSIZE 50

int main(){

    
    Matrix** testSetIn = new Matrix*[BATCHSIZE];
    Matrix** testSetOut = new Matrix*[BATCHSIZE];
    ifstream imFile;
    imFile.open("./trainData/images.txt");

    ifstream lbFile("./trainData/labels.txt",ios_base::in);

    NeuralNet* myNet = new NeuralNet(28*28,28,10);

    float value = 0;
    float fastTest = 0;
    int number = 0;
    string imLine;
    for(int k = 0; k < DATASIZE/BATCHSIZE; k++){
        for(int j = 0; j < BATCHSIZE; j++){
            getline(imFile,imLine);
            istringstream in(imLine);

            testSetOut[j] = new Matrix(10,1);
            lbFile >> number;
            for(int i = 0; i < 10; i++){
                if(i == number) testSetOut[j]->writeValue(1,i,0);
                else testSetOut[j]->writeValue(0,i,0);
            }

            testSetIn[j] = new Matrix(28*28,1);
            for(int i = 0; i < 28*28; i++){
                in >> value;
                testSetIn[j]->writeValue(value/255.0,i,0);
            }
        }

        myNet->train(testSetIn,testSetOut,BATCHSIZE,1,0.15);
        fastTest = myNet->test(testSetIn,testSetOut,BATCHSIZE);
        cout << "Batch no: " << k << " accuracy: " << fastTest << endl;

        for(int j = 0; j < BATCHSIZE; j++){
            delete testSetIn[j];
            delete testSetOut[j];
        }
    }

    saveNeuralNet("textRec.net",myNet);







    return 0;
}