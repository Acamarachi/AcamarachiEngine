#pragma once

#include <unistd.h>
#include "platform.h"

typedef char i8;
typedef unsigned char u8;

typedef short i16;
typedef unsigned short u16;

typedef int i32;
typedef unsigned int u32;

typedef long long int i64;
typedef unsigned long long int u64;

typedef float f32;
typedef double f64;

typedef int b32;
typedef bool b8;

#if ACAMARACHI_ARCH_32BIT
    typedef unsigned int size_t;
    typedef int isize_t;
#elif ACAMARACHI_ARCH_64BIT
    typedef unsigned long long int size_t;
    typedef long long int isize_t;
#endif