/**
 * covariance.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "covariance.h"

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 32;
  int m = 32;
  double float_n = 1.2;
  double data[m][n];
  double symmat[m][n];
  double mean[m];
  int i;
  int j;
  int j1;
  int j2;
  
#pragma scop
{
    int c3;
    int c2;
    int c6;
    int c1;
    int c5;
#pragma omp parallel for private(c5, c6, c2)
    for (c1 = 0; c1 <= 15; c1++) {
      for (c2 = ((c1 + -1) * 2 < 0?-(-(c1 + -1) / 2) : ((2 < 0?(-(c1 + -1) + - 2 - 1) / - 2 : (c1 + -1 + 2 - 1) / 2))); c2 <= 7; c2++) {
        for (c5 = (2 * c1 > 4 * c2?2 * c1 : 4 * c2); c5 <= 4 * c2 + 3; c5++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c6 = 2 * c1; c6 <= ((c5 < 2 * c1 + 1?c5 : 2 * c1 + 1)); c6++) {
            symmat[c6][c5] = 0.0;
          }
        }
      }
    }
#pragma omp parallel for private(c6)
    for (c1 = 0; c1 <= 15; c1++) {
#pragma ivdep
#pragma vector always
#pragma simd
      for (c6 = 2 * c1; c6 <= 2 * c1 + 1; c6++) {
        mean[c6] = 0.0;
      }
    }
#pragma omp parallel for private(c5, c6, c2)
    for (c1 = 0; c1 <= 15; c1++) {
      for (c2 = 0; c2 <= 7; c2++) {
        for (c5 = 4 * c2; c5 <= 4 * c2 + 3; c5++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c6 = 2 * c1; c6 <= 2 * c1 + 1; c6++) {
            mean[c6] += data[c5][c6];
          }
        }
      }
    }
#pragma omp parallel for private(c6)
    for (c1 = 0; c1 <= 15; c1++) {
#pragma ivdep
#pragma vector always
#pragma simd
      for (c6 = 2 * c1; c6 <= 2 * c1 + 1; c6++) {
        mean[c6] /= float_n;
      }
    }
#pragma omp parallel for private(c5, c6, c2)
    for (c1 = 0; c1 <= 15; c1++) {
      for (c2 = 0; c2 <= 7; c2++) {
        for (c5 = 4 * c2; c5 <= 4 * c2 + 3; c5++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c6 = 2 * c1; c6 <= 2 * c1 + 1; c6++) {
            data[c6][c5] -= mean[c5];
          }
        }
      }
    }
#pragma omp parallel for private(c5, c6, c2, c3)
    for (c1 = 0; c1 <= 15; c1++) {
      for (c2 = ((c1 + -1) * 2 < 0?-(-(c1 + -1) / 2) : ((2 < 0?(-(c1 + -1) + - 2 - 1) / - 2 : (c1 + -1 + 2 - 1) / 2))); c2 <= 7; c2++) {
        for (c3 = 0; c3 <= 31; c3++) {
          for (c5 = (2 * c1 > 4 * c2?2 * c1 : 4 * c2); c5 <= 4 * c2 + 3; c5++) {
#pragma ivdep
#pragma vector always
#pragma simd
            for (c6 = 2 * c1; c6 <= ((c5 < 2 * c1 + 1?c5 : 2 * c1 + 1)); c6++) {
              symmat[c6][c5] += data[c3][c6] * data[c3][c5];
            }
          }
        }
      }
    }
#pragma omp parallel for private(c5, c6, c2)
    for (c1 = 0; c1 <= 15; c1++) {
      for (c2 = ((c1 + -1) * 2 < 0?-(-(c1 + -1) / 2) : ((2 < 0?(-(c1 + -1) + - 2 - 1) / - 2 : (c1 + -1 + 2 - 1) / 2))); c2 <= 7; c2++) {
        for (c5 = (2 * c1 > 4 * c2?2 * c1 : 4 * c2); c5 <= 4 * c2 + 3; c5++) {
#pragma ivdep
#pragma vector always
#pragma simd
          for (c6 = 2 * c1; c6 <= ((c5 < 2 * c1 + 1?c5 : 2 * c1 + 1)); c6++) {
            symmat[c5][c6] = symmat[c6][c5];
          }
        }
      }
    }
  }
  
#pragma endscop
  return 0;
}
