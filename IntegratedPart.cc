#include "Matrix.h"
#include "HandleError.h"
#include "BranchAndCut.h"
#include "Time.h"

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>

int flag;

int main (int argc, char **argv) {
  int test_num = 0;
  flag = time(NULL);
  //std::cout << flag << std::endl;

  while (test_num < 10) {
    const int vars = 200;
    const int ineqs = 300;

    //gen_test(test_num, vars, ineqs, flag);

    char filename[MAX_LENG];
    //strcpy (filename, test_files[test_num]);
    sprintf(filename, "Vars-%d_Ineqs-%d_%d.ilp", vars, ineqs, test_num);
    //std::cout << filename << std::endl;
    //std::cin >> filename;
    if (filename[0] == '0') {
      return 0;
    }

    char fullname[MAX_LENG];
    sprintf(fullname, "/home/valerius/cuda-workspace/Benchmarks_txt/TestGenerator/Type1/%s", filename);
    //sprintf(fullname, "TestGenerator/%s", filename);

    Matrix input(fullname);

    //Simplex testing
    {
      int iters_man = 0;
      /*{
        Matrix matrix(input);
        int iters_cpu = cpuDualSimplex (matrix);
        iters_man = iters_cpu;
        std::cout << iters_man << std::endl;
        if (iters_cpu != iters_man) {
          std::cout << iters_cpu << " != " << iters_man << std::endl;
          std::cout << "ERROR wrong answer cpu" << std::endl;
        }
      }/**/

    }

    //BranchAndCut testing
    {
      double t = mtime();
      std::cout << (branchAndCut(input) ? "sat" : "unsat") << std::endl;
      t = mtime() - t;
      std::cout << "time " << t << std::endl;
    }/**/

    test_num++;
    return 0;
  }

}
