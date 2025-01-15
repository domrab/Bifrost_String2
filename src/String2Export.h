#ifndef STRING2_EXPORT_H
#define STRING2_EXPORT_H

#if defined(_WIN32)
#define STRING2_EXPORT __declspec(dllexport)
#define STRING2_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define STRING2_EXPORT __attribute__((visibility("default")))
#define STRING2_IMPORT __attribute__((visibility("default")))
#else
#error Unsupported platform.
#endif

#if defined(STRING2_BUILD_NODEDEF_DLL)
#define STRING2_DECL STRING2_EXPORT
#else
#define STRING2_DECL STRING2_IMPORT
#endif

#endif
