; RUN: llc -mtriple=llir_x86_64 -verify-machineinstrs < %s | FileCheck %s

; Test that wasm select instruction is selected from LLVM select instruction.

; CHECK-LABEL: select_i32_bool:
; CHECK-NEXT:  .args i8:zext, i32, i32
; CHECK-NEXT:  .call c
define i32 @select_i32_bool(i1 zeroext %a, i32 %b, i32 %c) {
  %cond = select i1 %a, i32 %b, i32 %c
  ret i32 %cond
}

; CHECK-LABEL: select_i32_eq:
; CHECK-NEXT:  .args i32, i32, i32
; CHECK-NEXT:  .call c
define i32 @select_i32_eq(i32 %a, i32 %b, i32 %c) {
  %cmp = icmp eq i32 %a, 0
  %cond = select i1 %cmp, i32 %b, i32 %c
  ret i32 %cond
}

; CHECK-LABEL: select_i32_ne:
; CHECK-NEXT:  .args i32, i32, i32
; CHECK-NEXT:  .call c
define i32 @select_i32_ne(i32 %a, i32 %b, i32 %c) {
  %cmp = icmp ne i32 %a, 0
  %cond = select i1 %cmp, i32 %b, i32 %c
  ret i32 %cond
}

; CHECK-LABEL: select_i64_bool:
; CHECK-NEXT:  .args i8:zext, i64, i64
; CHECK-NEXT:  .call c
define i64 @select_i64_bool(i1 zeroext %a, i64 %b, i64 %c) {
  %cond = select i1 %a, i64 %b, i64 %c
  ret i64 %cond
}

; CHECK-LABEL: select_i64_eq:
; CHECK-NEXT:  .args i32, i64, i64
; CHECK-NEXT:  .call c
define i64 @select_i64_eq(i32 %a, i64 %b, i64 %c) {
  %cmp = icmp eq i32 %a, 0
  %cond = select i1 %cmp, i64 %b, i64 %c
  ret i64 %cond
}

; CHECK-LABEL: select_i64_ne:
; CHECK-NEXT:  .args i32, i64, i64
; CHECK-NEXT:  .call c
define i64 @select_i64_ne(i32 %a, i64 %b, i64 %c) {
  %cmp = icmp ne i32 %a, 0
  %cond = select i1 %cmp, i64 %b, i64 %c
  ret i64 %cond
}
