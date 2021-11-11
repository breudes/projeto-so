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

void getMatrixValues(vector<vector<int>> matrix){
    for(int i = 0; i < matrix.size(); ++i)
    {
        for(int j = 0; j < matrix[i].size(); ++j){
            cout << matrix[i][j] << " ";
        }

        cout << "\n";
    }
}

vector<vector<int>> readMatrixFromTxtFile(string matrix_filename){
    ifstream file(matrix_filename);
    string str;
    
    int line,column;

    getline(file, str);
    size_t found = str.find(" ");

    string lineStr = str.substr(0, found);
    string columnStr = str.substr(found);

    stringstream intLine(lineStr);
    stringstream intColumn(columnStr);

    intLine >> line;
    intColumn >> column;

    vector<vector<int>> matrix;

    for(int i=0; i<line; i++){
        vector<int> vectorColumn;

        for(int j=0; j<column; j++){
            if(getline(file, str) && !(str.find("s") != string::npos)){

                stringstream valueStr(str);
                int value = 0;
                valueStr >> value;

                vectorColumn.push_back(value);
            }
        }

        matrix.push_back(vectorColumn);
    }

    return matrix;
}

void saveMatrix(vector<vector<int>> matrix, int dim_n, int dim_m, int time_result, string file_name) {
    string file = "./matrix-files/sequential/" + file_name + ".txt";
    ofstream outFile(file);

    if (!outFile) {
        cout << "Arquivo " + file_name + ".txt nao pode ser aberto" << endl;
        abort();
    }
    
    outFile << dim_n << " " << dim_m << '\n';

    for (int i = 0; i < dim_n; i++) {
      for (int j = 0; j < dim_m; j++) {
        string index = "c"+to_string(i)+to_string(j);
        outFile << index << matrix[i][j] << '\n';
      }
    }
    
    outFile << time_result << "ms";
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
    multiplyMatricesSequential(first_matrix,second_matrix);
    return 0;
}