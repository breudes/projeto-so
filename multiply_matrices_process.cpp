#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>

using namespace std;

vector<vector<int>> readMatrixFromTxtFile(string matrix_filename, int* dim_n1 = NULL, int* dim_m2 = NULL) {
    string str, file_name;

    file_name = "./matrix-files/" + matrix_filename;
    ifstream file(file_name);

    getline(file, str);
    size_t found = str.find(" ");

    string lineStr = str.substr(0, found);
    string columnStr = str.substr(found);

    stringstream intLine(lineStr);
    stringstream intColumn(columnStr);

    int line, column;

    intLine >> line;
    intColumn >> column;

    if (dim_n1 != NULL) {
        *dim_n1 = line;
    }

    if (dim_m2 != NULL) {
        *dim_n1 = column;
    }

    vector<vector<int>> matrix;

    for (int i = 0; i < line; i++) {
        vector<int> vectorColumn;

        for (int j=0; j<column; j++) {
            if (getline(file, str) && !(str.find("s") != string::npos)) {

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

int getFilesNumber(int dim_n1, int dim_m2, int p) {
    int division_result, result;

    division_result = ((dim_n1 * dim_m2)/p);
    result = ceil(division_result);

    return result;
}

void createMatrixSegmentsFiles(int files_quantity) {
    int length = files_quantity + 1;

    for (int i = 1; i < length; i++) {
        string root = "./matrix-files/process";
        string file = root + "seg" + to_string(i) + ".txt";

        ofstream outFile(file);
    }
}

int main(int argc, char *argv[]) {
    string first_matrix_file, second_matrix_file;
    vector<vector<int>> first_matrix, second_matrix;
    int p, dim_n1, dim_m2, files_quantity;

    first_matrix_file = argv[1];
    second_matrix_file = argv[2];
    p = atoi(argv[3]);

    first_matrix = readMatrixFromTxtFile(first_matrix_file, &dim_n1);
    second_matrix = readMatrixFromTxtFile(second_matrix_file, &dim_m2);

    files_quantity = getFilesNumber(dim_n1, dim_m2, p);

    createMatrixSegmentsFiles(files_quantity);
   
    return 0;
}