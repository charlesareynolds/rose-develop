/**
 * mvt.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "mvt.h"

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 32;
/* Variable declaration/allocation. */
  double A[32][32];
  double x1[32];
  double x2[32];
  double y_1[32];
  double y_2[32];
  int i;
  int j;
  
#pragma scop
{
    int c1;
    int c0;
{
      int c2;
      int c3;
      for (c2 = 0; c2 <= 31; c2++) {
        for (c3 = 0; c3 <= 31; c3++) {
          x1[c2] = x1[c2] + A[c2][c3] * y_1[c3];
          x2[c2] = x2[c2] + A[c3][c2] * y_2[c3];
        }
      }
    }
  }
  
#pragma endscop
  return 0;
}
