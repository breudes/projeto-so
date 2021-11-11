// rever
#include "utils.cpp"

int getFilesNumber(int dim_n1, int dim_m2, int p) {
  int division_result, result;

  division_result = ((dim_n1 * dim_m2)/p);
  result = ceil(division_result);

  return result;
}

void createMatrixSegmentsFiles(int segments_quantity) {
  int length = segments_quantity + 1;

  if (length > 1) {
    for (int i = 1; i < length; i++) {
      string root = "./matrix-files/process/";
      string file = root + "matrix_result_seg" + to_string(i) + ".txt";
      ofstream outFile(file);
    }
  }
}

vector<vector<int>> multiplyMatrices(int partition_start, int partition_end, vector<vector<int>> matrix_one, vector<vector<int>> matrix_two) {
  vector<vector<int>> result_matrix_segment;
  
  int second_line = matrix_two.size();
  int second_column = matrix_two[0].size();

  for (int i = partition_start; i < partition_end; i++) {
    vector<int> result;

    for (int j = 0; j < second_column; j++) {
      int value = 0;

      for(int k = 0; k < second_line; k++){
        value += matrix_one[i][k] * matrix_two[k][j];
      }

      result.push_back(value);
    }

    result_matrix_segment.push_back(result);

    partition_end -= 1;
  }

  return result_matrix_segment;
}

int main(int argc, char *argv[]) {
  string first_matrix_filename, second_matrix_filename;
  vector<vector<int>> first_matrix, second_matrix, result_matrix;
  int p;

  first_matrix_filename = argv[1];
  second_matrix_filename = argv[2];
  p = atoi(argv[3]);
  
  string first_filename = "./matrix-files/" + first_matrix_filename;
  first_matrix = readMatrixFromTxtFile(first_filename);

  string second_filename = "./matrix-files/" + second_matrix_filename;
  second_matrix = readMatrixFromTxtFile(second_filename);
 
  int dim_n1 = first_matrix.size();
  int dim_m2 = second_matrix[0].size();

  int elements_quantity = dim_n1 * dim_m2;

  if (p < 1 || p > elements_quantity) {
      cout << "Digite um valor válido para p" << endl;
    } else if (p == elements_quantity) {
      multiplyMatricesSequential(first_matrix, second_matrix);
    } else {
        int segments_quantity = getFilesNumber(dim_n1, dim_m2, p);
        //createMatrixSegmentsFiles(segments_quantity);
      if (getpid() > 0) {
        for (int i = 0; i < segments_quantity; i++) {
          auto start = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
          
          pid_t pid = fork();

          if (pid == 0) {
            int partition_start = i;
            int partition_end = dim_n1;
            
            vector<vector<int>> result_matrix_segment;

            result_matrix_segment = multiplyMatrices(partition_start, partition_end, first_matrix, second_matrix);

            auto end = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
    
            auto time_result = (end - start)  * 0.000001; // tempo em millisegundos

            int dim_n = result_matrix_segment.size();
            int dim_m = result_matrix_segment[0].size();

            string segment_number = to_string(i + 1);
            string file_name = "matrix_result_seg" + segment_number;
            string algorithm = "process";

            saveMatrixOnTxtFile(dim_n1, dim_m2, result_matrix_segment, dim_n, dim_m, (i+1), time_result, file_name, algorithm);

            exit(0);
          }
        }
      }
    }

    return 0;
}