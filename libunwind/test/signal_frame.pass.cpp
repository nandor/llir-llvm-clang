// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// Ensure that functions marked as signal frames are reported as such.

// UNSUPPORTED: libunwind-arm-ehabi
// UNSUPPORTED: llir

#include <assert.h>
#include <stdlib.h>
#include <libunwind.h>

void test() {
  asm(".cfi_signal_frame");
  unw_cursor_t cursor;
  unw_context_t uc;
  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);
  assert(unw_step(&cursor) > 0);
  assert(unw_is_signal_frame(&cursor));
}

int main(int, char**) {
  test();
  return 0;
}
