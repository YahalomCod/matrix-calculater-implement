#include <iostream>
#include <stdexcept>
#include "Matrix.hpp"
#include <vector>
#include <string>
using namespace std;
using namespace zich;
double const EPS = 0.000005; 
Matrix::Matrix(vector<double> const &vec, int row, int col){
    if (col * row != vec.size()){
        throw invalid_argument("Size of vector needs to be the multiplication outcome of rows and columns");
    }
    if(col < 1 || row < 1){
        throw invalid_argument("Size cannont be negative");
    }
    this->col = col;
    this->mat = vec;
    this->row = row;
    
}

Matrix Matrix::operator+(Matrix const &mat)
{
    this->check_input(mat);
    vector<double> ans;
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        ans.push_back(this->mat[i] + mat.mat[i]);
    }

    return Matrix(ans, this->row, this->col);
}

void Matrix::operator+=(Matrix const &mat)
{
    this->check_input(mat);
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        this->mat[i] += mat.mat[i];
    }
}

Matrix Matrix::operator+(double const a)
{
    vector<double> ans;
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        ans.push_back(this->mat[i] + a);
    }
    return Matrix(ans, this->row, this->col);
}

Matrix Matrix::operator+() { return *this; }

Matrix Matrix::operator++(int){
    Matrix temp(*this);
    ++(*this);
    return temp;
}

Matrix Matrix::operator++()
{
    for (size_t i = 0; i < this->row * this->col; i++){
        this->mat[i]++;
    }
    return *this;
}

Matrix Matrix::operator-(Matrix const &mat)
{
    this->check_input(mat);
    vector<double> ans;
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        ans.push_back(this->mat[i] - mat.mat[i]);
    }
    return Matrix(ans, this->row, this->col);
}

void Matrix::operator-=(Matrix const &mat)
{
    this->check_input(mat);
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        this->mat[i] -= mat.mat[i];
    }
}

Matrix Matrix::operator-(double const a)
{
    vector<double> ans;
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        ans.push_back(this->mat[i] - a);
    }
    return Matrix(ans, this->row, this->col);
}



Matrix Matrix::operator-()
{
    Matrix ans(*this);
    for (size_t i = 0; i < this->row * this->col; i++){
        ans.mat[i] = -ans.mat[i];
    }
    return ans;
}

Matrix Matrix::operator--(int){
    Matrix temp(*this);
    --(*this);
    return temp;
}

Matrix Matrix::operator--()
{
    for (size_t i = 0; i < this->row * this->col; i++)
    {
        this->mat[i]--;
    }
    return *this;
}

double helper(unsigned int row, unsigned int col, Matrix const &mat1, Matrix const &mat2)
{
    double ans = 0;
    for (size_t i = 0; i < mat1.col; i++){
        ans += (mat1.mat[i + ((unsigned int)mat1.col * row)] * mat2.mat[(i * (unsigned int)mat2.col) + col]);
    }
    return ans;
}
Matrix Matrix::operator*(const Matrix &mat)const
{
    if (this->col != mat.row){
        throw invalid_argument("Can't multiple the given matrixes");
    }
    vector<double> ans;
    for (size_t i = 0; i < this->row; i++){
        double temp = 0;
        for (size_t j = 0; j < mat.col; j++){
            temp = helper(i, j, *this, mat);
            ans.push_back(temp);
        }
    }
    return Matrix(ans, this->row, mat.col);
}

Matrix Matrix::operator*(double const &a) { 
    vector<double> ans;
    for (size_t i = 0; i < this->mat.size(); i++){
        ans.push_back(this->mat[i]*a);
    }
    return Matrix(ans, this->row, this->col); 
    }

Matrix& Matrix::operator*= (double const a) {
    return (*this = *this * a);
}

Matrix Matrix ::operator *= (Matrix const &mat){
    return (*this = *this * mat);    
}

double sum(Matrix mat){
    double ans = 0;
    for (size_t i = 0; i < mat.mat.size(); i++){
        ans += mat.mat[i];
    }
    if(ans < EPS){
        ans = 0;
    }
    return ans;
}
bool Matrix::operator>(Matrix const &mat)const{
    this->check_input(mat);
    return sum(*this) > sum(mat);
}

bool Matrix::operator>=(Matrix const &mat)const{
    this->check_input(mat);
    return sum(*this) >= sum(mat);
}

bool Matrix::operator<(Matrix const &mat)const{
    this->check_input(mat);
    return sum(*this) < sum(mat);
}

bool Matrix::operator<=(Matrix const &mat)const{
    this->check_input(mat);
    return sum(*this) <= sum(mat);
}

bool Matrix::operator==(Matrix const &mat)const{
    this->check_input(mat);
    for (size_t i = 0; i < this->mat.size(); i++)
    {
        if(this->mat[i] != mat.mat[i]){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix const &mat)const{
    this->check_input(mat);
    return !(*this == mat);
}

void Matrix::check_input(Matrix const &mat) const{
    if (this->col != mat.col || this->row != mat.row){
        throw invalid_argument("Size of matrixes is different");
    }
}
