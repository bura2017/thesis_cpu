#include "Matrix.h"
#include "HandleError.h"
#include "BranchAndCut.h"
#include "CudaDeviceProperties.h"
#include "GenTest.h"
#include "Epsilon.h"
#include "TimeCpu.h"

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>

int flag;

int main (int argc, char **argv) {

  std::ofstream results("Results.txt");

  for (int i = 100; i < 801; i += 10) {
    double cpu_time = 0.0;
    int test_num = 0;
    flag = time(NULL);
    while (test_num < 5) {
      int vars = 100;
      int ineqs = 100;

      gen_test(test_num, vars, ineqs, flag);

      char filename[MAX_LENG];
      sprintf(filename, "Vars-%d_Ineqs-%d_%d.ilp", vars, ineqs, test_num);

      char fullname[MAX_LENG];
      sprintf(fullname, "/home/valerius/cuda-workspace/Benchmarks_txt/TestGenerator/%s", filename);

      Matrix input(fullname);

      double time;
      cmp ((double) input.cols, (double) input.rows);

      //====================BRANCH AND BOUND========================

      {
        Matrix matrix(input);
        time = mtime();
        int cpu_probs = branchAndBound(matrix);
        //std::cout << cpu_probs << std::endl;
        time = mtime() - time;
        if (cpu_probs > 0) {
          cpu_time += time / cpu_probs;
        } else {
          cpu_time -= time / cpu_probs;
        }
        std::cout << " time " << time << std::endl << std::endl;
      }/**/
      test_num++;
      return 0;
    }
  }
}
