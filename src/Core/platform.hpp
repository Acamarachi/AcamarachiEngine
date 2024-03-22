//
// Copyright 2018 Sepehr Taghdisian (septag@github). All rights reserved.
// License: https://github.com/septag/sx#license-bsd-2-clause
//
// parts of this code is copied from bx library: https://github.com/bkaradzic/bx
// Copyright 2011-2019 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bx#license-bsd-2-clause
//
// platform.h - v1.0 - Platform preprocessor definitions
//					   Contains processor/arch/compiler/os definitions for different platforms
//
// Another useful reference: https://sourceforge.net/p/predef/wiki/Home/
//
// Copied from sx library: https://github.com/septag/sx
// Changes:
//      Replaced SX with ACAMARACHI
#pragma once

// Architecture
#define ACAMARACHI_ARCH_32BIT 0
#define ACAMARACHI_ARCH_64BIT 0

// Compiler
#define ACAMARACHI_COMPILER_CLANG 0
#define ACAMARACHI_COMPILER_CLANG_ANALYZER 0
#define ACAMARACHI_COMPILER_CLANG_CL 0
#define ACAMARACHI_COMPILER_GCC 0
#define ACAMARACHI_COMPILER_MSVC 0

// Endianess
#define ACAMARACHI_CPU_ENDIAN_BIG 0
#define ACAMARACHI_CPU_ENDIAN_LITTLE 0

// CPU
#define ACAMARACHI_CPU_ARM 0
#define ACAMARACHI_CPU_JIT 0
#define ACAMARACHI_CPU_MIPS 0
#define ACAMARACHI_CPU_PPC 0
#define ACAMARACHI_CPU_RISCV 0
#define ACAMARACHI_CPU_X86 0

// C Runtime
#define ACAMARACHI_CRT_BIONIC 0
#define ACAMARACHI_CRT_GLIBC 0
#define ACAMARACHI_CRT_LIBCXX 0
#define ACAMARACHI_CRT_MINGW 0
#define ACAMARACHI_CRT_MSVC 0
#define ACAMARACHI_CRT_NEWLIB 0

#ifndef ACAMARACHI_CRT_MUSL
#    define ACAMARACHI_CRT_MUSL 0
#endif    // ACAMARACHI_CRT_MUSL

#ifndef ACAMARACHI_CRT_NONE
#    define ACAMARACHI_CRT_NONE 0
#endif    // ACAMARACHI_CRT_NONE

// Platform
#define ACAMARACHI_PLATFORM_ANDROID 0
#define ACAMARACHI_PLATFORM_BSD 0
#define ACAMARACHI_PLATFORM_EMSCRIPTEN 0
#define ACAMARACHI_PLATFORM_HURD 0
#define ACAMARACHI_PLATFORM_IOS 0
#define ACAMARACHI_PLATFORM_LINUX 0
#define ACAMARACHI_PLATFORM_NX 0
#define ACAMARACHI_PLATFORM_OSX 0
#define ACAMARACHI_PLATFORM_PS4 0
#define ACAMARACHI_PLATFORM_RPI 0
#define ACAMARACHI_PLATFORM_WINDOWS 0
#define ACAMARACHI_PLATFORM_WINRT 0
#define ACAMARACHI_PLATFORM_XBOXONE 0

