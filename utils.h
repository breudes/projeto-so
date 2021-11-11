#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <cmath>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void printMatrixValues(vector<vector<int>> matrix);
vector<vector<int>> readMatrixFromTxtFile(string matrix_filename);
void saveMatrixOnTxtFile(int dim_n_original, int dim_m_original, vector<vector<int>> matrix, int dim_n, int dim_m, int segment_number,double time_result, string file_name, string algorithm);
void multiplyMatricesSequential(vector<vector<int>> matrix_one, vector<vector<int>> matrix_two);