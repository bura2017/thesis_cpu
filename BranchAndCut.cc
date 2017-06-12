/**
 * Copyright (c) 2016 ISP RAS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BranchAndCut.h"
#include <fstream>

int num_of_probs;

static void memFree(Matrix &matrix) {
  std::cout << num_of_probs << " probs "<< std::endl;
}

void initMatrix(Matrix &matrix, const Matrix &input, taskTree * &task) {
  //std::cout << "Init new matrix..." << std::endl;
  CHECK_NULL(task);
  matrix = input;

  int cut_rows = 0;
  for (taskTree *branch = task; branch->prev != NULL; branch = branch->prev) {
    cut_rows++;
  }
  if (!cut_rows) {
    CHECK_NULL(NULL);
  }
  Matrix cuts (cut_rows, input.cols);
  cut_rows = 0;
  for (taskTree *branch = task; branch->prev != NULL; branch = branch->prev) {
    int point = branch->prev->point;
    double value = branch->prev->value;
    if (branch->num == 0) {
      cuts.e[cut_rows + point * cuts.m] = 1.0;
      cuts.e[cut_rows + 0 * cuts.m] = value;
    } else {
      cuts.e[cut_rows + point * cuts.m] = -1.0;
      cuts.e[cut_rows + 0 * cuts.m] = -(value + 1.0);
    }
    cut_rows++;
  }
  matrix.add_cuts(cuts);
}

bool branchAndCut (Matrix &input) {
  num_of_probs = 0;

  Matrix matrix (input, input.cols);

  if (cpuDualSimplex (matrix) == 0) {
    std::cout << num_of_probs << std::endl;
    return false;
  }

  taskTree *root = new taskTree;
  orderList *start_order = new orderList (root);

  if (root->branchPoint(matrix)) {
    std::cout << num_of_probs << std::endl;
    return true;
  }

  while (1) {
    num_of_probs++;
    if (num_of_probs % 10000 == 0) {
      std::cout << "bz" << std::endl;
    }

    start_order->task->branchTask();

    for (int l = 0; l < NUM_OF_DAUGHT; l++) {
      initMatrix (matrix, input, start_order->task->next[l]);
      if (cpuDualSimplex (matrix) == 0) {
        delete start_order->task->next[l];
      } else {
        if (start_order->task->next[l]->branchPoint (matrix)) {
          memFree(matrix);
          return true;
        }
        if (start_order->next == NULL) {
          start_order->next = new orderList (start_order->task->next[l]);
        } else {
          start_order->next = start_order->next->pasteTask(start_order->task->next[l]);
        }
      }
    }
    orderList *temp = start_order;
    start_order = start_order->next;
    delete temp;
    if (start_order == NULL) {
      memFree(matrix);
      return false;
    }

  }
}
