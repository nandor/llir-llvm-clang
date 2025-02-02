//===----- lib/i386/fp_mode.c - Floaing-point mode utilities -----*- C -*-====//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../fp_mode.h"

#define X87_TONEAREST  0x0000
#define X87_DOWNWARD   0x0400
#define X87_UPWARD     0x0800
#define X87_TOWARDZERO 0x0c00
#define X87_RMODE_MASK (X87_TONEAREST | X87_UPWARD | X87_DOWNWARD | X87_TOWARDZERO)

FE_ROUND_MODE __fe_getround() {
  // Assume that the rounding mode state for the fpu agrees with the SSE unit.
  unsigned short cw;
  #ifdef __llir__
  __asm__ __volatile__ ("x86_fnstcw %0" : : "r" (&cw));
  #else
  __asm__ __volatile__ ("fnstcw %0" : "=m" (cw));
  #endif

  switch (cw & X87_RMODE_MASK) {
    case X87_TONEAREST:
      return FE_TONEAREST;
    case X87_DOWNWARD:
      return FE_DOWNWARD;
    case X87_UPWARD:
      return FE_UPWARD;
    case X87_TOWARDZERO:
      return FE_TOWARDZERO;
  }
  return FE_TONEAREST;
}

int __fe_raise_inexact() {
  #ifdef __llir__
  __builtin_trap();
  #else
  float f = 1.0f, g = 3.0f;
  __asm__ __volatile__ ("fdivs %1" : "+t" (f) : "m" (g));
  #endif
  return 0;
}