// C11 thread_local, Because we are missing threads.h
#if __STDC_VERSION__ >= 201112L
#    define thread_local _Thread_local
#endif

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(__clang__)
// clang defines __GNUC__ or _MSC_VER
#    undef ACAMARACHI_COMPILER_CLANG
#    define ACAMARACHI_COMPILER_CLANG \
        (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#    if defined(__clang_analyzer__)
#        undef ACAMARACHI_COMPILER_CLANG_ANALYZER
#        define ACAMARACHI_COMPILER_CLANG_ANALYZER 1
#    endif    // defined(__clang_analyzer__)
#    if defined(_MSC_VER)
#        undef ACAMARACHI_COMPILER_MSVC
#        define ACAMARACHI_COMPILER_MSVC _MSC_VER
#        undef ACAMARACHI_COMPILER_CLANG_CL
#        define ACAMARACHI_COMPILER_CLANG_CL ACAMARACHI_COMPILER_CLANG
#    endif
#elif defined(_MSC_VER)
#    undef ACAMARACHI_COMPILER_MSVC
#    define ACAMARACHI_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#    undef ACAMARACHI_COMPILER_GCC
#    define ACAMARACHI_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#    error "ACAMARACHI_COMPILER_* is not defined!"
#endif    //

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
#    undef ACAMARACHI_CPU_ARM
#    define ACAMARACHI_CPU_ARM 1
#    define ACAMARACHI_CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__) || defined(__mips_isa_rev) || defined(__mips64)
#    undef ACAMARACHI_CPU_MIPS
#    define ACAMARACHI_CPU_MIPS 1
#    define ACAMARACHI_CACHE_LINE_SIZE 64
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
#    undef ACAMARACHI_CPU_PPC
#    define ACAMARACHI_CPU_PPC 1
#    define ACAMARACHI_CACHE_LINE_SIZE 128
#elif defined(__riscv) || defined(__riscv__) || defined(RISCVEL)
#    undef ACAMARACHI_CPU_RISCV
#    define ACAMARACHI_CPU_RISCV 1
#    define ACAMARACHI_CACHE_LINE_SIZE 64
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
#    undef ACAMARACHI_CPU_X86
#    define ACAMARACHI_CPU_X86 1
#    define ACAMARACHI_CACHE_LINE_SIZE 64
#else    // PNaCl doesn't have CPU defined.
#    undef ACAMARACHI_CPU_JIT
#    define ACAMARACHI_CPU_JIT 1
#    define ACAMARACHI_CACHE_LINE_SIZE 64
#endif    //

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__64BIT__) || \
    defined(__mips64) || defined(__powerpc64__) || defined(__ppc64__) || defined(__LP64__)
#    undef ACAMARACHI_ARCH_64BIT
#    define ACAMARACHI_ARCH_64BIT 64
#else
#    undef ACAMARACHI_ARCH_32BIT
#    define ACAMARACHI_ARCH_32BIT 32
#endif    //

#if ACAMARACHI_CPU_PPC
#    undef ACAMARACHI_CPU_ENDIAN_BIG
#    define ACAMARACHI_CPU_ENDIAN_BIG 1
#else
#    undef ACAMARACHI_CPU_ENDIAN_LITTLE
#    define ACAMARACHI_CPU_ENDIAN_LITTLE 1
#endif    // ACAMARACHI_PLATFORM_

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_DURANGO) || defined(_XBOX_ONE)
#    undef ACAMARACHI_PLATFORM_XBOXONE
#    define ACAMARACHI_PLATFORM_XBOXONE 1
#elif defined(__ANDROID__) || defined(ANDROID)
// Android compiler defines __linux__
#    include <sys/cdefs.h>    // Defines __BIONIC__ and includes android/api-level.h
#    undef ACAMARACHI_PLATFORM_ANDROID
#    define ACAMARACHI_PLATFORM_ANDROID __ANDROID_API__
#elif defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#    ifndef NOMINMAX
#        define NOMINMAX
#    endif    // NOMINMAX
//  If _USING_V110_SDK71_ is defined it means we are using the v110_xp or v120_xp toolset.
#    if defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
#        include <winapifamily.h>
#    endif    // defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
#    if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#        undef ACAMARACHI_PLATFORM_WINDOWS
#        if !defined(WINVER) && !defined(_WIN32_WINNT)
#            if ACAMARACHI_ARCH_64BIT
//				When building 64-bit target Win7 and above.
#                define WINVER 0x0601
#                define _WIN32_WINNT 0x0601
#            else
//				Windows Server 2003 with SP1, Windows XP with SP2 and above
#                define WINVER 0x0502
#                define _WIN32_WINNT 0x0502
#            endif    // ACAMARACHI_ARCH_64BIT
#        endif        // !defined(WINVER) && !defined(_WIN32_WINNT)
#        define ACAMARACHI_PLATFORM_WINDOWS _WIN32_WINNT
#    else
#        undef ACAMARACHI_PLATFORM_WINRT
#        define ACAMARACHI_PLATFORM_WINRT 1
#    endif
#elif defined(__VCCOREVER__) || defined(__RPI__)
// RaspberryPi compiler defines __linux__
#    undef ACAMARACHI_PLATFORM_RPI
#    define ACAMARACHI_PLATFORM_RPI 1
#elif defined(__linux__)
#    undef ACAMARACHI_PLATFORM_LINUX
#    define ACAMARACHI_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || \
    defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
