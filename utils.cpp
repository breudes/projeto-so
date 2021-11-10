#include "utils.h"

void printMatrixValues(vector<vector<int>> matrix){
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
            if(getline(file, str) && (str.find("c") != string::npos)){
                size_t found = str.find(" ");
                string valueOnStr = str.substr(found);

                stringstream valueStr(valueOnStr);
                int value = 0;
                valueStr >> value;
                vectorColumn.push_back(value);
            }
        }

        matrix.push_back(vectorColumn);
    }
    return matrix;
}

void saveMatrixOnTxtFile(vector<vector<int>> matrix, int dim_n, int dim_m, int time_result, string file_name, string algorithm) {
    string file = "./matrix-files/" + algorithm + "/" + file_name + ".txt";
    ofstream outFile(file);

    if (!outFile) {
        cout << "Arquivo " + file_name + ".txt nao pode ser aberto" << endl;
        abort();
    }
    
    outFile << dim_n << " " << dim_m << '\n';

    for (int i = 0; i < dim_n; i++) {
      for (int j = 0; j < dim_m; j++) {
        string index = "c" + to_string(i) + to_string(j);
        outFile << index << " " << matrix[i][j] << '\n';
      }
    }
    
    outFile << time_result;
}