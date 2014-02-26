/**
 * durbin.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "durbin.h"

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 32;
/* Variable declaration/allocation. */
  double y[32][32];
  double sum[32][32];
  double alpha[32];
  double beta[32];
  double r[32];
  double out[32];
  int i;
  int k;
  
#pragma scop
{
    int c2;
    int c3;
{
      int c4;
      int c5;
      y[0][0] = r[0];
      beta[0] = 1;
      alpha[0] = r[0];
      beta[1] = beta[1 - 1] - alpha[1 - 1] * alpha[1 - 1] * beta[1 - 1];
      for (c4 = 1; c4 <= 31; c4++) {
        sum[0][c4] = r[c4];
      }
      sum[0 + 1][1] = sum[0][1] + r[1 - 0 - 1] * y[0][1 - 1];
      alpha[1] = -sum[1][1] * beta[1];
      y[- 1 * 1 + 1][1] = y[- 1 * 1 + 1][1 - 1] + alpha[1] * y[1 - (- 1 * 1 + 1) - 1][1 - 1];
      y[1][1] = alpha[1];
      sum[0 + 1][2] = sum[0][2] + r[2 - 0 - 1] * y[0][2 - 1];
      sum[1 + 1][2] = sum[1][2] + r[2 - 1 - 1] * y[1][2 - 1];
      beta[2] = beta[2 - 1] - alpha[2 - 1] * alpha[2 - 1] * beta[2 - 1];
      alpha[2] = -sum[2][2] * beta[2];
      y[- 1 * 2 + 2][2] = y[- 1 * 2 + 2][2 - 1] + alpha[2] * y[2 - (- 1 * 2 + 2) - 1][2 - 1];
      y[2][2] = alpha[2];
      y[- 1 * 2 + 3][2] = y[- 1 * 2 + 3][2 - 1] + alpha[2] * y[2 - (- 1 * 2 + 3) - 1][2 - 1];
      for (c4 = 3; c4 <= 31; c4++) {
        sum[0 + 1][c4] = sum[0][c4] + r[c4 - 0 - 1] * y[0][c4 - 1];
        sum[1 + 1][c4] = sum[1][c4] + r[c4 - 1 - 1] * y[1][c4 - 1];
        beta[c4] = beta[c4 - 1] - alpha[c4 - 1] * alpha[c4 - 1] * beta[c4 - 1];
        for (c5 = 2; c5 <= c4 + -1; c5++) {
          sum[c5 + 1][c4] = sum[c5][c4] + r[c4 - c5 - 1] * y[c5][c4 - 1];
        }
        alpha[c4] = -sum[c4][c4] * beta[c4];
        y[- 1 * c4 + c4][c4] = y[- 1 * c4 + c4][c4 - 1] + alpha[c4] * y[c4 - (- 1 * c4 + c4) - 1][c4 - 1];
        y[c4][c4] = alpha[c4];
        for (c5 = c4 + 1; c5 <= 2 * c4 + -1; c5++) {
          y[- 1 * c4 + c5][c4] = y[- 1 * c4 + c5][c4 - 1] + alpha[c4] * y[c4 - (- 1 * c4 + c5) - 1][c4 - 1];
        }
      }
      for (c4 = 0; c4 <= 31; c4++) {
        out[c4] = y[c4][32 - 1];
      }
    }
  }
  
#pragma endscop
  return 0;
}
