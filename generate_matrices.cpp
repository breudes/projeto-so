#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void generateMatrix(vector<vector<int>> &matrix, int dim_n, int dim_m) {
    for (int i = 0; i < dim_n; i++) {
        matrix.push_back(vector<int>());
        
        for (int j = 0; j < dim_m; j++) {
            int random_number = random() % 10 + 1;
            matrix[i].push_back(random_number);
        }
    }
}

void saveMatrix(vector<vector<int>> matrix, int dim_n, int dim_m, string file_name) {
    string file = "./matrix-files/" + file_name + ".txt";
    ofstream outFile(file);

    if (!outFile) {
        cout << "Arquivo " + file_name + ".txt nao pode ser aberto" << endl;
        abort();
    }
    
    outFile << dim_n << " " << dim_m << '\n';

    for (int i = 0; i < dim_n; i++) {
      for (int j = 0; j < dim_m; j++) {
        string index = "c"+ to_string(i) + to_string(j);
        outFile << index << matrix[i][j] << '\n';
      }
    }
}

int main(int argc, char *argv[]) {
    int dim_n1, dim_m1, dim_n2, dim_m2;

    dim_n1 = atoi(argv[1]);
    dim_m1 = atoi(argv[2]);
    dim_n2 = atoi(argv[3]);
    dim_m2 = atoi(argv[4]);

    vector<vector<int>> first_matrix;
    vector<vector<int>> second_matrix;

    srand(time(NULL));

    generateMatrix(first_matrix, dim_n1, dim_m1);
    generateMatrix(second_matrix, dim_n2, dim_m2);

    saveMatrix(first_matrix, dim_n1, dim_m1, "first_matrix");
    saveMatrix(second_matrix, dim_n2, dim_m2, "second_matrix");

    return 0;
}