#    undef ACAMARACHI_PLATFORM_IOS
#    define ACAMARACHI_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#    undef ACAMARACHI_PLATFORM_OSX
#    define ACAMARACHI_PLATFORM_OSX __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#elif defined(__EMSCRIPTEN__)
#    undef ACAMARACHI_PLATFORM_EMSCRIPTEN
#    define ACAMARACHI_PLATFORM_EMSCRIPTEN 1
#elif defined(__ORBIS__)
#    undef ACAMARACHI_PLATFORM_PS4
#    define ACAMARACHI_PLATFORM_PS4 1
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || \
    defined(__OpenBSD__) || defined(__DragonFly__)
#    undef ACAMARACHI_PLATFORM_BSD
#    define ACAMARACHI_PLATFORM_BSD 1
#elif defined(__GNU__)
#    undef ACAMARACHI_PLATFORM_HURD
#    define ACAMARACHI_PLATFORM_HURD 1
#elif defined(__NX__)
#    undef ACAMARACHI_PLATFORM_NX
#    define ACAMARACHI_PLATFORM_NX 1
#endif    //

#if !ACAMARACHI_CRT_NONE
// https://sourceforge.net/p/predef/wiki/Libraries/
#    if defined(__BIONIC__)
#        undef ACAMARACHI_CRT_BIONIC
#        define ACAMARACHI_CRT_BIONIC 1
#    elif defined(_MSC_VER)
#        undef ACAMARACHI_CRT_MSVC
#        define ACAMARACHI_CRT_MSVC 1
#    elif defined(__GLIBC__)
#        undef ACAMARACHI_CRT_GLIBC
#        define ACAMARACHI_CRT_GLIBC (__GLIBC__ * 10000 + __GLIBC_MINOR__ * 100)
#    elif defined(__MINGW32__) || defined(__MINGW64__)
#        undef ACAMARACHI_CRT_MINGW
#        define ACAMARACHI_CRT_MINGW 1
#    elif defined(__apple_build_version__) || defined(__ORBIS__) || defined(__EMSCRIPTEN__) || \
        defined(__llvm__)
#        undef ACAMARACHI_CRT_LIBCXX
#        define ACAMARACHI_CRT_LIBCXX 1
#    endif    //

#    if !ACAMARACHI_CRT_BIONIC && !ACAMARACHI_CRT_GLIBC && !ACAMARACHI_CRT_LIBCXX && !ACAMARACHI_CRT_MINGW && !ACAMARACHI_CRT_MSVC && \
        !ACAMARACHI_CRT_MUSL && !ACAMARACHI_CRT_NEWLIB
#        undef ACAMARACHI_CRT_NONE
#        define ACAMARACHI_CRT_NONE 1
#    endif    // ACAMARACHI_CRT_*
#endif        // !ACAMARACHI_CRT_NONE

#define ACAMARACHI_PLATFORM_POSIX                                                                         \
    (0 || ACAMARACHI_PLATFORM_ANDROID || ACAMARACHI_PLATFORM_BSD || ACAMARACHI_PLATFORM_EMSCRIPTEN || ACAMARACHI_PLATFORM_HURD || \
     ACAMARACHI_PLATFORM_IOS || ACAMARACHI_PLATFORM_LINUX || ACAMARACHI_PLATFORM_NX || ACAMARACHI_PLATFORM_OSX ||                 \
     ACAMARACHI_PLATFORM_PS4 || ACAMARACHI_PLATFORM_RPI)

