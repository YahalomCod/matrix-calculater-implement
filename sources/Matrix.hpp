#include <iostream>
#include <stdexcept>
using namespace std;
#include <vector>
#include <bits/stdc++.h>
#pragma once

namespace zich{
    class Matrix{
    public:
        int row, col;
        vector<double> mat;
        Matrix(vector<double> const &vec, int row, int col);
        void check_input(Matrix const &mat) const;
        Matrix operator + (Matrix const &mat);
        void operator += (Matrix const &mat);
        Matrix operator + (double const a);
        Matrix operator + ();
        Matrix operator++();
        Matrix operator++(int num);
        Matrix operator - (Matrix const &mat);
        void operator -= (Matrix const &mat);
        Matrix operator - (double const a);
        Matrix operator - ();
        Matrix operator -- ();
        Matrix operator--(int);

        Matrix operator * (Matrix const &mat)const;
        Matrix operator * (double const &a);

        Matrix& operator *= (double const a);
        Matrix operator *= (Matrix const &mat);

        bool operator > (Matrix const &mat)const;
        bool operator >= (Matrix const &mat)const;
        bool operator < (Matrix const &mat)const;
        bool operator <= (Matrix const &mat)const;
        bool operator == (Matrix const &mat)const;
        bool operator != (Matrix const &mat)const;

        friend Matrix operator* (double num, Matrix const &mat) {
            vector<double> ans;
            for (size_t i = 0; i < mat.col * mat.row; i++){
                ans.push_back(mat.mat[i] * num);
            }
            return Matrix(ans,  mat.row, mat.col);
        }  
    };

    inline ostream& operator << (ostream &out, const Matrix &mat){
        unsigned int count = 0 ;
        for (size_t i = 0; i < mat.row; i++){
            out << "[";
            for (size_t j = 0; j < mat.col - 1; j++){
                double val = mat.mat[count++];
                out << (val == 0.0 ? abs(val) : val)  << " ";
            }
            double val = mat.mat[count++];
            out << (val == 0.0 ? abs(val) : val)  << (i != mat.row -1 ? "]\n" : "]");
        }
        return out;
    }
    
    inline void check_str(const string str){
        int count = 0;
        for (size_t i = 0; i < str.size(); i++){
            if(str[i] == '['){
                count ++;
            }
            if(str[i] == ']'){
                count --;
            }
            if(count > 1 || count < 0){
                throw invalid_argument("Illegal Parenthesis");
            }
        }
        if(count != 0){
            throw invalid_argument("Illegal Parenthesis");
        }
        
        for (size_t i = 0; i < str.size()-2; i++){
            if(str[i] == ']'){
                if(str[i + 1] != ','){
                    throw invalid_argument("Needs to get ',' after end of each row");
                }
                else{ 
                    if(str[i + 2] != ' '){
                        throw invalid_argument("Needs to get ' ' after each ,");
                }}
            }
        }

        for (size_t i = 0; i < str.size() - 2; i++){
            if(str[i] == '['){
                i++;
                char* end;
                double temp = strtod(&str[i], &end);
                if(end != &str[i] && end[0] == ' '){//there is a number and a space after the number
                }
                else{throw invalid_argument("After each number needs to be space");}
            }
        }
    }

    inline istream& operator >> (istream &in, Matrix &mat){
        string str;
        std::getline(in >> std::ws, str);
        check_str(str);
        int rows = 0;
        for (size_t i = 0; i < str.size(); i++){
            if(str[i] == '['){
                rows ++;
            }
        }        
        string sub = str.substr(str.find("[") + 1,str.find("]") - 1);
        int cols = sub.size()/2 + 1;
        vector<double> vec;        
        stringstream stream(str);
        string word;
        double num_check =0;
        while(stream >> word) {
            num_check ++;
            size_t found_start = word.find("[");
            double temp;
            char* end;
            if (found_start != string::npos){
                temp = strtod(&word[1], &end);
            }
            else{
                temp = strtod(&word[0], &end);
            }
            vec.push_back(temp);
        }
        if(num_check != rows * cols){
            throw invalid_argument("Collumns and rows are not matching");
        }
        mat.col = cols;
        mat.row = rows;
        mat.mat = vec;
        return in;
    }
};


