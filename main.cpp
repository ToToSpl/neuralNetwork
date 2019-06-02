#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

#include "matrix.h"
#include "neural.h"


using namespace std;

int main(){

    Matrix* testIm = new Matrix(28*28,1);
    ifstream imFile;
    string imLine;
    imFile.open("./testData/images.txt");

    srand(time(NULL));
    int r = rand()%10000;
    for(int i = 0; i < r; i++) getline(imFile,imLine);

    istringstream in(imLine);

    float value;
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            in >> value;
            if(value != 0) cout << '@';
            else cout << ' ';
            testIm->write1Dvalue(value/255,i*28+j);
        }
        cout << endl;
    }

    NeuralNet* myNet = loadNeuralNet("textRec.net");

    int guessNum = myNet->guess(testIm)->returnBiggest();

    cout << "Guessed number by neural net: " << guessNum << endl;

    return 0;
}