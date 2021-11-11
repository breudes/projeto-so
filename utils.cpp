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

void multiplyMatricesSequential(vector<vector<int>> matrix_one, vector<vector<int>> matrix_two) {
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
    
    auto time_result = ((end - start) * 0.000001);

    // write matrix on new .txt file
    saveMatrixOnTxtFile(first_line, second_column, matrix_result, first_line, second_column, 0, time_result, "result_matrix","sequential");
}

void saveMatrixOnTxtFile(int dim_n_original, int dim_m_original, vector<vector<int>> matrix, int dim_n, int dim_m, int segment_number, double time_result, string file_name, string algorithm) {
    string file = "./matrix-files/" + algorithm + "/" + file_name + ".txt";
    ofstream outFile(file);

    if (!outFile) {
        cout << "Arquivo " + file_name + ".txt nao pode ser aberto" << endl;
        abort();
    }
    
    outFile << dim_n_original << " " << dim_m_original << '\n';

    if(segment_number>=0){

      int values[(dim_n*dim_m)]; 
      int k = 0;

      for (int i = 0; i < dim_n; i++) {
        for (int j = 0; j < dim_m; j++) {
          values[k] = matrix[i][j];
          cout << values[k];
          k++;
        }
      }

      int m=0;
      for (int i=0; i<dim_n_original; i++){
        for (int j=0; j<dim_m_original; j++){
          
          string index = "c" + to_string(i) + to_string(j);
          if(i == (segment_number-1)){
            cout << m << "       JESUS\n" ;
            outFile << index << " " << values[m] << '\n';
          } else {
            outFile << index << " " << "0" << '\n';
          }

          m++;
        }

        m=0;
      }
      
    } else {

      for (int i = 0; i < dim_n; i++) {
        for (int j = 0; j < dim_m; j++) {
          string index = "c" + to_string(i) + to_string(j);
          outFile << index << " " << matrix[i][j] << '\n';
        }
      }
      
    }
    
    outFile << time_result;
}