#include "utils.cpp"

int getFilesNumber(int dim_n1, int dim_m2, int p) {
  int division_result, result;

  division_result = ((dim_n1 * dim_m2)/p);
  result = ceil(division_result);

  return result;
}

void createMatrixSegmentsFiles(int files_quantity) {
  int length = files_quantity + 1;

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

void generateChildProcesses(){}

void saveSegmentFile(int segment_number, double time, vector<vector<int>> result_matrix_segment){}

int main(int argc, char *argv[]) {
  string first_matrix_filename, second_matrix_filename;
  vector<vector<int>> first_matrix, second_matrix, result_matrix;
  
  int p, dim_n1, dim_m2, files_quantity;

  // recebe os nomes dos 2 arquivos e o valor P 
  first_matrix_filename = argv[1];
  second_matrix_filename = argv[2];
  p = atoi(argv[3]);
  
  // ler matrizes dos arquivos .txt
  string first_filename = "./matrix-files/" + first_matrix_filename;
  first_matrix = readMatrixFromTxtFile(first_filename);

  string second_filename = "./matrix-files/" + second_matrix_filename;
  second_matrix = readMatrixFromTxtFile(second_filename);
 
  //printMatrixValues(first_matrix);
  //printMatrixValues(second_matrix);

  /* calcular os P elementos da matriz resultado
  cálculo: (N1*M2)/P, onde N1 é quantidade de linhas da 1a matriz e M2 é a quantidade colunas da 2a matriz */
  int N1 = first_matrix.size();
  int M2 = second_matrix[0].size();
  
  files_quantity = getFilesNumber(N1, M2, p);
  
  // cria 'files_quantity' arquivos previamente
  createMatrixSegmentsFiles(files_quantity);

  //
  if (p < 0 || p == 0) {
      cout << "Digite um valor válido para p" << endl;
    } else if (p == 1) {
      // rever esse caso
      int partition_start = 0;
      int partition_end = first_matrix.size();

      result_matrix = multiplyMatrices(partition_start, partition_end, first_matrix, second_matrix);      
    } else {
      // pai
      if (getpid() > 0) {
        // cout << "pai " << getpid() << endl;
        
        // criação de multiplos processos
        for (int i = 0; i < files_quantity; i++) {
          // iniciar contagem de tempo aqui
          auto start = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
          
          pid_t pid = fork();

          if (pid == 0) {
            // cout << "filho " << getpid() << endl;
            int partition_start = i;
            int partition_end = first_matrix.size();
            
            vector<vector<int>> result_matrix_segment;

            result_matrix_segment = multiplyMatrices(partition_start, partition_end, first_matrix, second_matrix);

            // finalizar contagem de tempo aqui
            auto end = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count();
    
            auto time_result = (end - start)  * 0.000001; // tempo em millisegundos

            // chamar função de salvar resultado e tempo no arquivo respectivo do segmento
            // passando a matriz resultado e tempo como parametros

            /*saveSegmentFile(int segment_number, double time, vector<vector<int>> result_matrix_segment)*/
            exit(0);
          }
        }
      }
    }

    return 0;
}