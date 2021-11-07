#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>

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

vector<vector<int>> multiplyMatrices(vector<vector<int>> matrix_one, vector<vector<int>> matrix_two){
    vector<vector<int>> matrix_result;
    
    int first_line = matrix_one.size();
    int first_column = matrix_one[0].size();

    int second_line = matrix_two.size();
    int second_column = matrix_two[0].size();

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

    return matrix_result;
}

void saveMatrix(vector<vector<int>> matrix, int dim_n, int dim_m, string file_name) {
    string file = "./matrix-files/sequential" + file_name + ".txt";
    ofstream outFile(file);

    if (!outFile) {
        cout << "Arquivo " + file_name + ".txt nao pode ser aberto" << endl;
        abort();
    }
    
    outFile << dim_n << " " << dim_m << '\n';

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < dim_n; i++) {
      for (int j = 0; j < dim_m; j++) {
        outFile << matrix[i][j] << '\n';
      }
    }

    auto end = chrono::high_resolution_clock::now();
    auto diff = chrono::duration_cast<std::chrono::nanoseconds> (end - start);

    auto time_result = (diff * 1e-9); //time result in seconds
    
    outFile << time_result.count() << "s";
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
    vector<vector<int>> result = multiplyMatrices(first_matrix,second_matrix);
    // write matrix on new .txt file
    saveMatrix(result, result.size(), result[0].size(), "result_matrix");
    return 0;
}