// Copyright 2021 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "include/v8config.h"
#include "src/trap-handler/trap-handler-simulator.h"

#if V8_OS_MACOSX
#define SYMBOL(name) "_" #name
#else  // !V8_OS_MACOSX
#define SYMBOL(name) #name
#endif  // !V8_OS_MACOSX

// Define the ProbeMemory function declared in trap-handler-simulators.h.
asm(
    ".globl " SYMBOL(ProbeMemory) "                 \n"
    SYMBOL(ProbeMemory) ":                          \n"
    // First parameter (address) passed in %rdi.
    // The second parameter (pc) is unused here. It is read by the trap handler
    // instead.
    "  movb (%rdi), %al                             \n"
    // Return 0 on success.
    "  xorl %eax, %eax                              \n"
    "  ret                                          \n"
    ".globl " SYMBOL(v8_probe_memory_continuation) "\n"
    SYMBOL(v8_probe_memory_continuation) ":         \n"
    // If the trap handler continues here, it wrote the landing pad in %rax.
    "  ret                                          \n");
