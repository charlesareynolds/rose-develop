/**
 * syr2k.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "syr2k.h"

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int ni = 32;
  int nj = 32;
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
    int c1;
    int c0;
    int c2;
{
      int c3;
      int c4;
      int c5;
      for (c3 = 0; c3 <= 31; c3++) {
        for (c4 = 0; c4 <= 31; c4++) {
          C[c3][c4] *= beta;
          for (c5 = 0; c5 <= 31; c5++) {
            C[c3][c4] += alpha * A[c3][c5] * B[c4][c5];
            C[c3][c4] += alpha * B[c3][c5] * A[c4][c5];
          }
        }
      }
    }
  }
  
#pragma endscop
  return 0;
}