#define ACAMARACHI_PLATFORM_NONE                                                                           \
    !(0 || ACAMARACHI_PLATFORM_ANDROID || ACAMARACHI_PLATFORM_BSD || ACAMARACHI_PLATFORM_EMSCRIPTEN || ACAMARACHI_PLATFORM_HURD || \
      ACAMARACHI_PLATFORM_IOS || ACAMARACHI_PLATFORM_LINUX || ACAMARACHI_PLATFORM_NX || ACAMARACHI_PLATFORM_OSX ||                 \
      ACAMARACHI_PLATFORM_PS4 || ACAMARACHI_PLATFORM_RPI || ACAMARACHI_PLATFORM_WINDOWS ||        \
      ACAMARACHI_PLATFORM_WINRT || ACAMARACHI_PLATFORM_XBOXONE)

#if ACAMARACHI_COMPILER_GCC
#    define ACAMARACHI_COMPILER_NAME                                                             \
        "GCC " ACAMARACHI_stringize(__GNUC__) "." ACAMARACHI_stringize(__GNUC_MINOR__) "." ACAMARACHI_stringize( \
            __GNUC_PATCHLEVEL__)
#elif ACAMARACHI_COMPILER_CLANG
#    define ACAMARACHI_COMPILER_NAME                                                                       \
        "Clang " ACAMARACHI_stringize(__clang_major__) "." ACAMARACHI_stringize(__clang_minor__) "." ACAMARACHI_stringize( \
            __clang_patchlevel__)
#elif ACAMARACHI_COMPILER_MSVC
#    if ACAMARACHI_COMPILER_MSVC >= 1920    // Visual Studio 2019
#        define ACAMARACHI_COMPILER_NAME "MSVC 16.0"
#    elif ACAMARACHI_COMPILER_MSVC >= 1910    // Visual Studio 2017
#        define ACAMARACHI_COMPILER_NAME "MSVC 15.0"
#    elif ACAMARACHI_COMPILER_MSVC >= 1900    // Visual Studio 2015
#        define ACAMARACHI_COMPILER_NAME "MSVC 14.0"
#    elif ACAMARACHI_COMPILER_MSVC >= 1800    // Visual Studio 2013
#        define ACAMARACHI_COMPILER_NAME "MSVC 12.0"
#    elif ACAMARACHI_COMPILER_MSVC >= 1700    // Visual Studio 2012
#        define ACAMARACHI_COMPILER_NAME "MSVC 11.0"
#    elif ACAMARACHI_COMPILER_MSVC >= 1600    // Visual Studio 2010
#        define ACAMARACHI_COMPILER_NAME "MSVC 10.0"
#    elif ACAMARACHI_COMPILER_MSVC >= 1500    // Visual Studio 2008
#        define ACAMARACHI_COMPILER_NAME "MSVC 9.0"
#    else
#        define ACAMARACHI_COMPILER_NAME "MSVC"
#    endif    //
#endif        // ACAMARACHI_COMPILER_

#if ACAMARACHI_PLATFORM_ANDROID
#    define ACAMARACHI_PLATFORM_NAME "Android " ACAMARACHI_stringize(ACAMARACHI_PLATFORM_ANDROID)
#elif ACAMARACHI_PLATFORM_BSD
#    define ACAMARACHI_PLATFORM_NAME "BSD"
#elif ACAMARACHI_PLATFORM_EMSCRIPTEN
#    define ACAMARACHI_PLATFORM_NAME                                           \
        "asm.js " ACAMARACHI_stringize(__EMSCRIPTEN_major__) "." ACAMARACHI_stringize( \
            __EMSCRIPTEN_minor__) "." ACAMARACHI_stringize(__EMSCRIPTEN_tiny__)
