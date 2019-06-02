#include "matrix.h"

Matrix::Matrix(int rows_, int cols_){
    //arr = (float*)malloc(sizeof(float) * rows_ * cols_);
    arr = new float[rows_*cols_];
    rows = rows_;
    cols = cols_;
}

void Matrix::print(){
    for(int i = 0; i < rows; i++){
        std::cout << "| ";
        for(int j = 0; j < cols; j++){
            std::cout << *val(i,j) << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

float Matrix::returnValue(int i, int j){
    if(i > rows || j > cols) throw "OUT OF BOUND OF MATRIX!";
    return arr[i*cols+j];
}

void  Matrix::writeValue(float value, int i, int j){
    if(i > rows || j > cols) throw "OUT OF BOUND OF MATRIX!";
    arr[i*cols+j] = value;
}

void Matrix::write1Dvalue(float value, int index){
    arr[index] = value;
}

float Matrix::operator()(int i, int j){
    if(i > rows || j > cols) throw "OUT OF BOUND OF MATRIX!";
    return arr[i*cols+j];
}

float* Matrix::val(int i, int j){
    if(i > rows || j > cols) throw "OUT OF BOUND OF MATRIX!";
    return &arr[i*cols+j];
}

Matrix* Matrix::add(Matrix* a){
    if(a->rows != rows || a->cols != cols)
    throw "ADDITION HAS TO BE DONE ON THE MATRICES OF THE SAME DIMENSION!";

    Matrix* temp = new Matrix(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            float value = *val(i,j) + a->returnValue(i,j);
            temp->writeValue(value,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::subtract(Matrix* a){
    if(a->rows != rows || a->cols != cols)
    throw "SUBTRACTION HAS TO BE DONE ON THE MATRICES OF THE SAME DIMENSION!";

    Matrix* temp = new Matrix(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            float value = *val(i,j) - a->returnValue(i,j);
            temp->writeValue(value,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::scalarMult(float scalar){
    Matrix* temp = new Matrix(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            float value = *val(i,j) * scalar;
            temp->writeValue(value,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::transpose(){
    Matrix* temp = new Matrix(cols,rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            temp->writeValue(*val(i,j),j,i);
        }
    }
    return temp;
}

Matrix* Matrix::simpleMult(Matrix* a){
    if(a->rows != rows || a->cols != cols)
    throw "SIMPLEMULT HAS TO BE DONE ON THE MATRICES OF THE SAME DIMENSION!";
    Matrix* temp = new Matrix(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            float value = *val(i,j) * a->returnValue(i,j);
            temp->writeValue(value,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::matMult(Matrix* a){
    if(cols != a->rows)
    throw "MATMULT WRONG DIMENSIONS!";

    Matrix* temp = new Matrix(rows,a->cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < a->cols; j++){
            float x = 0;
            for(int k = 0; k < a->rows; k++){
                x+= returnValue(i,k)*a->returnValue(k,j);
            }
            temp->writeValue(x,i,j);
        }
    }
    return temp;
}

void Matrix::fillRand(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            float r = static_cast <float> (rand() / (static_cast <float> (RAND_MAX/2))) - 1;
            writeValue(r,i,j);
        }
    }
}

Matrix* Matrix::applyReLu(){
    Matrix* temp = new Matrix(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(returnValue(i,j) > 0) temp->writeValue(returnValue(i,j),i,j);
            else temp->writeValue(0,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::applyDerReLu(){
    Matrix* temp = new Matrix(rows,cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(returnValue(i,j) >= 0) temp->writeValue(1,i,j);
            else temp->writeValue(0,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::applySigmoid(){
    Matrix* temp = new Matrix(rows,cols);
    float exponent;
    float value;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            exponent = expf(returnValue(i,j));
            value = exponent/(1+exponent);
            temp->writeValue(value,i,j);
        }
    }
    return temp;
}

Matrix* Matrix::applyDerSigmoid(){
    Matrix* temp = new Matrix(rows,cols);
    float exponent;
    float value;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            exponent = expf(returnValue(i,j));
            value = (exponent/(1+exponent))*(1-(exponent/(1+exponent)));
            temp->writeValue(value,i,j);
        }
    }
    return temp;
}

int Matrix::returnBiggest(){
    //works only for matrices nx1! return index of the biggest number
    int biggest = 0;
    for(int i = 0; i < rows; i++){
        if(returnValue(biggest,0) < returnValue(i,0)) biggest = i;
    }
    return biggest;
}

std::string Matrix::splitOutMatrix(){
    std::string temp;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            temp.append(std::to_string(returnValue(i,j)));
            temp.append("\n");
        }
    }

    return temp;
}