#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
    private:
        float *arr;
        float* val(int i, int j);
    public:
        int rows;
        int cols;

        Matrix(int rows, int cols);
        ~Matrix(){delete[] arr;};
        float returnValue(int i, int j);
        void writeValue(float value, int i, int j);
        void write1Dvalue(float value, int index);
        float operator()(int i,int k);
        void print();
        Matrix* add(Matrix* a);
        Matrix* subtract(Matrix* a);
        Matrix* scalarMult(float scalar);
        Matrix* transpose();
        Matrix* simpleMult(Matrix* a);
        Matrix* matMult(Matrix* a);
        Matrix* applyReLu();
        Matrix* applyDerReLu();
        Matrix* applySigmoid();
        Matrix* applyDerSigmoid();
        void fillRand();
        int returnBiggest();
        std::string splitOutMatrix();
};

#endif