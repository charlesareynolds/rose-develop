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

int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int ni = NI;
  int nj = NJ;

  /* Variable declaration/allocation. */
  double alpha;
  double beta;

  double C[NI][NJ];
  double A[NI][NJ];
  double B[NI][NJ];

  int i, j, k;

#pragma scop
  /*    C := alpha*A*B' + alpha*B*A' + beta*C */
  for (i = 0; i < _PB_NI; i++)
    for (j = 0; j < _PB_NI; j++)
      C[i][j] *= beta;
  for (i = 0; i < _PB_NI; i++)
    for (j = 0; j < _PB_NI; j++)
      for (k = 0; k < _PB_NJ; k++)
	{
	  C[i][j] += alpha * A[i][k] * B[j][k];
	  C[i][j] += alpha * B[i][k] * A[j][k];
	}
#pragma endscop


  return 0;
}
