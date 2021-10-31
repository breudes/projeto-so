#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>  

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
    std::ifstream file(matrix_filename);
    std::string str;
    
    int line,column;

    std::getline(file, str);
    std::size_t found = str.find(" ");

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
            if(std::getline(file, str) && !(str.find("s") != string::npos)){

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

void multiplyMatrices(vector<vector<int>> &matrix_one, vector<vector<int>> &matrix_two){
}

int main(int argc, char *argv[]) {
    // matrices filename

    string M1 = "./matrix-files/";
    string M2 = "./matrix-files/";

    M1 = M1 + argv[1]; //first matrix
    M2 = M2 + argv[2]; //second matrix

    if(! (M1.find(".txt") != string::npos) )  M1 = M1 + ".txt";
    if(! (M2.find(".txt") != string::npos) )  M2 = M2 + ".txt";
        
    // read M1 values
    vector<vector<int>> first_matrix = readMatrixFromTxtFile(M1);

    // read M2 values
    vector<vector<int>> second_matrix = readMatrixFromTxtFile(M2);

    // multiply matrices
    return 0;
}