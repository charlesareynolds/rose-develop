/**
 * fdtd-2d.c: This file is part of the PolyBench/C 3.2 test suite.
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
/* Default data type is double, default size is 50x1000x1000. */
#include "fdtd-2d.h"

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int tmax = 2;
  int nx = 32;
  int ny = 32;
/* Variable declaration/allocation. */
  double ex[32][32];
  double ey[32][32];
  double hz[32][32];
  double _fict_[2];
  int t;
  int i;
  int j;
  
#pragma scop
{
    int c2;
    int c3;
    int c4;
    int c0;
    for (c0 = 0; c0 <= 8; c0++) {
      for (c2 = 1; c2 <= 32; c2++) {
        if (c0 <= 7 && c2 == 1) {
          for (c4 = (1 > 4 * c0?1 : 4 * c0); c4 <= 4 * c0 + 3; c4++) {
            ey[1][c4 + -1] = ey[1][c4 + -1] - 0.5 * (hz[1][c4 + -1] - hz[1 - 1][c4 + -1]);
            ex[0][c4] = ex[0][c4] - 0.5 * (hz[0][c4] - hz[0][c4 - 1]);
            ey[0][c4 + -1] = _fict_[0];
            hz[0][c4 + -1] = hz[0][c4 + -1] - 0.7 * (ex[0][c4 + -1 + 1] - ex[0][c4 + -1] + ey[0 + 1][c4 + -1] - ey[0][c4 + -1]);
          }
        }
        if (c0 == 8 && c2 == 1) {
          ey[1][31] = ey[1][31] - 0.5 * (hz[1][31] - hz[1 - 1][31]);
          ey[0][31] = _fict_[0];
        }
        if (c2 == 1) {
          if (c0 == 0) {
            ey[0][0] = _fict_[1];
          }
          for (c4 = (2 > 4 * c0?2 : 4 * c0); c4 <= ((32 < 4 * c0 + 3?32 : 4 * c0 + 3)); c4++) {
            ex[0][c4 + -1] = ex[0][c4 + -1] - 0.5 * (hz[0][c4 + -1] - hz[0][c4 + -1 - 1]);
            ey[0][c4 + -1] = _fict_[1];
          }
        }
        if (c0 == 8 && c2 >= 2 && c2 <= 31) {
          ey[c2][31] = ey[c2][31] - 0.5 * (hz[c2][31] - hz[c2 - 1][31]);
        }
        if (c0 <= 7 && c2 == 32) {
          for (c4 = (1 > 4 * c0?1 : 4 * c0); c4 <= 4 * c0 + 3; c4++) {
            ex[31][c4] = ex[31][c4] - 0.5 * (hz[31][c4] - hz[31][c4 - 1]);
          }
        }
        if (c2 >= 2) {
          for (c3 = (((0 > 4 * c0 + -31?0 : 4 * c0 + -31)) > c2 + -31?((0 > 4 * c0 + -31?0 : 4 * c0 + -31)) : c2 + -31); c3 <= 1; c3++) {
            if (c0 == 0 && c3 == 1) {
              ey[c2 + -1][0] = ey[c2 + -1][0] - 0.5 * (hz[c2 + -1][0] - hz[c2 + -1 - 1][0]);
            }
            for (c4 = (4 * c0 > c3 + 1?4 * c0 : c3 + 1); c4 <= ((4 * c0 + 3 < c3 + 31?4 * c0 + 3 : c3 + 31)); c4++) {
              ey[c2 + -1 * c3][c4 + -1] = ey[c2 + -1 * c3][c4 + -1] - 0.5 * (hz[c2 + -1 * c3][c4 + -1] - hz[c2 + -1 * c3 - 1][c4 + -1]);
              ex[c2 + -1][-1 * c3 + c4] = ex[c2 + -1][-1 * c3 + c4] - 0.5 * (hz[c2 + -1][-1 * c3 + c4] - hz[c2 + -1][-1 * c3 + c4 - 1]);
              hz[c2 + -1 * c3 + -1][-1 * c3 + c4 + -1] = hz[c2 + -1 * c3 + -1][-1 * c3 + c4 + -1] - 0.7 * (ex[c2 + -1 * c3 + -1][-1 * c3 + c4 + -1 + 1] - ex[c2 + -1 * c3 + -1][-1 * c3 + c4 + -1] + ey[c2 + -1 * c3 + -1 + 1][-1 * c3 + c4 + -1] - ey[c2 + -1 * c3 + -1][-1 * c3 + c4 + -1]);
            }
          }
        }
      }
    }
  }
  
#pragma endscop
  return 0;
}
