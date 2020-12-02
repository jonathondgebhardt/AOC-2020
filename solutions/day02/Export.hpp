#pragma once

// clang-format off
#if defined(_MSC_VER)
    //  Microsoft
    #define DAY02_EXPORT __declspec(dllexport)
    #define DAY02_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define DAY02_EXPORT __attribute__((visibility("default")))
    #define DAY02_IMPORT
#else
    //  do nothing and hope for the best?
    #define DAY02_EXPORT
    #define DAY02_IMPORT
    #pragma warning Unknown dynamic link import / export semantics.
#endif
