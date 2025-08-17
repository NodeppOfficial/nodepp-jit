/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_JIT_DLL
#define NODEPP_JIT_DLL

/*────────────────────────────────────────────────────────────────────────────*/

#if   _KERNEL_ == NODEPP_KERNEL_WINDOWS
#include <nodepp/fs.h>
#include "windows/dll.cpp"
#elif _KERNEL_ == NODEPP_KERNEL_POSIX
#include <dlfcn.h>
#include <nodepp/fs.h>
#include "posix/dll.cpp"
#else
#error "This OS Does not support dll.h"
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/