#elif ACAMARACHI_PLATFORM_HURD
#    define ACAMARACHI_PLATFORM_NAME "Hurd"
#elif ACAMARACHI_PLATFORM_IOS
#    define ACAMARACHI_PLATFORM_NAME "iOS"
#elif ACAMARACHI_PLATFORM_LINUX
#    define ACAMARACHI_PLATFORM_NAME "Linux"
#elif ACAMARACHI_PLATFORM_NONE
#    define ACAMARACHI_PLATFORM_NAME "None"
#elif ACAMARACHI_PLATFORM_NX
#    define ACAMARACHI_PLATFORM_NAME "NX"
#elif ACAMARACHI_PLATFORM_OSX
#    define ACAMARACHI_PLATFORM_NAME "OSX"
#elif ACAMARACHI_PLATFORM_PS4
#    define ACAMARACHI_PLATFORM_NAME "PlayStation 4"
#elif ACAMARACHI_PLATFORM_RPI
#    define ACAMARACHI_PLATFORM_NAME "RaspberryPi"
#elif ACAMARACHI_PLATFORM_WINDOWS
#    define ACAMARACHI_PLATFORM_NAME "Windows"
#elif ACAMARACHI_PLATFORM_WINRT
#    define ACAMARACHI_PLATFORM_NAME "WinRT"
#elif ACAMARACHI_PLATFORM_XBOXONE
#    define ACAMARACHI_PLATFORM_NAME "Xbox One"
#else
#    error "Unknown ACAMARACHI_PLATFORM!"
#endif    // ACAMARACHI_PLATFORM_

#define ACAMARACHI_PLATFORM_APPLE (0 || ACAMARACHI_PLATFORM_IOS || ACAMARACHI_PLATFORM_OSX)

#if ACAMARACHI_CPU_ARM
#    define ACAMARACHI_CPU_NAME "ARM"
#elif ACAMARACHI_CPU_JIT
#    define ACAMARACHI_CPU_NAME "JIT-VM"
#elif ACAMARACHI_CPU_MIPS
#    define ACAMARACHI_CPU_NAME "MIPS"
#elif ACAMARACHI_CPU_PPC
#    define ACAMARACHI_CPU_NAME "PowerPC"
#elif ACAMARACHI_CPU_RISCV
#    define ACAMARACHI_CPU_NAME "RISC-V"
#elif ACAMARACHI_CPU_X86
#    define ACAMARACHI_CPU_NAME "x86"
#endif    // ACAMARACHI_CPU_

#if ACAMARACHI_CRT_BIONIC
#    define ACAMARACHI_CRT_NAME "Bionic libc"
#elif ACAMARACHI_CRT_GLIBC
#    define ACAMARACHI_CRT_NAME "GNU C Library"
#elif ACAMARACHI_CRT_MSVC
#    define ACAMARACHI_CRT_NAME "MSVC C Runtime"
#elif ACAMARACHI_CRT_MINGW
#    define ACAMARACHI_CRT_NAME "MinGW C Runtime"
#elif ACAMARACHI_CRT_LIBCXX
#    define ACAMARACHI_CRT_NAME "Clang C Library"
#elif ACAMARACHI_CRT_NEWLIB
#    define ACAMARACHI_CRT_NAME "Newlib"
#elif ACAMARACHI_CRT_MUSL
#    define ACAMARACHI_CRT_NAME "musl libc"
#elif ACAMARACHI_CRT_NONE
#    define ACAMARACHI_CRT_NAME "None"
#else
#    error "Unknown ACAMARACHI_CRT!"
#endif    // ACAMARACHI_CRT_

#if ACAMARACHI_ARCH_32BIT
#    define ACAMARACHI_ARCH_NAME "32-bit"
#elif ACAMARACHI_ARCH_64BIT
#    define ACAMARACHI_ARCH_NAME "64-bit"
#endif    // ACAMARACHI_ARCH_


#define ACAMARACHI_PLATFORM_MOBILE (ACAMARACHI_PLATFORM_ANDROID || ACAMARACHI_PLATFORM_IOS)
#define ACAMARACHI_PLATFORM_PC (ACAMARACHI_PLATFORM_WINDOWS || ACAMARACHI_PLATFORM_LINUX || ACAMARACHI_PLATFORM_OSX)