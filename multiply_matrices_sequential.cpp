#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include "utils.h"

using namespace std;

void multiplyMatrices(vector<vector<int>> matrix_one, vector<vector<int>> matrix_two){
    vector<vector<int>> matrix_result;
    
    int first_line = matrix_one.size();
    int first_column = matrix_one[0].size();

    int second_line = matrix_two.size();
    int second_column = matrix_two[0].size();

    auto start = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();

    for(int i=0; i<first_line; i++){
        vector<int> result;

        for(int j=0; j<second_column; j++){
            int value = 0;
            for(int k=0; k<second_line; k++){
                value += matrix_one[i][k]*matrix_two[k][j];
            }
            result.push_back(value);
        }
        matrix_result.push_back(result);
    }

    auto end = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
    auto time_result = (end - start) * 0.000001; //time result in milliseconds
    // write matrix on new .txt file
    saveMatrix(matrix_result, first_line, second_column, time_result, "result_matrix", "sequential");
}

int main(int argc, char *argv[]) {
    // matrices filename
    string M1 = "./matrix-files/first_matrix.txt";
    string M2 = "./matrix-files/second_matrix.txt";

    // read M1 values
    vector<vector<int>> first_matrix = readMatrixFromTxtFile(M1);
    // read M2 values
    vector<vector<int>> second_matrix = readMatrixFromTxtFile(M2);
    // multiply matrices
    multiplyMatrices(first_matrix,second_matrix);
    
    return 0;
}