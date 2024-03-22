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

typedef int bool32;

#if ACAMARACHI_ARCH_32BIT
    typedef unsigned int size_t;
    typedef int isize_t;
#elif ACAMARACHI_ARCH_64BIT
    typedef unsigned long long int size_t;
    typedef long long int isize_t;
#endif

typedef struct Range64 {
    u64 offset;
    u64 size;
};

typedef struct Range32 {
    u32 offset;
    u32 size;
};

static_assert(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
static_assert(sizeof(u16) == 2, "Expected u16 to be 2 byte.");
static_assert(sizeof(u32) == 4, "Expected u32 to be 4 byte.");
static_assert(sizeof(u64) == 8, "Expected u64 to be 8 byte.");
static_assert(sizeof(f32) == 4, "Expected f32 to be 4 byte."); 
static_assert(sizeof(f64) == 8, "Expected f64 to be 8 byte."); 