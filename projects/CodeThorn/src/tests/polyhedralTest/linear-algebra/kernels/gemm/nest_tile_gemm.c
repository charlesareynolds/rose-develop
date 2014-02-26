/**
 * gemm.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "gemm.h"

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int ni = 32;
  int nj = 32;
  int nk = 32;
/* Variable declaration/allocation. */
  double alpha;
  double beta;
  double C[32][32];
  double A[32][32];
  double B[32][32];
  int i;
  int j;
  int k;
  
#pragma scop
{
    int c4;
    int c2;
    int c6;
    int c3;
    int c1;
#pragma omp parallel for private(c6, c2, c4)
    for (c1 = 0; c1 <= 7; c1++) {
      for (c2 = 0; c2 <= 3; c2++) {
        for (c4 = 2 * c1; c4 <= 2 * c1 + 1; c4++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c6 = 4 * c2; c6 <= 4 * c2 + 3; c6++) {
            C[c4][c6] *= beta;
          }
        }
      }
    }
#pragma omp parallel for private(c3, c6, c2, c4)
    for (c1 = 0; c1 <= 7; c1++) {
      for (c2 = 0; c2 <= 3; c2++) {
        for (c3 = 0; c3 <= 15; c3++) {
          for (c4 = 2 * c1; c4 <= 2 * c1 + 1; c4++) {
#pragma ivdep
#pragma vector always
#pragma simd
            for (c6 = 4 * c2; c6 <= 4 * c2 + 3; c6++) {
              C[c4][c6] += alpha * A[c4][c3] * B[c3][c6];
            }
          }
        }
      }
    }
  }
  
#pragma endscop
  return 0;
}
