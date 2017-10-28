/* Generated from config.h.in during build configuration using CMake. */

// Note: This header file is only used internally. It is not part of public
// interface!

// ---------------------------------------------------------------------------
// System checks

// Define if you build this library for a MS Windows OS.
#define OS_WINDOWS 1

// Define if you have the <stdint.h> header file.
#define HAVE_STDINT_H 1

// Define if you have the <sys/types.h> header file.
// #define HAVE_SYS_TYPES_H 1

// Define if you have the <inttypes.h> header file.
// #define HAVE_INTTYPES_H 1

// Define if you have the <sys/stat.h> header file.
#define HAVE_SYS_STAT_H 1

// Define if you have the <unistd.h> header file.
// #define HAVE_UNISTD_H 1

// Define if you have the <fnmatch.h> header file.
// #define HAVE_FNMATCH_H 1

// Define if you have the <shlwapi.h> header file (Windows 2000/XP).
// #define HAVE_SHLWAPI_H 1

// Define if you have the strtoll function.
#define HAVE_STRTOLL 1

// Define if you have the strtoq function.
#define HAVE_STRTOQ 1

// Define if you have the <pthread.h> header file.
// #define HAVE_PTHREAD 1

// Define if your pthread library defines the type pthread_rwlock_t
// #define HAVE_RWLOCK 1

// gcc requires this to get PRId64, etc.
#if defined(HAVE_INTTYPES_H) && !defined(__STDC_FORMAT_MACROS)
#define __STDC_FORMAT_MACROS 1
#endif

// ---------------------------------------------------------------------------
// Package information

// Name of package.
#define PACKAGE "gflags"

// Define to the full name of this package.
#define PACKAGE_NAME "gflags"

// Define to the full name and version of this package.
#define PACKAGE_STRING "gflags 2.1.2"

// Define to the one symbol short name of this package.
#define PACKAGE_TARNAME "gflags-2.1.2"

// Define to the version of this package.
#define PACKAGE_VERSION "2.1.2"

// Version number of package.
#define VERSION PACKAGE_VERSION

// Define to the address where bug reports for this package should be sent.
#define PACKAGE_BUGREPORT "https://github.com/schuhschuh/gflags/issues"

// ---------------------------------------------------------------------------
// Path separator
#ifndef PATH_SEPARATOR
#ifdef OS_WINDOWS
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif
#endif

// ---------------------------------------------------------------------------
// Windows

// Always export symbols when compiling a shared library as this file is only
// included by internal modules when building the gflags library itself.
// The gflags_declare.h header file will set it to import these symbols
// otherwise.
#ifndef GFLAGS_DLL_DECL
#define GFLAGS_DLL_DECL
#endif
// Flags defined by the gflags library itself must be exported
#ifndef GFLAGS_DLL_DEFINE_FLAG
#define GFLAGS_DLL_DEFINE_FLAG
#endif

#ifdef OS_WINDOWS
#include "windows_port.h"
#endif
